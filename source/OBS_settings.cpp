#include "OBS_settings.h"

#include <windows.h>
vector<const char*> tabStreamTypes;

OBS_settings::OBS_settings() {

}
OBS_settings::~OBS_settings() {

}

void OBS_settings::OBS_settings_getGeneralSettings(v8Arguments args) {
	args.GetReturnValue().Set(getGeneralSettings());
}

void OBS_settings::OBS_settings_saveGeneralSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	Local<Array> generalSettings = v8::Local<v8::Array>::Cast(args[0]);

	v8::String::Utf8Value param2(args[1]->ToString());
	std::string pathConfigDirectory = std::string(*param2);

	saveGeneralSettings(generalSettings, pathConfigDirectory);
}

void OBS_settings::OBS_settings_getListCategories(v8Arguments args) {
	args.GetReturnValue().Set(getListCategories());
}

void OBS_settings::OBS_settings_getStreamSettings(v8Arguments args) {
	v8::String::Utf8Value param1(args[0]->ToString());
	std::string pathConfigDirectory = std::string(*param1);

	args.GetReturnValue().Set(getStreamSettings());
}

void OBS_settings::OBS_settings_saveStreamSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	Local<Array> streamSettings = v8::Local<v8::Array>::Cast(args[0]);

	saveStreamSettings(streamSettings);
}

void OBS_settings::OBS_settings_getStreamTypesForStreamSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	vector<std::string> listStreamTypes = getStreamTypesForStreamSettings();

	Handle<Array> result = Array::New(isolate, listStreamTypes.size());
	for (size_t i = 0; i < listStreamTypes.size(); i++) {
		result->Set(i, String::NewFromUtf8(isolate, listStreamTypes.at(i).c_str()));
	}

	args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_setStreamTypeForStreamSettings(v8Arguments args) {
	v8::String::Utf8Value param1(args[0]->ToString());
	std::string streamType = std::string(*param1);

	setStreamTypeForStreamSettings(streamType.c_str());
}

void OBS_settings::OBS_settings_getOutputSimpleStreamingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	vector<const char*> listOutputSimpleStreamingSettings = getOutputSimpleStreamingSettings();

	Handle<Array> result = Array::New(isolate, listOutputSimpleStreamingSettings.size());
	for (size_t i = 0; i < listOutputSimpleStreamingSettings.size(); i++) {
		result->Set(i, String::NewFromUtf8(isolate, listOutputSimpleStreamingSettings.at(i)));
	}

	args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveOutputSimpleStreamingSettings(v8Arguments args) {
	v8::String::Utf8Value param1(args[0]->ToString());
	std::string videoBitrate = std::string(*param1);

	v8::String::Utf8Value param2(args[1]->ToString());
	std::string streamEnc = std::string(*param2);

	v8::String::Utf8Value param3(args[2]->ToString());
	std::string audioBitrate = std::string(*param3);

	v8::String::Utf8Value param4(args[3]->ToString());
	std::string advanced = std::string(*param4);

	v8::String::Utf8Value param5(args[4]->ToString());
	std::string enforceBitrate = std::string(*param5);

	v8::String::Utf8Value param6(args[5]->ToString());
	std::string preset = std::string(*param6);

	v8::String::Utf8Value param7(args[6]->ToString());
	std::string qsvPreset = std::string(*param7);

	v8::String::Utf8Value param8(args[7]->ToString());
	std::string nvPreset = std::string(*param8);

	v8::String::Utf8Value param9(args[8]->ToString());
	std::string amdPreset = std::string(*param9);

	v8::String::Utf8Value param10(args[9]->ToString());
	std::string custom = std::string(*param10);

	saveOutputSimpleStreamingSettings(stoi(videoBitrate), streamEnc.c_str(),
		stoi(audioBitrate), stoi(advanced) ? 1 : 0,
		stoi(enforceBitrate) ? 1 : 0, preset.c_str(),
		qsvPreset.c_str(), nvPreset.c_str(),
		amdPreset.c_str(), custom.c_str());
}

void OBS_settings::OBS_settings_getOutputSimpleRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	vector<const char*> listOutputSimpleRecordingSettings = getOutputSimpleRecordingSettings();

	Handle<Array> result = Array::New(isolate, listOutputSimpleRecordingSettings.size());
	for (size_t i = 0; i < listOutputSimpleRecordingSettings.size(); i++) {
		result->Set(i, String::NewFromUtf8(isolate, listOutputSimpleRecordingSettings.at(i)));
	}

	args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveOutputSimpleRecordingSettings(v8Arguments args) {
	saveOutputSimpleRecordingSettings();
}

void OBS_settings::OBS_settings_getOutputAdvancedStreamingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	vector<const char*> listOutputAdvancedStreamingSettings = getOutputAdvancedStreamingSettings();

	Handle<Array> result = Array::New(isolate, listOutputAdvancedStreamingSettings.size());
	for (size_t i = 0; i < listOutputAdvancedStreamingSettings.size(); i++) {
		result->Set(i, String::NewFromUtf8(isolate, listOutputAdvancedStreamingSettings.at(i)));
	}

	args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveOutputAdvancedStreamingSettings(v8Arguments args) {
	saveOutputAdvancedStreamingSettings();
}

void OBS_settings::OBS_settings_getOutputAdvancedRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	vector<const char*> listOutputAdvancedRecordingSettings = getOutputAdvancedRecordingSettings();

	Handle<Array> result = Array::New(isolate, listOutputAdvancedRecordingSettings.size());
	for (size_t i = 0; i < listOutputAdvancedRecordingSettings.size(); i++) {
		result->Set(i, String::NewFromUtf8(isolate, listOutputAdvancedRecordingSettings.at(i)));
	}

	args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveOutputAdvancedRecordingSettings(v8Arguments args) {
	saveOutputAdvancedRecordingSettings();
}

void OBS_settings::OBS_settings_getOutputAdvancedAudioSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	vector<const char*> listOutputAdvancedAudioSettings = getOutputAdvancedAudioSettings();

	Handle<Array> result = Array::New(isolate, listOutputAdvancedAudioSettings.size());
	for (size_t i = 0; i < listOutputAdvancedAudioSettings.size(); i++) {
		result->Set(i, String::NewFromUtf8(isolate, listOutputAdvancedAudioSettings.at(i)));
	}

	args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveOutputAdvancedAudioSettings(v8Arguments args) {
	saveOutputAdvancedAudioSettings();
}

void OBS_settings::OBS_settings_getAudioSettings(v8Arguments args) {
	// Isolate* isolate = args.GetIsolate();
	// vector<const char*> listAudioSettings = getAudioSettings();

	// Handle<Array> result = Array::New(isolate, listAudioSettings.size());
	// for (size_t i = 0; i < listAudioSettings.size(); i++) {
	// 	result->Set(i, String::NewFromUtf8(isolate, listAudioSettings.at(i)));
	// }

	// args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveAudioSettings(v8Arguments args) {
	// saveAudioSettings();
}

void OBS_settings::OBS_settings_getVideoSettings(v8Arguments args) {
	// Isolate* isolate = args.GetIsolate();
	// vector<const char*> listVideoSettings = getVideoSettings();

	// Handle<Array> result = Array::New(isolate, listVideoSettings.size());
	// for (size_t i = 0; i < listVideoSettings.size(); i++) {
	// 	result->Set(i, String::NewFromUtf8(isolate, listVideoSettings.at(i)));
	// }

	// args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveVideoSettings(v8Arguments args) {
	// saveVideoSettings();
}

void OBS_settings::OBS_settings_getHotkeysSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	vector<const char*> listHotkeysSettings = getHotkeysSettings();

	Handle<Array> result = Array::New(isolate, listHotkeysSettings.size());
	for (size_t i = 0; i < listHotkeysSettings.size(); i++) {
		result->Set(i, String::NewFromUtf8(isolate, listHotkeysSettings.at(i)));
	}

	args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveHotkeysSettings(v8Arguments args) {
	saveHotkeysSettings();
}

void OBS_settings::OBS_settings_getAdvancedSettings(v8Arguments args) {
	// Isolate* isolate = args.GetIsolate();

	// v8::String::Utf8Value param1(args[0]->ToString());
	// std::string pathConfigDirectory = std::string(*param1);

	// vector<const char*> listAdvancedSettings = getAdvancedSettings(pathConfigDirectory);

	// Handle<Array> result = Array::New(isolate, listAdvancedSettings.size());
	// for (size_t i = 0; i < listAdvancedSettings.size(); i++) {
	// 	result->Set(i, String::NewFromUtf8(isolate, listAdvancedSettings.at(i)));
	// }

	// args.GetReturnValue().Set(result);
}

void OBS_settings::OBS_settings_saveAdvancedSettings(v8Arguments args) {
	// v8::String::Utf8Value param1(args[0]->ToString());
	// std::string pathConfigDirectory = std::string(*param1);

	// saveAdvancedSettings(pathConfigDirectory);
}

void OBS_settings::OBS_settings_getSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	v8::String::Utf8Value param1(args[0]->ToString());
	std::string nameCategory = std::string(*param1);

	args.GetReturnValue().Set(getSettings(nameCategory));
}

void OBS_settings::OBS_settings_saveSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	v8::String::Utf8Value param1(args[0]->ToString());
	std::string nameCategory = std::string(*param1);

	Local<Array> generalSettings = v8::Local<v8::Array>::Cast(args[1]);

	v8::String::Utf8Value param3(args[2]->ToString());
	std::string pathConfigDirectory = std::string(*param3);

	saveSettings(nameCategory, generalSettings);
}

