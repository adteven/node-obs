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
#include <vector>
#include <io.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "OBS_service.h"

using namespace std;
using namespace v8;

struct Screen {
	int width;
	int height;
};

class OBS_API {
	public:

	static void Initialize(v8Arguments args);
	static void Finalize(v8Arguments args);

	static void LoadPlugins(v8Arguments args);
	static void IntializePlugins(v8Arguments args);

	static void GetPerformanceStatistics(v8Arguments args);

	static void GetConfigurationDirectory(v8Arguments args);
	static void SetConfigurationDirectory(v8Arguments args);

	static void IsOBSStudioInstalled(v8Arguments args);
	static std::vector<string> GetOBSStudioProfilesRaw();
	static void GetOBSStudioProfiles(v8Arguments args);
	static std::vector<string> GetOBSStudioSceneCollectionsRaw();
	static void GetOBSStudioSceneCollections(v8Arguments args);
	static void OBS_API_getOBS_currentProfile(v8Arguments args);
	static void OBS_API_setOBS_currentProfile(v8Arguments args);
	static void OBS_API_getOBS_currentSceneCollection(v8Arguments args);
	static void OBS_API_setOBS_currentSceneCollection(v8Arguments args);

	private:
	static double 	getCPU_Percentage(void);
	static int 	 	getNumberOfDroppedFrames(void);
	static double 	getDroppedFramesPercentage(void);
	static double	getCurrentBandwidth(void);
	static double	getCurrentFrameRate(void);
	static bool		isOBS_installed(void);

	public:


	static std::string getOBS_currentProfile(void);
	static void setOBS_currentProfile(std::string profileName);
	static std::string getOBS_currentSceneCollection(void);
	static void setOBS_currentSceneCollection(std::string sceneCollectionName);
	static bool isOBS_configFilesUsed(void);
	static std::vector<Screen> availableResolutions(void);
	static std::string getGlobalConfigPath(void);
	static std::string getBasicConfigPath(void);
	static std::string getServiceConfigPath(void);
	static std::string getContentConfigPath(void);

	static config_t* openConfigFile(std::string configFile);

	private:
	OBS_API() {};
	~OBS_API() {};
};
