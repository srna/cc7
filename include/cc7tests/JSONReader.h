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
#include <cc7tests/JSONValue.h>

namespace cc7
{
namespace tests
{
	/**
	 Yet another JSON parser 
	 
	 
	 */
	
	class TestDirectory;
	
	/**
	 Parses a JSON string and stores the constructed DOM into the |out_value| reference. 
	 Returns false if parser can't process the provided string. If the |out_error| pointer
	 is not null then the detailed error description is stored to the string.
	 */
	bool JSON_ParseString(const std::string & str, JSONValue & out_value, std::string * out_error = nullptr);
	
	/**
	 Parses a provided JSON string in form of ByteRange and stores the constructed DOM into 
	 the |out_value| reference.  Returns false if parser can't process the provided string. 
	 If the |out_error| pointer is not null then the detailed error description is stored
	 to the string.
	 */
	bool JSON_ParseData(const cc7::ByteRange & range, JSONValue & out_value, std::string * out_error = nullptr);
	
	/**
	 Parses a requested file at |path| from the test directory |dir|.
	 Returns DOM constructed from the JSON data or throws an exception when the parser can't
	 parse the data.
	 */
	JSONValue JSON_ParseFile(const TestDirectory & dir, const std::string & path);
	
} // cc7::tests
} // cc7
