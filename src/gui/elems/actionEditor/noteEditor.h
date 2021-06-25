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

#ifndef GE_NOTE_EDITOR_H
#define GE_NOTE_EDITOR_H

#include "core/types.h"
#include "gui/elems/basics/scroll.h"

namespace giada::c::actionEditor
{
struct Data;
}
namespace giada::v
{
class gdMidiActionEditor;
class gePianoRoll;
class geNoteEditor : public geScroll
{
public:
	geNoteEditor(Pixel x, Pixel y, gdMidiActionEditor* base);
	~geNoteEditor();

	void rebuild(c::actionEditor::Data& d);
	void scroll();

	gePianoRoll* pianoRoll;

  private:
	gdMidiActionEditor* m_base;
};
} // namespace giada::v

#endif
