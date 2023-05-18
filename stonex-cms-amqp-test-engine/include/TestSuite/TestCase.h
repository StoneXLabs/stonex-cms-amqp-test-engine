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

#include <functional>
#include <string>
#include <Configuration/TestCaseConfiguration.h>
#include <Wrapper/CMSClientTestUnit.h>
#include <Notifier/TestNotifier.h>
#include <MessageSender/MessageSenderFactory.h>
#include "TestFunctionRegister.h"
#include "TestCaseStatus.h"
#include "TestCasePerformer.h"
#include "TestCaseVerifier.h"

class TestCase : public Notifier
{
public:
	TestCase(const TestCaseConfiguration& test_config, MessageSenderFactory* factory, const TestFunctionRegister& functionRegister, TestObserver* observer);
	void run();
	
private:
	void testEvent(const EventStatus& event) override;

private:
	CMSClientTestUnit mTestedObject;
	TestCasePerformer mTestPerformer;
	TestCaseVerifier mTestVerifier;
	test_method mTestFunction;
	const std::string mTestName;
	bool mTestSuccess{ true };
};

