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
#include "TestCase.h"

#include <string>
#include <functional>
#include "Configuration\TestCaseConfiguration.h"
#include "UnitUnderTest/CMSClientTestUnit.h"
#include "TestCasePerformer.h"
#include "MessageReceiver/TestMessageReceiver.h"
#include "TestFunctionRegister.h"


class CompoundTestVerifier;

class SingleTest : public TestCase
{
public:
	SingleTest(const TestCaseConfiguration & test, TestFunctionRegister& functionRegister, TestMessageReciever* receiver, CompoundTestVerifier* testVerifier, const MessageSenderFactory& senderFactory);

	TEST_CASE_STATUS run() override;

	std::function<TEST_CASE_STATUS(CMSClientTestUnit* uut, TestCasePerformer *tcp, TestMessageReciever *tmr)> mCurrentTestFunction{ nullptr };

	std::string SingleTest::testName() const override ;
	VerifierReport* getRaport() override;
private:
	const std::string mTestName;
	bool mEnabled;
	CMSClientTestUnit mUUT;
	TestCasePerformer mTCP;
	TestMessageReciever* mTMR{ nullptr };
	CompoundTestVerifier* mTestVerifier;
};
