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
#include <v8.h>
#include <obs.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <thread>
#include <mutex>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <ctime>
#include <fstream>
#include <map>
#include <nan.h>
#include "OBS_Display.h"
#include "OBS_API.h"
using namespace std;
using namespace v8;

struct SourceInfo {
	uint32_t fader;
	uint32_t volmeter;
};

extern map<std::string, SourceInfo*> sourceInfo;
extern vector<std::string> tabScenes;
extern string currentTransition;
extern map<string, obs_source_t*> transitions;

class OBS_content {
	public:
	OBS_content();
	~OBS_content();

	static void OBS_content_getSourceFilterVisibility(const FunctionCallbackInfo<Value> &args);

	static void OBS_content_setSourceFilterVisibility(const FunctionCallbackInfo<Value> &args);

	static void OBS_content_flipHorzSceneItems(v8Arguments args);

	static void OBS_content_flipVertSceneItems(v8Arguments args);

	static void OBS_content_resetSceneItems(v8Arguments args);

	static void OBS_content_stretchSceneItems(v8Arguments args);

	static void OBS_content_fitSceneItems(v8Arguments args);

	static void OBS_content_centerSceneItems(v8Arguments args);

	static void OBS_content_getSceneItemRot(v8Arguments args);

	static void OBS_content_getSceneItemCrop(v8Arguments args);

	static void OBS_content_setSceneItemRot(v8Arguments args);

	static void OBS_content_setSceneItemCrop(v8Arguments args);
	/**
	 * @return Return a list of strings containing current scenes
	*/
	static void OBS_content_getListCurrentScenes(v8Arguments args);

	/**
	 * @param name: String of the name of the scene.

	 * @return Return a list of strings containing current sources from a scene
	*/
	static void OBS_content_getListCurrentSourcesFromScene(v8Arguments args);

	/**
	 * @return Return a list of strings containing all available input sources
	*/
	static void OBS_content_getListInputSources(v8Arguments args);

	/**
	 * @return Return a list of strings containing all available filters
	*/
	static void OBS_content_getListFilters(v8Arguments args);

	/**
	 * @return Return a list of strings containing already created transitions.
	 */

	static void OBS_content_getListCurrentTransitions(v8Arguments args);

	/**
	 * @return Return a list of strings containing all available transitions
	*/
	static void OBS_content_getListTransitions(v8Arguments args);

	/**
	 * Create a new scene and add it to the list of current scenes

	 * @param name: String of the name of the scene.
	*/
	static void OBS_content_createScene(v8Arguments args);

	/**
	 * Remove a scene from the current context.

	 * @param name: String of the name of the scene.
	*/
	static void OBS_content_removeScene(v8Arguments args);


	static void OBS_content_getSourceFader(v8Arguments args);
	static void OBS_content_getSourceVolmeter(v8Arguments args);
	/**
	 * Add a new source and add it to the list of sources for a specific scene

	 * @param type source: String of the type of the desired source.
	 * @param name: String of the name of the source.
	 * @param settings: Settings to apply to the source.
	 * @param hotkey_data: Hotkeys associated to the source.
	 * @param scene_Name: Name of the scene to add to the source.
	*/
	static void OBS_content_addSource(v8Arguments args);

	/**
	 * Remove a scene from the current context.

	 * @param name: String of the name of the source.
	*/
	static void OBS_content_removeSource(v8Arguments args);

	/**
	 * Return the frame from a given source.

	 * @param name: String of the name of the source.
	*/
	static void OBS_content_getSourceFrame(v8Arguments args);

	static void OBS_content_getSourceProperties(v8Arguments args);

	static void OBS_content_getSourcePropertiesSubParameters(v8Arguments args);

	static void OBS_content_getSourcePropertyCurrentValue(v8Arguments args);

	static void OBS_content_setProperty(v8Arguments args);

	static void OBS_content_setCurrentScene(v8Arguments args);

	static void OBS_content_renameTransition(v8Arguments args);
	static void OBS_content_renameSourceFilter(v8Arguments args);
	static void OBS_content_renameSource(v8Arguments args);
	static void OBS_content_renameScene(v8Arguments args);

	static void OBS_content_addSourceFilter(v8Arguments args);

	static void OBS_content_removeSourceFilter(v8Arguments args);

	static void OBS_content_getSourceFilterProperties(v8Arguments args);

