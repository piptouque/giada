/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * beatMeter
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

#ifndef GE_SEQUENCER_H
#define GE_SEQUENCER_H

#include "core/types.h"
#include "glue/main.h"
#include <FL/Fl_Box.H>

namespace giada::v
{
class geSequencer : public Fl_Box
{
public:
	geSequencer(int x, int y, int w, int h);

	void draw() override;

	void refresh();

private:
	void paintCursor(int w) const;
	void paintCursor(int position, int w, Fl_Color col) const;

	c::main::Sequencer m_data;
};
} // namespace giada::v

#endif
