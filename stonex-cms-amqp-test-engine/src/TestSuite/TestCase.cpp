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

#include <chrono>
#include <TestSuite/TestCase.h>

ITestCase::ITestCase(const std::string& testName, TestObserver * observer)
	:mTestName{testName},
	Notifier(observer)
{
}

ITestCase::~ITestCase() {
	if (mTestSuccess)
		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_SUCCESS, " [" + mTestName + "] ", ""));
	else
		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, " [" + mTestName + "] ", "test failed"));

	TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_END, " [" + mTestName + "] ", std::to_string(mTestDuration.count()) + " [ms]"));

}

void TestCase::run()
{
	if (mTestFunction) {

		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_START, mTestName, ""));

		auto start = std::chrono::high_resolution_clock::now();
		mTestFunction(&mTestedObject, &mTestPerformer);
		auto end = std::chrono::high_resolution_clock::now();

		mTestDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	}

}

void ITestCase::testEvent(const EventStatus & event)
{
	Notifier::testEvent(event);
	if (mTestSuccess)
		mTestSuccess = event.correct();
}




TestCase::TestCase(const TestCaseConfiguration& test_config, MessageSenderFactory* senderFactory, MessageReceiverFactory* receiverFactory, const TestFunctionRegister& functionRegister, TestObserver* observer, std::shared_ptr<StonexLogger> logger)
	:ITestCase(test_config.testName(), observer),
	mTestExceptionVerifier(test_config.verifierConfig(),*this),
	mTestedObject(test_config.uutConfig(), logger,"",&mTestExceptionVerifier, &mTestExceptionVerifier, &mTestExceptionVerifier),
	mTestPerformer(test_config.performerConfig(), mTestedObject,*this, senderFactory),
	mTestVerifier(test_config.verifierConfig(), mTestedObject,*this, receiverFactory)
{
	if (test_config.enabled()) {
		mTestFunction = functionRegister.getTestFunction(test_config.testFunctionName());
		if (!mTestFunction)
			TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, " [" + mTestName + "] ", test_config.testFunctionName() + "not found"));
	}
	else
		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, " [" + mTestName + "] ", "test disabled by configuration"));

}

