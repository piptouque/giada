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

#ifndef GE_COLUMN_H
#define GE_COLUMN_H

#include "core/types.h"
#include "glue/channel.h"
#include <FL/Fl_Group.H>
#include <functional>
#include <vector>

class geButton;
class geResizerBar;

namespace giada::v
{
class geKeyboard;
class geChannel;
class geColumn : public Fl_Group
{
public:
	geColumn(int x, int y, int w, int h, ID id, geResizerBar* b);

	geChannel* getChannel(ID channelId) const;

	/* addChannel
	Adds a new channel in this column. */

	geChannel* addChannel(c::channel::Data d);

	/* refreshChannels
	Updates channels' graphical statues. Called on each GUI cycle. */

	void refresh();

	void init();

	void forEachChannel(std::function<void(geChannel& c)> f) const;

	ID id;

	geResizerBar* resizerBar;

  private:
	static void cb_addChannel(Fl_Widget* /*w*/, void* p);
	void        cb_addChannel();

	int countChannels() const;
	int computeHeight() const;

	std::vector<geChannel*> m_channels;

	geButton* m_addChannelBtn;
};
} // namespace giada::v

#endif
