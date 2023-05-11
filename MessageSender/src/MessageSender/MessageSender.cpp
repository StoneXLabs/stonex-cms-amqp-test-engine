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

#include <MessageSender/MessageSenderFactory.h>
#include <Notifier/EventStatus.h>

MessageSender::MessageSender(const TestCaseProducerConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
	:mSession{ client_params.session(params.connectionId(), params.sessionId()) },
	mProducer{ client_params.producer(params.connectionId(), params.sessionId(),params.producerId()) },
	mId{params.producerId()},
	mParent{parent}
{
}

bool MessageSender::sendMessage()
{
	bool sent{ false };
	if (mProducer) 
	{
		sent = send(0);
		if (sent)
			mParent.onEvent(EventStatus(sent, id(), ""));
		else
			mParent.onEvent(EventStatus(sent, id(), "failed to send message"));
	}
	else
		mParent.onEvent(EventStatus(sent, id(), "failed to send message. producer not initialized"));
	
	return sent;
}

std::string MessageSender::id() const
{
	return mId;
}

