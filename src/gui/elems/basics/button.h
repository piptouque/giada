/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * geButton
 * A regular button.
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

#ifndef GE_BUTTON_H
#define GE_BUTTON_H

#include <FL/Fl_Button.H>

class geButton : public Fl_Button
{
public:
	geButton(int x, int y, int w, int h, const char* l = nullptr,
	    const char** imgOff = nullptr, const char** imgOn = nullptr,
	    const char** imgDisabled = nullptr);

	void draw() override;

  protected:
	void draw(const char** img, Fl_Color bgColor, Fl_Color textColor);

	const char** imgOff;
	const char** imgOn;
	const char** imgDisabled;

	Fl_Color bgColor0; // background not clicked
	Fl_Color bgColor1; // background clicked
	Fl_Color bdColor;  // border
	Fl_Color txtColor; // text
};

#endif
