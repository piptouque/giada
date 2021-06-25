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

#include "core/conf.h"
#include "core/const.h"
#include "core/graphics.h"
#include <FL/Fl_Pixmap.H>
#include <FL/fl_draw.H>
#ifdef WITH_VST
#include "deps/juce-config.h"
#endif
#include "about.h"
#include "gui/elems/basics/box.h"
#include "gui/elems/basics/button.h"
#include "utils/gui.h"
#include "utils/string.h"

namespace giada::v
{
gdAbout::gdAbout()
#ifdef WITH_VST
: gdWindow(340, 415, "About Giada")
#else
: gdWindow(340, 330, "About Giada")
#endif
, logo(8, 20, 324, 86)
, text(8, 120, 324, 140)
, close(252, h() - 28, 80, 20, "Close")
#ifdef WITH_VST
, vstText(8, 315, 324, 46)
, vstLogo(8, 265, 324, 50)
#endif
{
	end();
	set_modal();

	std::string version = G_VERSION_STR;
#ifdef G_DEBUG_MODE
	version += " (debug build)";
#endif

	logo.image(new Fl_Pixmap(giada_logo_xpm));
	text.align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_TOP);
	text.copy_label(std::string(
	    "Version " + version + " (" BUILD_DATE ")\n\n"
	                           "Developed by Monocasual Laboratories\n\n"
	                           "Released under the terms of the GNU General\n"
	                           "Public License (GPL v3)\n\n"
	                           "News, infos, contacts and documentation:\n"
	                           "www.giadamusic.com")
	                    .c_str());

#ifdef WITH_VST

	vstLogo.image(new Fl_Pixmap(vstLogo_xpm));
	vstLogo.position(vstLogo.x(), text.y() + text.h() + 8);
	vstText.label(
	    "VST Plug-In Technology by Steinberg\n"
	    "VST is a trademark of Steinberg\nMedia Technologies GmbH");
	vstText.position(vstText.x(), vstLogo.y() + vstLogo.h());

#endif

	close.callback(cb_close, (void*)this);
	u::gui::setFavicon(this);
	setId(WID_ABOUT);
	show();
}

/* -------------------------------------------------------------------------- */

void gdAbout::cb_close(Fl_Widget* /*w*/, void* p) { ((gdAbout*)p)->cb_close(); }

/* -------------------------------------------------------------------------- */

void gdAbout::cb_close()
{
	do_callback();
}
} // namespace giada::v