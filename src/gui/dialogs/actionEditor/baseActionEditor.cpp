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

#include "baseActionEditor.h"
#include "core/action.h"
#include "core/clock.h"
#include "core/conf.h"
#include "core/const.h"
#include "core/midiEvent.h"
#include "glue/channel.h"
#include "gui/elems/actionEditor/gridTool.h"
#include "gui/elems/basics/choice.h"
#include "gui/elems/basics/scrollPack.h"
#include "utils/gui.h"
#include "utils/string.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <cassert>
#include <string>

namespace giada
{
namespace v
{
gdBaseActionEditor::gdBaseActionEditor(ID channelId)
: gdWindow(640, 284)
, channelId(channelId)
, ratio(G_DEFAULT_ZOOM_RATIO)
{
	using namespace giada::m;

	if (conf::conf.actionEditorW)
	{
		resize(conf::conf.actionEditorX, conf::conf.actionEditorY,
		    conf::conf.actionEditorW, conf::conf.actionEditorH);
		ratio = conf::conf.actionEditorZoom;
	}
}

/* -------------------------------------------------------------------------- */

gdBaseActionEditor::~gdBaseActionEditor()
{
	using namespace giada::m;

	conf::conf.actionEditorX    = x();
	conf::conf.actionEditorY    = y();
	conf::conf.actionEditorW    = w();
	conf::conf.actionEditorH    = h();
	conf::conf.actionEditorZoom = ratio;
}

/* -------------------------------------------------------------------------- */

void gdBaseActionEditor::cb_zoomIn(Fl_Widget* /*w*/, void* p) { ((gdBaseActionEditor*)p)->zoomIn(); }
void gdBaseActionEditor::cb_zoomOut(Fl_Widget* /*w*/, void* p) { ((gdBaseActionEditor*)p)->zoomOut(); }

/* -------------------------------------------------------------------------- */

void gdBaseActionEditor::computeWidth()
{
	fullWidth = frameToPixel(m::clock::getFramesInSeq());
	loopWidth = frameToPixel(m::clock::getFramesInLoop());
}

/* -------------------------------------------------------------------------- */

Pixel gdBaseActionEditor::frameToPixel(Frame f) const
{
	return f / ratio;
}

Frame gdBaseActionEditor::pixelToFrame(Pixel p, bool snap) const
{
	return snap ? gridTool->getSnapFrame(p * ratio) : p * ratio;
}

/* -------------------------------------------------------------------------- */

void gdBaseActionEditor::zoomIn()
{
	float ratioPrev = ratio;

	ratio /= 2;
	if (ratio < MIN_RATIO)
		ratio = MIN_RATIO;

	if (ratioPrev != ratio)
	{
		rebuild();
		centerViewportIn();
		redraw();
	}
}

/* -------------------------------------------------------------------------- */

void gdBaseActionEditor::zoomOut()
{
	float ratioPrev = ratio;

	ratio *= 2;
	if (ratio > MAX_RATIO)
		ratio = MAX_RATIO;

	if (ratioPrev != ratio)
	{
		rebuild();
		centerViewportOut();
		redraw();
	}
}

/* -------------------------------------------------------------------------- */

void gdBaseActionEditor::centerViewportIn()
{
	Pixel sx = Fl::event_x() + (viewport->xposition() * 2);
	viewport->scroll_to(sx, viewport->yposition());
}

void gdBaseActionEditor::centerViewportOut()
{
	Pixel sx = -((Fl::event_x() + viewport->xposition()) / 2) + viewport->xposition();
	if (sx < 0)
		sx = 0;
	viewport->scroll_to(sx, viewport->yposition());
}

/* -------------------------------------------------------------------------- */

int gdBaseActionEditor::getActionType() const
{
	if (actionType->value() == 0)
		return m::MidiEvent::NOTE_ON;
	else if (actionType->value() == 1)
		return m::MidiEvent::NOTE_OFF;
	else if (actionType->value() == 2)
		return m::MidiEvent::NOTE_KILL;

	assert(false);
	return -1;
}

/* -------------------------------------------------------------------------- */

void gdBaseActionEditor::prepareWindow()
{
	u::gui::setFavicon(this);

	std::string l = "Action Editor";
	if (m_data.channelName != "")
		l += " - " + m_data.channelName;
	copy_label(l.c_str());

	set_non_modal();
	size_range(640, 284);
	resizable(viewport);

	show();
}

/* -------------------------------------------------------------------------- */

int gdBaseActionEditor::handle(int e)
{
	switch (e)
	{
	case FL_MOUSEWHEEL:
		Fl::event_dy() == -1 ? zoomIn() : zoomOut();
		return 1;
	default:
		return Fl_Group::handle(e);
	}
}
} // namespace v
} // namespace giada
