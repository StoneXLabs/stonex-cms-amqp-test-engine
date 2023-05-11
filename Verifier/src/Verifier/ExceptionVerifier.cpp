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


#include <Verifier/ExceptionVerifier.h>
#include <algorithm>
#include <sstream>

#include <TestEventWrapper/ExceptionWrapper.h>
#include <TestEventWrapper/STDExceptionWrapper.h>



ExceptionVerifier::ExceptionVerifier(const std::string& verifier_id, int expectedExceptionsCount)
	: BaseVerifier(verifier_id, std::set< VERIFIED_ITEMS>{VERIFIED_ITEMS::EXCEPTIONS }),
	mExpectedExceptionCount{expectedExceptionsCount}
{
}

ExceptionVerifier::ExceptionVerifier(ExceptionsConfiguration& config)
	:ExceptionVerifier(config.exceptionSourceId(), config.expectedExceptionCount())
{
}

ExceptionVerifier::~ExceptionVerifier()
{
	std::for_each(std::begin(mEvents), std::end(mEvents), [](const EventWrapper* item) {delete item; });
}

EventStatus ExceptionVerifier::trigger(const EventWrapper* event)
{
	if (auto t = dynamic_cast<const ExceptionWrapper*>(event))
		mEvents.push_back(event);
	else if (auto t = dynamic_cast<const STDExceptionWrapper*>(event))
		mEvents.push_back(event);
	else
		delete event;

	return EventStatus(true, id(), "not implemented exception status");

}

//VerifierStatus ExceptionVerifier::verify() const
//{
//
//	bool success{ true };
//
//	if (mExpectedExceptionCount > -1)
//		if (mEvents.size() - mExpectedExceptionCount)
//		{
//			success = false;
//		}
//
////	return success;
//	return VerifierStatus(nullptr, 1);
//}

//VerifierReport* ExceptionVerifier::createReport()
//{
//	std::stringstream ss;
//	ss << "Exception Count Verifier "<<id()<<" [" << mEvents.size() << " of " << mExpectedExceptionCount << "] :";
//	if (mEvents.size() - mExpectedExceptionCount == 0)
//		ss << "OK";
//	else
//		ss << "FAILED";
//
//	std::for_each(std::begin(mEvents), std::end(mEvents), [&ss](const EventWrapper* item) {
//		ss <<"\n";
//		if (auto t = dynamic_cast<const ExceptionWrapper*>(item))
//			ss<<t->get().what();
//		else if (auto t = dynamic_cast<const STDExceptionWrapper*>(item))
//			ss << t->get().what();
//		});
//	return new VerifierReport(ss.str());
//}

void ExceptionVerifier::expectCount(int count) { mExpectedExceptionCount = count; };