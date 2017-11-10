// An experimental libobs wrapper for the Node.Js toolset.
// Copyright(C) 2017 General Workings Inc. (Streamlabs)
// 
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301, USA.

#include "OBS_API.h"
#include "util/platform.h"
#include "util/lexer.h"

#ifdef _WIN32
#define _WIN32_WINNT 0x0502

#include "OBS_content.h"
#include <mutex>
#include <fstream>
#include <codecvt>
#include <string>
#include <windows.h>
#include <ShlObj.h>
#endif

#ifdef _MSC_VER
#include <direct.h>
#define getcwd _getcwd
#endif

std::string g_applicationDataPath;
std::string g_configurationPath;
vector<pair<obs_module_t *, int>> g_pluginList;
os_cpu_usage_info_t *g_cpuUsageInfo = nullptr;
bool g_obsStudioIsInstalled;
std::fstream g_logStream;

std::string g_obsStudioPath;
std::string g_obsStudioCurrentProfile;
std::string g_obsStudioCurrentCollection;

bool useOBS_configFiles = false;
uint64_t lastBytesSent = 0;
uint64_t lastBytesSentTime = 0;

#pragma region Utility

static string GenerateTimeDateFilename(const char *extension) {
	time_t    now = time(0);
	char      file[256] = {};
	struct tm *cur_time;

	cur_time = localtime(&now);
	snprintf(file, sizeof(file), "%d-%02d-%02d %02d-%02d-%02d.%s",
		cur_time->tm_year + 1900,
		cur_time->tm_mon + 1,
		cur_time->tm_mday,
		cur_time->tm_hour,
		cur_time->tm_min,
		cur_time->tm_sec,
		extension);

	return string(file);
}

static void stdout_log_handler(int log_level, const char *format,
	va_list args, void *param) {
	char out[4096];
	vsnprintf(out, sizeof(out), format, args);

	switch (log_level) {
		case LOG_DEBUG:
			fprintf(stdout, "debug: %s\n", out);
			fflush(stdout);
			break;

		case LOG_INFO:
			fprintf(stdout, "info: %s\n", out);
			fflush(stdout);
			break;

		case LOG_WARNING:
			fprintf(stdout, "warning: %s\n", out);
			fflush(stdout);
			break;

		case LOG_ERROR:
			fprintf(stderr, "error: %s\n", out);
			fflush(stderr);
	}

	UNUSED_PARAMETER(param);
}

void node_obs_log
(int log_level, const char *msg,
	va_list args, void *param) {
	fstream &logFile = *static_cast<fstream*>(param);
	char str[4096];

	va_list args2;
	va_copy(args2, args);

	stdout_log_handler(log_level, msg, args, nullptr);
	vsnprintf(str, 4095, msg, args2);

	#ifdef _WIN32
	if (IsDebuggerPresent()) {
		int wNum = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		if (wNum > 1) {
			static wstring wide_buf;
			static mutex wide_mutex;

			lock_guard<mutex> lock(wide_mutex);
			wide_buf.reserve(wNum + 1);
			wide_buf.resize(wNum - 1);
			MultiByteToWideChar(CP_UTF8, 0, str, -1, &wide_buf[0],
				wNum);
			wide_buf.push_back('\n');

			OutputDebugStringW(wide_buf.c_str());
		}
	}
	#endif

	char *tmp_str = str;
	char *nextLine = tmp_str;

	while (*nextLine) {
		char *nextLine = strchr(tmp_str, '\n');
		if (!nextLine)
			break;

		if (nextLine != tmp_str && nextLine[-1] == '\r') {
			nextLine[-1] = 0;
		} else {
			nextLine[0] = 0;
		}

		logFile << tmp_str << endl;
		nextLine++;
		tmp_str = nextLine;
	}

	logFile << tmp_str << endl;

	#if defined(_WIN32) && defined(OBS_DEBUGBREAK_ON_ERROR)
	if (log_level <= LOG_ERROR && IsDebuggerPresent())
		__debugbreak();
	#endif
}

static bool get_token(lexer *lex, string &str, base_token_type type) {
	base_token token;
	if (!lexer_getbasetoken(lex, &token, IGNORE_WHITESPACE))
		return false;
	if (token.type != type)
		return false;

	str.assign(token.text.array, token.text.len);
	return true;
}

static bool expect_token(lexer *lex, const char *str, base_token_type type) {
	base_token token;
	if (!lexer_getbasetoken(lex, &token, IGNORE_WHITESPACE))
		return false;
	if (token.type != type)
		return false;

	return strref_cmp(&token.text, str) == 0;
}

