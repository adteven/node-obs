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

/* Fader API */
void OBS_audio_createFader(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_destroyFader(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderSetDb(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderGetDb(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderSetDeflection(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderGetDeflection(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderSetMul(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderGetMul(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderAttachSource(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderDetachSource(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderAddCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_faderRemoveCallback(const v8::FunctionCallbackInfo<v8::Value>& args);

/* Volmeter API */
void OBS_audio_createVolmeter(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_destroyVolmeter(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterAttachSource(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterDetachSource(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterSetUpdateInterval(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterGetUpdateInterval(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterSetPeakHold(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterGetPeakHold(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterAddCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
void OBS_audio_volmeterRemoveCallback(const v8::FunctionCallbackInfo<v8::Value>& args);