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

#include <algorithm>
#include <iterator>
#include <Configuration/TestSuiteConfiguration.h>
#include <fmt/format.h>

TestSuiteConfiguration::TestSuiteConfiguration(const std::string suiteName, const std::list<TestCaseConfiguration>& testCaseConfigs)
	:mTestSuiteName{ suiteName },
	mTests{ testCaseConfigs }
{
}


TestSuiteConfiguration& TestSuiteConfiguration::operator=(const TestSuiteConfiguration& other)
{
	mTestSuiteName = other.mTestSuiteName;
	mTests = other.mTests;
	return *this;
}

int TestSuiteConfiguration::testCaseCount() const
{
	return mTests.size(); 
};

std::string TestSuiteConfiguration::name() const
{
	return mTestSuiteName; 
};

std::list<TestCaseConfiguration>::const_iterator TestSuiteConfiguration::testsBegin()
{
	return mTests.begin(); 
};

std::list<TestCaseConfiguration>::const_iterator TestSuiteConfiguration::testsEnd()
{
	return mTests.end(); 
};

bool operator==(const TestSuiteConfiguration & lhs, const TestSuiteConfiguration & rhs)
{
	return 	lhs.mTestSuiteName == rhs.mTestSuiteName &&
		std::equal(std::cbegin(lhs.mTests), std::cend(lhs.mTests), std::cbegin(rhs.mTests));

}

std::ostream & operator<<(std::ostream & os, const TestSuiteConfiguration & dt)
{
	os << fmt::format("Test suite configuration file {}\nTest Case count {}\n", dt.mTestSuiteName, dt.testCaseCount());

	std::copy(std::begin(dt.mTests), std::end(dt.mTests), std::ostream_iterator<TestCaseConfiguration>(os, "\n"));

	return os;
}
