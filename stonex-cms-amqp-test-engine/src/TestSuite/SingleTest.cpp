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
#include <TestSuite/SingleTest.h>

#include <sstream>

#include <Verifier/MessageReceiverVerifier.h>
#include "MessageSender/MessageSenderFactory.h"


SingleTest::SingleTest(const TestCaseConfiguration & test, TestFunctionRegister & functionRegister, const MessageReceiverFactory& receiverFactory, const MessageSenderFactory& senderFactory, ExceptionListenerFactory& exceptionListenerFactory, TestObserver* reporter)
	:TestNotifier(test, reporter),
	mTestName{ test.testName() },
	mEnabled{ test.enabled() },
	mUUT{ test.uutConfig(), "", exceptionListenerFactory.create(*this), exceptionListenerFactory.create(*this), exceptionListenerFactory.create(*this) },
	mTCP{ test.performerConfig(),mUUT, *this, senderFactory },
	mTMR{ receiverFactory.create(test,*this) }
{
	mStatus.nextState();
	try
	{
		mCurrentTestFunction = functionRegister.getTestFunction(test.testFunctionName());
		if (mTMR)
			mTMR->initialize(mUUT, test.uutConfig());
			mStatus.nextState();
	}
	catch (const std::exception&)
	{
		mStatus.nextState(false);
	}

}

SingleTest::~SingleTest()
{
	delete mTMR;
	mTMR = nullptr;

}

TestCaseStatus SingleTest::run()
{
	 if (!mCurrentTestFunction)
		 return mStatus;
	 else if (mEnabled) {
		 start();
		 TEST_CASE_STATUS status =  mCurrentTestFunction(&mUUT, &mTCP, mTMR);
		 mStatus.nextState();
		 end();
	 }
	 else
		 mStatus.nextState(false);

	 std::cout << *this << std::endl;

	 return mStatus;
}

std::string SingleTest::testName() const
{
	return mTestName;
}

bool SingleTest::testStatus() const
{
	mTMR;
	return false;
}