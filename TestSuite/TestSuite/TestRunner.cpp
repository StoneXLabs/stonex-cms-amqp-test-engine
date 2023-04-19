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

#include "TestRunner.h"
#include "SingleTest.h"

TestRunner::TestRunner(TestSuiteConfigParser * configurationParser, TestFunctionRegister & functionRegister,  MessageReceiverFactory & receiverFactory,  MessageSenderFactory & senderFactory, const TestVerifierFactory & verifierFactory, TestReporter * reporter)
	:mRegister{ functionRegister },
	mReceiverFactory{ receiverFactory },
	mSenderFactory{ senderFactory },
	mVeifierFactory{ verifierFactory },
	mTestReporter{ reporter }
 {
	 mSuiteConfiguration = configurationParser->createConfiguration();
 }


 void TestRunner::run()
 {
	 mCurrentTestNumber = 0;

	/* if (mTestReporter)
		mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_SUITE_START, mSuiteConfiguration.name(), mSuiteConfiguration.name() });*/
	 
	

	 std::for_each(mSuiteConfiguration.testsCbegin(), mSuiteConfiguration.testsCend(), [this](const TestCaseConfiguration& test) {
		 
		 mCurrentTestNumber++;

		/* if (mTestReporter)
			 mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::GENERAL, test.testName(), "Initializing test [" + std::to_string(mCurrentTestNumber) + "/" + std::to_string(mSuiteConfiguration.testCaseCount()) + "] : " + test.testFunctionName() });
*/
			 
	//	 auto verifier = mVeifierFactory.create(test);
		 
	/*	 if (mTestReporter)
			 mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::STATUS, REPORT_MESSAGE_TYPE::TEST_START, test.testName(), "Test started" });*/

		 // use test status
		 SingleTest single_test(test, mRegister, mReceiverFactory.create(/*verifier*/), verifier, mSenderFactory);
		 TEST_CASE_STATUS status = single_test.run();

		 //if (mTestReporter)
			// mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::DEBUG, REPORT_MESSAGE_TYPE::TEST_END, test.testName(), "duration = '<test_duration_in_milliseconds>'" });

		 //if (mTestReporter)
			// mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::TRACE, REPORT_MESSAGE_TYPE::GENERAL, test.testName(), "Test result verification" });

		 auto rep = single_test.getRaport();
/*
		 if (mTestReporter != nullptr && rep == nullptr)
			 mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::WARNING, REPORT_MESSAGE_TYPE::GENERAL, test.testName(), "Raport empty" });
		 else	if (mTestReporter && rep)
		 {
			 if (mTestReporter) {
				 mTestReporter->addTestCaseRaport(rep);
				 mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::GENERAL, test.testName(), "Raport created" });
			 }
		 } */

		 //ADD globl test status

	 });


	 //if (mTestReporter)
		//mTestReporter->onMessage({ REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_SUITE_END, mSuiteConfiguration.name(), mSuiteConfiguration.name() });
 
//	 mTestReporter->printFullRaport();
 }