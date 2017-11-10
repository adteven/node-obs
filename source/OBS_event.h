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

#define SIGNAL_BINDING(name) \
    void name##(const v8::FunctionCallbackInfo<v8::Value> &args)

SIGNAL_BINDING(OBS_signal_sourceRemoved);
SIGNAL_BINDING(OBS_signal_sourceDestroyed);
SIGNAL_BINDING(OBS_signal_sourceSaved);
SIGNAL_BINDING(OBS_signal_sourceLoaded);
SIGNAL_BINDING(OBS_signal_sourceActivated);
SIGNAL_BINDING(OBS_signal_sourceDeactivated);
SIGNAL_BINDING(OBS_signal_sourceShown);
SIGNAL_BINDING(OBS_signal_sourceHidden);
SIGNAL_BINDING(OBS_signal_sourceMuted);

SIGNAL_BINDING(OBS_signal_createdSource);
SIGNAL_BINDING(OBS_signal_removedSource);
SIGNAL_BINDING(OBS_signal_destroyedSource);
SIGNAL_BINDING(OBS_signal_savedSource);
SIGNAL_BINDING(OBS_signal_loadedSource);
SIGNAL_BINDING(OBS_signal_activatedSource);
SIGNAL_BINDING(OBS_signal_deactivatedSource);
SIGNAL_BINDING(OBS_signal_showedSource);
SIGNAL_BINDING(OBS_signal_hidSource);

SIGNAL_BINDING(OBS_signal_outputStarted);
SIGNAL_BINDING(OBS_signal_outputStopped);
SIGNAL_BINDING(OBS_signal_outputStarting);
SIGNAL_BINDING(OBS_signal_outputStopping);
SIGNAL_BINDING(OBS_signal_outputActivated);
SIGNAL_BINDING(OBS_signal_outputDeactivated);
SIGNAL_BINDING(OBS_signal_outputReconnecting);
SIGNAL_BINDING(OBS_signal_outputReconnected);