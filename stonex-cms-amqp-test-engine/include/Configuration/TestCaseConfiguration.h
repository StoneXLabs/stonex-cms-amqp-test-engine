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

#pragma once
#include <string>

#include <Configuration/CMSWrapperConfiguration.h>
#include <Configuration/TestCasePerformerConfiguration.h>
#include <Configuration/TestCaseVerifierConfiguration.h>

class TestCaseConfiguration
{
public:
	TestCaseConfiguration(const std::string& testCaseName, const std::string& testFunctionName, bool enabled, const CMSWrapperConfiguration& uutConfiguration, const TestCasePerformerConfiguration& testPerformerConfiguration, const TestCaseVerifierConfiguration& testVertestVerifierConfiguration);

	TestCaseConfiguration& operator=(const TestCaseConfiguration& other);

	std::string testName() const;
	std::string testFunctionName() const;
	bool enabled() const;

	const CMSWrapperConfiguration& uutConfig() const;
	const TestCaseVerifierConfiguration& verifierConfig() const;
	const TestCasePerformerConfiguration& performerConfig() const;

	friend std::ostream& operator<<(std::ostream& os, const TestCaseConfiguration& dt);

private:
	std::string mTestCaseName;
	std::string mTestFunctionName;
	bool mEnabled;
	CMSWrapperConfiguration mUnitUnderTestConfig;
	TestCaseVerifierConfiguration mTestExpectationConfig;
	TestCasePerformerConfiguration mTestConfig;
};