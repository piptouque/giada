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

#include "sequencer.h"
#include "core/const.h"
#include <FL/fl_draw.H>

namespace giada::v
{
geSequencer::geSequencer(int x, int y, int w, int h)
: Fl_Box(x, y, w, h)
{
	copy_tooltip("Main sequencer");
}

/* -------------------------------------------------------------------------- */

void geSequencer::refresh()
{
	m_data = c::main::getSequencer();
	redraw();
}

/* -------------------------------------------------------------------------- */

void geSequencer::draw()
{
	const int cursorW = w() / G_MAX_BEATS;

	/* Border and background. */

	fl_rectf(x(), y(), w(), h(), FL_BACKGROUND_COLOR);
	fl_rect(x(), y(), w(), h(), G_COLOR_GREY_4);

	/* Beat cells. */

	fl_color(G_COLOR_GREY_4);
	for (int i = 1; i <= m_data.beats; i++)
		fl_line(x() + cursorW * i, y(), x() + cursorW * i, y() + h() - 2);

	/* Bar line. */

	fl_color(G_COLOR_LIGHT_1);
	const int delta = m_data.beats / m_data.bars;
	for (int i = 1; i < m_data.bars; i++)
		fl_line(x() + cursorW * (i * delta), y() + 1, x() + cursorW * (i * delta), y() + h() - 2);

	/* Unused grey area. */

	const int greyX = m_data.beats * cursorW;
	fl_rectf(x() + greyX, y(), w() - greyX, h(), G_COLOR_GREY_4);

	/* Cursor. */

	paintCursor(cursorW);
}

/* -------------------------------------------------------------------------- */

void geSequencer::paintCursor(int position, int width, Fl_Color color) const
{
	fl_rectf(x() + (position * width) + 3, y() + 3, width - 5, h() - 6, color);
}

/* -------------------------------------------------------------------------- */

void geSequencer::paintCursor(int width) const
{
	Fl_Color color = m_data.shouldBlink ? FL_BACKGROUND_COLOR : G_COLOR_LIGHT_1;

	if (m_data.isFreeModeInputRec)
	{
		for (int i = 0; i < m_data.beats; i++)
			paintCursor(i, width, color);
	}
	else
		paintCursor(m_data.currentBeat, width, color);
}
} // namespace giada::v
