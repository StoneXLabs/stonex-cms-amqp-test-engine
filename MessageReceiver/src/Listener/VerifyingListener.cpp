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


#include <Listener/VerifyingListener.h>

#include <sstream>

#include <cms/Queue.h>
#include <cms/Topic.h>
#include <cms/TemporaryQueue.h>
#include <cms/TemporaryTopic.h>

#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/StreamMessage.h>
#include <cms/MapMessage.h>


VerifyingListener::VerifyingListener(const std::string & id, std::shared_ptr<BaseVerifier> verifier)
	:mId{ id },
	mMessageVerifier{ verifier },
	mEventWrapperFactory{ nullptr /*new EventWrapperCoreFactory()*/ }
{
}

void VerifyingListener::onMessage(const cms::Message * message)
{
	auto m = dynamic_cast<const cms::TextMessage*>(message);

	std::stringstream destAddress;

	switch (m->getCMSDestination()->getDestinationType())
	{
	case cms::Destination::QUEUE:
		destAddress << " QUEUE ";
		destAddress << dynamic_cast<const cms::Queue*>(m->getCMSDestination())->getQueueName();
		break;
	case cms::Destination::TOPIC:
		destAddress << " TOPIC ";
		destAddress << dynamic_cast<const cms::Topic*>(m->getCMSDestination())->getTopicName();
		break;
	case cms::Destination::TEMPORARY_QUEUE:
		destAddress << " TEMPORARY QUEUE ";
		destAddress << dynamic_cast<const cms::TemporaryQueue*>(m->getCMSDestination())->getQueueName();
		break;
	case cms::Destination::TEMPORARY_TOPIC:
		destAddress << " TEMPORARY TOPIC ";
		destAddress << dynamic_cast<const cms::TemporaryTopic*>(m->getCMSDestination())->getTopicName();
		break;
	default:
		break;
	}

	if (mMessageVerifier)
		mMessageVerifier->trigger(mEventWrapperFactory->create(message));
	delete message;
}
