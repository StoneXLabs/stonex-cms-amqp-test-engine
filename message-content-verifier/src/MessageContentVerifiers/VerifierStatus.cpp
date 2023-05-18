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

#include <algorithm>
#include <MessageContentVerifiers/VerifierStatus.h>

VerifierStatus::VerifierStatus()
	:mCount{0},
	mExpectedCount{0},
	mNext{nullptr}
{
}

VerifierStatus::VerifierStatus(IExpectedField* value)
	:mCount{ 0 }
{
	if(value)
		mName = value->fieldName();
}


VerifierStatus::VerifierStatus(IExpectedField* value, int initCount, int expectedCount)
	:mCount{ initCount },
	mExpectedCount{expectedCount}
{
	if (value)
		mName = value->fieldName();
}

void VerifierStatus::addNext(IExpectedField* field, int expectedCount)
{
	if (!field)
		return;

	if (mName == field->fieldName())
		mCount++;
	else if (mNext)
		mNext->addNext(field, expectedCount);
	else
		mNext = new VerifierStatus(field,1, expectedCount);
}

void VerifierStatus::initNext(IExpectedField * field, int initCount, int expectedCount)
{
	if (!field)
		return;

	if (mName == field->fieldName())
		mCount++;
	else if (mNext)
		mNext->addNext(field, expectedCount);
	else
		mNext = new VerifierStatus(field, initCount,expectedCount);
}

bool VerifierStatus::status() const
{
	return mCount == mExpectedCount;
}

std::string VerifierStatus::statusMessage() const
{
	return "expected count " + std::to_string(mExpectedCount) + " received count " + std::to_string(mCount);
}

VerifierStatus* VerifierStatus::next()
{
	return mNext;
}
