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

#include "waveFx.h"
#include "const.h"
#include "utils/log.h"
#include "wave.h"
#include <algorithm>
#include <cassert>
#include <cmath>

namespace giada::m::wfx
{
namespace
{
void fadeFrame_(Wave& w, int i, float val)
{
	for (int j = 0; j < w.getChannels(); j++)
		w[i][j] *= val;
}

/* -------------------------------------------------------------------------- */

float getPeak_(const Wave& w, int a, int b)
{
	float peak = 0.0f;
	float abs  = 0.0f;
	for (int i = a; i < b; i++)
	{
		for (int j = 0; j < w.getChannels(); j++) // Find highest value in any channel
			abs = fabs(w[i][j]);
		if (abs > peak)
			peak = abs;
	}
	return peak;
}
} // namespace

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

constexpr int SMOOTH_SIZE = 32;

void normalize(Wave& w, int a, int b)
{
	float peak = getPeak_(w, a, b);
	if (peak == 0.0f || peak > 1.0f)
		return;

	for (int i = a; i < b; i++)
	{
		for (int j = 0; j < w.getChannels(); j++)
			w[i][j] = w[i][j] * (1.0f / peak);
	}
	w.setEdited(true);
}

/* -------------------------------------------------------------------------- */

int monoToStereo(Wave& w)
{
	if (w.getChannels() >= G_MAX_IO_CHANS)
		return G_RES_OK;

	AudioBuffer newData;
	newData.alloc(w.getSize(), G_MAX_IO_CHANS);

	for (int i = 0; i < newData.countFrames(); i++)
		for (int j = 0; j < newData.countChannels(); j++)
			newData[i][j] = w[i][0];

	w.replaceData(std::move(newData));

	return G_RES_OK;
}

/* -------------------------------------------------------------------------- */

void silence(Wave& w, int a, int b)
{
	u::log::print("[wfx::silence] silencing from %d to %d\n", a, b);

	for (int i = a; i < b; i++)
		for (int j = 0; j < w.getChannels(); j++)
			w[i][j] = 0.0f;
	w.setEdited(true);
}

/* -------------------------------------------------------------------------- */

void cut(Wave& w, int a, int b)
{
	if (a < 0)
		a = 0;
	if (b > w.getSize())
		b = w.getSize();

	/* Create a new temp wave and copy there the original one, skipping the a-b
    range. */

	int newSize = w.getSize() - (b - a);

	AudioBuffer newData;
	newData.alloc(newSize, w.getChannels());

	u::log::print("[wfx::cut] cutting from %d to %d\n", a, b);

	for (int i = 0, k = 0; i < w.getSize(); i++)
	{
		if (i < a || i >= b)
		{
			for (int j = 0; j < w.getChannels(); j++)
				newData[k][j] = w[i][j];
			k++;
		}
	}

	w.replaceData(std::move(newData));
	w.setEdited(true);
}

/* -------------------------------------------------------------------------- */

void trim(Wave& w, Frame a, Frame b)
{
	if (a < 0)
		a = 0;
	if (b > w.getSize())
		b = w.getSize();

	Frame newSize = b - a;

	AudioBuffer newData;
	newData.alloc(newSize, w.getChannels());

	u::log::print("[wfx::trim] trimming from %d to %d (area = %d)\n", a, b, b - a);

	for (int i = 0; i < newData.countFrames(); i++)
		for (int j = 0; j < newData.countChannels(); j++)
			newData[i][j] = w[i + a][j];

	w.replaceData(std::move(newData));
	w.setEdited(true);
}

/* -------------------------------------------------------------------------- */

void paste(const Wave& src, Wave& des, Frame a)
{
	assert(src.getChannels() == des.getChannels());

	AudioBuffer newData;
	newData.alloc(src.getSize() + des.getSize(), des.getChannels());

	/* |---original data---|///paste data///|---original data---|
	         des[0, a)      src[0, src.size)   des[a, des.size)	*/

	newData.copyData(des[0], a, 0);
	newData.copyData(src[0], src.getSize(), a);
	newData.copyData(des[a], des.getSize() - a, src.getSize() + a);

	des.replaceData(std::move(newData));
	des.setEdited(true);
}

/* -------------------------------------------------------------------------- */

void fade(Wave& w, int a, int b, Fade type)
{
	u::log::print("[wfx::fade] fade from %d to %d (range = %d)\n", a, b, b - a);

	float m = 0.0f;
	float d = 1.0f / (float)(b - a);

	if (type == Fade::IN)
		for (int i = a; i <= b; i++, m += d)
			fadeFrame_(w, i, m);
	else
		for (int i = b; i >= a; i--, m += d)
			fadeFrame_(w, i, m);

	w.setEdited(true);
}

/* -------------------------------------------------------------------------- */

void smooth(Wave& w, int a, int b)
{
	/* Do nothing if fade edges (both of SMOOTH_SIZE samples) are > than selected 
	portion of wave. SMOOTH_SIZE*2 to count both edges. */

	if (SMOOTH_SIZE * 2 > (b - a))
	{
		u::log::print("[wfx::smooth] selection is too small, nothing to do\n");
		return;
	}

	fade(w, a, a + SMOOTH_SIZE, Fade::IN);
	fade(w, b - SMOOTH_SIZE, b, Fade::OUT);
}

/* -------------------------------------------------------------------------- */

void shift(Wave& w, Frame offset)
{
	if (offset < 0)
		offset = (w.getSize() + w.getChannels()) + offset;

	float* begin = w.getFrame(0);
	float* end   = w.getFrame(0) + (w.getSize() * w.getChannels());

	std::rotate(begin, end - (offset * w.getChannels()), end);
	w.setEdited(true);
}

/* -------------------------------------------------------------------------- */

void reverse(Wave& w, Frame a, Frame b)
{
	/* https://stackoverflow.com/questions/33201528/reversing-an-array-of-structures-in-c */
	float* begin = w.getFrame(0) + (a * w.getChannels());
	float* end   = w.getFrame(0) + (b * w.getChannels());

	std::reverse(begin, end);

	w.setEdited(true);
}
} // namespace giada::m::wfx
