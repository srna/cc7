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

#include <cc7/ByteArray.h>

namespace cc7
{
namespace tests
{
	class TestResource;
	
	/**
	 The TestFile is a simple interface providing a filesystem-like
	 operations, like data reading & seeking over the file.
	 
	 In fact, there's no regular file behind this object and all data
	 is provided from static memory buffer.
	 */
	class TestFile
	{
	public:
		
		/**
		 Constructs a copy of test file |f|. The copy will have the same 
		 size, reading offset and the referenced TestResource, but can be used 
		 as a completely separated handle to the underlying resource.
		 */
		TestFile(const TestFile & f) = default;
		/**
		 Move constrctor.
		 */
		TestFile(TestFile && f) = default;
		/**
		 Assign operator.
		 */
		TestFile & operator=(const TestFile & t) = default;
		/**
		 Move operator.
		 */
		TestFile & operator=(TestFile && t) = default;
		
		/**
		 Returns true if this file is valid.
		 */
		bool isValid() const;
		
		/**
		 Returns a file size in bytes.
		 */
		size_t size() const;
		
		/**
		 Returns a current reading offset in this file.
		 */
		size_t offset() const;
		
		/**
		 Returns a number of bytes remaining for reading.
		 */
		size_t remaining() const;
		
		/**
		 Changes a reading offset to |pos| offset and returns actual
		 reading offset after the change. If requested position
		 is greater than the size of file, then it sets offset
		 to the end of file.
		 */
		size_t seekTo(size_t pos);
		
		/**
		 Skips |size| bytes in the file and returns how many bytes were 
		 skipped.
		 */
		size_t skipSize(size_t size);
		
		/**
		 Reads |size| bytes from the file. If the |size| is less than 
		 the remaining bytes then returns as much bytes as possible.
		 The returned ByteRange is always initialized with the static area
		 of memory, which is never disposed off.
		 */
		cc7::ByteRange readMemory(size_t size);
		
		/**
		 Reads an one byte from the file. If there's no bytes left, then
		 returns TestFile::EndOfFile constant.
		 */
		cc7::U16 readByte();
		
		/**
		 Reads an one line fromt he file. If there's no bytes left, then
		 returns an empty string. Note that the method may return empty
		 string also when the line is empty (e.g. there's new line character
		 at the current offset), so you should check the remaining bytes
		 to distinguish between these two situations.
		 */
		std::string readLine();
		
		/**
		 A constant returned from readByte(), when there's no bytes left.
		 */
		static const cc7::U16 EndOfFile = 0xFFFF;
		
		
	private:
		friend class TestDirectory;
		
		// Private constructor with a resource
		
		/**
		 Constructs an object with TestResource object. This is a private
		 constructor used exclusively in the TestDirectory class. There's
		 no other way for TestFile creation.
		 */
		TestFile(const TestResource * resource);
		
		/**
		 Referenced TestResource object.
		 */
		const TestResource *	_resource;
		
		/**
		 Current reading offset.
		 */
		size_t					_offset;
	};
	
} // cc7::tests
} // cc7