/* os_dirent mimics POSIX dirent structure.
 * Perhaps a better cross-platform solution can take
 * place but this is as cross-platform as it gets
 * for right now.  */
static uint64_t convert_log_name(const char *name) {
	lexer  lex;
	string     year, month, day, hour, minute, second;

	lexer_init(&lex);
	lexer_start(&lex, name);

	if (!get_token(&lex, year, BASETOKEN_DIGIT)) return 0;
	if (!expect_token(&lex, "-", BASETOKEN_OTHER)) return 0;
	if (!get_token(&lex, month, BASETOKEN_DIGIT)) return 0;
	if (!expect_token(&lex, "-", BASETOKEN_OTHER)) return 0;
	if (!get_token(&lex, day, BASETOKEN_DIGIT)) return 0;
	if (!get_token(&lex, hour, BASETOKEN_DIGIT)) return 0;
	if (!expect_token(&lex, "-", BASETOKEN_OTHER)) return 0;
	if (!get_token(&lex, minute, BASETOKEN_DIGIT)) return 0;
	if (!expect_token(&lex, "-", BASETOKEN_OTHER)) return 0;
	if (!get_token(&lex, second, BASETOKEN_DIGIT)) return 0;

	std::string timestring(year);
	timestring += month + day + hour + minute + second;
	lexer_free(&lex);
	return std::stoull(timestring);
}

static void delete_oldest_file(const char *location, unsigned maxLogs) {
	string           oldestLog;
	uint64_t         oldest_ts = (uint64_t)-1;
	struct os_dirent *entry;

	os_dir_t *dir = os_opendir(location);

	if (!dir) {
		std::cout << "Failed to open log directory." << std::endl;
	}

	unsigned count = 0;

	while ((entry = os_readdir(dir)) != NULL) {
		if (entry->directory || *entry->d_name == '.')
			continue;

		uint64_t ts = convert_log_name(entry->d_name);

		if (ts) {
			if (ts < oldest_ts) {
				oldestLog = entry->d_name;
				oldest_ts = ts;
			}

			count++;
		}
	}

	os_closedir(dir);

	if (count > maxLogs) {
		string delPath;

		delPath = delPath + location + "/" + oldestLog;
		os_unlink(delPath.c_str());
	}
}
#pragma endregion Utility

void OBS_API::Initialize(v8Arguments args) {
	MAKE_ISOLATE(isolate);

	// Test Argument length and type.
	if ((args.Length() >= 1) && args[0]->IsString()) {
		g_applicationDataPath = g_configurationPath = std::string(*String::Utf8Value(args[0]));
		g_applicationDataPath += "/node-obs/";
	} else {
		char *tmp;
		g_applicationDataPath = tmp = os_get_config_path_ptr("node-obs/");
		bfree(tmp);
	}

	// Initialize libOBS
	std::string t_nodeObsData = g_configurationPath + "/plugin_config/";
	obs_startup("en-US", t_nodeObsData.data(), NULL);

	// Track CPU Usage
	g_cpuUsageInfo = os_cpu_usage_info_start();

	// Check if OBS is installed
	std::vector<char> path(32767);
	int pathLen = os_get_config_path(path.data(), path.size(), "obs-studio");
	if (pathLen > 0) {
		g_obsStudioPath = path.data();
		std::string profiles = g_obsStudioPath + "/basic/profiles";
		std::string scenes = g_obsStudioPath + "/basic/scenes";
		g_obsStudioIsInstalled = os_file_exists(g_obsStudioPath.c_str())
			&& os_file_exists(profiles.c_str())
			&& os_file_exists(scenes.c_str());
		if (g_obsStudioIsInstalled) {
			g_obsStudioCurrentProfile = GetOBSStudioProfilesRaw().at(0);
			g_obsStudioCurrentCollection = GetOBSStudioSceneCollectionsRaw().at(0);
		}
	}

	// Logging
	std::string logFileName = GenerateTimeDateFilename("txt");
	std::string logPath = g_applicationDataPath + "/logs/";
	if (os_mkdirs(logPath.c_str()) == MKDIR_ERROR) {
		std::cerr << "Unable to create directory for log files." << std::endl;
	} else {
		delete_oldest_file(logPath.c_str(), 3);
		std::string logFull = logPath + logFileName;
		g_logStream = std::fstream(logFull, ios_base::out | ios_base::trunc);
		if (g_logStream.bad()) {
			std::cerr << "Unable to create log file." << std::endl;
		} else {
			base_set_log_handler(node_obs_log, &g_logStream);
		}
	}

	args.GetReturnValue().Set(obs_initialized());
}

