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

#include <cc7tests/TestFile.h>

namespace cc7
{
namespace tests
{
	class TestResource;
	
	/**
	 The DestDirectory class is a v
	 */
	class TestDirectory
	{
	public:
		typedef const cc7::tests::TestResource* TResource;
		typedef std::vector<TResource> TResourceList;
		
		/**
		 Constructs an object with list of resources.
		 */
		TestDirectory(std::initializer_list<TResource> il);
		
		/**
		 Destructs an directory object.
		 */
		~TestDirectory();

		/**
		 Returns a new TestFile object for required |path|. The method throws
		 an invalid exception when there's no such file at requested path.
		 */
		TestFile findFile(const std::string & path) const;
		
		/**
		 Returns const reference to all resources available in this directory.
		 */
		const TResourceList & allResources() const;
		
	private:
		
		/**
		 A list of resources stored in this directory.
		 */
		TResourceList _resources;
	};
	
} // cc7::tests
} // cc7
