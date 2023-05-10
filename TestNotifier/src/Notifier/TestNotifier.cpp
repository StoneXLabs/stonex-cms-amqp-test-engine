/*
 * Copyright 2022 StoneX Financial Ltd.
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Notifier/TestNotifier.h>
#include <string>
//
//TestNotifier::TestNotifier(const TestCaseConfiguration& config, TestObserver* reporter)
//	:mConfiguration{ config },
//	mReporter{ reporter }
//{
//}
//TestNotifier::~TestNotifier()
//{
//	if (mReporter)
//	{
//		if (mErrorCount) 		
//			mReporter->onMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, mConfiguration.testName(), "Encountered "+ std::to_string(mErrorCount) + "errors"));
//
//		mReporter->onMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_END, mConfiguration.testName(), "duration='" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(mEnd - mStart).count()) + "'"));
//
//
//	}
//}
//;
//
//void TestNotifier::start() {
//	mStart = std::chrono::system_clock::now();
//	if (mReporter)
//		mReporter->onMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_START,mConfiguration.testName(), mConfiguration.testFunctionName()));
//};
//
//void TestNotifier::end() {
//	mEnd = std::chrono::system_clock::now();
//};
//
//void TestNotifier::skip()
//{
//	if (mReporter)
//		mReporter->onMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_IGNORED, mConfiguration.testName(), mConfiguration.testFunctionName()));
//	end();
//}
//
//void TestNotifier::testEvent(const EventStatus& event)
//{
//	if (mReporter)
//	{
//		if (!event.correct()) 
//		{
//			mErrorCount++;
//			mReporter->onMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, mConfiguration.testName(), " [" + event.eventSource() + "] " + event.errorMessage()));
//
//		}
//	}
//}
//
//std::ostream & operator<<(std::ostream & os, const TestNotifier & dt)
//{
//	os << "[" << std::chrono::system_clock::to_time_t(dt.mEnd) << "]";
//	os << "Test Case\n" << dt.mConfiguration;
//	return os;
//}

Notifier::Notifier(TestObserver * reporter)
	:mReporter{ reporter }
{
}

void Notifier::testEvent(const EventStatus & event)
{
	if (mReporter)
	{
		if (!event.correct()) 
		{
			mReporter->onMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, "mConfiguration.testName()", " [" + event.eventSource() + "] " + event.errorMessage()));

		}
	}
}


std::ostream & operator<<(std::ostream & os, const Notifier & dt)
{
//	os << "[" << std::chrono::system_clock::to_time_t(dt.mEnd) << "]";
//	os << "Test Case\n" << dt.mConfiguration;
	return os;
}