void OBS_API::Finalize(v8Arguments args) {
	if (obs_initialized()) {
		if (g_cpuUsageInfo) {
			os_cpu_usage_info_destroy(g_cpuUsageInfo);
			g_cpuUsageInfo = nullptr;
		}
		obs_shutdown();
	}
	args.GetReturnValue().Set(!obs_initialized());
}

void OBS_API::LoadPlugins(v8Arguments args) {
	OBS_service::resetVideoContext();

	// Retrieve current directory.
	// TODO: Replace with proper initialization function so that CWD changes
	//  do not mess us up.
	std::string currentDirectory;
	{
		std::vector<char> pathCWD(257); // Should use MAX_PATH here
		char *answer = getcwd(pathCWD.data(), pathCWD.size() - 1);
		currentDirectory = std::string(pathCWD.data());
		replaceAll(currentDirectory, "\\", "/");
	}

	// Set up several directories used.
	std::string pathOBS = currentDirectory + "/node-obs";
	std::string pathOBSPlugins = pathOBS + "/obs-plugins";
	std::string pathOBSPluginData = pathOBS + "/data/obs-plugins";

	// Switch working directory to where node-obs is loaded from.
	_chdir(pathOBS.c_str());
	#ifdef _WIN32
	SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_USER_DIRS | LOAD_LIBRARY_SEARCH_SYSTEM32);
	SetDllDirectory(NULL);
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(pathOBS);
		AddDllDirectory(wide.c_str());
	}
	#endif

	if (!os_file_exists(pathOBSPlugins.c_str())) {
		args.GetReturnValue().Set(false);
		return;
	}

	os_dir_t* pluginDir = os_opendir(pathOBSPlugins.c_str());
	if (!pluginDir) {
		args.GetReturnValue().Set(false);
		return;
	}

	for (os_dirent* ent = os_readdir(pluginDir);
		ent != nullptr;
		ent = os_readdir(pluginDir)) {
		if (!ent->directory) { // Only list actual files
			std::string pathFile = ent->d_name;
			std::string pathFileName = pathFile.substr(0, pathFile.find_last_of('.'));
			std::string pathPlugin = pathOBSPlugins + "/" + pathFile;
			std::string pathPluginData = pathOBSPluginData + "/" + pathFileName;

			#ifdef _WIN32
			// Only try to load .dll files
			istring tempFile = pathFile.c_str();
			if (tempFile.length() >= 4) {
				if (tempFile.substr(tempFile.length() - 4, 4).compare(".dll") != 0) {
					continue;
				}
			} else { // Don't bother with files that have no name
				continue;
			}
			#else

			#endif

			obs_module_t *currentModule;
			int result = obs_open_module(&currentModule, pathPlugin.c_str(), pathPluginData.c_str());
			switch (result) {
				case MODULE_SUCCESS:
					g_pluginList.push_back(make_pair(currentModule, result));
					break;
				case MODULE_FILE_NOT_FOUND:
					std::cerr << "Unable to load '" << pathPlugin << "', could not find file." << std::endl;
					break;
				case MODULE_MISSING_EXPORTS:
					std::cerr << "Unable to load '" << pathPlugin << "', missing exports." << std::endl;
					break;
				case MODULE_INCOMPATIBLE_VER:
					std::cerr << "Unable to load '" << pathPlugin << "', incompatible version." << std::endl;
					break;
				case MODULE_ERROR:
					std::cerr << "Unable to load '" << pathPlugin << "', generic error." << std::endl;
					break;
			}
		}
	}
	os_closedir(pluginDir);

	// Restore old working directory.
	_chdir(currentDirectory.c_str());

	args.GetReturnValue().Set(true);
}

void OBS_API::IntializePlugins(v8Arguments args) {
	int error = 0;
	for (int i = 0; i < g_pluginList.size(); i++) {
		if (g_pluginList.at(i).second == MODULE_SUCCESS) {
			if (!obs_init_module(g_pluginList.at(i).first)) {
				error--;
			}
		}
	}
}

