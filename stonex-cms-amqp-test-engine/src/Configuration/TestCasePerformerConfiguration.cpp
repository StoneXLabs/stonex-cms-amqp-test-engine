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

#include <Configuration/TestCaseConfiguration.h>

TestCasePerformerConfiguration::TestCasePerformerConfiguration(const std::vector<MessageSenderConfiguration*>& params)
{
	std::transform(std::cbegin(params), std::cend(params), std::back_inserter(mSendersConfiguration), [](const MessageSenderConfiguration* item) {return new MessageSenderConfiguration(*item); });

}

void TestCasePerformerConfiguration::addProducerMessagesParameter(MessageSenderConfiguration* params)
{
	mSendersConfiguration.push_back(params);
}

const std::vector<MessageSenderConfiguration*> & TestCasePerformerConfiguration::senders() const
{
	return mSendersConfiguration;
}

TestCasePerformerConfiguration & TestCasePerformerConfiguration::operator=(const TestCasePerformerConfiguration & other)
{
	std::transform(std::cbegin(other.mSendersConfiguration), std::cend(other.mSendersConfiguration), std::back_inserter(mSendersConfiguration), [](const MessageSenderConfiguration* item) {return new MessageSenderConfiguration(*item); });
	return *this;
}


bool operator== (const TestCasePerformerConfiguration& lhs, const TestCasePerformerConfiguration& rhs)
{
	return 	std::equal(std::cbegin(lhs.mSendersConfiguration), std::cend(lhs.mSendersConfiguration), std::cbegin(rhs.mSendersConfiguration), std::cend(rhs.mSendersConfiguration), [](const MessageSenderConfiguration* lhs, const MessageSenderConfiguration* rhs) {return *lhs == *rhs; });
}