void OBS_settings::OBS_settings_test_getGeneralSettings(v8Arguments args) {
	// Isolate* isolate = args.GetIsolate();

 //    string result;
	// vector<const char*> listGeneralSettings = getGeneralSettings();

	// if(strcmp(listGeneralSettings.at(0), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(1), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(2), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(3), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(4), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(5), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(6), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(7), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(8), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(9), "false") == 0 && 
	// 	strcmp(listGeneralSettings.at(10), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(11), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(12), "10") == 0 &&
	// 	strcmp(listGeneralSettings.at(13), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(14), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(15), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(16), "true") == 0) {
	// 	result = "SUCCESS";
	// } 
	// else {
	// 	result = "FAILURE";
	// }

 //    args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveGeneralSettings(v8Arguments args) {
	// Isolate* isolate = args.GetIsolate();
	// string result;

 //    saveGeneralSettings(true, true,
	// 					true, true, 
	// 					true, true,
	// 					true, true,
	// 					false, true,
	// 					true, true,
	// 					11, false,
	// 					false, false, false);

 //    vector<const char*> listGeneralSettings = getGeneralSettings();

	// if(strcmp(listGeneralSettings.at(0), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(1), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(2), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(3), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(4), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(5), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(6), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(7), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(8), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(9), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(10), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(11), "true") == 0 &&
	// 	strcmp(listGeneralSettings.at(12), "11") == 0 &&
	// 	strcmp(listGeneralSettings.at(13), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(14), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(15), "false") == 0 &&
	// 	strcmp(listGeneralSettings.at(16), "false") == 0) 
	// {
	// 	result = "SUCCESS";
	// 	//Writting initial values
	//     saveGeneralSettings(false, false,
	// 						false, false, 
	// 						false, false,
	// 						false, false,
	// 						true, false,
	// 						false, false,
	// 						10, true,
	// 						true, true, true);
	// } 
	// else {
	// 	result = "FAILURE";
	// }

 //    args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getStreamSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveStreamSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getStreamTypesForStreamSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	vector<std::string> listStreamTypes = getStreamTypesForStreamSettings();

	if (listStreamTypes.size() == 2 &&
		listStreamTypes.at(0).compare("Streaming Services") == 0 &&
		listStreamTypes.at(1).compare("Custom Streaming Server") == 0) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_setStreamTypeForStreamSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	setStreamTypeForStreamSettings("Custom Streaming Server");

	obs_service_t* customService = OBS_service::getService();

	setStreamTypeForStreamSettings("Streaming Services");
	obs_service_t* commonService = OBS_service::getService();

	if (strcmp(obs_service_get_type(customService), "rtmp_custom") == 0 &&
		strcmp(obs_service_get_type(commonService), "rtmp_common") == 0) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getOutputSimpleStreamingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;
	vector<const char*> listSettings = getOutputSimpleStreamingSettings();

	if (strcmp(listSettings.at(0), "3000") == 0 &&
		strcmp(listSettings.at(1), "Software (x264)") == 0 &&
		strcmp(listSettings.at(2), "160") == 0 &&
		strcmp(listSettings.at(3), "true") == 0 &&
		strcmp(listSettings.at(4), "true") == 0 &&
		strcmp(listSettings.at(5), "veryfast") == 0 &&
		strcmp(listSettings.at(6), "0") == 0 &&
		strcmp(listSettings.at(7), "0") == 0 &&
		strcmp(listSettings.at(8), "0") == 0 &&
		strcmp(listSettings.at(9), "0") == 0) {
		result = "SUCCESS";
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveOutputSimpleStreamingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();
	string result;

	saveOutputSimpleStreamingSettings(1000, "Software (x264)",
		320, false,
		false, "veryfast",
		"0", "0",
		"0", "0");

	vector<const char*> listSettings = getOutputSimpleStreamingSettings();

	if (strcmp(listSettings.at(0), "1000") == 0 &&
		strcmp(listSettings.at(1), "Software (x264)") == 0 &&
		strcmp(listSettings.at(2), "320") == 0 &&
		strcmp(listSettings.at(3), "false") == 0 &&
		strcmp(listSettings.at(4), "false") == 0 &&
		strcmp(listSettings.at(5), "veryfast") == 0 &&
		strcmp(listSettings.at(6), "0") == 0 &&
		strcmp(listSettings.at(7), "0") == 0 &&
		strcmp(listSettings.at(8), "0") == 0 &&
		strcmp(listSettings.at(9), "0") == 0) {
		result = "SUCCESS";
		//Writting initial values
		saveOutputSimpleStreamingSettings(3000, "Software (x264)",
			160, true,
			true, "veryfast",
			"0", "0",
			"0", "0");
	} else {
		result = "FAILURE";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getOutputSimpleRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveOutputSimpleRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getOutputAdvancedStreamingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveOutputAdvancedStreamingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getOutputAdvancedRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveOutputAdvancedRecordingSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getOutputAdvancedAudioSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveOutputAdvancedAudioSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}


void OBS_settings::OBS_settings_test_getAudioSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveAudioSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getVideoSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveVideoSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getHotkeysSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveHotkeysSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_getAdvancedSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void OBS_settings::OBS_settings_test_saveAdvancedSettings(v8Arguments args) {
	Isolate* isolate = args.GetIsolate();

	string result = "FAILURE";

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

static bool compareStringValue(std::pair<std::string, std::string> value) {
	if (value.first.compare("currentValue") == 0) {
		return true;
	} else {
		return false;
	}
}

Local<Object> OBS_settings::serializeSettingsData(std::string nameSubCategory,
	std::vector<std::vector<std::pair<std::string, std::string>>> entries,
	config_t* config, std::string section, bool isVisible, bool isEnabled) {
	os_cpu_usage_info_t *cpuUsageInfo = nullptr;

	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Object> object = Object::New(isolate);

	Local<Array> subCategoryParameters = Array::New(isolate);
	Local<Object> subCategory = Object::New(isolate);

	for (int i = 0; i < entries.size(); i++) {
		Local<Object> parameter = Object::New(isolate);

		std::string name = entries.at(i).at(0).second.c_str();
		parameter->Set(String::NewFromUtf8(isolate, entries.at(i).at(0).first.c_str()),
			String::NewFromUtf8(isolate, entries.at(i).at(0).second.c_str()));

		std::string type = entries.at(i).at(1).second.c_str();
		parameter->Set(String::NewFromUtf8(isolate, entries.at(i).at(1).first.c_str()),
			String::NewFromUtf8(isolate, entries.at(i).at(1).second.c_str()));

		parameter->Set(String::NewFromUtf8(isolate, entries.at(i).at(2).first.c_str()),
			String::NewFromUtf8(isolate, entries.at(i).at(2).second.c_str()));

		std::string currentValue;
		if (entries.at(i).size() > 3) {
			currentValue = entries.at(i).at(3).first.c_str();
		}

		if (!currentValue.empty() && currentValue.compare("currentValue") == 0) {
			parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, entries.at(i).at(3).second.c_str()));
			entries.at(i).erase(entries.at(i).begin() + 3);
		} else {
			if (type.compare("OBS_PROPERTY_LIST") == 0 ||
				type.compare("OBS_PROPERTY_PATH") == 0 ||
				type.compare("OBS_PROPERTY_EDIT_PATH") == 0 ||
				type.compare("OBS_PROPERTY_EDIT_TEXT") == 0) {
				const char* currentValue = config_get_string(config, section.c_str(), name.c_str());

				if (currentValue != NULL) {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, currentValue));
				} else {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, ""));
				}
			} else if (type.compare("OBS_PROPERTY_INT") == 0) {
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Integer::New(isolate, config_get_int(config, section.c_str(), name.c_str())));
			} else if (type.compare("OBS_PROPERTY_UINT") == 0) {
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Integer::New(isolate, config_get_uint(config, section.c_str(), name.c_str())));
			} else if (type.compare("OBS_PROPERTY_BOOL") == 0) {
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Integer::New(isolate, config_get_bool(config, section.c_str(), name.c_str())));
			} else if (type.compare("OBS_PROPERTY_DOUBLE") == 0) {
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Integer::New(isolate, config_get_double(config, section.c_str(), name.c_str())));
			}
		}
		if (entries.at(i).size() > 3) {
			Local<Array> values = Array::New(isolate);
			for (int j = 3; j < entries.at(i).size(); j++) {
				Local<Object> value = Object::New(isolate);
				value->Set(String::NewFromUtf8(isolate, entries.at(i).at(j).first.c_str()),
					String::NewFromUtf8(isolate, entries.at(i).at(j).second.c_str()));
				values->Set(j - 3, value);
			}
			parameter->Set(String::NewFromUtf8(isolate, "values"), values);
		}

		parameter->Set(String::NewFromUtf8(isolate, "visible"), Integer::New(isolate, isVisible));
		parameter->Set(String::NewFromUtf8(isolate, "enabled"), Integer::New(isolate, isEnabled));
		parameter->Set(String::NewFromUtf8(isolate, "masked"), Integer::New(isolate, false));

		subCategoryParameters->Set(i, parameter);
	}
	subCategory->Set(String::NewFromUtf8(isolate, "nameSubCategory"), String::NewFromUtf8(isolate, nameSubCategory.c_str()));
	subCategory->Set(String::NewFromUtf8(isolate, "parameters"), subCategoryParameters);
	return subCategory;
}

Local<Array> OBS_settings::getGeneralSettings() {
	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Array> generalSettings = Array::New(isolate);

	std::string globalConfigFile = OBS_API::getGlobalConfigPath();

	config_t* config;
	int result = config_open(&config, globalConfigFile.c_str(), CONFIG_OPEN_EXISTING);

	if (result != CONFIG_SUCCESS) {
		config = config_create(globalConfigFile.c_str());

		config_set_bool(config, "BasicWindow", "SnappingEnabled", true);
		config_set_double(config, "BasicWindow", "SnapDistance", 10);
		config_set_bool(config, "BasicWindow", "ScreenSnapping", true);
		config_set_bool(config, "BasicWindow", "SourceSnapping", true);
		config_set_bool(config, "BasicWindow", "CenterSnapping", false);

		config_save_safe(config, "tmp", nullptr);
	}

	std::vector<std::vector<std::pair<std::string, std::string>>> entries;

	// General
	generalSettings->Set(0, serializeSettingsData("General", entries, config, "BasicWindow", true, true));
	entries.clear();

	// Output 
	std::vector<std::pair<std::string, std::string>> warnBeforeStartingStream;
	warnBeforeStartingStream.push_back(std::make_pair("name", "WarnBeforeStartingStream"));
	warnBeforeStartingStream.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	warnBeforeStartingStream.push_back(std::make_pair("description", "Show confirmation dialog when starting streams"));
	entries.push_back(warnBeforeStartingStream);

	std::vector<std::pair<std::string, std::string>> warnBeforeStoppingStream;
	warnBeforeStoppingStream.push_back(std::make_pair("name", "WarnBeforeStoppingStream"));
	warnBeforeStoppingStream.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	warnBeforeStoppingStream.push_back(std::make_pair("description", "Show confirmation dialog when stoping streams"));
	entries.push_back(warnBeforeStoppingStream);

	std::vector<std::pair<std::string, std::string>> recordWhenStreaming;
	recordWhenStreaming.push_back(std::make_pair("name", "RecordWhenStreaming"));
	recordWhenStreaming.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	recordWhenStreaming.push_back(std::make_pair("description", "Automatically record when streaming"));
	entries.push_back(recordWhenStreaming);

	std::vector<std::pair<std::string, std::string>> keepRecordingWhenStreamStops;
	keepRecordingWhenStreamStops.push_back(std::make_pair("name", "KeepRecordingWhenStreamStops"));
	keepRecordingWhenStreamStops.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	keepRecordingWhenStreamStops.push_back(std::make_pair("description", "Keep recording when stream stops"));
	entries.push_back(keepRecordingWhenStreamStops);

	std::vector<std::pair<std::string, std::string>> replayBufferWhileStreaming;
	replayBufferWhileStreaming.push_back(std::make_pair("name", "ReplayBufferWhileStreaming"));
	replayBufferWhileStreaming.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	replayBufferWhileStreaming.push_back(std::make_pair("description", "Automatically start replay buffer when streaming"));
	entries.push_back(replayBufferWhileStreaming);

	std::vector<std::pair<std::string, std::string>> keepReplayBufferStreamStops;
	keepReplayBufferStreamStops.push_back(std::make_pair("name", "KeepReplayBufferStreamStops"));
	keepReplayBufferStreamStops.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	keepReplayBufferStreamStops.push_back(std::make_pair("description", "Keep replay buffer active when stream stops"));
	entries.push_back(keepReplayBufferStreamStops);

	generalSettings->Set(1, serializeSettingsData("Output", entries, config, "BasicWindow", true, true));
	entries.clear();

	// Source Alignement Snapping
	std::vector<std::pair<std::string, std::string>> snappingEnabled;
	snappingEnabled.push_back(std::make_pair("name", "SnappingEnabled"));
	snappingEnabled.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	snappingEnabled.push_back(std::make_pair("description", "Enable"));
	entries.push_back(snappingEnabled);

	std::vector<std::pair<std::string, std::string>> snapDistance;
	snapDistance.push_back(std::make_pair("name", "SnapDistance"));
	snapDistance.push_back(std::make_pair("type", "OBS_PROPERTY_DOUBLE"));
	snapDistance.push_back(std::make_pair("description", "Snap Sensitivy"));
	entries.push_back(snapDistance);

	std::vector<std::pair<std::string, std::string>> screenSnapping;
	screenSnapping.push_back(std::make_pair("name", "ScreenSnapping"));
	screenSnapping.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	screenSnapping.push_back(std::make_pair("description", "Snap Sources to edge of screen"));
	entries.push_back(screenSnapping);

	std::vector<std::pair<std::string, std::string>> sourceSnapping;
	sourceSnapping.push_back(std::make_pair("name", "SourceSnapping"));
	sourceSnapping.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	sourceSnapping.push_back(std::make_pair("description", "Snap Sources to other sources"));
	entries.push_back(sourceSnapping);

	std::vector<std::pair<std::string, std::string>> centerSnapping;
	centerSnapping.push_back(std::make_pair("name", "CenterSnapping"));
	centerSnapping.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	centerSnapping.push_back(std::make_pair("description", "Snap Sources to horizontal and vertical center"));
	entries.push_back(centerSnapping);

	generalSettings->Set(2, serializeSettingsData("Source Alignement Snapping", entries, config, "BasicWindow", true, true));
	entries.clear();

	// Projectors
	std::vector<std::pair<std::string, std::string>> hideProjectorCursor;
	hideProjectorCursor.push_back(std::make_pair("name", "HideProjectorCursor"));
	hideProjectorCursor.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	hideProjectorCursor.push_back(std::make_pair("description", "Hide cursor over projectors"));
	entries.push_back(hideProjectorCursor);

	std::vector<std::pair<std::string, std::string>> projectorAlwaysOnTop;
	projectorAlwaysOnTop.push_back(std::make_pair("name", "ProjectorAlwaysOnTop"));
	projectorAlwaysOnTop.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	projectorAlwaysOnTop.push_back(std::make_pair("description", "Make projectors always on top"));
	entries.push_back(projectorAlwaysOnTop);

	std::vector<std::pair<std::string, std::string>> saveProjectors;
	saveProjectors.push_back(std::make_pair("name", "SaveProjectors"));
	saveProjectors.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	saveProjectors.push_back(std::make_pair("description", "Save projectors on exit"));
	entries.push_back(saveProjectors);

	generalSettings->Set(3, serializeSettingsData("Projectors", entries, config, "BasicWindow", true, true));
	entries.clear();

	// System Tray
	std::vector<std::pair<std::string, std::string>> sysTrayEnabled;
	sysTrayEnabled.push_back(std::make_pair("name", "SysTrayEnabled"));
	sysTrayEnabled.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	sysTrayEnabled.push_back(std::make_pair("description", "Enable"));
	entries.push_back(sysTrayEnabled);

	std::vector<std::pair<std::string, std::string>> sysTrayWhenStarted;
	sysTrayWhenStarted.push_back(std::make_pair("name", "SysTrayWhenStarted"));
	sysTrayWhenStarted.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	sysTrayWhenStarted.push_back(std::make_pair("description", "Minimize to system tray when started"));
	entries.push_back(sysTrayWhenStarted);

	std::vector<std::pair<std::string, std::string>> sysTrayMinimizeToTray;
	sysTrayMinimizeToTray.push_back(std::make_pair("name", "SysTrayMinimizeToTray"));
	sysTrayMinimizeToTray.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	sysTrayMinimizeToTray.push_back(std::make_pair("description", "Always minimize to system try instead of task bar"));
	entries.push_back(sysTrayMinimizeToTray);

	generalSettings->Set(4, serializeSettingsData("System Tray", entries, config, "BasicWindow", true, true));
	entries.clear();

	return generalSettings;
}

