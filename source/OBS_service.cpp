#include "OBS_service.h"

#include <windows.h>
#include <ShlObj.h>

obs_output_t* streamingOutput;
obs_output_t* recordingOutput;
obs_encoder_t* audioEncoder;
obs_encoder_t* videoStreamingEncoder;
obs_encoder_t* videoRecordingEncoder;
obs_service_t *service;

OBS_service::OBS_service() {

}
OBS_service::~OBS_service() {

}

void OBS_service::OBS_service_resetAudioContext(v8Arguments args) {
	resetAudioContext();
}

void OBS_service::OBS_service_resetVideoContext(v8Arguments args) {
	resetVideoContext();
}

void OBS_service::OBS_service_createAudioEncoder(v8Arguments args) {
	createAudioEncoder();
}

void OBS_service::OBS_service_createVideoStreamingEncoder(v8Arguments args) {
	createVideoStreamingEncoder();
}

void OBS_service::OBS_service_createVideoRecordingEncoder(v8Arguments args) {
	createVideoRecordingEncoder();
}

void OBS_service::OBS_service_createService(v8Arguments args) {
	createService();
}

void OBS_service::OBS_service_createRecordingSettings(v8Arguments args) {
	createRecordingSettings();
}

void OBS_service::OBS_service_createStreamingOutput(v8Arguments args) {
	createStreamingOutput();
}

void OBS_service::OBS_service_createRecordingOutput(v8Arguments args) {
	createRecordingOutput();
}

void OBS_service::OBS_service_startStreaming(v8Arguments args) {
	startStreaming();
}

void OBS_service::OBS_service_startRecording(v8Arguments args) {
	startRecording();
}

void OBS_service::OBS_service_stopStreaming(v8Arguments args) {
	stopStreaming();
}

void OBS_service::OBS_service_stopRecording(v8Arguments args) {
	stopRecording();
}

void OBS_service::OBS_service_associateAudioAndVideoToTheCurrentStreamingContext(v8Arguments args) {
	associateAudioAndVideoToTheCurrentStreamingContext();
}

void OBS_service::OBS_service_associateAudioAndVideoToTheCurrentRecordingContext(v8Arguments args) {
	associateAudioAndVideoToTheCurrentRecordingContext();
}

void OBS_service::OBS_service_associateAudioAndVideoEncodersToTheCurrentStreamingOutput(v8Arguments args) {
	associateAudioAndVideoEncodersToTheCurrentStreamingOutput();
}

void OBS_service::OBS_service_associateAudioAndVideoEncodersToTheCurrentRecordingOutput(v8Arguments args) {
	associateAudioAndVideoEncodersToTheCurrentRecordingOutput();
}

void OBS_service::OBS_service_setServiceToTheStreamingOutput(v8Arguments args) {
	setServiceToTheStreamingOutput();
}

void OBS_service::OBS_service_setRecordingSettings(v8Arguments args) {
	setRecordingSettings();
}

void OBS_service::OBS_service_isStreamingOutputActive(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	int isActive = isStreamingOutputActive();

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, to_string(isActive).c_str()));
}

