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

#pragma once

#include "shared.h"
#include <string>
#include <iostream>
#include <sstream>
#include "OBS_service.h"
#include <util/platform.h>
#include <util/lexer.h>

#include "audio-encoders.h"

using namespace std;
using namespace v8;

class OBS_settings {
	public:
	OBS_settings();
	~OBS_settings();

	/**
	 * Return a list of strings containing general settings and their values

	 * @return list of string, every even number is a key avdn every odd is a value.

	 * @return Language
	 * @return Theme
	 * @return Confirmation dialog when starting stream
	 * @return Confirmation dialog when stoping stream
	 * @return Hide cursor over projectors
	 * @return Make projectors always on top
	 * @return Automatically record when streaming
	 * @return Keep recording when stream stops
	 * @return Enable system tray icon
	 * @return Source Alignement Snapping enabled
	 * @return Snap Sensitivity
	 * @return To edge of screen
	 * @return To other sources
	 * @return To horizontal and vertical center
	*/
	static void OBS_settings_getGeneralSettings(v8Arguments args);

	/**
	 * Save general settings by update every value

	 * @param Language
	 * @param Theme
	 * @param Confirmation dialog when starting stream
	 * @param Confirmation dialog when stoping stream
	 * @param Hide cursor over projectors
	 * @param Make projectors always on top
	 * @param Automatically record when streaming
	 * @param Keep recording when stream stops
	 * @param Enable system tray icon
	 * @param Source Alignement Snapping enabled
	 * @param Snap Sensitivity
	 * @param To edge of screen
	 * @param To other sources
	 * @param To horizontal and vertical center
	*/
	static void OBS_settings_saveGeneralSettings(v8Arguments args);

	static void OBS_settings_getStreamSettings(v8Arguments args);
	static void OBS_settings_saveStreamSettings(v8Arguments args);

	static void OBS_settings_getStreamTypesForStreamSettings(v8Arguments args);
	static void OBS_settings_setStreamTypeForStreamSettings(v8Arguments args);

	static void OBS_settings_getOutputSimpleStreamingSettings(v8Arguments args);
	static void OBS_settings_saveOutputSimpleStreamingSettings(v8Arguments args);
	static void OBS_settings_getOutputSimpleRecordingSettings(v8Arguments args);
	static void OBS_settings_saveOutputSimpleRecordingSettings(v8Arguments args);
	static void OBS_settings_getOutputAdvancedStreamingSettings(v8Arguments args);
	static void OBS_settings_saveOutputAdvancedStreamingSettings(v8Arguments args);
	static void OBS_settings_getOutputAdvancedRecordingSettings(v8Arguments args);
	static void OBS_settings_saveOutputAdvancedRecordingSettings(v8Arguments args);
	static void OBS_settings_getOutputAdvancedAudioSettings(v8Arguments args);
	static void OBS_settings_saveOutputAdvancedAudioSettings(v8Arguments args);
	static void OBS_settings_getAudioSettings(v8Arguments args);
	static void OBS_settings_saveAudioSettings(v8Arguments args);
	static void OBS_settings_getVideoSettings(v8Arguments args);
	static void OBS_settings_saveVideoSettings(v8Arguments args);
	static void OBS_settings_getHotkeysSettings(v8Arguments args);
	static void OBS_settings_saveHotkeysSettings(v8Arguments args);
	static void OBS_settings_getAdvancedSettings(v8Arguments args);
	static void OBS_settings_saveAdvancedSettings(v8Arguments args);
	static void OBS_settings_getSettings(v8Arguments args);
	static void OBS_settings_saveSettings(v8Arguments args);
	static void OBS_settings_getListCategories(v8Arguments args);

	static void OBS_settings_test_getGeneralSettings(v8Arguments args);
	static void OBS_settings_test_saveGeneralSettings(v8Arguments args);

	static void OBS_settings_test_getStreamSettings(v8Arguments args);
	static void OBS_settings_test_saveStreamSettings(v8Arguments args);