void OBS_API::GetPerformanceStatistics(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	Local<Object> statistics = Object::New(isolate);
	statistics->Set(v8::String::NewFromUtf8(isolate, "CPU"),
		Number::New(isolate, getCPU_Percentage()));
	statistics->Set(v8::String::NewFromUtf8(isolate, "numberDroppedFrames"),
		Number::New(isolate, getNumberOfDroppedFrames()));
	statistics->Set(v8::String::NewFromUtf8(isolate, "percentageDroppedFrames"),
		Number::New(isolate, getDroppedFramesPercentage()));
	statistics->Set(v8::String::NewFromUtf8(isolate, "bandwidth"),
		Number::New(isolate, getCurrentBandwidth()));
	statistics->Set(v8::String::NewFromUtf8(isolate, "frameRate"),
		Number::New(isolate, getCurrentFrameRate()));
	args.GetReturnValue().Set(statistics);
}

void OBS_API::GetConfigurationDirectory(v8Arguments args) {
	args.GetReturnValue().Set(v8::String::NewFromUtf8(args.GetIsolate(),
		g_configurationPath.c_str()));
}

void OBS_API::SetConfigurationDirectory(v8Arguments args) {
	auto s = args[0]->ToString();

	if (s->Utf8Length() == 0) {
		args.GetReturnValue().Set(false);
		return;
	}

	if (useOBS_configFiles) {
		args.GetReturnValue().Set(false);
		return;
	}

	g_configurationPath = std::string(*v8::String::Utf8Value(s));
	args.GetReturnValue().Set(true);
}

void OBS_API::IsOBSStudioInstalled(v8Arguments args) {
	MAKE_ISOLATE(isolate);

	args.GetReturnValue().Set(g_obsStudioIsInstalled);
}

std::vector<std::string> OBS_API::GetOBSStudioProfilesRaw() {
	std::string pathProfiles = g_obsStudioPath + "/basic/profiles/";
	os_dir_t* profileDir = os_opendir(pathProfiles.c_str());
	if (!profileDir)
		return std::vector<std::string>();

	std::vector<std::string> profiles;
	for (os_dirent* ent = os_readdir(profileDir);
		ent != nullptr;
		ent = os_readdir(profileDir)) {
		if (ent->directory) {
			profiles.emplace_back(ent->d_name);
		}
	}

	return profiles;
}

void OBS_API::GetOBSStudioProfiles(v8Arguments args) {
	MAKE_ISOLATE(isolate);
	v8::Local<Array> profiles = Array::New(isolate);

	size_t index = 0;
	for (std::string s : GetOBSStudioProfilesRaw()) {
		profiles->Set(index, v8::String::NewFromUtf8(isolate, s.c_str()));
		index++;
	}

	args.GetReturnValue().Set(profiles);
}

std::vector<std::string> OBS_API::GetOBSStudioSceneCollectionsRaw() {
	std::string pathProfiles = g_obsStudioPath + "/basic/scenes/";
	os_dir_t* profileDir = os_opendir(pathProfiles.c_str());
	if (!profileDir)
		return std::vector<std::string>();

	std::vector<std::string> collections;
	for (os_dirent* ent = os_readdir(profileDir);
		ent != nullptr;
		ent = os_readdir(profileDir)) {
		size_t endpoint = (strlen(ent->d_name) - 5);
		if (!ent->directory
			&& (strcmp(ent->d_name + endpoint, ".json") == 0)) {
			collections.emplace_back(ent->d_name);
		}
	}

	return collections;
}

void OBS_API::GetOBSStudioSceneCollections(v8Arguments args) {
	MAKE_ISOLATE(isolate);
	v8::Local<Array> collections = Array::New(isolate);

	size_t index = 0;
	for (std::string s : GetOBSStudioSceneCollectionsRaw()) {
		collections->Set(index, v8::String::NewFromUtf8(isolate, s.c_str()));
		index++;
	}

	args.GetReturnValue().Set(collections);
}

void OBS_API::OBS_API_getOBS_currentProfile(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, getOBS_currentProfile().c_str()));
}

void OBS_API::OBS_API_setOBS_currentProfile(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	v8::String::Utf8Value param1(args[0]->ToString());
	std::string currentProfile = std::string(*param1);

	setOBS_currentProfile(currentProfile);
}

void OBS_API::OBS_API_getOBS_currentSceneCollection(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, getOBS_currentSceneCollection().c_str()));
}

void OBS_API::OBS_API_setOBS_currentSceneCollection(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	v8::String::Utf8Value param1(args[0]->ToString());
	std::string currentSceneCollection = std::string(*param1);

	setOBS_currentSceneCollection(currentSceneCollection);
}

