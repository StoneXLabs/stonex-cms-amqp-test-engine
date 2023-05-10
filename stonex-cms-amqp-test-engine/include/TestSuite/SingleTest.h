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
#include <Configuration/TestCaseConfiguration.h>
#include <Wrapper/CMSClientTestUnit.h>
#include "TestCasePerformer.h"
#include "MessageReceiver/TestMessageReceiver.h"
#include "MessageReceiver/MessageReceiverFactory.h"
#include "TestFunctionRegister.h"


#include <TestEventListenerFactory/ExceptionListenerFactory.h>

#include <chrono>

#include <Notifier/TestNotifier.h>

class SingleTest : public TestCase, public Notifier
{
public:
	SingleTest(const TestCaseConfiguration & test, TestFunctionRegister& functionRegister, const MessageReceiverFactory& receiverFactory, const MessageSenderFactory& senderFactory, ExceptionListenerFactory& exceptionListenerFactory, TestObserver* reporter, std::shared_ptr<StonexLogger> logger);
	~SingleTest();

	TestCaseStatus run() override;

	std::function<TEST_CASE_STATUS(CMSClientTestUnit* uut, TestCasePerformer *tcp, TestMessageReceiver *tmr)> mCurrentTestFunction{ nullptr };

	std::string testName() const override ;
private:
	bool testStatus() const;
private:
	const std::string mTestName;
	bool mEnabled;
	TestMessageReceiver* mTMR{ nullptr };
	CMSClientTestUnit mUUT;
	TestCasePerformer mTCP;
	TestCaseStatus mStatus;
};
