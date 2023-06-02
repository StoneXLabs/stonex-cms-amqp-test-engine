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
	mSessionId{ params.sessionId() },
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
	MESSAGE_SEND_STATUS sent;
	if (mProducer) 
	{
		sent = send(0);

		switch (sent)
		{
		case MESSAGE_SEND_STATUS::SUCCESS:
			mParent.testEvent(EventStatus(true, id(), ""));
			break;
		case MESSAGE_SEND_STATUS::FAILED:
			mParent.testEvent(EventStatus(false, id(), "failed to send message"));
			break;
		case MESSAGE_SEND_STATUS::ALL_SENT:
			mParent.testEvent(EventStatus(true, id(), ""));
			break;
		case MESSAGE_SEND_STATUS::SEND_ERROR:
			mParent.testEvent(EventStatus(false, id(), "sender error"));
			break;
		default:
			break;
		}

	}
	else {
		mParent.testEvent(EventStatus(false, id(), "failed to send message. producer not initialized"));
		sent = MESSAGE_SEND_STATUS::SEND_ERROR;
	}
	
	return sent == MESSAGE_SEND_STATUS::SUCCESS;
}

std::string MessageSender::id() const
{
	return mId;
}

std::string MessageSender::sessionId() const
{
	return mSessionId;
}

SessionHandler * MessageSender::getSessionHandler(const std::string& session_id) const
{
	if (mSession->id() == session_id)
		return new SessionHandler(mSession);
	else
		return nullptr;
}

ProducerHandler * MessageSender::getProducerHandler() const
{
	return new ProducerHandler(mProducer);
}

MESSAGE_SEND_STATUS MessageSender::send(int msg_delay_ms)
{
	return mSendFunction(msg_delay_ms);
}

MESSAGE_SEND_STATUS MessageSender::send_text(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return MESSAGE_SEND_STATUS::FAILED;

	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		mProducer->send(message);
		delete message;
		return MESSAGE_SEND_STATUS::ALL_SENT;
	}
	else
		return MESSAGE_SEND_STATUS::SEND_ERROR;
}

MESSAGE_SEND_STATUS MessageSender::send_bytes(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return MESSAGE_SEND_STATUS::FAILED;

	if (mSession && mProducer)
	{
		auto message = mSession->createBytesMessage((const unsigned char*)message_body.c_str(),message_body.size());
		mProducer->send(message);
		delete message;
		return MESSAGE_SEND_STATUS::ALL_SENT;
	}
	else
		return MESSAGE_SEND_STATUS::FAILED;
}

MESSAGE_SEND_STATUS MessageSender::send_stream(int msg_delay_ms)
{
	return MESSAGE_SEND_STATUS::SEND_ERROR;
}

MESSAGE_SEND_STATUS MessageSender::send_map(int msg_delay_ms)
{
	return MESSAGE_SEND_STATUS::SEND_ERROR;
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

