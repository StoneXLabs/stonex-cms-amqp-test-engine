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
#include <chrono>
#include <Configuration/TestCaseConfiguration.h>
#include "TestObserver.h"
#include <Verifier/EventStatus.h>

class TestNotifier {
public:
	TestNotifier(const TestCaseConfiguration& config, TestObserver* reporter);
	virtual ~TestNotifier();
	void start();
	void end();
	void skip();
	void testEvent(const EventStatus& event);


	friend std::ostream& operator<<(std::ostream& os, const TestNotifier& dt);


private:
	TestCaseConfiguration mConfiguration;
	TestObserver* mReporter{ nullptr };
	std::chrono::system_clock::time_point mStart;
	std::chrono::system_clock::time_point mEnd;
	int mErrorCount{ 0 };
};

