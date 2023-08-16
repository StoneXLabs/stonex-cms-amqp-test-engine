#include "../../include/MessageReceiver/MessageReceiver.h"
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

#include <chrono>
#include <thread>
#include <MessageReceiver/MessageReceiverFactory.h>
#include <Notifier/EventStatus.h>

MessageReceiver::MessageReceiver(const MessageReceiverConfiguration& params, CMSClientTestUnit & client_params)
	:mConsumer{ client_params.consumer(params.connectionId(), params.sessionId(),params.consumerId()) },
	mId{params.consumerId()},
	mMessageType{ fromString(params.messageType()) }
{
	if (mConsumer)
		mConsumer->setMessageListener(this);
}

MessageReceiver::~MessageReceiver() 
{
	if (mConsumer)
		mConsumer->setMessageListener(nullptr);
}

std::string MessageReceiver::id() const
{
	return mId;
}

void MessageReceiver::onMessage(const cms::Message* message) {
	
	if (mListener)
		mListener->onMessage(message);
	else
		delete message;
}

void MessageReceiver::waitForMessage(long long millis) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

MESSAGE_TYPE MessageReceiver::fromString(const std::string & message_type_string)
{
	if (message_type_string == "text")
		return MESSAGE_TYPE::TEXT_MESSAGE;
	else if (message_type_string == "binary")
		return MESSAGE_TYPE::BYTES_MESSAGE;
	else if (message_type_string == "stream")
		return MESSAGE_TYPE::STREAM_MESSAGE;
	else if (message_type_string == "map")
		return MESSAGE_TYPE::MAP_MESSAGE;
	else
		return MESSAGE_TYPE::UNKNOWN_TYPE;
}

void MessageReceiver::closeConsumer()
{
	if (mConsumer)
		mConsumer->close();
}

void MessageReceiver::setMessageListener(cms::MessageListener* listener)
{
	mListener = listener;
}