void OBS_service::OBS_service_test_resetAudioContext(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;
	if (resetAudioContext()) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_resetVideoContext(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;
	if (resetVideoContext() == OBS_VIDEO_SUCCESS) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_createAudioEncoder(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	createAudioEncoder();

	if (audioEncoder != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_createVideoStreamingEncoder(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	createVideoStreamingEncoder();

	if (videoStreamingEncoder != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_createVideoRecordingEncoder(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	createVideoRecordingEncoder();

	if (videoRecordingEncoder != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_createService(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;
	createService();
	if (service != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_createRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;
	if (createRecordingSettings() != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_createStreamingOutput(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	createStreamingOutput();

	if (streamingOutput != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_createRecordingOutput(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	createRecordingOutput();

	if (recordingOutput != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_startStreaming(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	//Create output
	createStreamingOutput();

	//Creating video encoder
	createVideoStreamingEncoder();

	//Creating audio encoder
	createAudioEncoder();

	//Reset audio
	resetAudioContext();

	//Reset video
	resetVideoContext();

	//Associate A/V encoders with current context
	associateAudioAndVideoToTheCurrentStreamingContext();

	//Load service
	createService();

	//Update stream output settings
	associateAudioAndVideoEncodersToTheCurrentStreamingOutput();

	//Assign service to an ouput
	setServiceToTheStreamingOutput();


	string result;
	if (startStreaming()) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	int timeout = 8;

	while (!obs_output_active(streamingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			result = "FAILURE";
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}

	stopStreaming();

	timeout = 8;
	while (obs_output_active(streamingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_startRecording(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	createRecordingOutput();

	//Creating video encoder
	createVideoRecordingEncoder();

	//Creating audio encoder
	createAudioEncoder();

	//Reset audio
	resetAudioContext();

	//Reset video
	resetVideoContext();

	//Associate A/V encoders with current context
	associateAudioAndVideoToTheCurrentRecordingContext();

	//Update stream output A/V encoders
	associateAudioAndVideoEncodersToTheCurrentRecordingOutput();

	//Setting recording output settings
	setRecordingSettings();

	string result;
	if (startRecording()) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	int timeout = 8;

	while (!obs_output_active(recordingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			result = "FAILURE";
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}

	stopRecording();

	timeout = 8;
	while (obs_output_active(recordingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_stopStreaming(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	//Create output
	createStreamingOutput();

	//Creating video encoder
	createVideoStreamingEncoder();

	//Creating audio encoder
	createAudioEncoder();

	//Reset audio
	resetAudioContext();

	//Reset video
	resetVideoContext();

	//Associate A/V encoders with current context
	associateAudioAndVideoToTheCurrentStreamingContext();

	//Load service
	createService();

	//Update stream output settings
	associateAudioAndVideoEncodersToTheCurrentStreamingOutput();

	//Assign service to an ouput
	setServiceToTheStreamingOutput();

	startStreaming();

	int timeout = 8;

	while (!obs_output_active(streamingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			result = "FAILURE";
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}

	stopStreaming();

	timeout = 8;
	while (obs_output_active(streamingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			result = "FAILURE";
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}

	if (!obs_output_active(streamingOutput)) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_stopRecording(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	createRecordingOutput();

	//Creating video encoder
	createVideoRecordingEncoder();

	//Creating audio encoder
	createAudioEncoder();

	//Reset audio
	resetAudioContext();

	//Reset video
	resetVideoContext();

	//Associate A/V encoders with current context
	associateAudioAndVideoToTheCurrentRecordingContext();

	//Update stream output A/V encoders
	associateAudioAndVideoEncodersToTheCurrentRecordingOutput();

	//Setting recording output settings
	setRecordingSettings();


	startRecording();

	int timeout = 8;

	while (!obs_output_active(recordingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			result = "FAILURE";
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}

	stopRecording();

	timeout = 8;
	while (obs_output_active(recordingOutput)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//usleep(500000);
		timeout--;
		if (timeout == 0) {
			result = "FAILURE";
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
			return;
		}
	}

	if (!obs_output_active(recordingOutput)) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_associateAudioAndVideoToTheCurrentStreamingContext(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	associateAudioAndVideoToTheCurrentStreamingContext();

	video_t* video = obs_encoder_video(videoStreamingEncoder);
	audio_t* audio = obs_encoder_audio(audioEncoder);

	if (video == obs_get_video() && audio == obs_get_audio()) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_associateAudioAndVideoToTheCurrentRecordingContext(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	associateAudioAndVideoToTheCurrentRecordingContext();

	video_t* video = obs_encoder_video(videoRecordingEncoder);
	audio_t* audio = obs_encoder_audio(audioEncoder);

	if (video == obs_get_video() && audio == obs_get_audio()) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_associateAudioAndVideoEncodersToTheCurrentStreamingOutput(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	associateAudioAndVideoEncodersToTheCurrentStreamingOutput();

	obs_encoder_t* currentVideoEncoder = obs_output_get_video_encoder(streamingOutput);
	obs_encoder_t* currentAudioEncoder = obs_output_get_audio_encoder(streamingOutput, 0);

	if (currentVideoEncoder == videoStreamingEncoder && currentAudioEncoder == audioEncoder) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_associateAudioAndVideoEncodersToTheCurrentRecordingOutput(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	associateAudioAndVideoEncodersToTheCurrentRecordingOutput();

	obs_encoder_t* currentVideoEncoder = obs_output_get_video_encoder(recordingOutput);
	obs_encoder_t* currentAudioEncoder = obs_output_get_audio_encoder(recordingOutput, 0);

	if (currentVideoEncoder == videoRecordingEncoder && currentAudioEncoder == audioEncoder) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_setServiceToTheStreamingOutput(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	setServiceToTheStreamingOutput();
	obs_service_t* currentService = obs_output_get_service(streamingOutput);

	if (currentService == service) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_service::OBS_service_test_setRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	setRecordingSettings();

	obs_data_t* currentSettings = obs_output_get_settings(recordingOutput);

	if (currentSettings != NULL) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void LoadAudioDevice(const char *name, int channel, obs_data_t *parent) {
	obs_data_t *data = obs_data_get_obj(parent, name);
	if (!data)
		return;

	obs_source_t *source = obs_load_source(data);
	if (source) {
		obs_set_output_source(channel, source);
		obs_source_release(source);
	}

	obs_data_release(data);
}

bool OBS_service::resetAudioContext(void) {
	struct obs_audio_info ai;

	ai.samples_per_sec = 44100;
	ai.speakers = SPEAKERS_STEREO;

	// const char* file = "./config/Untitled.json";
	// obs_data_t *data = obs_data_create_from_json_file_safe(file, "bak");

	// //Loading all audio devices
	// LoadAudioDevice("DesktopAudioDevice1", 1, data);
	// LoadAudioDevice("DesktopAudioDevice2", 2, data);
	// LoadAudioDevice("AuxAudioDevice1", 3, data);
	// LoadAudioDevice("AuxAudioDevice2", 4, data);
	// LoadAudioDevice("AuxAudioDevice3", 5, data);

	return obs_reset_audio(&ai);
}

static inline enum video_format GetVideoFormatFromName(const char *name) {
	if (name != NULL) {
		if (astrcmpi(name, "I420") == 0)
			return VIDEO_FORMAT_I420;
		else if (astrcmpi(name, "NV12") == 0)
			return VIDEO_FORMAT_NV12;
		else if (astrcmpi(name, "I444") == 0)
			return VIDEO_FORMAT_I444;
		#if 0 //currently unsupported
		else if (astrcmpi(name, "YVYU") == 0)
			return VIDEO_FORMAT_YVYU;
		else if (astrcmpi(name, "YUY2") == 0)
			return VIDEO_FORMAT_YUY2;
		else if (astrcmpi(name, "UYVY") == 0)
			return VIDEO_FORMAT_UYVY;
		#endif
		else
			return VIDEO_FORMAT_RGBA;
	} else {
		return VIDEO_FORMAT_I420;
	}

}

static inline enum obs_scale_type GetScaleType(config_t* config) {
	const char *scaleTypeStr = config_get_string(config, "Video", "ScaleType");

	if (scaleTypeStr != NULL) {
		if (astrcmpi(scaleTypeStr, "bilinear") == 0)
			return OBS_SCALE_BILINEAR;
		else if (astrcmpi(scaleTypeStr, "lanczos") == 0)
			return OBS_SCALE_LANCZOS;
		else
			return OBS_SCALE_BICUBIC;
	} else {
		return OBS_SCALE_BICUBIC;
	}


}

static inline const char *GetRenderModule(config_t* config) {
	const char* renderer = config_get_string(config, "Video", "Renderer");

	const char* DL_D3D11 = "libobs-d3d11.dll";
	const char* DL_OPENGL;

	#ifdef _WIN32
	DL_OPENGL = "libobs-opengl.dll";
	#else
	DL_OPENGL = "libobs-opengl.so";
	#endif

	if (renderer != NULL) {
		return (astrcmpi(renderer, "Direct3D 11") == 0) ? DL_D3D11 : DL_OPENGL;
	} else {
		return DL_D3D11;
	}
}

void GetFPSInteger(config_t* basicConfig, uint32_t &num, uint32_t &den) {
	num = (uint32_t)config_get_uint(basicConfig, "Video", "FPSInt");
	den = 1;
}

void GetFPSFraction(config_t* basicConfig, uint32_t &num, uint32_t &den) {
	num = (uint32_t)config_get_uint(basicConfig, "Video", "FPSNum");
	den = (uint32_t)config_get_uint(basicConfig, "Video", "FPSDen");
}

void GetFPSNanoseconds(config_t* basicConfig, uint32_t &num, uint32_t &den) {
	num = 1000000000;
	den = (uint32_t)config_get_uint(basicConfig, "Video", "FPSNS");
}

void GetFPSCommon(config_t* basicConfig, uint32_t &num, uint32_t &den) {
	const char *val = config_get_string(basicConfig, "Video", "FPSCommon");
	if (val != NULL) {
		if (strcmp(val, "10") == 0) {
			num = 10;
			den = 1;
		} else if (strcmp(val, "20") == 0) {
			num = 20;
			den = 1;
		} else if (strcmp(val, "24 NTSC") == 0) {
			num = 24000;
			den = 1001;
		} else if (strcmp(val, "25") == 0) {
			num = 25;
			den = 1;
		} else if (strcmp(val, "29.97") == 0) {
			num = 30000;
			den = 1001;
		} else if (strcmp(val, "48") == 0) {
			num = 48;
			den = 1;
		} else if (strcmp(val, "59.94") == 0) {
			num = 60000;
			den = 1001;
		} else if (strcmp(val, "60") == 0) {
			num = 60;
			den = 1;
		} else {
			num = 30;
			den = 1;
		}
	} else {
		num = 30;
		den = 1;
		config_set_uint(basicConfig, "Video", "FPSType", 0);
		config_set_string(basicConfig, "Video", "FPSCommon", "30");
		config_save_safe(basicConfig, "tmp", nullptr);
	}
}

void GetConfigFPS(config_t* basicConfig, uint32_t &num, uint32_t &den) {
	uint32_t type = config_get_uint(basicConfig, "Video", "FPSType");
	if (type == 1) //"Integer"
		GetFPSInteger(basicConfig, num, den);
	else if (type == 2) //"Fraction"
		GetFPSFraction(basicConfig, num, den);
	else if (false) //"Nanoseconds", currently not implemented
		GetFPSNanoseconds(basicConfig, num, den);
	else
		GetFPSCommon(basicConfig, num, den);
}

/* some nice default output resolution vals */
static const double vals[] =
{
    1.0,
    1.25,
    (1.0 / 0.75),
    1.5,
    (1.0 / 0.6),
    1.75,
    2.0,
    2.25,
    2.5,
    2.75,
    3.0
};

static const size_t numVals = sizeof(vals) / sizeof(double);

bool OBS_service::resetVideoContext(void) {
	#ifdef _WIN32
	#define PATH_DELIM "\\"
	#else
	#define PATH_DELIM "/"
	#endif

	// Retrieve current directory. TODO: Replace with proper initialization function so that CWD changes do not mess us up.
	std::string currentDirectory;
	{
		char* buffer = getcwd(nullptr, 1);
		currentDirectory = std::string(buffer);
		free(buffer);
	}

	config_t* basicConfig = OBS_API::openConfigFile(OBS_API::getBasicConfigPath());

	obs_video_info ovi;
	std::string gslib = "";
	#ifdef _WIN32
	gslib = std::string(currentDirectory + PATH_DELIM + "node-obs" + PATH_DELIM + GetRenderModule(basicConfig)).c_str();
	#else
	gslib = std::string(currentDirectory + PATH_DELIM + "node-obs" + PATH_DELIM + "libobs-opengl.dll").c_str();
	#endif
	ovi.graphics_module = gslib.c_str();

	ovi.base_width = (uint32_t)config_get_uint(basicConfig, "Video", "BaseCX");
	ovi.base_height = (uint32_t)config_get_uint(basicConfig, "Video", "BaseCY");
	ovi.output_width = (uint32_t)config_get_uint(basicConfig, "Video", "OutputCX");
	ovi.output_height = (uint32_t)config_get_uint(basicConfig, "Video", "OutputCY");

	std::vector<Screen> resolutions = OBS_API::availableResolutions();

	if (ovi.base_width == 0 || ovi.base_height == 0) {
		for (int i = 0; i < resolutions.size(); i++) {
			if (ovi.base_width * ovi.base_height < resolutions.at(i).width * resolutions.at(i).height) {
				ovi.base_width = resolutions.at(i).width;
				ovi.base_height = resolutions.at(i).height;
			}
		}
	}

	config_set_uint(basicConfig, "Video", "BaseCX", ovi.base_width);
	config_set_uint(basicConfig, "Video", "BaseCY", ovi.base_height);

	if (ovi.output_width == 0 || ovi.output_height == 0) {
		if (ovi.base_width > 1280 && ovi.base_height > 720) {
			int idx = 0;
			do {
				ovi.output_width = uint32_t(double(ovi.base_width) / vals[idx]);
				ovi.output_height = uint32_t(double(ovi.base_height) / vals[idx]);
				idx++;
			} while (ovi.output_width > 1280 && ovi.output_height > 720);
		} else {
			ovi.output_width = ovi.base_width;
			ovi.output_height = ovi.base_height;
		}

		config_set_uint(basicConfig, "Video", "OutputCX", ovi.output_width);
		config_set_uint(basicConfig, "Video", "OutputCY", ovi.output_height);
	}

	GetConfigFPS(basicConfig, ovi.fps_num, ovi.fps_den);

	const char *colorFormat = config_get_string(basicConfig, "Video", "ColorFormat");
	const char *colorSpace = config_get_string(basicConfig, "Video", "ColorSpace");
	const char *colorRange = config_get_string(basicConfig, "Video", "ColorRange");

	ovi.output_format = GetVideoFormatFromName(colorFormat);

	ovi.adapter = 0;
	ovi.gpu_conversion = true;

	ovi.colorspace = astrcmpi(colorSpace, "601") == 0 ? VIDEO_CS_601 : VIDEO_CS_709;
	ovi.range = astrcmpi(colorRange, "Full") == 0 ? VIDEO_RANGE_FULL : VIDEO_RANGE_PARTIAL;

	ovi.scale_type = GetScaleType(basicConfig);

	config_save_safe(basicConfig, "tmp", nullptr);

	return obs_reset_video(&ovi);
}

void OBS_service::createAudioEncoder(void) {
	obs_data_t *aacSettings = obs_encoder_defaults("mf_aac");

	audioEncoder = obs_audio_encoder_create("mf_aac", "simple_aac", aacSettings, 0, nullptr);
}


void OBS_service::createVideoStreamingEncoder() {
	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config;
	int result = config_open(&config, basicConfigFile.c_str(), CONFIG_OPEN_EXISTING);

	const char *encoder = config_get_string(config, "SimpleOutput", "StreamEncoder");
	const char *streamEncoderID;

	if (encoder != NULL) {

		if (strcmp(encoder, SIMPLE_ENCODER_QSV) == 0)
			streamEncoderID = "obs_qsv11";
		else if (strcmp(encoder, SIMPLE_ENCODER_AMD) == 0)
			streamEncoderID = "amd_amf_h264";
		else if (strcmp(encoder, SIMPLE_ENCODER_NVENC) == 0)
			streamEncoderID = "ffmpeg_nvenc";
		else
			streamEncoderID = "obs_x264";
	} else {
		streamEncoderID = "obs_x264";
	}


	videoStreamingEncoder = obs_video_encoder_create(streamEncoderID, "streaming_h264", nullptr, nullptr);

	if (result != CONFIG_SUCCESS) {
		obs_data_t *h264Settings = obs_data_create();
		config = config_create(basicConfigFile.c_str());
		h264Settings = obs_encoder_defaults("obs_x264");
		config_set_uint(config, "SimpleOutput", "VBitrate", 2500);
		config_save_safe(config, "tmp", nullptr);
		obs_data_release(h264Settings);
	} else {
		updateVideoStreamEncoder();
	}
}

static inline bool valid_string(const char *str) {
	while (str && *str) {
		if (*(str++) != ' ')
			return true;
	}

	return false;
}
static void replace_text(struct dstr *str, size_t pos, size_t len,
	const char *new_text) {
	struct dstr front = { 0 };
	struct dstr back = { 0 };

	dstr_left(&front, str, pos);
	dstr_right(&back, str, pos + len);
	dstr_copy_dstr(str, &front);
	dstr_cat(str, new_text);
	dstr_cat_dstr(str, &back);
	dstr_free(&front);
	dstr_free(&back);
}

static void erase_ch(struct dstr *str, size_t pos) {
	struct dstr new_str = { 0 };
	dstr_left(&new_str, str, pos);
	dstr_cat(&new_str, str->array + pos + 1);
	dstr_free(str);
	*str = new_str;
}

char *os_generate_formatted_filename(const char *extension, bool space,
	const char *format) {
	time_t now = time(0);
	struct tm *cur_time;
	cur_time = localtime(&now);

	const size_t spec_count = 23;
	static const char *spec[][2] = {
	    {"%CCYY", "%Y"},
	    {"%YY",   "%y"},
	    {"%MM",   "%m"},
	    {"%DD",   "%d"},
	    {"%hh",   "%H"},
	    {"%mm",   "%M"},
	    {"%ss",   "%S"},
	    {"%%",    "%%"},

	    {"%a",    ""},
	    {"%A",    ""},
	    {"%b",    ""},
	    {"%B",    ""},
	    {"%d",    ""},
	    {"%H",    ""},
	    {"%I",    ""},
	    {"%m",    ""},
	    {"%M",    ""},
	    {"%p",    ""},
	    {"%S",    ""},
	    {"%y",    ""},
	    {"%Y",    ""},
	    {"%z",    ""},
	    {"%Z",    ""},
	};

	char convert[128] = { 0 };
	struct dstr sf;
	struct dstr c = { 0 };
	size_t pos = 0;

	dstr_init_copy(&sf, format);

	while (pos < sf.len) {
		for (size_t i = 0; i < spec_count && !convert[0]; i++) {
			size_t len = strlen(spec[i][0]);

			const char *cmp = sf.array + pos;

			if (astrcmp_n(cmp, spec[i][0], len) == 0) {
				if (strlen(spec[i][1]))
					strftime(convert, sizeof(convert),
						spec[i][1], cur_time);
				else
					strftime(convert, sizeof(convert),
						spec[i][0], cur_time);


				dstr_copy(&c, convert);
				if (c.len && valid_string(c.array))
					replace_text(&sf, pos, len, convert);
			}
		}

		if (convert[0]) {
			pos += strlen(convert);
			convert[0] = 0;
		} else if (!convert[0] && sf.array[pos] == '%') {
			erase_ch(&sf, pos);
		} else {
			pos++;
		}
	}

	if (!space)
		dstr_replace(&sf, " ", "_");

	dstr_cat_ch(&sf, '.');
	dstr_cat(&sf, extension);
	dstr_free(&c);

	if (sf.len > 255)
		dstr_mid(&sf, &sf, 0, 255);

	return sf.array;
}

std::string GenerateSpecifiedFilename(const char *extension, bool noSpace,
	const char *format) {
	BPtr<char> filename = os_generate_formatted_filename(extension,
		!noSpace, format);
	return string(filename);
}

static void ensure_directory_exists(string &path) {
	replace(path.begin(), path.end(), '\\', '/');

	size_t last = path.rfind('/');
	if (last == string::npos)
		return;

	string directory = path.substr(0, last);
	os_mkdirs(directory.c_str());
}

static void FindBestFilename(string &strPath, bool noSpace) {
	int num = 2;

	if (!os_file_exists(strPath.c_str()))
		return;

	const char *ext = strrchr(strPath.c_str(), '.');
	if (!ext)
		return;

	int extStart = int(ext - strPath.c_str());
	for (;;) {
		string testPath = strPath;
		string numStr;

		numStr = noSpace ? "_" : " (";
		numStr += to_string(num++);
		if (!noSpace)
			numStr += ")";

		testPath.insert(extStart, numStr);

		if (!os_file_exists(testPath.c_str())) {
			strPath = testPath;
			break;
		}
	}
}

static void remove_reserved_file_characters(string &s) {
	replace(s.begin(), s.end(), '/', '_');
	replace(s.begin(), s.end(), '\\', '_');
	replace(s.begin(), s.end(), '*', '_');
	replace(s.begin(), s.end(), '?', '_');
	replace(s.begin(), s.end(), '"', '_');
	replace(s.begin(), s.end(), '|', '_');
	replace(s.begin(), s.end(), ':', '_');
	replace(s.begin(), s.end(), '>', '_');
	replace(s.begin(), s.end(), '<', '_');
}

void OBS_service::createVideoRecordingEncoder() {
	videoRecordingEncoder = obs_video_encoder_create("obs_x264", "simple_h264_recording", nullptr, nullptr);
}

void OBS_service::createService() {
	const char *type;

	struct stat buffer;
	std::string serviceConfigFile = OBS_API::getServiceConfigPath();
	bool fileExist = (stat(serviceConfigFile.c_str(), &buffer) == 0);

	obs_data_t *data;
	obs_data_t *settings;
	obs_data_t *hotkey_data;

	if (!fileExist) {
		service = obs_service_create("rtmp_common", "default_service", nullptr, nullptr);
		data = obs_data_create();
		settings = obs_service_get_settings(service);

		obs_data_set_string(settings, "streamType", "rtmp_common");
		obs_data_set_string(settings, "service", "Twitch");
		obs_data_set_bool(settings, "show_all", 0);
		obs_data_set_string(settings, "server", "rtmp://live.twitch.tv/app");
		obs_data_set_string(settings, "key", "");

		obs_data_set_string(data, "type", obs_service_get_type(service));
		obs_data_set_obj(data, "settings", settings);

	} else {
		data = obs_data_create_from_json_file_safe(serviceConfigFile.c_str(), "bak");

		obs_data_set_default_string(data, "type", "rtmp_common");
		type = obs_data_get_string(data, "type");

		settings = obs_data_get_obj(data, "settings");
		hotkey_data = obs_data_get_obj(data, "hotkeys");

		service = obs_service_create(type, "default_service", settings, hotkey_data);


		obs_data_release(hotkey_data);
	}

	if (!obs_data_save_json_safe(data, serviceConfigFile.c_str(), "tmp", "bak")) {
		blog(LOG_WARNING, "Failed to save service %s", serviceConfigFile.c_str());
	}

	obs_data_release(settings);
	obs_data_release(data);
}

obs_data_t* OBS_service::createRecordingSettings(void) {
	obs_data_t *settings = obs_data_create();
	/*obs_data_set_string(settings, "format_name", "avi");
	obs_data_set_string(settings, "video_encoder", "utvideo");
	obs_data_set_string(settings, "audio_encoder", "pcm_s16le");
	obs_data_set_string(settings, "path", "./recording_1.avi");*/
	// obs_data_t *settings = obs_encoder_get_settings(videoRecordingEncoder);


	return settings;
}

void OBS_service::createStreamingOutput(void) {
	streamingOutput = obs_output_create("rtmp_output", "simple_stream", nullptr, nullptr);
}

void OBS_service::createRecordingOutput(void) {
	recordingOutput = obs_output_create("ffmpeg_muxer", "simple_file_output", nullptr, nullptr);
	updateRecordingOutput();
}

bool OBS_service::startStreaming(void) {
	setServiceToTheStreamingOutput();

	updateVideoStreamEncoder();

	associateAudioAndVideoToTheCurrentStreamingContext();
	associateAudioAndVideoEncodersToTheCurrentStreamingOutput();

	return obs_output_start(streamingOutput);
}

bool OBS_service::startRecording(void) {
	updateRecordingOutput();
	return obs_output_start(recordingOutput);
}

void OBS_service::stopStreaming(void) {
	obs_output_stop(streamingOutput);
}

void OBS_service::stopRecording(void) {
	obs_output_stop(recordingOutput);
}

void OBS_service::associateAudioAndVideoToTheCurrentStreamingContext(void) {
	obs_encoder_set_video(videoStreamingEncoder, obs_get_video());
	obs_encoder_set_audio(audioEncoder, obs_get_audio());
}

void OBS_service::associateAudioAndVideoToTheCurrentRecordingContext(void) {
	obs_encoder_set_video(videoRecordingEncoder, obs_get_video());
	obs_encoder_set_audio(audioEncoder, obs_get_audio());
}

void OBS_service::associateAudioAndVideoEncodersToTheCurrentStreamingOutput(void) {
	obs_output_set_video_encoder(streamingOutput, videoStreamingEncoder);
	obs_output_set_audio_encoder(streamingOutput, audioEncoder, 0);
}

void OBS_service::associateAudioAndVideoEncodersToTheCurrentRecordingOutput(void) {
	obs_output_set_video_encoder(recordingOutput, videoRecordingEncoder);
	obs_output_set_audio_encoder(recordingOutput, audioEncoder, 0);
}

void OBS_service::setServiceToTheStreamingOutput(void) {
	obs_output_set_service(streamingOutput, service);
}

void OBS_service::setRecordingSettings(void) {
	obs_data_t *settings = createRecordingSettings();
	obs_output_update(recordingOutput, settings);
	obs_data_release(settings);
}

obs_service_t* OBS_service::getService(void) {
	const char* serviceType = obs_service_get_type(service);
	return service;
}

void OBS_service::setService(obs_service_t* newService) {
	obs_service_release(service);
	service = newService;
}

void OBS_service::saveService(void) {
	if (!service)
		return;

	obs_data_t *data = obs_data_create();
	obs_data_t *settings = obs_service_get_settings(service);

	const char* serviceType = obs_service_get_type(service);

	obs_data_set_string(data, "type", obs_service_get_type(service));
	obs_data_set_obj(data, "settings", settings);

	if (!obs_data_save_json_safe(data, OBS_API::getServiceConfigPath().c_str(), "tmp", "bak"))
		blog(LOG_WARNING, "Failed to save service");

	obs_service_update(service, settings);

	serviceType = obs_service_get_type(service);

	// obs_data_release(settings);
	// obs_data_release(data);
}

bool OBS_service::isStreamingOutputActive(void) {
	return obs_output_active(streamingOutput);
}

int GetAudioBitrate() {
	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	int bitrate = (int)config_get_uint(config, "SimpleOutput",
		"ABitrate");

	return FindClosestAvailableAACBitrate(bitrate);
}

void OBS_service::updateVideoStreamEncoder() {
	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	obs_data_t *h264Settings = obs_data_create();
	obs_data_t *aacSettings = obs_data_create();

	int videoBitrate = config_get_uint(config, "SimpleOutput", "VBitrate");
	int audioBitrate = GetAudioBitrate();
	bool advanced = config_get_bool(config, "SimpleOutput", "UseAdvanced");
	bool enforceBitrate = config_get_bool(config, "SimpleOutput", "EnforceBitrate");
	const char *custom = config_get_string(config, "SimpleOutput", "x264Settings");
	const char *encoder = config_get_string(config, "SimpleOutput", "StreamEncoder");
	const char *encoderID;
	const char *presetType;
	const char *preset;

	if (encoder != NULL) {
		if (strcmp(encoder, SIMPLE_ENCODER_QSV) == 0) {
			presetType = "QSVPreset";
			encoderID = "obs_qsv11";
		} else if (strcmp(encoder, SIMPLE_ENCODER_AMD) == 0) {
			presetType = "AMDPreset";
			// UpdateStreamingSettings_amd(h264Settings, videoBitrate);
			encoderID = "amd_amf_h264";
		} else if (strcmp(encoder, SIMPLE_ENCODER_NVENC) == 0) {
			presetType = "NVENCPreset";
			encoderID = "ffmpeg_nvenc";
		} else {
			presetType = "Preset";
			encoderID = "obs_x264";
		}
		preset = config_get_string(config, "SimpleOutput", presetType);

		if (strcmp(obs_encoder_get_id(videoStreamingEncoder), encoderID) != 0)
			videoStreamingEncoder = obs_video_encoder_create(encoderID, "streaming_h264", nullptr, nullptr);
	}

	if (videoBitrate == 0) {
		videoBitrate = 2500;
		config_set_uint(config, "SimpleOutput", "VBitrate", videoBitrate);
		config_save_safe(config, "tmp", nullptr);
	}

	obs_data_set_string(h264Settings, "rate_control", "CBR");
	obs_data_set_int(h264Settings, "bitrate", videoBitrate);

	if (advanced) {
		obs_data_set_string(h264Settings, "preset", preset);
		obs_data_set_string(h264Settings, "x264opts", custom);
	}

	// obs_data_set_string(aacSettings, "rate_control", "CBR");
	obs_data_set_int(aacSettings, "bitrate", audioBitrate);

	const char* url = obs_service_get_url(service);

	obs_service_apply_encoder_settings(service, h264Settings, aacSettings);

	if (advanced && !enforceBitrate) {
		obs_data_set_int(h264Settings, "bitrate", videoBitrate);
		obs_data_set_int(aacSettings, "bitrate", audioBitrate);
	}

	video_t *video = obs_get_video();
	enum video_format format = video_output_get_format(video);

	if (format != VIDEO_FORMAT_NV12 && format != VIDEO_FORMAT_I420)
		obs_encoder_set_preferred_video_format(videoStreamingEncoder,
			VIDEO_FORMAT_NV12);

	obs_encoder_update(videoStreamingEncoder, h264Settings);
	obs_encoder_update(audioEncoder, aacSettings);

	obs_data_release(h264Settings);
	obs_data_release(aacSettings);
}


string GetDefaultVideoSavePath() {
	wchar_t path_utf16[MAX_PATH];
	char    path_utf8[MAX_PATH] = {};

	SHGetFolderPathW(NULL, CSIDL_MYVIDEO, NULL, SHGFP_TYPE_CURRENT,
		path_utf16);

	os_wcs_to_utf8(path_utf16, wcslen(path_utf16), path_utf8, MAX_PATH);
	return string(path_utf8);
}

void OBS_service::updateRecordingOutput(void) {
	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	obs_data_t *h264Settings = obs_data_create();

	const char *path = config_get_string(config, "SimpleOutput", "FilePath");

	if (!path) {
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

	path = config_get_string(config, "SimpleOutput", "FilePath");
	// std::string path = path_c_str ? path_c_str : std::string();
	const char *format = config_get_string(config, "SimpleOutput", "RecFormat");
	const char *mux = config_get_string(config, "SimpleOutput", "MuxerCustom");
	bool noSpace = config_get_bool(config, "SimpleOutput", "FileNameWithoutSpace");
	const char *filenameFormat = config_get_string(config, "Output", "FilenameFormatting");
	bool overwriteIfExists = config_get_bool(config, "Output", "OverwriteIfExists");
	const char *rbPrefix = config_get_string(config, "SimpleOutput", "RecRBPrefix");
	const char *rbSuffix = config_get_string(config, "SimpleOutput", "RecRBSuffix");
	int rbTime = config_get_int(config, "SimpleOutput", "RecRBTime");
	int rbSize = config_get_int(config, "SimpleOutput", "RecRBSize");

	if (filenameFormat == NULL) {
		filenameFormat = "%CCYY-%MM-%DD %hh-%mm-%ss";
	}
	string strPath;
	strPath += path;


	char lastChar = strPath.back();
	if (lastChar != '/' && lastChar != '\\')
		strPath += "/";

	bool ffmpegOutput = false;
	bool usingRecordingPreset = true;

	if (filenameFormat != NULL && format != NULL) {
		strPath += GenerateSpecifiedFilename(ffmpegOutput ? "avi" : format, noSpace, filenameFormat);
		if (!strPath.empty())
			ensure_directory_exists(strPath);
	}
	if (!overwriteIfExists)
		FindBestFilename(strPath, noSpace);

	bool useReplayBuffer = config_get_bool(config, "SimpleOutput", "RecRB");
	// bool useReplayBuffer = true;
	if (useReplayBuffer) {
		string f;

		if (rbPrefix && *rbPrefix) {
			f += rbPrefix;
			if (f.back() != ' ')
				f += " ";
		}

		f += filenameFormat;

		if (rbSuffix && *rbSuffix) {
			if (*rbSuffix != ' ')
				f += " ";
			f += rbSuffix;
		}

		remove_reserved_file_characters(f);

		obs_data_set_string(h264Settings, "directory", path);
		obs_data_set_string(h264Settings, "extension", format);
		obs_data_set_int(h264Settings, "max_time_sec", rbTime);
		obs_data_set_int(h264Settings, "max_size_mb", usingRecordingPreset ? rbSize : 0);
	} else {
		obs_data_set_string(h264Settings, ffmpegOutput ? "url" : "path", strPath.c_str());
	}

	obs_output_update(recordingOutput, h264Settings);
}

obs_output_t* OBS_service::getStreamingOutput(void) {
	return streamingOutput;
}