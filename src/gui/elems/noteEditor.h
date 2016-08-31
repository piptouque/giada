/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2016 Giovanni A. Zuliani | Monocasual
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


#ifndef GE_PIANOROLL_H
#define GE_PIANOROLL_H

#include <FL/Fl.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include "../../core/recorder.h"
#include "baseActionEditor.h"


class geNoteEditor : public Fl_Scroll
{
private:

	class gdActionEditor *pParent;
	class gePianoRoll    *pianoRoll;

public:

	geNoteEditor(int x, int y, class gdActionEditor *parent);
	~geNoteEditor();
	void draw();
	void updateActions();
};


/* -------------------------------------------------------------------------- */


class gePianoRoll : public geBaseActionEditor
{
private:

	/* onItem
	 * is curson on a gePianoItem? */

	bool onItem(int rel_x, int rel_y);

	/* drawSurface*
	 * generate a complex drawing in memory first and copy it to the
	 * screen at a later point in time. Fl_Offscreen surface holds the
	 * necessary data. */

	/* drawSurface1
	 * draw first tile of note values. */

	void drawSurface1();

	/* drawSurface2
	 * draw the rest of the piano roll. */

	void drawSurface2();

	int  push_y;
	Fl_Offscreen surface1;  // notes, no repeat
	Fl_Offscreen surface2;  // lines, x-repeat


public:

	gePianoRoll(int x, int y, int w, class gdActionEditor *pParent);

	void draw();
	int  handle(int e);
	void updateActions();

	enum
	{
		MAX_NOTES = 127,
		CELL_H    = 15
	};
};


/* -------------------------------------------------------------------------- */


class gePianoItem : public Fl_Box
{
private:

	/* getRelX/Y
	 * return x/y point of this item, relative to piano roll (and not to
	 * entire screen) */

	int getRelY() { return y() - parent()->y() - 3; };
	int getRelX() { return x() - parent()->x(); };

	/* getNote
	 * from a relative_y return the real MIDI note, range 0-127. 15 is
	 * the hardcoded value for note height in pixels */

	int getNote(int rel_y);

	/* getY
	 * from a note, return the y position on piano roll */

	int getY(int note);

	/* overlap
	 * check if this item don't overlap with another one. */

	bool overlap();

	Recorder::action *a;
	Recorder::action *b;
	class gdActionEditor *pParent;

	bool selected;
	int  push_x;

	/* MIDI note, start frame, end frame - Used only if it's a newly added
	 * action */ /** FIXME - is it true? */

	int  note;
	int  frame_a;
	int  frame_b;

	/* event - bitmasked MIDI events, generated by record() or by ctor if
	 * not newly added action */

	int event_a;
	int event_b;

	/* changed - if Item has been moved or resized: re-recording needed */

	bool changed;

	/* onLeft,RightEdge - if cursor is on a widget's edge */

	bool onLeftEdge;
	bool onRightEdge;

	/* old_x, old_w - store previous width and position while dragging
	 * and moving, in order to restore it if overlap */

	int old_x, old_w;

public:

	/* pianoItem ctor
	 * if action *a == NULL, record a new action */

	gePianoItem(int x, int y, int rel_x, int rel_y, Recorder::action *a,
		Recorder::action *b, class gdActionEditor *pParent);

	void draw();
	int  handle(int e);
	void record();
	void remove();

	int getFrame_a() { return frame_a; }
	int getFrame_b() { return frame_b; }
	int getNote()    { return note;    }
};

#endif
