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

#include <fmt/format.h>
#include <utils/ExceptionVerifier.h>

ExceptionVerifier::ExceptionVerifier(const std::string &id, long long expected_exception_count, Notifier& parent)
	:EventCounter(expected_exception_count),
	mId{id},
	mParent{parent}
{
}

ExceptionVerifier::ExceptionVerifier(const ExceptionVerifier & other)
	: EventCounter(other),
	mId{ other.mId },
	mParent{other.mParent}
{
}

ExceptionVerifier::ExceptionVerifier(ExceptionVerifier && other)
	: EventCounter(other),
	mId{ other.mId },
	mParent{ other.mParent }
{
}

ExceptionVerifier::~ExceptionVerifier()
{
	if (expectedEventCount() > mCaughtExceptionCount)
		mParent.testEvent(EventStatus(false, mId, fmt::format("{} missing {} exceptions. received [{}/{}]", mId, expectedEventCount() - mCaughtExceptionCount, mCaughtExceptionCount, expectedEventCount())));

}

long long ExceptionVerifier::caughtExceptionCount() const
{
	return mCaughtExceptionCount;
}

void ExceptionVerifier::incrementCaughtExceptionCount()
{
	mCaughtExceptionCount++;
	if (mCaughtExceptionCount > expectedEventCount())
		mParent.testEvent(EventStatus(false, mId, fmt::format("{} expected exceptions count exceeded [{}/{}]", mId, mCaughtExceptionCount, expectedEventCount())));

}

std::string ExceptionVerifier::id() const
{
	return mId;
}

void ExceptionVerifier::onException(const cms::CMSException& ex)
{
	incrementCaughtExceptionCount();
}
