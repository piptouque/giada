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

#ifndef G_AUDIO_BUFFER_H
#define G_AUDIO_BUFFER_H

#include "core/types.h"
#include <array>

namespace giada::m
{
/* AudioBuffer
A class that holds a buffer filled with audio data. NOTE: currently it only
supports 2 channels (stereo). Give it a mono stream and it will convert it to
stereo. Give it a multichannel stream and it will throw an assertion. */

class AudioBuffer
{
public:
	static constexpr int NUM_CHANS = 2;

	using Pan = std::array<float, NUM_CHANS>;

	/* AudioBuffer (1)
	Creates an empty (and invalid) audio buffer. */

	AudioBuffer();

	/* AudioBuffer (2)
	Creates an audio buffer and allocates memory for size * channels frames. */

	AudioBuffer(Frame size, int channels);

	/* AudioBuffer (3)
	Creates an audio buffer out of a raw pointer. AudioBuffer created this way
	is instructed not to free the owned data on destruction. */

	AudioBuffer(float* data, Frame size, int channels);

	/* AudioBuffer(const AudioBuffer&)
	Copy constructor. */

	AudioBuffer(const AudioBuffer& o);

	/* AudioBuffer(AudioBuffer&&)
	Move constructor. */

	AudioBuffer(AudioBuffer&& o);

	/* ~AudioBuffer
	Destructor. */

	~AudioBuffer();

	/* operator = (const AudioBuffer& o)
	Copy assignment operator. */

	AudioBuffer& operator=(const AudioBuffer& o);

	/* operator = (AudioBuffer&& o)
	Move assignment operator. */

	AudioBuffer& operator=(AudioBuffer&& o);

	/* operator []
	Given a frame 'offset', returns a pointer to it. This is useful for digging 
	inside a frame, i.e. parsing each channel. How to use it:

		for (int k=0; k<buffer->countFrames(), k++)
			for (int i=0; i<buffer->countChannels(); i++)
				... buffer[k][i] ...

	Also note that buffer[0] will give you a pointer to the whole internal data
	array. */

	float* operator[](int offset) const;

	Frame countFrames() const;
	int   countSamples() const;
	int   countChannels() const;
	bool  isAllocd() const;

	/* getPeak
	Returns the highest value from any channel. */

	float getPeak() const;

	void alloc(Frame size, int channels);
	void free();

	/* copyData (1)
	Copies 'frames' frames from the new 'data' into m_data, and fills m_data 
	starting from frame 'offset'. The new data MUST NOT contain more than
	NUM_CHANS channels. If channels < NUM_CHANS, they will be spread over the
	stereo buffer. */

	void copyData(const float* data, Frame frames, int channels = NUM_CHANS, int offset = 0);

	/* copyData (2)
	Copies 'frames' frames of buffer 'b' onto this one. If 'frames' == -1 the
	whole buffer will be copied. If 'b' has less channels than this one, they 
	will be spread over the current ones. Buffer 'b' MUST NOT contain more 
	channels than this one.  */

	void copyData(const AudioBuffer& b, float gain = 1.0f, Frame frames = -1);

	/* addData
	Merges audio data from buffer 'b' onto this one. Applies optional gain and
	pan if needed. */

	void addData(const AudioBuffer& b, float gain = 1.0f, Pan pan = {1.0f, 1.0f});

	/* clear
	Clears the internal data by setting all bytes to 0.0f. Optional parameters
	'a' and 'b' set the range. */

	void clear(Frame a = 0, Frame b = -1);

	void applyGain(float g);

private:
	void move(AudioBuffer&& o);
	void copy(const AudioBuffer& o);

	float* m_data;
	Frame  m_size;
	int    m_channels;
	bool   m_viewing;
};
} // namespace giada::m

#endif