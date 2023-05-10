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

#include <Configuration/TestCaseConfiguration.h>
#include <sstream>

TestCaseConfiguration::TestCaseConfiguration(const std::string& testCaseName, const std::string& testFunctionName, bool enabled, const CMSWrapperConfiguration& uutConfiguration, const TestCasePerformerConfiguration& testPerformerConfiguration, const TestCaseVerifierConfiguration& testVertestVerifierConfiguration)
	:mTestCaseName{ testCaseName },
	mTestFunctionName{ testFunctionName },
	mEnabled{ enabled },
	mUnitUnderTestConfig{ uutConfiguration },
	mTestConfig{ testPerformerConfiguration },
	mTestExpectationConfig{ testVertestVerifierConfiguration }
{
}

TestCaseConfiguration& TestCaseConfiguration::operator=(const TestCaseConfiguration& other)
{
	mTestCaseName = other.mTestCaseName;
	mTestFunctionName = other.mTestFunctionName;
	mEnabled = other.mEnabled; 
	mUnitUnderTestConfig = other.mUnitUnderTestConfig;
	mTestConfig = other.mTestConfig;
	mTestExpectationConfig = other.mTestExpectationConfig;

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

const CMSWrapperConfiguration& TestCaseConfiguration::uutConfig() const
{
	return mUnitUnderTestConfig; 
}

const TestCaseVerifierConfiguration & TestCaseConfiguration::verifierConfig() const
{
	return mTestExpectationConfig;
}

const TestCasePerformerConfiguration & TestCaseConfiguration::performerConfig() const
{
	return mTestConfig;
}


std::ostream& operator<<(std::ostream& os, const TestCaseConfiguration& dt)
{
	os << dt.mTestCaseName << dt.mEnabled ? "\n" : "Test Disabled\n";
	os << "CMS config\n" << dt.mUnitUnderTestConfig;
	return os;
}
