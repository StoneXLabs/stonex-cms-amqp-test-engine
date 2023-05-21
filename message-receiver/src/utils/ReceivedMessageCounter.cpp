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

#include <utils/ReceivedMessageCounter.h>
#include <Notifier/TestNotifier.h>
#include <fmt/format.h>

ReceivedMessageCounter::ReceivedMessageCounter(const std::string &id, long long expected_message_count, Notifier & parent)
	:EventCounter(expected_message_count),
	mParent{ parent },
	mId{id}
{
}

ReceivedMessageCounter::~ReceivedMessageCounter()
{
	if (expectedEventCount() == mReceivedMessagesCount)
		mParent.testEvent(EventStatus(true, mId, fmt::format("expected message count reached [{}/{}]", receivedMessageCount(), expectedEventCount())));
	else if (expectedEventCount() > mReceivedMessagesCount)
		mParent.testEvent(EventStatus(false, mId, fmt::format("missing {} messages. received [{}/{}]", expectedEventCount() - receivedMessageCount(), receivedMessageCount(), expectedEventCount())));

}

long long ReceivedMessageCounter::receivedMessageCount() const
{
	return mReceivedMessagesCount;
}

void ReceivedMessageCounter::incrementReceivedCount()
{
	mReceivedMessagesCount++;
	if (mReceivedMessagesCount > expectedEventCount())
		mParent.testEvent(EventStatus(false, mId, fmt::format("expected message count exceeded [{}/{}]", receivedMessageCount(), expectedEventCount())));
}
