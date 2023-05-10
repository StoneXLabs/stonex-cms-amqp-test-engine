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

#include <Verifier/MessageVerifier.h>

#include <cms/Queue.h>
#include <cms/Topic.h>
#include <cms/TemporaryQueue.h>
#include <cms/TemporaryTopic.h>

#include <Configuration/TestCaseMessageReceiverConfiguration.h>
#include <MessageContentVerifiers/FieldVerifierFactory.h>


MessageVerifier::MessageVerifier(const std::string& verifier_id, const std::string msg_destination_type, const std::string msg_destination_address)
	: BaseVerifier(verifier_id, std::set< VERIFIED_ITEMS>{VERIFIED_ITEMS::MESSAGE }),
	mDestinationAddress{ msg_destination_address }
{
	if (msg_destination_type == "queue")
		mMsgDestType = cms::Destination::QUEUE;
	else if (msg_destination_type == "topic")
		mMsgDestType = cms::Destination::TOPIC;
	else if (msg_destination_type == "temporary-queue")
		mMsgDestType = cms::Destination::TEMPORARY_QUEUE;
	else if (msg_destination_type == "temporary-topic")
		mMsgDestType = cms::Destination::TEMPORARY_TOPIC;
	else
		mMsgDestType = cms::Destination::QUEUE;


}

MessageVerifier::MessageVerifier(TestCaseMessageReceiverConfiguration & config)
	:MessageVerifier(config.consumerId(), config.destinationType(), config.destinationAddress())
{
}

void MessageVerifier::addFieldVerifier(IExpectedField* fieldVerifier)
{
	if (fieldVerifier)
		mFieldVerifiers.push_back(fieldVerifier);
	else
		std::cout << "can't create verifier " << std::endl;
}

EventStatus MessageVerifier::trigger(const EventWrapper* event)
{
	mMessageCount++;
	bool status{ false };

	if (auto ptr = dynamic_cast<const MessageWrapper*>(event))
	{
		FieldVerifierFactory fwf;

		 status = std::none_of(std::begin(mFieldVerifiers), std::end(mFieldVerifiers), [ptr, &fwf](IExpectedField* item) {
			return fwf.create(ptr->get(), item) == nullptr; });

	};

	delete event;

	if(status)
		return EventStatus(status, id(), "all required message fields exists");
	else
		return EventStatus(status, id(), "missing required message field");
}

void MessageVerifier::expectCount(int count)
{
	mExpectedMessageCount = count;
}

int MessageVerifier::expectCount() const { 
	return mExpectedMessageCount;
};