void OBS_settings::saveGeneralSettings(Local<Array> generalSettings, std::string pathConfigDirectory) {
	Isolate *isolate = v8::Isolate::GetCurrent();
	config_t* config;
	pathConfigDirectory += "global.ini";

	int result = config_open(&config, pathConfigDirectory.c_str(), CONFIG_OPEN_EXISTING);

	if (result != CONFIG_SUCCESS) {
		config = config_create(pathConfigDirectory.c_str());
	}

	for (int i = 0; i < generalSettings->Length(); i++) {
		Local<Object> generalSettingsObject = v8::Local<v8::Object>::Cast(generalSettings->Get(i));

		v8::String::Utf8Value param0(generalSettingsObject->Get(String::NewFromUtf8(isolate, "nameSubCategory")));
		std::string nameSubcategory = std::string(*param0);

		Local<Array> parameters = v8::Local<v8::Array>::Cast(generalSettingsObject->Get(String::NewFromUtf8(isolate, "parameters")));

		for (int j = 0; j < parameters->Length(); j++) {
			Local<Object> parameter = v8::Local<v8::Object>::Cast(parameters->Get(j));

			std::string name, type, value;

			v8::String::Utf8Value param0(parameter->Get(String::NewFromUtf8(isolate, "name")));
			name = std::string(*param0);

			v8::String::Utf8Value param1(parameter->Get(String::NewFromUtf8(isolate, "type")));
			type = std::string(*param1);

			if (type.compare("OBS_PROPERTY_LIST") == 0) {
				v8::String::Utf8Value param2(parameter->Get(String::NewFromUtf8(isolate, "currentValue")));
				value = std::string(*param2);
				config_set_string(config, "BasicWindow", name.c_str(), value.c_str());
			} else if (type.compare("OBS_PROPERTY_INT") == 0) {
				int64_t value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_int(config, "BasicWindow", name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_UINT") == 0) {
				uint64_t value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_uint(config, "BasicWindow", name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_BOOL") == 0) {
				uint64_t value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_bool(config, "BasicWindow", name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_DOUBLE") == 0) {
				double value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_double(config, "BasicWindow", name.c_str(), value);
			}
		}
	}
	config_save_safe(config, "tmp", nullptr);
}

Local<Array> OBS_settings::getStreamSettings() {
	Isolate *isolate = v8::Isolate::GetCurrent();

	bool isCategoryEnabled = !OBS_service::isStreamingOutputActive();

	obs_service_t* currentService = OBS_service::getService();
	obs_data_t* settings = obs_service_get_settings(currentService);

	Local<Array> streamSettings = Array::New(isolate);
	Local<Object> object = Object::New(isolate);

	Local<Array> subCategoryParametersStreamType = Array::New(isolate);

	Local<Object> streamType = Object::New(isolate);
	Local<Object> parameter = Object::New(isolate);

	streamType->Set(String::NewFromUtf8(isolate, "nameSubCategory"), String::NewFromUtf8(isolate, "Untitled"));
	streamType->Set(String::NewFromUtf8(isolate, "parameters"), subCategoryParametersStreamType);

	parameter->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "streamType"));

	parameter->Set(String::NewFromUtf8(isolate, "type"), String::NewFromUtf8(isolate, "OBS_PROPERTY_LIST"));

	int index = 0;
	const char* type;
	Local<Array> values = Array::New(isolate);
	while (obs_enum_service_types(index++, &type)) {
		Local<Object> parameterValue = Object::New(isolate);

		parameterValue->Set(String::NewFromUtf8(isolate, obs_service_get_display_name(type)),
			String::NewFromUtf8(isolate, type));

		values->Set(index - 1, parameterValue);
	}

	parameter->Set(String::NewFromUtf8(isolate, "values"), values);

	parameter->Set(String::NewFromUtf8(isolate, "description"), String::NewFromUtf8(isolate, "Stream Type"));

	const char* servType = obs_service_get_type(currentService);

	parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, obs_service_get_type(currentService)));

	parameter->Set(String::NewFromUtf8(isolate, "visible"), Integer::New(isolate, true));

	parameter->Set(String::NewFromUtf8(isolate, "enabled"), Integer::New(isolate, isCategoryEnabled));

	parameter->Set(String::NewFromUtf8(isolate, "masked"), Integer::New(isolate, false));

	streamSettings->Set(0, streamType);

	subCategoryParametersStreamType->Set(0, parameter);

	Local<Object> serviceConfiguration = Object::New(isolate);

	Local<Array> subCategoryParametersServiceConfiguration = Array::New(isolate);

	obs_properties_t* properties = obs_service_properties(currentService);
	obs_property_t* property = obs_properties_first(properties);
	obs_combo_format format;
	string formatString;

	index = 0;

	while (property) {
		Local<Object> parameter = Object::New(isolate);

		parameter->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, obs_property_name(property)));

		Local<Array> values = Array::New(isolate);
		int count = (int)obs_property_list_item_count(property);

		for (int i = 0; i < count; i++) {
			Local<Object> parameterValue = Object::New(isolate);

			//Value
			format = obs_property_list_format(property);

			if (format == OBS_COMBO_FORMAT_INT) {
				long long value = obs_property_list_item_int(property, i);
				parameterValue->Set(String::NewFromUtf8(isolate, obs_property_list_item_name(property, i)),
					Integer::New(isolate, value));
				formatString = "OBS_PROPERTY_INT";
			} else if (format == OBS_COMBO_FORMAT_FLOAT) {
				double value = obs_property_list_item_float(property, i);
				parameterValue->Set(String::NewFromUtf8(isolate, obs_property_list_item_name(property, i)),
					Integer::New(isolate, value));
				formatString = "OBS_PROPERTY_DOUBLE";
			} else if (format == OBS_COMBO_FORMAT_STRING) {
				const char* value = obs_property_list_item_string(property, i);
				parameterValue->Set(String::NewFromUtf8(isolate, obs_property_list_item_name(property, i)),
					String::NewFromUtf8(isolate, value));
				formatString = "OBS_PROPERTY_LIST";
			} else {
				cout << "INVALID FORMAT" << endl;
			}
			values->Set(i, parameterValue);
		}

		if (count == 0) {
			if (strcmp(obs_property_name(property), "key") == 0) {
				const char* stream_key = obs_service_get_key(currentService);
				formatString = "OBS_PROPERTY_EDIT_TEXT";

				if (stream_key != NULL) {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, stream_key));
				} else {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, ""));
				}
			}
			if (strcmp(obs_property_name(property), "show_all") == 0) {
				bool show_all = obs_data_get_bool(settings, "show_all");
				formatString = "OBS_PROPERTY_BOOL";
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Integer::New(isolate, show_all));
			}
			if (strcmp(obs_property_name(property), "server") == 0) {
				const char* server = obs_service_get_url(currentService);
				if (strcmp(obs_service_get_type(currentService), "rtmp_common") == 0) {
					formatString = "OBS_PROPERTY_LIST";
				} else {
					formatString = "OBS_PROPERTY_EDIT_TEXT";
				}

				if (server != NULL) {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, server));
				} else {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, ""));
				}
			}
			if (strcmp(obs_property_name(property), "username") == 0) {
				const char* username = obs_service_get_username(currentService);
				formatString = "OBS_PROPERTY_EDIT_TEXT";

				if (username != NULL) {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, username));
				} else {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, ""));
				}
			}
			if (strcmp(obs_property_name(property), "password") == 0) {
				const char* password = obs_service_get_password(currentService);
				formatString = "OBS_PROPERTY_EDIT_TEXT";

				if (password != NULL) {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, password));
				} else {
					parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, ""));
				}
			}
			if (strcmp(obs_property_name(property), "use_auth") == 0) {
				bool use_auth = obs_data_get_bool(settings, "use_auth");
				formatString = "OBS_PROPERTY_BOOL";
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Integer::New(isolate, use_auth));
			}
		} else {
			if (format == OBS_COMBO_FORMAT_INT) {
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Integer::New(isolate, obs_data_get_double(settings, obs_property_name(property))));
			} else if (format == OBS_COMBO_FORMAT_FLOAT) {
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), Number::New(isolate, obs_data_get_double(settings, obs_property_name(property))));
			} else if (format == OBS_COMBO_FORMAT_STRING) {
				parameter->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, obs_data_get_string(settings, obs_property_name(property))));
			}
			parameter->Set(String::NewFromUtf8(isolate, "values"), values);
		}
		v8::String::Utf8Value param1(parameter->Get(String::NewFromUtf8(isolate, "currentValue")));
		std::string current = std::string(*param1);

		parameter->Set(String::NewFromUtf8(isolate, "type"), String::NewFromUtf8(isolate, formatString.c_str()));

		parameter->Set(String::NewFromUtf8(isolate, "description"), String::NewFromUtf8(isolate, obs_property_description(property)));

		parameter->Set(String::NewFromUtf8(isolate, "visible"), Integer::New(isolate, obs_property_visible(property)));

		parameter->Set(String::NewFromUtf8(isolate, "enabled"), Integer::New(isolate, isCategoryEnabled));

		if (formatString.compare("OBS_PROPERTY_EDIT_TEXT") == 0 && obs_proprety_text_type(property) == OBS_TEXT_PASSWORD) {
			parameter->Set(String::NewFromUtf8(isolate, "masked"), Integer::New(isolate, true));
		} else {
			parameter->Set(String::NewFromUtf8(isolate, "masked"), Integer::New(isolate, false));
		}

		subCategoryParametersServiceConfiguration->Set(index, parameter);

		index++;
		obs_property_next(&property);
	}

	serviceConfiguration->Set(String::NewFromUtf8(isolate, "nameSubCategory"), String::NewFromUtf8(isolate, "Untitled"));
	serviceConfiguration->Set(String::NewFromUtf8(isolate, "parameters"), subCategoryParametersServiceConfiguration);

	streamSettings->Set(1, serviceConfiguration);

	return streamSettings;
}

