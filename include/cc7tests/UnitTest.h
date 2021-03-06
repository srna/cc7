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
#include <cc7tests/TestLog.h>
#include <functional>

namespace cc7
{
namespace tests
{
	class TestLog;
	class TestManager;
	
	/**
	 The UnitTest is a base class for all unit tests in cc7tests framework.
	 You can inherit your own unit test from this class.
	 */
	class UnitTest
	{
	public:
		
		/**
		 Constructs a new base unit test. You should register all test methods
		 in your derived test's constructor.
		 */
		UnitTest();
		
		/**
		 Destructs unit test
		 */
		virtual ~UnitTest();
		
		
		//
		// Methods for overriding
		//
		
		/**
		 Called only once per test run, before the test execution.
		 */
		virtual void	instanceSetUp() { }
		
		/**
		 Called only once per test run, after the test execution.
		 */
		virtual void	instanceTearDown() { }
		
		/**
		 Called for each test method, before the method execution.
		 */
		virtual void	setUp() { }
		
		/**
		 Called for each test method, after the method execution.
		 */
		virtual void	tearDown() { }

		/**
		 Returns associated test log.
		 */
		TestLog & tl();
		TestLog & tl() const;
		
		/**
		 Returns associated TestManager
		 */
		TestManager & testManager();
		TestManager & testManager() const;
		
	protected:
		
		void registerTestMethod(std::function<void()> method, const char * description);
		
		
	private:
		
		friend class TestManager;
		
		// Private methods
		bool runTest(TestManager * manager, TestLog * log);
		
		// Members
		TestLog * _log;
		TestManager * _manager;
		std::vector<std::tuple<std::function<void()>, std::string>>	_methods;
	};
	
	
} // cc7::tests
} // cc7