int GetConfigPath(char *path, size_t size, const char *name) {
	return os_get_config_path(path, size, name);
}

bool dirExists(const std::string& path) {
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

bool containsDirectory(const std::string& path) {
	const char* pszDir = path.c_str();
	char szBuffer[MAX_PATH];

	DWORD dwRet = GetCurrentDirectory(MAX_PATH, szBuffer);
	SetCurrentDirectory(pszDir);

	WIN32_FIND_DATA fd;

	HANDLE hFind = ::FindFirstFile("*.", &fd);

	// Get all sub-folders:

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			char* pszName = fd.cFileName;
			if (_stricmp(pszName, ".") != 0 && _stricmp(pszName, "..") != 0) {
				//Only look for at least one directory
				::FindClose(hFind);
				SetCurrentDirectory(szBuffer);
				return true;
			}

		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	// Set the current folder back to what it was:
	SetCurrentDirectory(szBuffer);
	return false;
}


static void SaveProfilerData(const profiler_snapshot_t *snap) {
	string dst(g_applicationDataPath);
	dst.append("profiler_data/");

	if (os_mkdirs(dst.c_str()) == MKDIR_ERROR) {
		cerr << "Failed to open profiler snapshot for writing" << endl;
	}

	dst.append(GenerateTimeDateFilename("csv.gz"));

	if (!profiler_snapshot_dump_csv_gz(snap, dst.c_str()))
		blog(LOG_WARNING, "Could not save profiler data to '%s'",
			dst.c_str());
}

double OBS_API::getCPU_Percentage(void) {
	double cpuPercentage = os_cpu_usage_info_query(g_cpuUsageInfo);

	cpuPercentage *= 10;
	cpuPercentage = trunc(cpuPercentage);
	cpuPercentage /= 10;

	return cpuPercentage;
}

int OBS_API::getNumberOfDroppedFrames(void) {
	obs_output_t* streamOutput = OBS_service::getStreamingOutput();

	int totalDropped = 0;

	if (obs_output_active(streamOutput)) {
		totalDropped = obs_output_get_frames_dropped(streamOutput);
	}

	return totalDropped;
}

double OBS_API::getDroppedFramesPercentage(void) {
	obs_output_t* streamOutput = OBS_service::getStreamingOutput();

	double percent = 0;

	if (obs_output_active(streamOutput)) {
		int totalDropped = obs_output_get_frames_dropped(streamOutput);
		int totalFrames = obs_output_get_total_frames(streamOutput);
		percent = (double)totalDropped / (double)totalFrames * 100.0;
	}

	return percent;
}

double OBS_API::getCurrentBandwidth(void) {
	obs_output_t* streamOutput = OBS_service::getStreamingOutput();

	double kbitsPerSec = 0;

	if (obs_output_active(streamOutput)) {
		uint64_t bytesSent = obs_output_get_total_bytes(streamOutput);
		uint64_t bytesSentTime = os_gettime_ns();

		if (bytesSent < lastBytesSent)
			bytesSent = 0;
		if (bytesSent == 0)
			lastBytesSent = 0;

		uint64_t bitsBetween = (bytesSent - lastBytesSent) * 8;

		double timePassed = double(bytesSentTime - lastBytesSentTime) /
			1000000000.0;

		kbitsPerSec = double(bitsBetween) / timePassed / 1000.0;

		lastBytesSent = bytesSent;
		lastBytesSentTime = bytesSentTime;
	}

	return kbitsPerSec;
}

double OBS_API::getCurrentFrameRate(void) {
	return obs_get_active_fps();
}

std::string OBS_API::getOBS_currentProfile(void) {
	return g_obsStudioCurrentProfile;
}

void OBS_API::setOBS_currentProfile(std::string profileName) {
	g_obsStudioCurrentProfile = profileName;
}

std::string OBS_API::getOBS_currentSceneCollection(void) {
	return g_obsStudioCurrentCollection;
}

void OBS_API::setOBS_currentSceneCollection(std::string sceneCollectionName) {
	g_obsStudioCurrentCollection = sceneCollectionName;
}

bool OBS_API::isOBS_configFilesUsed(void) {
	return useOBS_configFiles;
}

static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor,
	HDC      hdcMonitor,
	LPRECT   lprcMonitor,
	LPARAM   dwData) {
	MONITORINFO info;
	info.cbSize = sizeof(info);
	if (GetMonitorInfo(hMonitor, &info)) {
		std::vector<Screen>* resolutions = reinterpret_cast<std::vector<Screen>*>(dwData);

		Screen screen;

		screen.width = std::abs(info.rcMonitor.left - info.rcMonitor.right);
		screen.height = std::abs(info.rcMonitor.top - info.rcMonitor.bottom);

		resolutions->push_back(screen);
	}
	return true;
}

