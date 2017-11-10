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
#include <thread>
#include <util/config-file.h>
#include <util/dstr.h>
#include <util/platform.h>
#include <util/util.hpp>
#include <algorithm>
#include <sys/stat.h>
#include "OBS_API.h"
#include <map>
#include <mutex>

#include "audio-encoders.h"

#ifdef _WIN32

#ifdef _MSC_VER
#include <direct.h>
#define getcwd _getcwd
#endif 
#else
#include <unistd.h>
#endif

#define SIMPLE_ENCODER_X264                    "x264"
#define SIMPLE_ENCODER_X264_LOWCPU             "x264_lowcpu"
#define SIMPLE_ENCODER_QSV                     "qsv"
#define SIMPLE_ENCODER_NVENC                   "nvenc"
#define SIMPLE_ENCODER_AMD                     "amd"

using namespace std;
using namespace v8;

class OBS_service {
	public:
	OBS_service();
	~OBS_service();

	/**
	 * Sets base audio output format/channels/samples/etc
	 *
	 * @note Cannot reset base audio if an output is currently active.
	 */
	static void OBS_service_resetAudioContext(v8Arguments args);

	/**
	 * Sets base video ouput base resolution/fps/format.
	 *
	 * @note This data cannot be changed if an output is corrently active.
	 * @note The graphics module cannot be changed without fully destroying the
	 *       OBS context.
	 *
	 * @param   ovi  Pointer to an obs_video_info structure containing the
	 *               specification of the graphics subsystem,

	 * @return       OBS_VIDEO_SUCCESS if sucessful
	 * 		         OBS_VIDEO_NOT_SUPPORTED  if the adapter lacks capabilities
	 * 		         OBS_VIDEO_INVALID_PARAM if a parameter is invalid
	 * 	             OBS_VIDEO_CURRENTLY_ACTIVE if video is currently active
	 * 		         OBS_VIDEO_MODULE_NOT_FOUND if the graphics module is not found
	 * 		         OBS_VIDEO_FAIL for generic failure
	 */
	static void OBS_service_resetVideoContext(v8Arguments args);

	/**
	 * Create a default AAC audio encoder

	 * @return       Return an audio encoder if successfull, NULL otherwise.
	*/
	static void OBS_service_createAudioEncoder(v8Arguments args);

	/**
	 * Create a default x264 video encoder

	 * @return       Return a video streaming encoder if successfull, NULL otherwise.
	*/
	static void OBS_service_createVideoStreamingEncoder(v8Arguments args);

	/**
	 * Create a default x264 video encoder

	 * @return       Return a video recording encoder if successfull, NULL otherwise.
	*/
	static void OBS_service_createVideoRecordingEncoder(v8Arguments args);

	/**
	 * Create a service that will be associate to the streaming output.
	 * @note The service configuration is composed by the type of the targeted plateform (e.g Twitch, youtube, ...).
	 * @note The configuration file is located under OBS global configuration files.

	 * @return       Return a service if successfull, NULL otherwise.

	*/
	static void OBS_service_createService(v8Arguments args);

	/*obs_data_set_string(settings, "format_name", "avi");
	obs_data_set_string(settings, "video_encoder", "utvideo");
	obs_data_set_string(settings, "audio_encoder", "pcm_s16le");
	obs_data_set_string(settings, "path", "./recording_1.avi");*/

	/**
	 * Create the settings that will be associated to the recording output.

	 * @param   format_name:  	output file extension, possible values are: avi, mpeg4,...
     * @param   video_encoder:  video encoder that will be used to generate the outptut
	 * @param   audio_encoder:  video encoder that will be used to generate the outptut
     * @param   output_path:  	specify the path of the output file that will be recorded

	 * @return       Return the output settings if successfull, NULL otherwise.
	*/
	static void OBS_service_createRecordingSettings(v8Arguments args);

	/**
	 * Create a RTMP streaming output
	*/
	static void OBS_service_createStreamingOutput(v8Arguments args);

	/**
	 * Create a Ffmpeg muxer recording output
	*/
	static void OBS_service_createRecordingOutput(v8Arguments args);

	/**
	 * Start the streaming output
	*/
	static void OBS_service_startStreaming(v8Arguments args);