void OBS_settings::saveStreamSettings(Local<Array> streamSettings) {
	Isolate *isolate = v8::Isolate::GetCurrent();

	obs_service_t* currentService = OBS_service::getService();

	obs_data_t* settings;

	std::string currentStreamType = obs_service_get_type(currentService);
	std::string newserviceTypeValue;

	std::string currentServiceName = obs_data_get_string(obs_service_get_settings(currentService), "service");

	for (int i = 0; i < streamSettings->Length(); i++) {
		Local<Object> streamSettingsCategory = v8::Local<v8::Object>::Cast(streamSettings->Get(i));

		v8::String::Utf8Value param0(streamSettingsCategory->Get(String::NewFromUtf8(isolate, "nameSubCategory")));
		std::string nameSubcategory = std::string(*param0);

		Local<Array> parameters = v8::Local<v8::Array>::Cast(streamSettingsCategory->Get(String::NewFromUtf8(isolate, "parameters")));

		bool serviceChanged = false;

		for (int j = 0; j < parameters->Length(); j++) {
			Local<Array> parameter = v8::Local<v8::Array>::Cast(parameters->Get(j));
			Local<Object> object;

			std::string name, type, value;

			object = v8::Local<v8::Object>::Cast(parameters->Get(j));
			v8::String::Utf8Value param0(object->Get(String::NewFromUtf8(isolate, "name")));

			name = std::string(*param0);
			object->Delete(String::NewFromUtf8(isolate, "name"));

			v8::String::Utf8Value param1(object->Get(String::NewFromUtf8(isolate, "type")));

			type = std::string(*param1);
			object->Delete(String::NewFromUtf8(isolate, "type"));
			const char *servName;
			if (type.compare("OBS_PROPERTY_LIST") == 0 ||
				type.compare("OBS_PROPERTY_EDIT_TEXT") == 0) {
				v8::String::Utf8Value param2(object->Get(String::NewFromUtf8(isolate, "currentValue")));
				value = std::string(*param2);

				if (name.compare("streamType") == 0) {
					newserviceTypeValue = value;
					settings = obs_service_defaults(newserviceTypeValue.c_str());
				} else if (name.compare("service") == 0 && value.compare(currentServiceName) != 0) {
					serviceChanged = true;
				}

				object = v8::Local<v8::Object>::Cast(parameters->Get(0));
				v8::String::Utf8Value param(object->Get(String::NewFromUtf8(isolate, "value")));

				std::string serviceTypeName = std::string(*param);

				if (name.compare("server") == 0 && serviceChanged) {
					obs_service_t *newService = obs_service_create(newserviceTypeValue.c_str(),
						"service", settings, NULL);

					obs_properties_t* properties = obs_service_properties(newService);
					obs_property_t* property = obs_properties_first(properties);

					while (property) {
						int count = (int)obs_property_list_item_count(property);
						const char *nameProperty = obs_property_name(property);
						if (strcmp(nameProperty, "server") == 0) {
							value = obs_property_list_item_string(property, 0);
							break;
						}

						obs_property_next(&property);
					}
				}

				obs_data_set_string(settings, name.c_str(), value.c_str());
				object->Delete(String::NewFromUtf8(isolate, "currentValue"));
			} else if (type.compare("OBS_PROPERTY_INT") == 0 ||
				type.compare("OBS_PROPERTY_UINT") == 0) {
				int64_t value = object->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				cout << "value " << value << endl;
				obs_data_set_int(settings, name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_BOOL") == 0) {
				uint64_t value = object->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				cout << "value " << value << endl;
				obs_data_set_bool(settings, name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_DOUBLE") == 0) {
				double value = object->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				cout << "value " << value << endl;
				obs_data_set_double(settings, name.c_str(), value);
			}
		}
	}
	if (currentStreamType.compare(newserviceTypeValue) != 0) {
		//Stream type value has changed
		settings = obs_service_defaults(newserviceTypeValue.c_str());
	}

	obs_data_t *data = obs_data_create();

	obs_data_t *hotkeyData = obs_hotkeys_save_service(currentService);

	obs_service_t *newService = obs_service_create(newserviceTypeValue.c_str(),
		"default_service", settings, hotkeyData);

	obs_data_release(hotkeyData);

	OBS_service::setService(newService);

	obs_data_set_string(data, "type", obs_service_get_type(newService));
	obs_data_set_obj(data, "settings", settings);

	if (!obs_data_save_json_safe(data, OBS_API::getServiceConfigPath().c_str(), "tmp", "bak")) {
		blog(LOG_WARNING, "Failed to save service");
	}
}

vector<std::string> OBS_settings::getStreamTypesForStreamSettings(void) {
	vector<std::string> listStreamTypes;

	const char    *type;
	size_t        index = 0;

	if (tabStreamTypes.size() != 0) {
		tabStreamTypes.clear();
	}

	while (obs_enum_service_types(index++, &type)) {
		tabStreamTypes.push_back(type);
		listStreamTypes.push_back(obs_service_get_display_name(type));
	}

	return listStreamTypes;
}

void OBS_settings::setStreamTypeForStreamSettings(const char* streamTypeDisplayName) {
	obs_service_t* newService;

	const char* streamType = "";
	int index = 0;

	while (index < tabStreamTypes.size()) {
		if (strcmp(obs_service_get_display_name(tabStreamTypes.at(index)), streamTypeDisplayName) == 0) {
			streamType = tabStreamTypes.at(index);
		}
		index++;
	}

	newService = obs_service_create(streamType, "default_service", nullptr, nullptr);

	OBS_service::setService(newService);
}

void OBS_settings::getServices(void) {}

static bool EncoderAvailable(const char *encoder) {
	const char *val;
	int i = 0;

	while (obs_enum_encoder_types(i++, &val)) {
		if (strcmp(val, encoder) == 0)
			return true;
	}

	return false;
}

Local<Array> OBS_settings::getOutputSettings() {
	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Array> outputSettings = Array::New(isolate);

	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	std::vector<std::vector<std::pair<std::string, std::string>>> entries;

	//Untitled
	Local<Array> subCategoryParametersUntitled = Array::New(isolate);

	Local<Object> untitledObject = Object::New(isolate);

	untitledObject->Set(String::NewFromUtf8(isolate, "nameSubCategory"), String::NewFromUtf8(isolate, "Untitled"));

	Local<Object> simple = Object::New(isolate);
	simple->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "outputMode"));
	simple->Set(String::NewFromUtf8(isolate, "type"), String::NewFromUtf8(isolate, "OBS_PROPERTY_LIST"));
	simple->Set(String::NewFromUtf8(isolate, "currentValue"), String::NewFromUtf8(isolate, "Simple"));
	simple->Set(String::NewFromUtf8(isolate, "description"), String::NewFromUtf8(isolate, "Output Mode"));
	simple->Set(String::NewFromUtf8(isolate, "visible"), Integer::New(isolate, true));
	simple->Set(String::NewFromUtf8(isolate, "enabled"), Integer::New(isolate, true));
	simple->Set(String::NewFromUtf8(isolate, "masked"), Integer::New(isolate, false));

	Local<Array> values = Array::New(isolate);

	Local<Object> simpleMode = Object::New(isolate);
	simpleMode->Set(String::NewFromUtf8(isolate, "Simple"), String::NewFromUtf8(isolate, "Simple"));
	// Local<Object> advancedMode = Object::New(isolate);
	// advancedMode->Set(String::NewFromUtf8(isolate, "Advanced"), String::NewFromUtf8(isolate, "Advanced"));

	values->Set(0, simpleMode);
	// values->Set(1, advancedMode);

	simple->Set(String::NewFromUtf8(isolate, "values"), values);

	subCategoryParametersUntitled->Set(0, simple);

	untitledObject->Set(String::NewFromUtf8(isolate, "parameters"), subCategoryParametersUntitled);

	outputSettings->Set(0, untitledObject);
	entries.clear();

	//Streaming

	//Video Bitrate
	std::vector<std::pair<std::string, std::string>> vBitrate;
	vBitrate.push_back(std::make_pair("name", "VBitrate"));
	vBitrate.push_back(std::make_pair("type", "OBS_PROPERTY_INT"));
	vBitrate.push_back(std::make_pair("description", "Video Bitrate"));
	entries.push_back(vBitrate);

	//Encoder
	std::vector<std::pair<std::string, std::string>> streamEncoder;
	streamEncoder.push_back(std::make_pair("name", "StreamEncoder"));
	streamEncoder.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	streamEncoder.push_back(std::make_pair("description", "Encoder"));

	streamEncoder.push_back(std::make_pair("Software (x264)", "x264"));
	if (EncoderAvailable("obs_qsv11")) {
		streamEncoder.push_back(std::make_pair("QSV", "qsv"));
	}

	if (EncoderAvailable("ffmpeg_nvenc")) {
		streamEncoder.push_back(std::make_pair("NVENC", "nvenc"));
	}
	if (EncoderAvailable("amd_amf_h264")) {
		streamEncoder.push_back(std::make_pair("AMD", "amd"));
	}

	entries.push_back(streamEncoder);

	//Audio Bitrate
	std::vector<std::pair<std::string, std::string>> aBitrate;
	aBitrate.push_back(std::make_pair("name", "ABitrate"));
	aBitrate.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	aBitrate.push_back(std::make_pair("description", "Audio Bitrate"));


	auto &bitrateMap = GetAACEncoderBitrateMap();
	for (auto &entry : bitrateMap)
		aBitrate.push_back(std::make_pair(std::to_string(entry.first), std::to_string(entry.first)));

	entries.push_back(aBitrate);

	//Enable Advanced Encoder Settings
	std::vector<std::pair<std::string, std::string>> useAdvanced;
	useAdvanced.push_back(std::make_pair("name", "UseAdvanced"));
	useAdvanced.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	useAdvanced.push_back(std::make_pair("description", "Enable Advanced Encoder Settings"));
	entries.push_back(useAdvanced);

	if (config_get_bool(config, "SimpleOutput", "UseAdvanced")) {
		//Enforce streaming service bitrate limits
		std::vector<std::pair<std::string, std::string>> enforceBitrate;
		enforceBitrate.push_back(std::make_pair("name", "EnforceBitrate"));
		enforceBitrate.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
		enforceBitrate.push_back(std::make_pair("description", "Enforce streaming service bitrate limits"));
		entries.push_back(enforceBitrate);

		//Encoder Preset
		const char* defaultPreset;
		const char* encoder = config_get_string(config, "SimpleOutput", "StreamEncoder");

		std::vector<std::pair<std::string, std::string>> preset;

		if (strcmp(encoder, SIMPLE_ENCODER_QSV) == 0) {
			preset.push_back(std::make_pair("name", "QSVPreset"));
			preset.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
			preset.push_back(std::make_pair("description", "Encoder Preset (higher = less CPU)"));

			preset.push_back(std::make_pair("Speed", "speed"));
			preset.push_back(std::make_pair("Balanced", "balanced"));
			preset.push_back(std::make_pair("Quality", "quality"));

			defaultPreset = "balanced";
			// preset = curQSVPreset;

		} else if (strcmp(encoder, SIMPLE_ENCODER_NVENC) == 0) {
			preset.push_back(std::make_pair("name", "NVENCPreset"));
			preset.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
			preset.push_back(std::make_pair("description", "Encoder Preset (higher = less CPU)"));

			obs_properties_t *props =
				obs_get_encoder_properties("ffmpeg_nvenc");

			obs_property_t *p = obs_properties_get(props, "preset");
			size_t num = obs_property_list_item_count(p);
			for (size_t i = 0; i < num; i++) {
				const char *name = obs_property_list_item_name(p, i);
				const char *val = obs_property_list_item_string(p, i);

				/* bluray is for ideal bluray disc recording settings,
				 * not streaming */
				if (strcmp(val, "bd") == 0)
					continue;
				/* lossless should of course not be used to stream */
				if (astrcmp_n(val, "lossless", 8) == 0)
					continue;

				preset.push_back(std::make_pair(name, val));
			}

			obs_properties_destroy(props);

			defaultPreset = "default";
			// preset = curNVENCPreset;

		} else if (strcmp(encoder, SIMPLE_ENCODER_AMD) == 0) {
			preset.push_back(std::make_pair("name", "AMDPreset"));
			preset.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
			preset.push_back(std::make_pair("description", "Encoder Preset (higher = less CPU)"));

			preset.push_back(std::make_pair("Speed", "speed"));
			preset.push_back(std::make_pair("Balanced", "balanced"));
			preset.push_back(std::make_pair("Quality", "quality"));

			defaultPreset = "balanced";
			// preset = curAMDPreset;
		} else {
			preset.push_back(std::make_pair("name", "Preset"));
			preset.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
			preset.push_back(std::make_pair("description", "Encoder Preset (higher = less CPU)"));

			preset.push_back(std::make_pair("ultrafast", "ultrafast"));
			preset.push_back(std::make_pair("superfast", "superfast"));
			preset.push_back(std::make_pair("veryfast", "veryfast"));
			preset.push_back(std::make_pair("faster", "faster"));
			preset.push_back(std::make_pair("fast", "fast"));
			preset.push_back(std::make_pair("medium", "medium"));
			preset.push_back(std::make_pair("slow", "slow"));
			preset.push_back(std::make_pair("slower", "slower"));

			defaultPreset = "veryfast";
			// preset = curPreset;
		}

		entries.push_back(preset);

		//Custom Encoder Settings
		std::vector<std::pair<std::string, std::string>> x264opts;
		x264opts.push_back(std::make_pair("name", "x264Settings"));
		x264opts.push_back(std::make_pair("type", "OBS_PROPERTY_EDIT_TEXT"));
		x264opts.push_back(std::make_pair("description", "Custom Encoder Settings"));
		entries.push_back(x264opts);
	}

	outputSettings->Set(1, serializeSettingsData("Streaming", entries, config, "SimpleOutput", true, true));
	entries.clear();

	//Recording

	//Recording Path
	std::vector<std::pair<std::string, std::string>> filePath;
	filePath.push_back(std::make_pair("name", "FilePath"));
	filePath.push_back(std::make_pair("type", "OBS_PROPERTY_PATH"));
	filePath.push_back(std::make_pair("description", "Recording Path"));
	entries.push_back(filePath);

	//Generate File Name without Space
	std::vector<std::pair<std::string, std::string>> fileNameWithoutSpace;
	fileNameWithoutSpace.push_back(std::make_pair("name", "FileNameWithoutSpace"));
	fileNameWithoutSpace.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	fileNameWithoutSpace.push_back(std::make_pair("description", "Generate File Name without Space"));
	entries.push_back(fileNameWithoutSpace);

	//Recording Quality
	std::vector<std::pair<std::string, std::string>> recQuality;
	recQuality.push_back(std::make_pair("name", "RecQuality"));
	recQuality.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	recQuality.push_back(std::make_pair("description", "Recording Quality"));
	recQuality.push_back(std::make_pair("Same as stream", "Same as stream"));
	recQuality.push_back(std::make_pair("High Quality, Medium File Size", "High Quality, Medium File Size"));
	recQuality.push_back(std::make_pair("Indistinguishable Quality, Large File Size", "Indistinguishable Quality, Large File Size"));
	recQuality.push_back(std::make_pair("Lossless Quality, Tremendously Large File Size", "Lossless Quality, Tremendously Large File Size"));
	entries.push_back(recQuality);

	//Recording Format
	std::vector<std::pair<std::string, std::string>> recFormat;
	recFormat.push_back(std::make_pair("name", "RecFormat"));
	recFormat.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	recFormat.push_back(std::make_pair("description", "Recording Format"));
	recFormat.push_back(std::make_pair("flv", "flv"));
	recFormat.push_back(std::make_pair("mp4", "mp4"));
	recFormat.push_back(std::make_pair("mov", "mov"));
	recFormat.push_back(std::make_pair("mkv", "mkv"));
	recFormat.push_back(std::make_pair("ts", "ts"));
	recFormat.push_back(std::make_pair("m3u8", "m3u8"));
	entries.push_back(recFormat);

	//Custom Muxer Settings
	std::vector<std::pair<std::string, std::string>> muxerCustom;
	muxerCustom.push_back(std::make_pair("name", "MuxerCustom"));
	muxerCustom.push_back(std::make_pair("type", "OBS_PROPERTY_EDIT_TEXT"));
	muxerCustom.push_back(std::make_pair("description", "Custom Muxer Settings"));
	entries.push_back(muxerCustom);

	//Enable Replay Buffer
	std::vector<std::pair<std::string, std::string>> recRB;
	recRB.push_back(std::make_pair("name", "RecRB"));
	recRB.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	recRB.push_back(std::make_pair("description", "Enable Replay Buffer"));
	entries.push_back(recRB);

	outputSettings->Set(2, serializeSettingsData("Recording", entries, config, "SimpleOutput", true, true));

	return outputSettings;
}

