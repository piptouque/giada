/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2021 Giovanni A. Zuliani | Monocasual
 *
 * This file is part of Giada - Your Hardcore Loopmachine.
 *
 * Giada - Your Hardcore Loopmachine is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * Giada - Your Hardcore Loopmachine is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Giada - Your Hardcore Loopmachine. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------- */

#ifndef G_RECORDER_HANDLER_H
#define G_RECORDER_HANDLER_H

#include "core/midiEvent.h"
#include "core/recorder.h"
#include "core/types.h"
#include <unordered_set>

namespace giada::m::patch
{
struct Action;
}
namespace giada::m
{
struct Action;
}
namespace giada::m::recorderHandler
{
void init();

bool isBoundaryEnvelopeAction(const Action& a);

/* updateBpm
Changes actions position by calculating the new bpm value. */

void updateBpm(float ratio, int quantizerStep);

/* updateSamplerate
Changes actions position by taking in account the new samplerate. If 
f_system == f_patch nothing will change, otherwise the conversion is 
mandatory. */

void updateSamplerate(int systemRate, int patchRate);

/* cloneActions
Clones actions in channel 'channelId', giving them a new channel ID. Returns
whether any action has been cloned. */

bool cloneActions(ID channelId, ID newChannelId);

/* liveRec
Records a user-generated action. NOTE_ON or NOTE_OFF only for now. */

void liveRec(ID channelId, MidiEvent e, Frame global);

/* consolidate
Records all live actions. Returns a set of channels IDs that have been 
recorded. */

std::unordered_set<ID> consolidate();

/* clearAllActions
Deletes all recorded actions. */

void clearAllActions();

/* (de)serializeActions
Creates new Actions given the patch raw data and vice versa. */

recorder::ActionMap        deserializeActions(const std::vector<patch::Action>& as);
std::vector<patch::Action> serializeActions(const recorder::ActionMap& as);
} // namespace giada::m::recorderHandler

#endif