	/**
	 * Start the recording output
	*/
	static void OBS_service_startRecording(v8Arguments args);

	/**
	 * Stop the streaming output
	*/
	static void OBS_service_stopStreaming(v8Arguments args);

	/**
	 * Stop the recording output
	*/
	static void OBS_service_stopRecording(v8Arguments args);

	/**
	 * Associate the audio and video encoder to the current streaming context
	*/
	static void OBS_service_associateAudioAndVideoToTheCurrentStreamingContext(v8Arguments args);

	/**
	 * Associate the audio and video encoder to the current recording context
	*/
	static void OBS_service_associateAudioAndVideoToTheCurrentRecordingContext(v8Arguments args);

	/**
	 * Associate the audio and video encoder to the current streaming output
	*/
	static void OBS_service_associateAudioAndVideoEncodersToTheCurrentStreamingOutput(v8Arguments args);

	/**
	 * Associate the audio and video encoder to the current recording output
	*/
	static void OBS_service_associateAudioAndVideoEncodersToTheCurrentRecordingOutput(v8Arguments args);

	/**
	 * Set the service configuration to the current streaming output
	*/
	static void OBS_service_setServiceToTheStreamingOutput(v8Arguments args);

	/**
	 * Set the settings to the current recording output
	*/
	static void OBS_service_setRecordingSettings(v8Arguments args);

	static void OBS_service_isStreamingOutputActive(v8Arguments args);

	static void OBS_service_test_resetAudioContext(v8Arguments args);
	static void OBS_service_test_resetVideoContext(v8Arguments args);
	static void OBS_service_test_createAudioEncoder(v8Arguments args);
	static void OBS_service_test_createVideoStreamingEncoder(v8Arguments args);
	static void OBS_service_test_createVideoRecordingEncoder(v8Arguments args);
	static void OBS_service_test_createService(v8Arguments args);
	static void OBS_service_test_createRecordingSettings(v8Arguments args);
	static void OBS_service_test_createStreamingOutput(v8Arguments args);
	static void OBS_service_test_createRecordingOutput(v8Arguments args);
	static void OBS_service_test_startStreaming(v8Arguments args);
	static void OBS_service_test_startRecording(v8Arguments args);
	static void OBS_service_test_stopStreaming(v8Arguments args);
	static void OBS_service_test_stopRecording(v8Arguments args);
	static void OBS_service_test_associateAudioAndVideoToTheCurrentStreamingContext(v8Arguments args);
	static void OBS_service_test_associateAudioAndVideoToTheCurrentRecordingContext(v8Arguments args);
	static void OBS_service_test_associateAudioAndVideoEncodersToTheCurrentStreamingOutput(v8Arguments args);
	static void OBS_service_test_associateAudioAndVideoEncodersToTheCurrentRecordingOutput(v8Arguments args);
	static void OBS_service_test_setServiceToTheStreamingOutput(v8Arguments args);
	static void OBS_service_test_setRecordingSettings(v8Arguments args);

	private:
	static void createAudioEncoder(void);
	static void createVideoStreamingEncoder();
	static void createVideoRecordingEncoder();
	static void createService();
	static obs_data_t* createRecordingSettings(void);
	static void createStreamingOutput(void);
	static void createRecordingOutput(void);
	static bool startStreaming(void);
	static bool startRecording(void);
	static void stopStreaming(void);
	static void stopRecording(void);
	static void associateAudioAndVideoToTheCurrentStreamingContext(void);
	static void associateAudioAndVideoToTheCurrentRecordingContext(void);
	static void associateAudioAndVideoEncodersToTheCurrentStreamingOutput(void);
	static void associateAudioAndVideoEncodersToTheCurrentRecordingOutput(void);
	static void setServiceToTheStreamingOutput(void);
	static void setRecordingSettings(void);


	public:
	static obs_service_t* getService(void);
	static void setService(obs_service_t* newService);
	static void saveService(void);
	static void updateVideoStreamEncoder(void);
	static void updateRecordingOutput(void);
	static obs_output_t* getStreamingOutput(void);
	static bool resetAudioContext(void);
	static bool resetVideoContext(void);
	static bool isStreamingOutputActive(void);
};
