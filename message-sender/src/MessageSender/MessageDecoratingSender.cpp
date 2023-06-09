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

#include <MessageSender/MessageDecoratingSender.h>
#include <MessageDecorator/MessageDecoratorFactory.h>

MessageDecoratingSender::MessageDecoratingSender(const MessageDecoratingSenderConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageSender(config, client_params, parent),
	MessageDecorator(config.decorations())
{
}

MessageDecoratingSender::MessageDecoratingSender(MessageDecoratingSender&& other)
	: MessageSender(std::move(other)),
	MessageDecorator(std::move(other))
{
}

MESSAGE_SEND_STATUS MessageDecoratingSender::send_text(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return MESSAGE_SEND_STATUS::FAILED;


	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		decorate(message, mSession);
		mProducer->send(message);
		delete message;
		return MESSAGE_SEND_STATUS::ALL_SENT;
	}
	else
		return MESSAGE_SEND_STATUS::FAILED;
}

MESSAGE_SEND_STATUS MessageDecoratingSender::send_bytes(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return MESSAGE_SEND_STATUS::FAILED;

	if (mSession && mProducer)
	{
		auto message = mSession->createBytesMessage((const unsigned char*)message_body.c_str(), message_body.size());
		decorate(message, mSession);
		mProducer->send(message);
		delete message;
		return MESSAGE_SEND_STATUS::ALL_SENT;
	}
	else
		return MESSAGE_SEND_STATUS::FAILED;
}

MESSAGE_SEND_STATUS MessageDecoratingSender::send_stream(int msg_delay_ms)
{
	return MESSAGE_SEND_STATUS::SEND_ERROR;
}

MESSAGE_SEND_STATUS MessageDecoratingSender::send_map(int msg_delay_ms)
{
	return MESSAGE_SEND_STATUS::SEND_ERROR;
}

//bool MessageDecoratingSender::operator==(const MessageDecoratingSender& other)
//{
//	return false;
//}


