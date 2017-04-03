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

#include <cc7/ByteRange.h>

namespace cc7
{
namespace tests
{
	/**
	 The TestResource class represents a continuous immutable region 
	 of the memory which can be used later as a data for unit testing.
	 This object is usually used in a cooperation with TestDirectory to
	 build a simple directory-file hierarchies. Check documentation about
	 TestDirectory for more details.
	 
	 Discussion
	 
	 Constructing the test resources and directories manually is possible, but
	 it's notvery practical technique. Instead of doing this, you can prefer 
	 a "data-converter" which is specially designed for creation a hierarchies
	 of TestResource & TestDirectory objects. Check the documentation
	 */
	class TestResource
	{
	public:
		/**
		 Constructs a test resource object for given memory region and for |path|.
		 The associated memory and path string must exist during the lifetime
		 of the TestResource object.
		 */
		TestResource(const cc7::byte * data, size_t size, const char * path);
		
		/**
		 Returns a pointer to resource data pointer.
		 */
		const cc7::byte * data() const
		{
			return _range.data();
		}
		
		/**
		 Returns a number of bytes stored in the resource.
		 */
		size_t size() const
		{
			return _range.size();
		}
		
		/**
		 Returns a path associated with this resource.
		 */
		const char * path() const
		{
			return _path;
		}
		
		/**
		 Returns a ByteRange object with all bytes stored in the resource.
		 */
		cc7::ByteRange range() const
		{
			return _range;
		}
		
	private:
		
		cc7::ByteRange		_range;
		const char *		_path;
	};
	
} // cc7::tests
} // cc7
