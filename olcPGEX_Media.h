/*
	olcPGEX_Media.h

	+-------------------------------------------------------------+
	|         OneLoneCoder Pixel Game Engine Extension            |
	|                       Media - v1.0                          |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	This is an extension to the olcPixelGameEngine, which provides
	the ability to easily load various video formats.


	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2022 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


	Author
	~~~~~~
	Piratux


	Contributors
	~~~~~~~~~~~~
*/

#ifndef OLC_PGEX_MEDIA_H
#define OLC_PGEX_MEDIA_H

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

#include "opencv2/opencv.hpp"

namespace olc
{
	// A threadsafe-queue.
	// Modification of queue provided here: https://stackoverflow.com/a/16075550
	// Should be compatible with C++11
	template <class T>
	class SafeQueue
	{
	public:
		SafeQueue(void)
			: q()
			, m()
			, c()
		{}

		~SafeQueue(void)
		{}

		// Add an element to the queue.
		void enqueue(T t)
		{
			std::lock_guard<std::mutex> lock(m);
			q.push(t);
			c.notify_one();
		}

		// Get the "front"-element.
		// If the queue is empty, wait till a element is avaiable.
		T dequeue(void)
		{
			std::unique_lock<std::mutex> lock(m);
			while (q.empty())
			{
				// release lock as long as the wait and reaquire it afterwards.
				c.wait(lock);
			}
			T val = q.front();
			q.pop();
			return val;
		}

		size_t size() {
			std::unique_lock<std::mutex> lock(m);
			return q.size();
		}

	private:
		std::queue<T> q;
		mutable std::mutex m;
		std::condition_variable c;
	};



	using namespace cv;

	// OpenCV wrapper that simplifies reading frame data from a video with 
	// an optimisation of storing decoded images in a queue.
	class Media : public olc::PGEX
	{
	private:
		std::string video_path;
		int32_t max_queue_size;

		std::mutex mutex;
		std::condition_variable conditional;

		VideoCapture cap;
		SafeQueue<Mat> frames;

		std::thread frame_loader;

		// forces frame loading thread 
		std::atomic<bool> keep_loading = true;
		// if false, video capture wasn't opened, or end of video was reached
		std::atomic<bool> can_capture_frames = false;

	public:
		Media(const std::string& video_path, uint32_t max_queue_size = 5);
		~Media();

		// Returns next decoded video frame.
		// WARNING: You must always check if returned frame is valid with "IsFrameValid()"
		// WARNING: In case of unexpected error(although it shouldn't happen), this function 
		// may block the thread which calls this function.
		Mat GetFrame();

		// Returns true if frame isn't empty.
		// Should be called 
		inline bool IsFrameValid(const Mat& frame);

	private:
		void FrameLoadingThread();
	};
}

#ifdef OLC_PGEX_MEDIA
#undef OLC_PGEX_MEDIA

namespace olc
{
	Media::Media(const std::string& video_path, uint32_t max_queue_size)
		: video_path(video_path),
		max_queue_size(max_queue_size)
	{
		cap.open(video_path);

		// Check if opened successfully
		if (!cap.isOpened()) {
			throw std::runtime_error("Exception in Media::Media(): Error opening video stream or file");
		}

		can_capture_frames = true;

		frame_loader = std::thread(&Media::FrameLoadingThread, this);
	}

	Media::~Media() {
		keep_loading = false;
		conditional.notify_one();
		frame_loader.join();
	}

	Mat Media::GetFrame() {
		if (can_capture_frames == false && frames.size() == 0) {
			return Mat();
		}

		while (frames.size() == 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		Mat frame = frames.dequeue();
		conditional.notify_one();

		return frame;
	}


	void Media::FrameLoadingThread() {
		std::unique_lock<std::mutex> lock(mutex);

		while (true) {
			while (frames.size() > max_queue_size && keep_loading) {
				conditional.wait(lock);
			}

			if (keep_loading == false)
				break;

			Mat frame;
			cap >> frame;

			frames.enqueue(frame);

			if (frame.empty()) {
				can_capture_frames = false;
				break;
			}
		}
	}
}

#endif // OLC_PGEX_MEDIA
#endif // OLC_PGEX_MEDIA_H