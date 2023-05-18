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

#include <TestSuite/TestRunner.h>
#include <TestSuite/TestCase.h>

TestRunner::TestRunner(TestSuiteConfigParser & configurationParser, TestFunctionRegister & functionRegister, MessageReceiverFactory & receiverFactory,  MessageSenderFactory & senderFactory, TestObserver * reporter, std::shared_ptr<StonexLogger> logger)
	:mRegister{ functionRegister },
	mReceiverFactory{ receiverFactory },
	mSenderFactory{ senderFactory },
	mTestReporter{ reporter },
	mLogger{logger}
 {
	 mSuiteConfiguration = configurationParser.createConfiguration();
 }


 void TestRunner::run()
 {

	 mCurrentTestNumber = 0;

	 if (mTestReporter)
		mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_SUITE_START, mSuiteConfiguration.name(), mSuiteConfiguration.name() });
	

	 std::for_each(mSuiteConfiguration.testsBegin(), mSuiteConfiguration.testsEnd(), [this](const TestCaseConfiguration& test) {

		 mCurrentTestNumber++;

		 if (mTestReporter) 
		 {
			 mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::GENERAL, "", "\n\n---------------------------------- " + test.testName() + " ----------------------------------\n\n" });
			 mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::GENERAL, test.testName(), "Initializing test [" + std::to_string(mCurrentTestNumber) + "/" + std::to_string(mSuiteConfiguration.testCaseCount()) + "] : " + test.testFunctionName() });
		 }

		 // use test status
		///* TestCaseStatus status;
		// {
		//	 SingleTest single_test(test, mRegister, mReceiverFactory, mSenderFactory, *mExceptionListenerFactory, mTestReporter, mLogger);
		//	 status = single_test.run();
		// }
		// */
		 {
			 TestCase testCase(test, nullptr, mRegister, mTestReporter);
			 testCase.run();
		 }
		 
		 if (mTestReporter)
			 mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::TRACE, REPORT_MESSAGE_TYPE::GENERAL, test.testName(), "Test result verification" });


	 });


	 if (mTestReporter)
		mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_SUITE_END, mSuiteConfiguration.name(), mSuiteConfiguration.name() });
 }