void OBS_settings::saveOutputSettings(Local<Array> streamSettings) {

}

vector<const char*>  OBS_settings::getOutputSimpleStreamingSettings(void) {
	vector<const char*> listOutputSimpleStreamingSettings;

	config_t* config;
	config_open(&config, "./config/basic.ini", CONFIG_OPEN_EXISTING);

	int videoBitrate = config_get_uint(config, "SimpleOutput",
		"VBitrate");
	const char *streamEnc = config_get_string(config, "SimpleOutput",
		"StreamEncoder");
	int audioBitrate = config_get_uint(config, "SimpleOutput",
		"ABitrate");
	bool advanced = config_get_bool(config, "SimpleOutput",
		"UseAdvanced");
	bool enforceBitrate = config_get_bool(config, "SimpleOutput",
		"EnforceBitrate");
	const char *preset = config_get_string(config, "SimpleOutput",
		"Preset");
	const char *qsvPreset = config_get_string(config, "SimpleOutput",
		"QSVPreset");
	const char *nvPreset = config_get_string(config, "SimpleOutput",
		"NVENCPreset");
	const char* amdPreset = config_get_string(config, "SimpleOutput",
		"AMDPreset");
	const char *custom = config_get_string(config, "SimpleOutput",
		"x264Settings");

	string videoBitrateString = std::to_string(videoBitrate);
	char * videoBitrate_str = new char[videoBitrateString.size() + 1];
	std::copy(videoBitrateString.begin(), videoBitrateString.end(), videoBitrate_str);
	videoBitrate_str[videoBitrateString.size()] = '\0';
	listOutputSimpleStreamingSettings.push_back(videoBitrate_str);

	listOutputSimpleStreamingSettings.push_back(streamEnc);

	string audioBitrateString = std::to_string(audioBitrate);
	char * audioBitrate_str = new char[audioBitrateString.size() + 1];
	std::copy(audioBitrateString.begin(), audioBitrateString.end(), audioBitrate_str);
	audioBitrate_str[audioBitrateString.size()] = '\0';
	listOutputSimpleStreamingSettings.push_back(audioBitrate_str);

	listOutputSimpleStreamingSettings.push_back(advanced ? "true" : "false");
	listOutputSimpleStreamingSettings.push_back(enforceBitrate ? "true" : "false");
	listOutputSimpleStreamingSettings.push_back(preset);
	listOutputSimpleStreamingSettings.push_back(qsvPreset);
	listOutputSimpleStreamingSettings.push_back(nvPreset);
	listOutputSimpleStreamingSettings.push_back(amdPreset);
	listOutputSimpleStreamingSettings.push_back(custom);

	return listOutputSimpleStreamingSettings;

	vector<const char*> listAvailableEncoders;

	listAvailableEncoders.push_back("Software (Xx264)");

	if (EncoderAvailable("obs_qsv11")) {
		listAvailableEncoders.push_back("QSV");
	}

	if (EncoderAvailable("ffmpeg_nvenc")) {
		listAvailableEncoders.push_back("NVENC");
	}
	if (EncoderAvailable("amd_amf_h264")) {
		listAvailableEncoders.push_back("AMD");
	}

}

void OBS_settings::saveOutputSimpleStreamingSettings(int videoBitrate, const char* streamEnc,
	int audioBitrate, bool advanced,
	bool enforceBitrate, const char* preset,
	const char* qsvPreset, const char* nvPreset,
	const char* amdPreset, const char* custom) {
	config_t* config;
	config_open(&config, "./config/basic.ini", CONFIG_OPEN_EXISTING);

	config_set_uint(config, "SimpleOutput", "VBitrate", videoBitrate);
	config_set_string(config, "SimpleOutput", "StreamEncoder", streamEnc);
	config_set_uint(config, "SimpleOutput", "ABitrate", audioBitrate);
	config_set_bool(config, "SimpleOutput", "UseAdvanced", advanced);
	config_set_bool(config, "SimpleOutput", "EnforceBitrate", enforceBitrate);
	config_set_string(config, "SimpleOutput", "Preset", preset);
	config_set_string(config, "SimpleOutput", "QSVPreset", qsvPreset);
	config_set_string(config, "SimpleOutput", "NVENCPreset", nvPreset);
	config_set_string(config, "SimpleOutput", "AMDPreset", amdPreset);
	config_set_string(config, "SimpleOutput", "x264Settings", custom);

	config_save_safe(config, "tmp", nullptr);
}

vector<const char*>  OBS_settings::getOutputSimpleRecordingSettings(void) {
	vector<const char*> listOutputSimpleRecordingSettings;

	/*const char *path = config_get_string(main->Config(), "SimpleOutput",
			"FilePath");
	bool noSpace = config_get_bool(main->Config(), "SimpleOutput",
			"FileNameWithoutSpace");
	const char *format = config_get_string(main->Config(), "SimpleOutput",
			"RecFormat");
	const char *recQual = config_get_string(main->Config(), "SimpleOutput",
			"RecQuality");
	const char *recEnc = config_get_string(main->Config(), "SimpleOutput",
			"RecEncoder");
	const char *muxCustom = config_get_string(main->Config(),
			"SimpleOutput", "MuxerCustom");

	listOutputSimpleRecordingSettings.push_back(path);
	listOutputSimpleRecordingSettings.push_back(noSpace ? "true" : "false");
	listOutputSimpleRecordingSettings.push_back(format);
	listOutputSimpleRecordingSettings.push_back(recQual);
	listOutputSimpleRecordingSettings.push_back(recEnc);
	listOutputSimpleRecordingSettings.push_back(muxCustom);

	return listOutputSimpleRecordingSettings;

	/*vector<const char*> quality = NULL;

	quality.push_back("Same as stream");
	quality.push_back("High Quality, Medium File Size");
	quality.push_back("Indistinguishable Quality, Large File Size");
	quality.push_back("Lossless Quality, Tremendously Large File Size");

	vector<const char*> outputFormat = NULL;
	outputFormat.push_back("flv");
	outputFormat.push_back("mp4");
	outputFormat.push_back("mov");
	outputFormat.push_back("mkv");
	outputFormat.push_back("ts");
	outputFormat.push_back("m3u8");*/
	return listOutputSimpleRecordingSettings;
}

void OBS_settings::saveOutputSimpleRecordingSettings(void) {

}

vector<const char*>  OBS_settings::getOutputAdvancedStreamingSettings(void) {
	return vector<const char*>();
}

void OBS_settings::saveOutputAdvancedStreamingSettings(void) {

}

vector<const char*>  OBS_settings::getOutputAdvancedRecordingSettings(void) {
	return vector<const char*>();
}

void OBS_settings::saveOutputAdvancedRecordingSettings(void) {

}

vector<const char*>  OBS_settings::getOutputAdvancedAudioSettings(void) {
	return vector<const char*>();
}

void OBS_settings::saveOutputAdvancedAudioSettings(void) {

}

static void LoadListValues(obs_property_t *prop, int index, std::vector<std::pair<std::string, std::string>>* listValues) {
	size_t count = obs_property_list_item_count(prop);

	obs_source_t *source = obs_get_output_source(index);
	const char *deviceId = nullptr;
	obs_data_t *settings = nullptr;

	if (source) {
		settings = obs_source_get_settings(source);
		if (settings)
			deviceId = obs_data_get_string(settings, "device_id");
	}

	for (size_t i = 0; i < count; i++) {
		std::string name = obs_property_list_item_name(prop, i);
		std::string val = obs_property_list_item_string(prop, i);
		listValues->push_back(std::make_pair(name, val));
	}

	if (settings)
		obs_data_release(settings);
	if (source)
		obs_source_release(source);
}

static void LoadAudioDevices(std::vector<std::pair<std::string, std::string>>* desktopAudioDevice,
	std::vector<std::pair<std::string, std::string>>* desktopAudioDevice2,
	std::vector<std::pair<std::string, std::string>>* auxAudioDevice,
	std::vector<std::pair<std::string, std::string>>* auxAudioDevice2,
	std::vector<std::pair<std::string, std::string>>* auxAudioDevice3) {
	const char *input_id = "wasapi_input_capture";
	const char *output_id = "wasapi_output_capture";

	obs_properties_t *input_props = obs_get_source_properties(input_id);
	obs_properties_t *output_props = obs_get_source_properties(output_id);

	if (output_props) {
		obs_property_t *outputs = obs_properties_get(output_props,
			"device_id");
		LoadListValues(outputs, 1, desktopAudioDevice);
		LoadListValues(outputs, 2, desktopAudioDevice2);
		obs_properties_destroy(output_props);
	}

	if (input_props) {
		obs_property_t *inputs = obs_properties_get(input_props,
			"device_id");
		LoadListValues(inputs, 3, auxAudioDevice);
		LoadListValues(inputs, 4, auxAudioDevice2);
		LoadListValues(inputs, 5, auxAudioDevice3);
		obs_properties_destroy(input_props);
	}
}

