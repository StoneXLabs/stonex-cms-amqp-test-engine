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
#include <list>

#include "TestCaseConfiguration.h"


class TestSuiteConfiguration
{
public:
	TestSuiteConfiguration(const std::string suiteName = "", const std::list<TestCaseConfiguration>& testCaseConfigs = {});

	TestSuiteConfiguration& operator=(const TestSuiteConfiguration& other);

	int testCaseCount() const;
	std::string name() const;


	std::list<TestCaseConfiguration>::const_iterator testsBegin();
	std::list<TestCaseConfiguration>::const_iterator testsEnd();

private:
	std::string mTestSuiteName;
	std::list<TestCaseConfiguration> mTests;
};

