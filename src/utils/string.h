/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * utils
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

#ifndef G_UTILS_STRING_H
#define G_UTILS_STRING_H

#include <sstream>
#include <string>
#include <vector>

namespace giada
{
namespace u
{
namespace string
{
template <typename T>
std::string iToString(T t, bool hex = false)
{
	std::stringstream out;
	if (hex)
		out << std::hex << std::uppercase << t;
	else
		out << t;
	return out.str();
}

std::string replace(std::string in, const std::string& search,
    const std::string& replace);

std::string trim(const std::string& s);

std::vector<std::string> split(std::string in, std::string sep);

std::string fToString(float f, int precision);

std::string format(const char* format, ...);

} // namespace string
} // namespace u
} // namespace giada

#endif
