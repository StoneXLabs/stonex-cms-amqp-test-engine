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

#include <sstream>
#include <Configuration/TestCaseConfiguration.h>

TestCaseConfiguration::TestCaseConfiguration(const std::string& testCaseName, const std::string& testFunctionName, bool enabled, const WrapperConfiguration& uutConfiguration, const TestCasePerformerConfiguration& testPerformerConfiguration, const TestCaseVerifierConfiguration& testVerifierConfiguration)
	:WrapperConfiguration(uutConfiguration),
	TestCasePerformerConfiguration(testPerformerConfiguration),
	TestCaseVerifierConfiguration(testVerifierConfiguration),
	mTestCaseName{ testCaseName },
	mTestFunctionName{ testFunctionName },
	mEnabled{ enabled }
{
}

TestCaseConfiguration& TestCaseConfiguration::operator=(const TestCaseConfiguration& other)
{
	mTestCaseName = other.mTestCaseName;
	mTestFunctionName = other.mTestFunctionName;
	mEnabled = other.mEnabled;

	return *this;
}

std::string TestCaseConfiguration::testName() const 
{
	return mTestCaseName; 
}

std::string TestCaseConfiguration::testFunctionName() const 
{
	return mTestFunctionName; 
}

bool TestCaseConfiguration::enabled() const 
{ 
	return mEnabled; 
}

const WrapperConfiguration& TestCaseConfiguration::uutConfig() const
{
	return *this;
}

const TestCaseVerifierConfiguration & TestCaseConfiguration::verifierConfig() const
{
	return *this;
}

const TestCasePerformerConfiguration & TestCaseConfiguration::performerConfig() const
{
	return *this;
}

bool operator== (const TestCaseConfiguration& lhs, const TestCaseConfiguration& rhs)
{


	
	return lhs.mTestCaseName == rhs.mTestCaseName &&
		lhs.mTestFunctionName == rhs.mTestFunctionName &&
		lhs.mEnabled == rhs.mEnabled &&
		lhs.uutConfig() == rhs.uutConfig() &&
		lhs.verifierConfig() == rhs.verifierConfig() &&
		lhs.performerConfig() == rhs.performerConfig();
}

std::ostream& operator<<(std::ostream& os, const TestCaseConfiguration& dt)
{
	os << dt.mTestCaseName << dt.mEnabled ? "\n" : "Test Disabled\n";
	os << "CMS config\n" << dt.uutConfig();
	return os;
}