Local<Array> OBS_settings::getAudioSettings() {
	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Array> audioSettings = Array::New(isolate);

	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	std::vector<std::vector<std::pair<std::string, std::string>>> entries;

	//Untitled

	//Sample Rate
	std::vector<std::pair<std::string, std::string>> sampleRate;
	sampleRate.push_back(std::make_pair("name", "SampleRate"));
	sampleRate.push_back(std::make_pair("type", "OBS_PROPERTY_UINT"));
	sampleRate.push_back(std::make_pair("description", "Sample Rate"));
	entries.push_back(sampleRate);

	//Channels
	std::vector<std::pair<std::string, std::string>> channelSetup;
	channelSetup.push_back(std::make_pair("name", "ChannelSetup"));
	channelSetup.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	channelSetup.push_back(std::make_pair("description", "Channels"));
	channelSetup.push_back(std::make_pair("Mono", "Mono"));
	channelSetup.push_back(std::make_pair("Stereo", "Stereo"));
	entries.push_back(channelSetup);

	//Desktop Audio Device
	std::vector<std::pair<std::string, std::string>> desktopAudioDevice;
	desktopAudioDevice.push_back(std::make_pair("name", "Desktop Audio"));
	desktopAudioDevice.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	desktopAudioDevice.push_back(std::make_pair("description", "Desktop Audio Device"));

	//Desktop Audio Device 2
	std::vector<std::pair<std::string, std::string>> desktopAudioDevice2;
	desktopAudioDevice2.push_back(std::make_pair("name", "Desktop Audio 2"));
	desktopAudioDevice2.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	desktopAudioDevice2.push_back(std::make_pair("description", "Desktop Audio Device 2"));

	//Mic/Auxiliary Audio Device
	std::vector<std::pair<std::string, std::string>> auxAudioDevice;
	auxAudioDevice.push_back(std::make_pair("name", "Mic/Aux"));
	auxAudioDevice.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	auxAudioDevice.push_back(std::make_pair("description", "Mic/Auxiliary Audio Device"));

	//Mic/Auxiliary Audio Device 2
	std::vector<std::pair<std::string, std::string>> auxAudioDevice2;
	auxAudioDevice2.push_back(std::make_pair("name", "Mic/Aux 2"));
	auxAudioDevice2.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	auxAudioDevice2.push_back(std::make_pair("description", "Mic/Auxiliary Audio Device 2"));

	//Mic/Auxiliary Audio Device 3
	std::vector<std::pair<std::string, std::string>> auxAudioDevice3;
	auxAudioDevice3.push_back(std::make_pair("name", "Mic/Aux 3"));
	auxAudioDevice3.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	auxAudioDevice3.push_back(std::make_pair("description", "Mic/Auxiliary Audio Device 3"));

	LoadAudioDevices(&desktopAudioDevice, &desktopAudioDevice2,
		&auxAudioDevice, &auxAudioDevice2, &auxAudioDevice3);

	entries.push_back(desktopAudioDevice);
	entries.push_back(desktopAudioDevice2);
	entries.push_back(auxAudioDevice);
	entries.push_back(auxAudioDevice2);
	entries.push_back(auxAudioDevice3);

	audioSettings->Set(0, serializeSettingsData("Untitled", entries, config, "Audio", true, true));
	entries.clear();

	return audioSettings;
}

void resetAudioDevice(const char *sourceId, const char *deviceId,
	const char *deviceDesc, int channel) {
	obs_source_t *source;
	obs_data_t *settings;
	bool same = false;

	source = obs_get_output_source(channel);
	if (source) {
		settings = obs_source_get_settings(source);
		const char *curId = obs_data_get_string(settings, "device_id");

		same = (strcmp(curId, deviceId) == 0);

		obs_data_release(settings);
		obs_source_release(source);
	}

	if (!same)
		obs_set_output_source(channel, nullptr);

	if (!same && strcmp(deviceId, "disabled") != 0) {
		obs_data_t *settings = obs_data_create();
		obs_data_set_string(settings, "device_id", deviceId);
		source = obs_source_create(sourceId, deviceDesc, settings,
			nullptr);
		obs_data_release(settings);

		obs_set_output_source(channel, source);
		obs_source_release(source);
	}
}