std::vector<Screen> OBS_API::availableResolutions(void) {
	std::vector<Screen> resolutions;
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(&resolutions));

	return resolutions;
}

std::string OBS_API::getGlobalConfigPath(void) {
	std::string globalConfigPath;

	globalConfigPath += g_configurationPath;
	globalConfigPath += "\\global.ini";

	return globalConfigPath;
}

std::string OBS_API::getBasicConfigPath(void) {
	std::string basicConfigPath;

	basicConfigPath += g_configurationPath;

	if (useOBS_configFiles && !g_obsStudioCurrentProfile.empty()) {
		basicConfigPath += "\\basic\\profiles\\";
		basicConfigPath += g_obsStudioCurrentProfile;
	}

	basicConfigPath += "\\basic.ini";

	return basicConfigPath;
}

std::string OBS_API::getServiceConfigPath(void) {
	std::string serviceConfigPath;

	serviceConfigPath += g_configurationPath;

	if (useOBS_configFiles && !g_obsStudioCurrentProfile.empty()) {
		serviceConfigPath += "\\basic\\profiles\\";
		serviceConfigPath += g_obsStudioCurrentProfile;
	}

	serviceConfigPath += "\\service.json";

	return serviceConfigPath;
}

std::string OBS_API::getContentConfigPath(void) {
	std::string contentConfigPath;

	contentConfigPath += g_configurationPath;

	if (useOBS_configFiles && !g_obsStudioCurrentCollection.empty()) {
		contentConfigPath += "\\basic\\scenes\\";
		contentConfigPath += g_obsStudioCurrentCollection;;
		contentConfigPath += ".json";
	} else {
		contentConfigPath += "\\config.json";
	}

	return contentConfigPath;
}

static inline string GetDefaultVideoSavePath() {
	wchar_t path_utf16[MAX_PATH];
	char    path_utf8[MAX_PATH] = {};

	SHGetFolderPathW(NULL, CSIDL_MYVIDEO, NULL, SHGFP_TYPE_CURRENT,
		path_utf16);

	os_wcs_to_utf8(path_utf16, wcslen(path_utf16), path_utf8, MAX_PATH);
	return string(path_utf8);
}

config_t* OBS_API::openConfigFile(std::string configFile) {
	config_t* config;

	int result = config_open(&config, configFile.c_str(), CONFIG_OPEN_EXISTING);

	if (result != CONFIG_SUCCESS) {
		config = config_create(configFile.c_str());
		config_open(&config, configFile.c_str(), CONFIG_OPEN_EXISTING);
		std::string basic = "basic.ini";
		std::string subString = configFile.substr(configFile.size() - basic.size(), basic.size()).c_str();

		if (subString.compare(basic) == 0) {
			config_set_string(config, "Output", "Mode", "Simple");
			config_set_string(config, "SimpleOutput", "FilePath", GetDefaultVideoSavePath().c_str());
			config_set_string(config, "SimpleOutput", "RecFormat", "flv");
			config_set_uint(config, "SimpleOutput", "VBitrate", 2500);
			config_set_string(config, "SimpleOutput", "StreamEncoder", SIMPLE_ENCODER_X264);
			config_set_uint(config, "SimpleOutput", "ABitrate", 160);
			config_set_bool(config, "SimpleOutput", "UseAdvanced", false);
			config_set_bool(config, "SimpleOutput", "EnforceBitrate", true);
			config_set_string(config, "SimpleOutput", "Preset", "veryfast");
			config_set_string(config, "SimpleOutput", "RecQuality", "Stream");
			config_set_string(config, "SimpleOutput", "RecEncoder", SIMPLE_ENCODER_X264);
			config_set_bool(config, "SimpleOutput", "RecRB", false);
			config_set_int(config, "SimpleOutput", "RecRBTime", 20);
			config_set_int(config, "SimpleOutput", "RecRBSize", 512);
			config_set_string(config, "SimpleOutput", "RecRBPrefix", "Replay");

			config_save_safe(config, "tmp", nullptr);
		}
	}

	return config;
}

bool OBS_API::isOBS_installed(void) {
	return g_obsStudioIsInstalled;
}