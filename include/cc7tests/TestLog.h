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
#include <mutex>
#include <set>

namespace cc7
{
namespace tests
{
	/**
	 The TestLogData structure contains all information collected 
	 during the testing session. You can obtain a copy of this
	 structure by calling TestLog::logData() method.
	 */
	struct TestLogData
	{
		/**
		 The Counters structure contains various counters
		 about the testing session.
		 */
		struct Counters
		{
			Counters() :
				incidents_count(0),
				current_test_incidents_count(0),
				executed_tests(0),
				passed_tests(0),
				failed_tests(0),
				skipped_tests(0),
				elapsed_time(0.0)
			{
			}
			
			/**
			 Resets all counters to initial values.
			 */
			void reset()
			{
				incidents_count = 0;
				current_test_incidents_count = 0;
				executed_tests = 0;
				passed_tests = 0;
				failed_tests = 0;
				skipped_tests = 0;
				elapsed_time = 0.f;
			}

			/**
			 Number of incidents valid for a whole testing session.
			 */
			int incidents_count;
			/**
			 Number of incidents valid for running test.
			 */
			int current_test_incidents_count;
			
			/**
			 Number of executed tests;
			 */
			int executed_tests;
			/**
			 Number of passed tests.
			 */
			int passed_tests;
			/**
			 Number of failed tests.
			 */
			int failed_tests;
			/**
			 Number of skipped tests.
			 */
			int skipped_tests;
			/**
			 Time spent for tests.
			 */
			double elapsed_time;
		};
		
		TestLogData()
		{
		}
		
		/**
		 Resets all members of TestLogData structure to appropriate
		 initial values.
		 */
		void reset()
		{
			log.clear();
			incidents.clear();
			c.reset();
		}
		
		/**
		 Full log from testing.
		 */
		std::string log;
		/**
		 Contains only incidents.
		 */
		std::string incidents;
		/**
		 Contains all counters.
		 */
		Counters c;
	};
	
	/**
	 The TestLog class collects all testing information during the testing.
	 Typically, this class collects all logs and incidents which occured 
	 during the tests.
	 
	 The TestLog implementation is thread-safe.
	 */
	class TestLog
	{
	public:
		
		// Construction / Destruction
		
		TestLog();
		~TestLog();
		
		// MARK: - Messages
		
		/**
		 Adds |message| to the test log.
		 */
		void logMessage(const char * message);
		
		/**
		 Adds |message| to the test log.
		 */
		void logMessage(const std::string & message);
		
		/**
		 Adds formatted message to the test log. The formatted string depends on
		 |format| string and optional parameters.
		 */
		void logFormattedMessage(const char * format, ...);

		/**
		 Adds incident to the test log. The |file| and |line| parameter determines an unique
		 location of the incident while the repetitive events will be ignored. So, only the first 
		 occurence of the same incident is added to the test log and incidents log. The optional 
		 |condition| parameter may represent a failed condition, which triggered the incident report. 
		 The |format| string and subsequent optional parameters allows construction of almost arbitrary
		 formatted message.
		 
		 Unlike logMessage or logFormattedMessage methods, the method adds an incident to the both test 
		 and incidents log.
		 */
		void logIncident(const char * file, int line, const char * condition, const char * format, ...);

		
		// MARK: - Indentation
		
		/**
		 Sets current indentation level to |indentation_level| value.
		 */
		void setIndentationLevel(size_t indentation_level);
		
		/**
		 Returns current indentation level.
		 */
		size_t indentationLevel() const;
		
		/**
		 Sets indentation prefix to desired |prefix| value. The final indentation is
		 constructed as |prefix| + |' ' x indentation_level| + |suffix|.
		 */
		void setIndentationPrefix(const std::string & prefix);
		
		/**
		 Returns current identation prefix.
		 */
		std::string indentationPrefix() const;

		/**
		 Sets indentation suffix to desired |suffix| value. The final indentation is
		 constructed as |prefix| + |' ' x indentation_level| + |suffix|.
		 */
		void setIndentationSuffix(const std::string & suffix);
		
		/**
		 Returns current identation suffix.
		 */
		std::string indentationSuffix() const;
		
		
		// MARk: - Configuration
		
		/**
		 Enables or disables passing messages to system log. The logging also depends
		 on whether the CC7_LOG() is enabled.
		 */
		void setDumpToSystemLogEnabled(bool enabled);
		
		/**
		 Returns whether the dumping to system log is enabled or not.
		 */
		bool dumpToSystemLogEnabled() const;
		
		/**
		 Enables or disables software breakpoint triggered on any incident.
		 */
		void setIncidentBreakpointEnabled(bool enabled);
		/**
		 Returns whether the incidents breakpoint is enabled or not.
		 */
		bool incidentBreakpointEnabled() const;
		
		
		// MARK: - Results and control
		
		/**
		 Returns copy of internal TestLogData structure with actual and full 
		 content of the testing log.
		 */
		TestLogData logData() const;
		
		/**
		 Returns copy of internal TestLogData::Counters structure with actual counters.
		 */
		TestLogData::Counters logDataCounters() const;
		
		/**
		 Clears whole content of test log including current level indentation.
		 */
		void clearLogData();
		
		/**
		 Clears incidents counter for current test. The test framework must call this
		 method before start of each test.
		 */
		void clearCurrentTestIncidentsCount();
		
		
		
		// MARK: - Passed / Failed counters
		
		/**
		 Increases number of passed tests
		 */
		void addPassedTest();
		/**
		 Increases number of failed tests
		 */
		void addFailedTest();
		/**
		 Increases number of sipped tests.
		 */
		void addSkippedTest();
		/**
		 Sets elapsed time to internal TestLogData structure.
		 */
		void setElapsedTime(double time);
		
	private:
		
		// MARK: - Private methods & members
		
		/**
		 Updates internal _indentation string, based on desired level of indentation.
		 The final string is constructed as |prefix| + |' ' x indentation_level| + |suffix|
		 */
		void updateIndentationToLevel(size_t level);
		
		/**
		 Appends |string| to the log. The provided string can contain multiple lines.
		 */
		void appendMultilineString(const std::string & string);
		
		/**
		 Returns current indentation level.
		 */
		size_t indentationLevelImpl() const;
		
		/**
		 Private mutex. The member is mutable, due to fact, that we need to access
		 lock also in const getters.
		 */
		mutable std::mutex	_lock;
		/**
		 The whole indentation string which is prepended to each line added to the log.
		 It is constructed as: _indentation_prefix + (' ' x indentation_level) + _indentation_suffix.
		 */
		std::string		_indentation;
		/**
		 Current indentation prefix.
		 */
		std::string		_indentation_prefix;
		/**
		 Current indentation suffix.
		 */
		std::string		_indentation_suffix;
		/**
		 Collected log.
		 */
		TestLogData		_log_data;
		/**
		 The set<string> contains locations for already reported incidents. The key for 
		 an unique location is calculated as "path:line"
		 */
		std::set<std::string> _incident_locations_set;
		/**
		 If true, then the logger will pass log immediately to the system log.
		 */
		bool			_dump_to_system_log;
		/**
		 If true, then the logger will break execution at software breakpoint, for each reported
		 incident.
		 */
		bool			_incident_breakpoint;
	};
	
	
} // cc7::tests
} // cc7
