/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * gLiquidScroll
 * custom scroll that tells children to follow scroll's width when
 * resized. Thanks to Greg Ercolano from FLTK dev team.
 * http://seriss.com/people/erco/fltk/
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

#include "liquidScroll.h"
#include "boxtypes.h"
#include "core/const.h"

geLiquidScroll::geLiquidScroll(int x, int y, int w, int h)
: geScroll(x, y, w, h, Fl_Scroll::VERTICAL_ALWAYS)
{
}

/* -------------------------------------------------------------------------- */

void geLiquidScroll::resize(int X, int Y, int W, int H)
{
	int nc = children() - 2; // skip hscrollbar and vscrollbar
	for (int t = 0; t < nc; t++)
	{ // tell children to resize to our new width
		Fl_Widget* c = child(t);
		c->resize(c->x(), c->y(), W - 24, c->h()); // W-24: leave room for scrollbar
	}
	init_sizes(); // tell scroll children changed in size
	Fl_Scroll::resize(X, Y, W, H);
}