	static void OBS_settings_test_getStreamTypesForStreamSettings(v8Arguments args);
	static void OBS_settings_test_setStreamTypeForStreamSettings(v8Arguments args);

	static void OBS_settings_test_getOutputSimpleStreamingSettings(v8Arguments args);
	static void OBS_settings_test_saveOutputSimpleStreamingSettings(v8Arguments args);
	static void OBS_settings_test_getOutputSimpleRecordingSettings(v8Arguments args);
	static void OBS_settings_test_saveOutputSimpleRecordingSettings(v8Arguments args);
	static void OBS_settings_test_getOutputAdvancedStreamingSettings(v8Arguments args);
	static void OBS_settings_test_saveOutputAdvancedStreamingSettings(v8Arguments args);
	static void OBS_settings_test_getOutputAdvancedRecordingSettings(v8Arguments args);
	static void OBS_settings_test_saveOutputAdvancedRecordingSettings(v8Arguments args);
	static void OBS_settings_test_getOutputAdvancedAudioSettings(v8Arguments args);
	static void OBS_settings_test_saveOutputAdvancedAudioSettings(v8Arguments args);
	static void OBS_settings_test_getAudioSettings(v8Arguments args);
	static void OBS_settings_test_saveAudioSettings(v8Arguments args);
	static void OBS_settings_test_getVideoSettings(v8Arguments args);
	static void OBS_settings_test_saveVideoSettings(v8Arguments args);
	static void OBS_settings_test_getHotkeysSettings(v8Arguments args);
	static void OBS_settings_test_saveHotkeysSettings(v8Arguments args);
	static void OBS_settings_test_getAdvancedSettings(v8Arguments args);
	static void OBS_settings_test_saveAdvancedSettings(v8Arguments args);

	private:
	static Local<Array> getListCategories(void);
	static Local<Array> getSettings(std::string nameCategory);
	static void saveSettings(std::string nameCategory, Local<Array> settings);
	static void saveGenericSettings(Local<Array> genericSettings, std::string section, std::string pathFile);

	static Local<Object> serializeSettingsData(std::string nameSubCategory,
		std::vector<std::vector<std::pair<std::string, std::string>>> entries,
		config_t* config, std::string section, bool isVisible, bool isEnabled);

	static Local<Array> getGeneralSettings();
	static void saveGeneralSettings(Local<Array> generalSettings, std::string pathConfigDirectory);

	static Local<Array> getStreamSettings();
	static void saveStreamSettings(Local<Array> streamSettings);
	static vector<std::string> getStreamTypesForStreamSettings(void);
	static void setStreamTypeForStreamSettings(const char* streamTypeDisplayName);
	static void getServices(void);

	static Local<Array> getOutputSettings();
	static void saveOutputSettings(Local<Array> streamSettings);

	static vector<const char*>  getOutputSimpleStreamingSettings(void);
	static void saveOutputSimpleStreamingSettings(int videoBitrate, const char* streamEnc,
		int audioBitrate, bool advanced,
		bool enforceBitrate, const char* preset,
		const char* qsvPreset, const char* nvPreset,
		const char* amdPreset, const char* custom);
	static vector<const char*> getOutputSimpleRecordingSettings(void);
	static void saveOutputSimpleRecordingSettings(void);
	static vector<const char*> getOutputAdvancedStreamingSettings(void);
	static void saveOutputAdvancedStreamingSettings(void);
	static vector<const char*> getOutputAdvancedRecordingSettings(void);
	static void saveOutputAdvancedRecordingSettings(void);
	static vector<const char*> getOutputAdvancedAudioSettings(void);

	static void saveOutputAdvancedAudioSettings(void);

	static Local<Array> getAudioSettings();
	static void saveAudioSettings(Local<Array> audioSettings);

	static Local<Array> getVideoSettings();
	static void saveVideoSettings(Local<Array> videoSettings);
	static vector<const char*> getHotkeysSettings();
	static void saveHotkeysSettings();
	static Local<Array> getAdvancedSettings();
	static void saveAdvancedSettings(Local<Array> advancedSettings);
};