void OBS_settings::saveAudioSettings(Local<Array> audioSettings) {
	Isolate *isolate = v8::Isolate::GetCurrent();

	Local<Object> audioSettingsObject = v8::Local<v8::Object>::Cast(audioSettings->Get(0));
	Local<Array> parameters = v8::Local<v8::Array>::Cast(audioSettingsObject->Get(String::NewFromUtf8(isolate, "parameters")));

	std::string audioType;

	for (int i = 2; i < parameters->Length(); i++) {
		Local<Object> audioDevice = v8::Local<v8::Object>::Cast(parameters->Get(i));

		v8::String::Utf8Value param0(audioDevice->Get(String::NewFromUtf8(isolate, "name")));
		v8::String::Utf8Value param1(audioDevice->Get(String::NewFromUtf8(isolate, "currentValue")));

		std::string name = std::string(*param0);
		std::string currentValue = std::string(*param1);

		if (i < 4)
			audioType = "wasapi_output_capture";
		else
			audioType = "wasapi_input_capture";

		resetAudioDevice(audioType.c_str(), currentValue.c_str(), name.c_str(), i);
	}
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

static string ResString(uint32_t cx, uint32_t cy) {
	ostringstream res;
	res << cx << "x" << cy;
	return res.str();
}

static inline void LoadFPSCommon(config_t* config) {
	const char *val = config_get_string(config, "Video", "FPSCommon");
}

static inline void LoadFPSInteger(config_t* config) {
	uint32_t val = config_get_uint(config, "Video", "FPSInt");
}

static inline void LoadFPSFraction(config_t* config) {
	uint32_t num = config_get_uint(config, "Video", "FPSNum");
	uint32_t den = config_get_uint(config, "Video", "FPSDen");
}

Local<Array>  OBS_settings::getVideoSettings() {
	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Array> videoSettings = Array::New(isolate);

	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	bool isCategoryEnabled = !OBS_service::isStreamingOutputActive();

	std::vector<std::vector<std::pair<std::string, std::string>>> entries;

	//Base (Canvas) Resolution
	std::vector<std::pair<std::string, std::string>> baseResolution;
	baseResolution.push_back(std::make_pair("name", "Base"));
	baseResolution.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	baseResolution.push_back(std::make_pair("description", "Base (Canvas) Resolution"));

	uint32_t base_cx = config_get_uint(config, "Video", "BaseCX");
	uint32_t base_cy = config_get_uint(config, "Video", "BaseCY");

	std::string baseResolutionString = ResString(base_cx, base_cy);

	baseResolution.push_back(std::make_pair("1920x1080", "1920x1080"));
	baseResolution.push_back(std::make_pair("1280x720", "1280x720"));

	std::vector<Screen> resolutions = OBS_API::availableResolutions();

	// Fill available display resolutions
	for (int i = 0; i < resolutions.size(); i++) {
		std::string baseResolutionString;
		baseResolutionString = to_string(resolutions.at(i).width);
		baseResolutionString += "x";
		baseResolutionString += to_string(resolutions.at(i).height);

		pair<std::string, std::string> newBaseResolution = std::make_pair(baseResolutionString.c_str(), baseResolutionString.c_str());

		std::vector<pair<std::string, std::string>>::iterator it =
			std::find_if(baseResolution.begin(), baseResolution.end(),
				[&baseResolutionString](const pair<std::string, std::string> value) {
			return (value.second.compare(baseResolutionString) == 0);
		});

		if (baseResolution.size() == 3 || it == baseResolution.end()) {
			baseResolution.push_back(newBaseResolution);
		}
	}

	// Set the current base resolution selected by the user
	pair<std::string, std::string> newBaseResolution = std::make_pair("currentValue", baseResolutionString);

	//Check if the current resolution is in the available ones
	std::vector<pair<std::string, std::string>>::iterator it =
		std::find_if(baseResolution.begin(), baseResolution.end(),
			[&baseResolutionString](const pair<std::string, std::string> value) {
		return (value.second.compare(baseResolutionString) == 0);
	});

	if (it == baseResolution.end()) {
		baseResolution.push_back(std::make_pair(baseResolutionString.c_str(), baseResolutionString.c_str()));
	}

	int indexFirstValue = 3;
	baseResolution.insert(baseResolution.begin() + indexFirstValue, newBaseResolution);

	entries.push_back(baseResolution);

	std::vector<std::pair<std::string, std::string>> outputResolution;
	outputResolution.push_back(std::make_pair("name", "Output"));
	outputResolution.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	outputResolution.push_back(std::make_pair("description", "Output (Scaled) Resolution"));

	uint32_t out_cx = config_get_uint(config, "Video", "OutputCX");
	uint32_t out_cy = config_get_uint(config, "Video", "OutputCY");

	std::string outputResString = ResString(out_cx, out_cy);

	outputResolution.push_back(std::make_pair("currentValue", outputResString));

	for (size_t idx = 0; idx < numVals; idx++) {
		uint32_t outDownscaleCX = uint32_t(double(base_cx) / vals[idx]);
		uint32_t outDownscaleCY = uint32_t(double(base_cy) / vals[idx]);

		string outRes = ResString(outDownscaleCX, outDownscaleCY);

		outputResolution.push_back(std::make_pair(outRes, outRes)); // !!!
	}

	entries.push_back(outputResolution);

	//Downscale Filter
	std::vector<std::pair<std::string, std::string>> scaleType;
	scaleType.push_back(std::make_pair("name", "ScaleType"));
	scaleType.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	scaleType.push_back(std::make_pair("description", "Downscale Filter"));
	scaleType.push_back(std::make_pair("bilinear", "Bilinear (Fastest, but blurry if scaling)"));
	scaleType.push_back(std::make_pair("bicubic", "Bicubic (Sharpened scaling, 16 samples"));
	scaleType.push_back(std::make_pair("lanczos", "Lanczos (Sharpened scaling, 32 samples)"));
	entries.push_back(scaleType);

	//FPS Type
	std::vector<std::pair<std::string, std::string>> fpsType;
	fpsType.push_back(std::make_pair("name", "FPSType"));
	fpsType.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	fpsType.push_back(std::make_pair("description", "FPS Type"));

	uint32_t fpsTypeValue = config_get_uint(config, "Video", "FPSType");

	if (fpsTypeValue == 0) {
		fpsType.push_back(std::make_pair("currentValue", "Common FPS Values"));
		fpsType.push_back(std::make_pair("Common FPS Values", "Common FPS Values"));
		fpsType.push_back(std::make_pair("Integer FPS Value", "Integer FPS Value"));
		fpsType.push_back(std::make_pair("Fractional FPS Value", "Fractional FPS Value"));
		entries.push_back(fpsType);

		//Common FPS Values
		std::vector<std::pair<std::string, std::string>> fpsCommon;
		fpsCommon.push_back(std::make_pair("name", "FPSCommon"));
		fpsCommon.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
		fpsCommon.push_back(std::make_pair("description", "Common FPS Values"));
		fpsCommon.push_back(std::make_pair("10", "10"));
		fpsCommon.push_back(std::make_pair("20", "20"));
		fpsCommon.push_back(std::make_pair("24 NTSC", "24 NTSC"));
		fpsCommon.push_back(std::make_pair("29.97", "29.97"));
		fpsCommon.push_back(std::make_pair("30", "30"));
		fpsCommon.push_back(std::make_pair("48", "48"));
		fpsCommon.push_back(std::make_pair("59.94", "59.94"));
		fpsCommon.push_back(std::make_pair("60", "60"));
		entries.push_back(fpsCommon);
	} else if (fpsTypeValue == 1) {
		fpsType.push_back(std::make_pair("currentValue", "Integer FPS Value"));
		fpsType.push_back(std::make_pair("Common FPS Values", "Common FPS Values"));
		fpsType.push_back(std::make_pair("Integer FPS Value", "Integer FPS Value"));
		fpsType.push_back(std::make_pair("Fractional FPS Value", "Fractional FPS Value"));
		entries.push_back(fpsType);

		std::vector<std::pair<std::string, std::string>> fpsInt;
		fpsInt.push_back(std::make_pair("name", "FPSInt"));
		fpsInt.push_back(std::make_pair("type", "OBS_PROPERTY_UINT"));
		fpsInt.push_back(std::make_pair("description", "Integer FPS Value"));
		entries.push_back(fpsInt);
	} else if (fpsTypeValue == 2) {
		fpsType.push_back(std::make_pair("currentValue", "Fractional FPS Value"));
		fpsType.push_back(std::make_pair("Common FPS Values", "Common FPS Values"));
		fpsType.push_back(std::make_pair("Integer FPS Value", "Integer FPS Value"));
		fpsType.push_back(std::make_pair("Fractional FPS Value", "Fractional FPS Value"));
		entries.push_back(fpsType);

		std::vector<std::pair<std::string, std::string>> fpsNum;
		fpsNum.push_back(std::make_pair("name", "FPSNum"));
		fpsNum.push_back(std::make_pair("type", "OBS_PROPERTY_UINT"));
		fpsNum.push_back(std::make_pair("description", "FPSNum"));
		entries.push_back(fpsNum);

		std::vector<std::pair<std::string, std::string>> fpsDen;
		fpsDen.push_back(std::make_pair("name", "FPSDen"));
		fpsDen.push_back(std::make_pair("type", "OBS_PROPERTY_UINT"));
		fpsDen.push_back(std::make_pair("description", "FPSDen"));
		entries.push_back(fpsDen);
	}

	videoSettings->Set(0, serializeSettingsData("Untitled", entries, config, "Video", true, isCategoryEnabled));
	entries.clear();

	return videoSettings;
}

struct BaseLexer {
	lexer lex;
	public:
	inline BaseLexer() {
		lexer_init(&lex);
	}
	inline ~BaseLexer() {
		lexer_free(&lex);
	}
	operator lexer*() {
		return &lex;
	}
};

/* parses "[width]x[height]", string, i.e. 1024x768 */
static bool ConvertResText(const char *res, uint32_t &cx, uint32_t &cy) {
	BaseLexer lex;
	base_token token;

	lexer_start(lex, res);

	/* parse width */
	if (!lexer_getbasetoken(lex, &token, IGNORE_WHITESPACE))
		return false;
	if (token.type != BASETOKEN_DIGIT)
		return false;

	cx = std::stoul(token.text.array);

	/* parse 'x' */
	if (!lexer_getbasetoken(lex, &token, IGNORE_WHITESPACE))
		return false;
	if (strref_cmpi(&token.text, "x") != 0)
		return false;

	/* parse height */
	if (!lexer_getbasetoken(lex, &token, IGNORE_WHITESPACE))
		return false;
	if (token.type != BASETOKEN_DIGIT)
		return false;

	cy = std::stoul(token.text.array);

	/* shouldn't be any more tokens after this */
	if (lexer_getbasetoken(lex, &token, IGNORE_WHITESPACE))
		return false;

	return true;
}

void OBS_settings::saveVideoSettings(Local<Array> videoSettings) {
	Isolate *isolate = v8::Isolate::GetCurrent();

	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	Local<Object> videoSettingsObject = v8::Local<v8::Object>::Cast(videoSettings->Get(0));
	Local<Array> parameters = v8::Local<v8::Array>::Cast(videoSettingsObject->Get(String::NewFromUtf8(isolate, "parameters")));

	//Base resolution
	Local<Object> baseRes = v8::Local<v8::Object>::Cast(parameters->Get(0));

	v8::String::Utf8Value param0(baseRes->Get(String::NewFromUtf8(isolate, "currentValue")));
	std::string baseResString = std::string(*param0);

	uint32_t baseWidth, baseHeight;

	ConvertResText(baseResString.c_str(), baseWidth, baseHeight);
	config_set_uint(config, "Video", "BaseCX", baseWidth);
	config_set_uint(config, "Video", "BaseCY", baseHeight);

	//Output resolution
	Local<Object> outputRes = v8::Local<v8::Object>::Cast(parameters->Get(1));

	v8::String::Utf8Value param1(outputRes->Get(String::NewFromUtf8(isolate, "currentValue")));
	std::string outputResString = std::string(*param1);

	uint32_t outputWidth, outputHeight;

	ConvertResText(outputResString.c_str(), outputWidth, outputHeight);
	config_set_uint(config, "Video", "OutputCX", outputWidth);
	config_set_uint(config, "Video", "OutputCY", outputHeight);

	bool valueFound = false;

	for (size_t idx = 0; idx < numVals; idx++) {
		uint32_t outDownscaleCX = uint32_t(double(baseWidth) / vals[idx]);
		uint32_t outDownscaleCY = uint32_t(double(baseHeight) / vals[idx]);

		string outRes = ResString(outDownscaleCX, outDownscaleCY);

		if (outputResString.compare(outRes) == 0) {
			valueFound = true;
		}
	}

	if (!valueFound) {
		cout << "VALUE NOT FOUND " << endl;
		config_set_uint(config, "Video", "OutputCX", baseWidth);
		config_set_uint(config, "Video", "OutputCY", baseHeight);
	}

	Local<Object> scaleParameter = v8::Local<v8::Object>::Cast(parameters->Get(2));

	v8::String::Utf8Value param2(scaleParameter->Get(String::NewFromUtf8(isolate, "currentValue")));
	std::string scaleString = std::string(*param2);

	config_set_string(config, "Video", "ScaleType", scaleString.c_str());

	Local<Object> fpsType = v8::Local<v8::Object>::Cast(parameters->Get(3));
	v8::String::Utf8Value param3(fpsType->Get(String::NewFromUtf8(isolate, "currentValue")));
	std::string fpsTypeString = std::string(*param3);

	if (fpsTypeString.compare("Common FPS Values") == 0) {
		config_set_uint(config, "Video", "FPSType", 0);

		Local<Object> fpsCommon = v8::Local<v8::Object>::Cast(parameters->Get(4));
		v8::String::Utf8Value param4(fpsCommon->Get(String::NewFromUtf8(isolate, "currentValue")));
		std::string fpsCommonString = std::string(*param4);
		config_set_string(config, "Video", "FPSCommon", fpsCommonString.c_str());

	} else if (fpsTypeString.compare("Integer FPS Value") == 0) {
		config_set_uint(config, "Video", "FPSType", 1);

		Local<Object> fpsInt = v8::Local<v8::Object>::Cast(parameters->Get(4));
		v8::Local<v8::Integer> fpsIntValue = v8::Local<v8::Integer>::Cast(fpsInt->Get(String::NewFromUtf8(isolate, "currentValue")));
		config_set_uint(config, "Video", "FPSInt", fpsIntValue->Uint32Value());

	} else if (fpsTypeString.compare("Fractional FPS Value") == 0) {
		config_set_uint(config, "Video", "FPSType", 2);

		Local<Object> fpsNum = v8::Local<v8::Object>::Cast(parameters->Get(4));
		v8::Local<v8::Integer> fpsNumValue = v8::Local<v8::Integer>::Cast(fpsNum->Get(String::NewFromUtf8(isolate, "currentValue")));
		config_set_uint(config, "Video", "FPSNum", fpsNumValue->Uint32Value());

		if (parameters->Length() > 5) {
			Local<Object> fpsDen = v8::Local<v8::Object>::Cast(parameters->Get(5));
			v8::Local<v8::Integer> fpsDenValue = v8::Local<v8::Integer>::Cast(fpsDen->Get(String::NewFromUtf8(isolate, "currentValue")));
			config_set_uint(config, "Video", "FPSDen", fpsDenValue->Uint32Value());
		}
	}

	config_save_safe(config, "tmp", nullptr);
}

vector<const char*>  OBS_settings::getHotkeysSettings() {
	return vector<const char*>();
}

void OBS_settings::saveHotkeysSettings() {

}

Local<Array>  OBS_settings::getAdvancedSettings() {
	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Array> advancedSettings = Array::New(isolate);

	std::string basicConfigFile = OBS_API::getBasicConfigPath();
	config_t* config = OBS_API::openConfigFile(basicConfigFile);

	std::string globalConfigFile = OBS_API::getGlobalConfigPath();
	config_t* globalConfig = OBS_API::openConfigFile(globalConfigFile);

	std::vector<std::vector<std::pair<std::string, std::string>>> entries;

	#if _WIN32
	//General

	//Process Priority
	std::vector<std::pair<std::string, std::string>> processPriority;
	processPriority.push_back(std::make_pair("name", "ProcessPriority"));
	processPriority.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	processPriority.push_back(std::make_pair("description", "Process Priority"));
	processPriority.push_back(std::make_pair("High", "High"));
	processPriority.push_back(std::make_pair("Above Normal", "Above Normal"));
	processPriority.push_back(std::make_pair("Normal", "Normal"));
	processPriority.push_back(std::make_pair("Idle", "Idle"));

	const char* processPriorityCurrentValue = config_get_string(globalConfig, "General", "ProcessPriority");

	entries.push_back(processPriority);

	advancedSettings->Set(0, serializeSettingsData("General", entries, globalConfig, "General", true, true));
	entries.clear();

	// bool enableNewSocketLoop = config_get_bool(config, "Output", "NewSocketLoopEnable");
	// bool enableLowLatencyMode = config_get_bool(config, "Output", "LowLatencyEnable");
	#endif
		//Video
	const char *videoColorFormat = config_get_string(config, "Video", "ColorFormat");
	const char *videoColorSpace = config_get_string(config, "Video", "ColorSpace");
	const char *videoColorRange = config_get_string(config, "Video", "ColorRange");

	//Renderer
	std::vector<std::pair<std::string, std::string>> renderer;
	renderer.push_back(std::make_pair("name", "Renderer"));
	renderer.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	renderer.push_back(std::make_pair("description", "Renderer"));

	const char* rendererValue = config_get_string(config, "Video", "Renderer");
	if (rendererValue == NULL) {
		rendererValue = "";
	}

	renderer.push_back(std::make_pair("currentValue", rendererValue));
	renderer.push_back(std::make_pair("Direct3D 11", "Direct3D 11"));
	renderer.push_back(std::make_pair("OpenGL", "OpenGL"));
	entries.push_back(renderer);

	//Video Adapter

	//Color Format
	std::vector<std::pair<std::string, std::string>> colorFormat;
	colorFormat.push_back(std::make_pair("name", "ColorFormat"));
	colorFormat.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	colorFormat.push_back(std::make_pair("description", "Color Format"));
	colorFormat.push_back(std::make_pair("NV12", "NV12"));
	colorFormat.push_back(std::make_pair("I420", "I420"));
	colorFormat.push_back(std::make_pair("I444", "I444"));
	colorFormat.push_back(std::make_pair("RGB", "RGB"));
	entries.push_back(colorFormat);

	//YUV Color Space
	std::vector<std::pair<std::string, std::string>> colorSpace;
	colorSpace.push_back(std::make_pair("name", "ColorSpace"));
	colorSpace.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	colorSpace.push_back(std::make_pair("description", "YUV Color Space"));
	colorSpace.push_back(std::make_pair("601", "601"));
	colorSpace.push_back(std::make_pair("709", "709"));
	entries.push_back(colorSpace);

	//YUV Color Range
	std::vector<std::pair<std::string, std::string>> colorRange;
	colorRange.push_back(std::make_pair("name", "ColorRange"));
	colorRange.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	colorRange.push_back(std::make_pair("description", "YUV Color Range"));
	colorRange.push_back(std::make_pair("Partial", "Partial"));
	colorRange.push_back(std::make_pair("Full", "Full"));
	entries.push_back(colorRange);

	advancedSettings->Set(1, serializeSettingsData("Video", entries, config, "Video", true, true));
	entries.clear();

	#if defined(_WIN32) || defined(__APPLE__)
	//Audio
	const char *monDevName = config_get_string(config, "Audio", "MonitoringDeviceName");
	const char *monDevId = config_get_string(config, "Audio", "MonitoringDeviceId");

	//Audio Monitoring Device
	std::vector<std::pair<std::string, std::string>>* monitoringDevice = new std::vector<std::pair<std::string, std::string>>();
	monitoringDevice->push_back(std::make_pair("name", "MonitoringDeviceName"));
	monitoringDevice->push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	monitoringDevice->push_back(std::make_pair("description", "Audio Monitoring Device"));
	monitoringDevice->push_back(std::make_pair("Default", "Default"));

	auto enum_devices = [](void *param, const char *name, const char *id) {
		std::vector<std::pair<std::string, std::string>> *monitoringDevice =
			(std::vector<std::pair<std::string, std::string>>*)param;
		monitoringDevice->push_back(std::make_pair(name, name));
		return true;
	};
	obs_enum_audio_monitoring_devices(enum_devices, monitoringDevice);
	entries.push_back(*monitoringDevice);

	advancedSettings->Set(2, serializeSettingsData("Audio", entries, config, "Audio", true, true));
	entries.clear();
	#endif

	//Recording

	//Filename Formatting
	std::vector<std::pair<std::string, std::string>> filenameFormatting;
	filenameFormatting.push_back(std::make_pair("name", "FilenameFormatting"));
	filenameFormatting.push_back(std::make_pair("type", "OBS_PROPERTY_EDIT_TEXT"));
	filenameFormatting.push_back(std::make_pair("description", "Filename Formatting"));
	// filenameFormatting.push_back(std::make_pair("currentValue", config_get_string(config, "Output", "FilenameFormatting")));
	entries.push_back(filenameFormatting);

	//Overwrite if file exists
	std::vector<std::pair<std::string, std::string>> overwriteIfExists;
	overwriteIfExists.push_back(std::make_pair("name", "OverwriteIfExists"));
	overwriteIfExists.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	overwriteIfExists.push_back(std::make_pair("description", "Overwrite if file exists"));
	// overwriteIfExists.push_back(std::make_pair("currentValue", to_string(config_get_bool(config, "Output", "OverwriteIfExists"))));
	entries.push_back(overwriteIfExists);

	//Replay Buffer Filename Prefix
	std::vector<std::pair<std::string, std::string>> recRBPrefix;
	recRBPrefix.push_back(std::make_pair("name", "RecRBPrefix"));
	recRBPrefix.push_back(std::make_pair("type", "OBS_PROPERTY_EDIT_TEXT"));
	recRBPrefix.push_back(std::make_pair("description", "Replay Buffer Filename Prefix"));
	entries.push_back(recRBPrefix);

	//Replay Buffer Filename Suffix
	std::vector<std::pair<std::string, std::string>> recRBSuffix;
	recRBSuffix.push_back(std::make_pair("name", "RecRBSuffix"));
	recRBSuffix.push_back(std::make_pair("type", "OBS_PROPERTY_EDIT_TEXT"));
	recRBSuffix.push_back(std::make_pair("description", "Replay Buffer Filename Suffix"));
	entries.push_back(recRBSuffix);

	advancedSettings->Set(3, serializeSettingsData("Recording", entries, config, "SimpleOutput", true, true));
	entries.clear();

	//Stream Delay

	//Enable
	std::vector<std::pair<std::string, std::string>> delayEnable;
	delayEnable.push_back(std::make_pair("name", "DelayEnable"));
	delayEnable.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	delayEnable.push_back(std::make_pair("description", "Enable"));
	entries.push_back(delayEnable);

	//Duration (seconds)
	std::vector<std::pair<std::string, std::string>> delaySec;
	delaySec.push_back(std::make_pair("name", "DelaySec"));
	delaySec.push_back(std::make_pair("type", "OBS_PROPERTY_INT"));
	delaySec.push_back(std::make_pair("description", "Duration (seconds)"));
	entries.push_back(delaySec);


	//Preserved curtoff point (increase delay) when reconnecting
	std::vector<std::pair<std::string, std::string>> delayPreserve;
	delayPreserve.push_back(std::make_pair("name", "DelayPreserve"));
	delayPreserve.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	delayPreserve.push_back(std::make_pair("description", "Preserved curtoff point (increase delay) when reconnecting"));
	entries.push_back(delayPreserve);

	advancedSettings->Set(4, serializeSettingsData("Stream Delay", entries, config, "Output", true, true));
	entries.clear();

	//Automatically Reconnect

	//Enable
	std::vector<std::pair<std::string, std::string>> reconnect;
	reconnect.push_back(std::make_pair("name", "Reconnect"));
	reconnect.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	reconnect.push_back(std::make_pair("description", "Enable"));
	entries.push_back(reconnect);

	//Retry Delay (seconds)
	std::vector<std::pair<std::string, std::string>> retryDelay;
	retryDelay.push_back(std::make_pair("name", "RetryDelay"));
	retryDelay.push_back(std::make_pair("type", "OBS_PROPERTY_INT"));
	retryDelay.push_back(std::make_pair("description", "Retry Delay (seconds)"));
	entries.push_back(retryDelay);

	//Maximum Retries
	std::vector<std::pair<std::string, std::string>> maxRetries;
	maxRetries.push_back(std::make_pair("name", "MaxRetries"));
	maxRetries.push_back(std::make_pair("type", "OBS_PROPERTY_INT"));
	maxRetries.push_back(std::make_pair("description", "Maximum Retries"));
	entries.push_back(maxRetries);

	advancedSettings->Set(5, serializeSettingsData("Automatically Reconnect", entries, config, "Output", true, true));
	entries.clear();

	// const char *bindIP = config_get_string(config, "Output", "BindIP");
	// bool enableNewSocketLoop = config_get_bool(config, "Output", "NewSocketLoopEnable");
	// bool enableLowLatencyMode = config_get_bool(config, "Output", "LowLatencyEnable");

	//Network

	//Bind to IP
	std::vector<std::pair<std::string, std::string>> bindIP;
	bindIP.push_back(std::make_pair("name", "BindIP"));
	bindIP.push_back(std::make_pair("type", "OBS_PROPERTY_LIST"));
	bindIP.push_back(std::make_pair("description", "Bind to IP"));

	obs_properties_t *ppts = obs_get_output_properties("rtmp_output");
	obs_property_t *p = obs_properties_get(ppts, "bind_ip");

	size_t count = obs_property_list_item_count(p);
	for (size_t i = 0; i < count; i++) {
		const char *name = obs_property_list_item_name(p, i);
		const char *val = obs_property_list_item_string(p, i);

		bindIP.push_back(std::make_pair(name, name));
	}

	entries.push_back(bindIP);

	//Enable new networking code
	std::vector<std::pair<std::string, std::string>> newSocketLoopEnable;
	newSocketLoopEnable.push_back(std::make_pair("name", "NewSocketLoopEnable"));
	newSocketLoopEnable.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	newSocketLoopEnable.push_back(std::make_pair("description", "Enable new networking code"));
	entries.push_back(newSocketLoopEnable);

	//Low latency mode
	std::vector<std::pair<std::string, std::string>> lowLatencyEnable;
	lowLatencyEnable.push_back(std::make_pair("name", "LowLatencyEnable"));
	lowLatencyEnable.push_back(std::make_pair("type", "OBS_PROPERTY_BOOL"));
	lowLatencyEnable.push_back(std::make_pair("description", "Low latency mode"));
	entries.push_back(lowLatencyEnable);

	advancedSettings->Set(6, serializeSettingsData("Network", entries, config, "Output", true, true));
	entries.clear();

	return advancedSettings;
}

void OBS_settings::saveAdvancedSettings(Local<Array> advancedSettings) {
	Isolate *isolate = v8::Isolate::GetCurrent();

	std::string globalConfigFile = OBS_API::getGlobalConfigPath();
	std::string basicConfigFile = OBS_API::getBasicConfigPath();

	//General
	Local<Array> generalAdvancedSettings = Array::New(isolate);

	generalAdvancedSettings->Set(0, advancedSettings->Get(0));
	saveGenericSettings(generalAdvancedSettings, "General", globalConfigFile);

	//Video
	Local<Array> videoAdvancedSettings = Array::New(isolate);

	videoAdvancedSettings->Set(0, advancedSettings->Get(1));
	saveGenericSettings(videoAdvancedSettings, "Video", basicConfigFile);

	//Audio
	Local<Array> audioAdvancedSettings = Array::New(isolate);

	audioAdvancedSettings->Set(0, advancedSettings->Get(2));
	saveGenericSettings(audioAdvancedSettings, "Audio", basicConfigFile);

	//Recording
	Local<Array> recordingAdvancedSettings = Array::New(isolate);

	recordingAdvancedSettings->Set(0, advancedSettings->Get(3));
	saveGenericSettings(recordingAdvancedSettings, "SimpleOutput", basicConfigFile);

	//Stream Delay
	Local<Array> stresmDelayAdvancedSettings = Array::New(isolate);

	stresmDelayAdvancedSettings->Set(0, advancedSettings->Get(4));
	saveGenericSettings(stresmDelayAdvancedSettings, "Output", basicConfigFile);

	//Automatically Reconnect
	Local<Array> automaticallyReconnectAdvancedSettings = Array::New(isolate);

	automaticallyReconnectAdvancedSettings->Set(0, advancedSettings->Get(5));
	saveGenericSettings(automaticallyReconnectAdvancedSettings, "Output", basicConfigFile);

	//Network
	Local<Array> networkAdvancedSettings = Array::New(isolate);

	networkAdvancedSettings->Set(0, advancedSettings->Get(6));
	saveGenericSettings(networkAdvancedSettings, "Output", basicConfigFile);
}

Local<Array> OBS_settings::getListCategories(void) {
	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Array> categories = Array::New(isolate);

	categories->Set(0, String::NewFromUtf8(isolate, "General"));
	categories->Set(1, String::NewFromUtf8(isolate, "Stream"));
	categories->Set(2, String::NewFromUtf8(isolate, "Output"));
	categories->Set(3, String::NewFromUtf8(isolate, "Audio"));
	categories->Set(4, String::NewFromUtf8(isolate, "Video"));
	categories->Set(5, String::NewFromUtf8(isolate, "Hotkeys"));
	categories->Set(6, String::NewFromUtf8(isolate, "Advanced"));

	return categories;
}

Local<Array> OBS_settings::getSettings(std::string nameCategory) {
	Isolate *isolate = v8::Isolate::GetCurrent();
	Local<Array> settings = Array::New(isolate);

	if (nameCategory.compare("General") == 0) {
		settings = getGeneralSettings();
	} else if (nameCategory.compare("Stream") == 0) {
		settings = getStreamSettings();
	} else if (nameCategory.compare("Output") == 0) {
		settings = getOutputSettings();
	} else if (nameCategory.compare("Audio") == 0) {
		settings = getAudioSettings();
	} else if (nameCategory.compare("Video") == 0) {
		settings = getVideoSettings();
	} else if (nameCategory.compare("Hotkeys") == 0) {

	} else if (nameCategory.compare("Advanced") == 0) {
		settings = getAdvancedSettings();
	}

	return settings;
}

void OBS_settings::saveSettings(std::string nameCategory, Local<Array> settings) {
	std::string globalConfigFile = OBS_API::getGlobalConfigPath();
	std::string basicConfigFile = OBS_API::getBasicConfigPath();

	if (nameCategory.compare("General") == 0) {
		saveGenericSettings(settings, "BasicWindow", globalConfigFile);
	} else if (nameCategory.compare("Stream") == 0) {
		saveStreamSettings(settings);
	} else if (nameCategory.compare("Output") == 0) {
		saveGenericSettings(settings, "SimpleOutput", basicConfigFile);
		OBS_service::updateVideoStreamEncoder();
	} else if (nameCategory.compare("Audio") == 0) {
		saveAudioSettings(settings);
	} else if (nameCategory.compare("Video") == 0) {
		saveVideoSettings(settings);
		OBS_service::resetVideoContext();
	} else if (nameCategory.compare("Hotkeys") == 0) {

	} else if (nameCategory.compare("Advanced") == 0) {
		saveAdvancedSettings(settings);
	}
}

void OBS_settings::saveGenericSettings(Local<Array> genericSettings, std::string section, std::string pathFile) {
	Isolate *isolate = v8::Isolate::GetCurrent();
	config_t* config = OBS_API::openConfigFile(pathFile);

	for (int i = 0; i < genericSettings->Length(); i++) {
		Local<Object> generalSettingsObject = v8::Local<v8::Object>::Cast(genericSettings->Get(i));

		v8::String::Utf8Value param0(generalSettingsObject->Get(String::NewFromUtf8(isolate, "nameSubCategory")));
		std::string nameSubcategory = std::string(*param0);

		Local<Array> parameters = v8::Local<v8::Array>::Cast(generalSettingsObject->Get(String::NewFromUtf8(isolate, "parameters")));

		for (int j = 0; j < parameters->Length(); j++) {
			Local<Object> parameter = v8::Local<v8::Object>::Cast(parameters->Get(j));

			std::string name, type, value;

			v8::String::Utf8Value param0(parameter->Get(String::NewFromUtf8(isolate, "name")));
			name = std::string(*param0);

			v8::String::Utf8Value param1(parameter->Get(String::NewFromUtf8(isolate, "type")));
			type = std::string(*param1);

			if (type.compare("OBS_PROPERTY_LIST") == 0 ||
				type.compare("OBS_PROPERTY_EDIT_TEXT") == 0 ||
				type.compare("OBS_PROPERTY_PATH") == 0) {
				v8::String::Utf8Value param2(parameter->Get(String::NewFromUtf8(isolate, "currentValue")));
				value = std::string(*param2);
				config_set_string(config, section.c_str(), name.c_str(), value.c_str());
			} else if (type.compare("OBS_PROPERTY_INT") == 0) {
				int64_t value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_int(config, section.c_str(), name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_UINT") == 0) {
				uint64_t value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_uint(config, section.c_str(), name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_BOOL") == 0) {
				uint64_t value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_bool(config, section.c_str(), name.c_str(), value);
			} else if (type.compare("OBS_PROPERTY_DOUBLE") == 0) {
				double value = parameter->Get(String::NewFromUtf8(isolate, "currentValue"))->NumberValue();
				config_set_double(config, section.c_str(), name.c_str(), value);
			} else {
				std::cout << "type not found ! " << type.c_str() << std::endl;
			}
		}
	}
	config_save_safe(config, "tmp", nullptr);
}