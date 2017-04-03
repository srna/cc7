/*
 * Copyright 2016 Juraj Durech <durech.juraj@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cc7/Platform.h>
#include <functional>

namespace cc7
{
namespace tests
{
	/**
	 The PerformanceTimer class can be used for measuring an elapsed time
	 during the unit testing. The timer is used internally in the testing
	 framework, but can be used also in your own unit testing codes.
	 */
	class PerformanceTimer
	{
	public:
		
		/**
		 Constructs an object and starts counting an elapsed time.
		 */
		PerformanceTimer();
		
		/**
		 Starts a timer. If the timer was started before, then starting
		 the timer will begin a new measurement.
		 */
		void start();
		
		/**
		 Returns elapsed time in seconds since the last start.
		 */
		double elapsedTime();
		
		/**
		 Measures the execution time of |block| and returns elapsed
		 time in seconds.
		 */
		double measureBlock(std::function<void()> block);
	
		/**
		 Returns a human readable string from given time.
		 The |time| parameter is an elapsed time in seconds.
		 */
		static std::string humanReadableTime(double time);
		
	private:
		
		/**
		 Base representing a time at start of the event.
		 */
		cc7::U64 _base;
	};
	
	
	// Following two functions must have platform specific implementation.
	
	/**
	 Returns a current system time. The time representation may differ between
	 the platforms, so you have to use a Platform_GetTimeDiff() function to 
	 convert a two values to the elapsed time. 
	 
	 Platform specific notes
	 
	 The returned value has to represent time at least at the millisecond 
	 precision.
	 */
	cc7::U64 Platform_GetCurrentTime();
	
	/**
	 Returns a time in seconds, calculated from two platform specific time values.
	 The |start| represents a time at the start of the event and the |future| parameter
	 is a time in the future. 
	 
	 
	 Platform specific notes
	 
	 If the |future| is less than the |start| then the behavior is not defined.
	 The implementation may return negative value or zero in this case.
	 */
	double Platform_GetTimeDiff(cc7::U64 start, cc7::U64 future);
	
} // cc7::tests
} // cc7