	static void OBS_content_updateSourceFilterProperties(v8Arguments args);

	static void OBS_content_getListSourceFilters(v8Arguments args);

	static void OBS_content_getCurrentTransition(v8Arguments args);

	static void OBS_content_getSourceFilterPropertyCurrentValue(v8Arguments args);

	static void OBS_content_setSourceFilterProperty(v8Arguments args);

	static void OBS_content_getSourceFilterPropertiesSubParameters(v8Arguments args);

	static void OBS_content_getTransitionPropertiesSubParameters(v8Arguments args);

	static void OBS_content_setTransitionProperty(v8Arguments args);

	static void OBS_content_setTransitionDuration(v8Arguments args);

	static void OBS_content_getTransitionDuration(v8Arguments args);

	static void OBS_content_addTransition(v8Arguments args);

	static void OBS_content_removeTransition(v8Arguments args);

	static void OBS_content_setTransition(v8Arguments args);

	static void OBS_content_getTransitionPropertyCurrentValue(v8Arguments args);
	static void OBS_content_getTransitionProperties(v8Arguments args);

	static void OBS_content_updateTransitionProperties(v8Arguments args);

	static void OBS_content_getSourceFrameSettings(v8Arguments args);

	static void OBS_content_setSourcePosition(v8Arguments args);

	static void OBS_content_setSourceScaling(v8Arguments args);

	static void OBS_content_getSourcePosition(v8Arguments args);

	static void OBS_content_getSourceScaling(v8Arguments args);

	static void OBS_content_getSourceSize(v8Arguments args);

	static void OBS_content_setSourceOrder(v8Arguments args);

	static void OBS_content_updateSourceProperties(v8Arguments args);

	static void OBS_content_createDisplay(v8Arguments args);
	static void OBS_content_destroyDisplay(v8Arguments args);
	static void OBS_content_getDisplayPreviewOffset(v8Arguments args);
	static void OBS_content_getDisplayPreviewSize(v8Arguments args);
	static void OBS_content_createSourcePreviewDisplay(v8Arguments args);
	static void OBS_content_resizeDisplay(v8Arguments args);
	static void OBS_content_moveDisplay(v8Arguments args);
	static void OBS_content_setPaddingSize(v8Arguments args);
	static void OBS_content_setPaddingColor(v8Arguments args);
	static void OBS_content_setBackgroundColor(v8Arguments args);
	static void OBS_content_setOutlineColor(v8Arguments args);
	static void OBS_content_setGuidelineColor(v8Arguments args);
	static void OBS_content_setResizeBoxOuterColor(v8Arguments args);
	static void OBS_content_setResizeBoxInnerColor(v8Arguments args);
	static void OBS_content_setShouldDrawUI(v8Arguments args);
	static void OBS_content_selectSource(v8Arguments args);
	static void OBS_content_selectSources(v8Arguments args);
	static void OBS_content_dragSelectedSource(v8Arguments args);
	static void OBS_content_loadConfigFile(v8Arguments args);
	static void OBS_content_saveIntoConfigFile(v8Arguments args);
	static void OBS_content_getSourceFlags(v8Arguments args);
	static void OBS_content_sourceSetMuted(v8Arguments args);
	static void OBS_content_isSourceMuted(v8Arguments args);
	static void OBS_content_getSourceVisibility(v8Arguments args);
	static void OBS_content_setSourceVisibility(v8Arguments args);
	static void OBS_content_fillTabScenes(v8Arguments args);

