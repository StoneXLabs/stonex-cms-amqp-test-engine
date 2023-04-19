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
#include "SingleTest.h"

#include <sstream>
//#include "Reporters/VerifierReport.h"
//#include "Verifiers/TestFunctionVerifier.h"
#include "MessageSender/MessageSenderFactory.h"


SingleTest::SingleTest(const TestCaseConfiguration & test, TestFunctionRegister & functionRegister, TestMessageReciever * receiver, CompoundTestVerifier * testVerifier, const MessageSenderFactory& senderFactory)
	:mTestName{ test.testName() },
	mEnabled{ test.enabled() },
	mUUT{ test.uutConfig() },
	mTCP{ test.performerConfig(),mUUT, senderFactory },
	mTMR{ receiver },
	mTestVerifier{ testVerifier }
{
	try
	{
		mCurrentTestFunction = functionRegister.getTestFunction(test.testFunctionName());
		if (mTMR)
			mTMR->initialize(mUUT, test.uutConfig());
	}
	catch (const std::exception&)
	{

	}
}

TEST_CASE_STATUS SingleTest::run()
{
 if (!mCurrentTestFunction)
	 return TEST_CASE_STATUS::NOT_REGISTERED;
 else if (mEnabled) {
	 TEST_CASE_STATUS status =  mCurrentTestFunction(&mUUT, &mTCP, mTMR);
 }
 else
	 return TEST_CASE_STATUS::DISABLED;
}

std::string SingleTest::testName() const
{
	return mTestName;
}

VerifierReport* SingleTest::getRaport()
{
	if (mTestVerifier)
		return mTestVerifier->callVerifiers();
	else
		return nullptr;
}




//SingleTest SingleTest::runTest()
//{
//	//if (!mEnabled)
//	//	return	SingleTest(mTestName, 1);
//	//else
//	//{
//	//	SingleTest test(mTestName, 1);
//	//	mCurrentTestFunction(mUut, mTcp, mTmr);
//	//	test.setRaport(mVerifier->callVerifiers());
//
//
//	//	////////////////////////////
//	//	auto sub_verifiers = mVerifier->verifiers();
//
//	//	std::for_each(std::cbegin(sub_verifiers), std::cend(sub_verifiers), [/*&reporter*/](std::shared_ptr<BaseVerifier> item) {
//	//		if (!item->verify())
//	//		{
//	//			std::stringstream ss;
//	//			auto report = item->createReport();
//	//			if (report)
//	//				ss << *report;
//	//			//				reporter.onMessage({ REPORT_MESSAGE_SEVERITY::ERROR, REPORT_MESSAGE_TYPE::GENERAL, item->id(), ss.str() });
//
//	//			if (report)
//	//				delete report;
//	//		}
//	//		else {
//	//			std::stringstream ss;
//	//			auto report = item->createReport();
//	//			if (report)
//	//				ss << *report;
//	//			//			reporter.onMessage({ REPORT_MESSAGE_SEVERITY::STATUS, REPORT_MESSAGE_TYPE::GENERAL, item->id(), ss.str() });
//
//	//			if (report)
//	//				delete report;
//	//		}
//	//	});
//
//	//	return test;
//	//}
//
//	
//}

