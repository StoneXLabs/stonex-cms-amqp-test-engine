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

MessageSender::MessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent)
	:mSession{ client_params.session(params.connectionId(), params.sessionId()) },
	mProducer{ client_params.producer(params.connectionId(), params.sessionId(),params.producerId()) },
	mId{params.producerId()},
	mParent{parent},
	mMessageType{fromString(params.messageType())}	
{
	switch (mMessageType)
	{
	case MESSAGE_TYPE::TEXT_MESSAGE:
		mSendFunction = std::bind(&MessageSender::send_text, this, std::placeholders::_1);
		break;
	case MESSAGE_TYPE::BYTES_MESSAGE:
		mSendFunction = std::bind(&MessageSender::send_bytes, this, std::placeholders::_1);
		break;
	case MESSAGE_TYPE::STREAM_MESSAGE:
		mSendFunction = std::bind(&MessageSender::send_map, this, std::placeholders::_1);
		break;
	case MESSAGE_TYPE::MAP_MESSAGE:
		mSendFunction = std::bind(&MessageSender::send_stream, this, std::placeholders::_1);
		break;
	default:
		break;
	}
}

bool MessageSender::sendMessage()
{
	bool sent{ false };
	if (mProducer) 
	{
		sent = send(0);
		if (sent)
			mParent.testEvent(EventStatus(sent, id(), ""));
		else
			mParent.testEvent(EventStatus(sent, id(), "failed to send message"));
	}
	else
		mParent.testEvent(EventStatus(sent, id(), "failed to send message. producer not initialized"));
	
	return sent;
}

std::string MessageSender::id() const
{
	return mId;
}

bool MessageSender::send(int msg_delay_ms)
{
	return mSendFunction(msg_delay_ms);
}

bool MessageSender::send_text(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;

	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		mProducer->send(message);
		return true;
	}
	else
		return false;
}

bool MessageSender::send_bytes(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;

	if (mSession && mProducer)
	{
		auto message = mSession->createBytesMessage((const unsigned char*)message_body.c_str(),message_body.size());
		mProducer->send(message);
		return true;
	}
	else
		return false;
}

bool MessageSender::send_stream(int msg_delay_ms)
{
	return false;
}

bool MessageSender::send_map(int msg_delay_ms)
{
	return false;
}

MESSAGE_TYPE MessageSender::fromString(const std::string & message_type_string)
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