	static void OBS_content_test_getListCurrentScenes(v8Arguments args);
	static void OBS_content_test_getListCurrentSourcesFromScene(v8Arguments args);
	static void OBS_content_test_getListInputSources(v8Arguments args);
	static void OBS_content_test_getListFilters(v8Arguments args);
	static void OBS_content_test_getListTransitions(v8Arguments args);
	static void OBS_content_test_createScene(v8Arguments args);
	static void OBS_content_test_removeScene(v8Arguments args);
	static void OBS_content_test_addSource(v8Arguments args);
	static void OBS_content_test_removeSource(v8Arguments args);
	static void OBS_content_test_getSourceProperties(v8Arguments args);
	static void OBS_content_test_getSourcePropertiesSubParameters(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_boolType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_colorType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_intType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_floatType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_textType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_fontType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_pathType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_buttonType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_editableListType(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_listType_intFormat(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_listType_floatFormat(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_listType_stringFormat(v8Arguments args);
	static void OBS_content_test_getSourcePropertyCurrentValue_frameRateType(v8Arguments args);
	static void OBS_content_test_setProperty(v8Arguments args);
	static void OBS_content_test_getSourceFrameSettings(v8Arguments args);
	static void OBS_content_test_setSourcePosition(v8Arguments args);
	static void OBS_content_test_setSourceScaling(v8Arguments args);
	static void OBS_content_test_setSourceOrder(v8Arguments args);


	void DisplayCallback(OBS::Display* dp, uint32_t cx, uint32_t cy);

	static vector<std::string> getListCurrentScenes(void);
	static vector<const char*> getListCurrentSourcesFromScene(const std::string &name);
	static vector<const char*> getListInputSources(void);
	static vector<const char*> getListFilterNames(void);
	static vector<const char*> getListFilterTypes(void);
	static vector<const char*> getListTransitionNames(void);
	static vector<const char*> getListTransitionTypes(void);
	static bool createScene(const std::string &name);
	static bool removeScene(const std::string &name);
	static bool addSource(const std::string &typeSource, const std::string &name,
		obs_data_t* settings, obs_data_t *hotkey_data,
		const char* sceneName);
	static bool removeSource(const std::string &name);
	static uint8_t* convert_UYVY422_to_I420(uint8_t* source, int width, int height);
	static uint8_t* convert_YUY2_to_I420(uint8_t* source, int width, int height);

	static vector<std::string> getSourceProperties(obs_source_t* source);
	static vector<string> getSourcePropertiesSubParameters(obs_source_t* source, const std::string &propertyNameSelected);
	static Local<Object> getSourcePropertyCurrentValue(obs_source_t* source, const std::string &propertyNameSelected);
	static bool setProperty(obs_source_t* source, const std::string &propertyNameSelected, Local<Object> objectValue);
	static const char* pathTypeToString(obs_path_type type);
	static void setCurrentScene(const std::string &name);
	static obs_source_t *setTransition(const std::string &id, const std::string &name, obs_data_t *settings);
	static void addTransition(const std::string &id, const std::string &name, obs_data_t *settings);
	static void removeTransition(const std::string &name);
	static void setTransitionDuration(const uint32_t duration);
	static obs_source_t* setTransition(const std::string &name);
	static void setSourcePosition(const std::string &sceneName, const std::string &sourceName, float x, float y);
	static void setSourceScaling(const std::string &sceneName, const std::string &sourceName, float x, float y);
	static Local<Object> getSourcePosition(const std::string &sceneName, const std::string &sourceName);
	static Local<Object> getSourceScaling(const std::string &sceneName, const std::string &sourceName);
	static Local<Object> getSourceSize(const std::string &name);

	static void setSourceOrder(const std::string &name, const std::string &order);
	static void updateSourceProperties(obs_source_t* source, obs_data_t* settings);

	static void createDisplay(const std::string key, uint64_t windowHandle);
	static void destroyDisplay(const std::string key);
	static void createSourcePreviewDisplay(const std::string key, uint64_t windowHandle, const std::string sourceName);
	static void selectSource(int x, int y);
	static void selectSources(Local<Array> sources);
	static void dragSelectedSource(int x, int y);
	static void SourceLoaded(void* data, obs_source_t* source);
	static void LoadSceneListOrder(obs_data_array_t *array);
	static void LoadTransitions(obs_data_array_t *);
	static void loadConfigFile();

	static obs_data_array_t* saveSceneListOrder(void);
	static obs_data_array_t* saveTransitions();
	static void SaveAudioDevice(const char *name, int channel, obs_data_t *parent, vector<obs_source_t*> &audioSources);
	static obs_data_array_t* saveSource(obs_data_t* saveData);
	static void saveIntoConfigFile();
	static Local<Object> getSourceFlags(std::string sourceName);
	static void sourceSetMuted(std::string sourceName, bool muted);
	static bool isSourceMuted(std::string sourceName);
	static bool getSourceVisibility(std::string sceneName, std::string sourceName);
	static void setSourceVisibility(std::string sceneName, std::string sourceName, bool isVisible);
	static void fillTabScenes(v8::Local<v8::Array> arrayScenes);
};
