/*
 * Copyright 2023 StoneX Financial Ltd.
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

#include <string>
#include <Notifier/TeamCityTestObserver.h>

void TeamCityTestObserver::onMessage(const NotifyMessage& report)
{
	switch (auto s = report.messageType())
	{
	case REPORT_MESSAGE_TYPE::TEST_SUITE_START:
		std::cout << "##teamcity[testSuiteStarted name='" << report.source() << "']" << std::endl;
		break;
	case REPORT_MESSAGE_TYPE::TEST_SUITE_END:
		std::cout << "##teamcity[testSuiteFinished name='" << report.source() << "']" << std::endl;
		break;
	case REPORT_MESSAGE_TYPE::TEST_START:
		std::cout << "##teamcity[testStarted name='"<< report.source()<<"']" << std::endl;
		break;
	case REPORT_MESSAGE_TYPE::TEST_END:
		std::cout << "##teamcity[testFinished name='" << report.source() <<  "' " << report.message() <<"]" << std::endl;
		break;
	case REPORT_MESSAGE_TYPE::TEST_ERROR:
		std::cout << "##teamcity[testFailed name='" << report.source() << "' message='"<<report.message()<<"' details='message and stack trace']" << std::endl;
		mErrorCount++;
		break;
	case REPORT_MESSAGE_TYPE::TEST_SUCCESS:
		std::cout << "##teamcity[testFinished name='" << report.source() << "' duration='<test_duration_in_milliseconds>']" << std::endl;
		break;
	case REPORT_MESSAGE_TYPE::TEST_IGNORED:
		std::cout << "##teamcity[testIgnored name='" << report.source() << "' message='test disabled']" << std::endl;
		break;
	case REPORT_MESSAGE_TYPE::EXCEPTION:
		break;
		std::cout << "##teamcity[message text='compiler output']"<<std::endl;
	case REPORT_MESSAGE_TYPE::GENERAL:
		break;
		std::cout << "##teamcity[message text='compiler output']" << std::endl;
	default:
		break;
	}
}

long long TeamCityTestObserver::errorCount() const
{
	return mErrorCount;
}

