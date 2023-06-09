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

#include <MessageSender/MessageCountingFileSender.h>
#include <fmt/format.h>

MessageCountingFileSender::MessageCountingFileSender(const FileMessageCountingSenderConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageSender(config, client_params,parent),
	SentMessageCounter(config.expectedEventCount()),
	MessageFileSource(config.filePath())
{
}

MessageCountingFileSender::MessageCountingFileSender(MessageCountingFileSender&& other)
	: MessageSender(std::move(other)),
	SentMessageCounter(std::move(other)),
	MessageFileSource(std::move(other))
{
}

MESSAGE_SEND_STATUS MessageCountingFileSender::send_text(int msg_delay_ms)
{
	if (expectedEventCount() == sentMessageCount())
		return MESSAGE_SEND_STATUS::ALL_SENT;

	auto message_body = createMessageBody();
	if (message_body.empty())
		return MESSAGE_SEND_STATUS::FAILED;

	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		mProducer->send(message);
		incrementSentCount();
		delete message;
		if (expectedEventCount() == sentMessageCount())
			return MESSAGE_SEND_STATUS::ALL_SENT;
		else if (expectedEventCount() < sentMessageCount())
			return MESSAGE_SEND_STATUS::SEND_ERROR;
		else
			return MESSAGE_SEND_STATUS::SUCCESS;
	}
	else
		return MESSAGE_SEND_STATUS::FAILED;
}

MESSAGE_SEND_STATUS MessageCountingFileSender::send_bytes(int msg_delay_ms)
{
	if (expectedEventCount() == sentMessageCount())
		return MESSAGE_SEND_STATUS::ALL_SENT;

	auto message_body = createMessageBody();
	if (message_body.empty())
		return MESSAGE_SEND_STATUS::FAILED;

	if (mSession && mProducer)
	{
		auto message = mSession->createBytesMessage((const unsigned char*)message_body.c_str(), message_body.size());
		mProducer->send(message);
		incrementSentCount();
		delete message;
		if (expectedEventCount() == sentMessageCount())
			return MESSAGE_SEND_STATUS::ALL_SENT;
		else if (expectedEventCount() < sentMessageCount())
			return MESSAGE_SEND_STATUS::SEND_ERROR;
		else
			return MESSAGE_SEND_STATUS::SUCCESS;
	}
	else
		return MESSAGE_SEND_STATUS::FAILED;
}

MESSAGE_SEND_STATUS MessageCountingFileSender::send_stream(int msg_delay_ms)
{
	return MESSAGE_SEND_STATUS::SEND_ERROR;
}

MESSAGE_SEND_STATUS MessageCountingFileSender::send_map(int msg_delay_ms)
{
	return MESSAGE_SEND_STATUS::SEND_ERROR;
}

std::string MessageCountingFileSender::createMessageBody()
{
	try
	{
		return getMessage();
	}
	catch (const std::exception&)
	{
		mParent.testEvent(EventStatus(false, mId, fmt::format("{} can not read line from file", mId)));
	}

	return "";
}

//bool MessageCountingFileSender::operator==(const MessageCountingFileSender& other)
//{
//	return false;
//}

