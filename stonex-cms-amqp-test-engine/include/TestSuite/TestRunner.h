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

#pragma once

#include "TestFunctionRegister.h"
#include <ConfigurationParser/TestSuiteConfigParser.h>
#include <Configuration/TestSuiteConfiguration.h>
#include <MessageReceiver/MessageReceiverFactory.h>
#include <MessageSender/MessageSenderFactory.h>
#include <Notifier/TestObserver.h>
#include <logger/StoneXLogger.h>
#include <logger/StonexLogSource.h>
#include <TestSuite/ITestCase.h>

class TestRunner
{

public:
	TestRunner(TestSuiteConfigParser& configurationParser, TestFunctionRegister& functionRegister, MessageReceiverFactory& receiverFactory,  MessageSenderFactory& senderFactory, TestObserver* reporter, std::shared_ptr<StonexLogger> logger);
	void run();
protected:
	virtual ITestCase* createTestCase(const TestCaseConfiguration& test_config, MessageSenderFactory* senderFactory, MessageReceiverFactory* receiverFactory, const TestFunctionRegister& functionRegister, TestObserver* observer, std::shared_ptr<StonexLogger> logger);

private:
	TestSuiteConfiguration mSuiteConfiguration;
	TestFunctionRegister& mRegister;
	MessageReceiverFactory& mReceiverFactory;
	MessageSenderFactory& mSenderFactory;
	TestObserver* mTestReporter{ nullptr };
	int mCurrentTestNumber{ 0 };
	std::shared_ptr<StonexLogger> mLogger;
};

