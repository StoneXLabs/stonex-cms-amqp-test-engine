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

#include <MessageSender/MessageCountingFileSender.h>

MessageCountingFileSender::MessageCountingFileSender(const FileMessageCountingSenderConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageSender(config, client_params,parent),
	SentMessageCounter(config.expectedEventCount()),
	MessageFileSource(config.filePath())
{
}

bool MessageCountingFileSender::send_text(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;


	if (mSession && mProducer)
	{
		auto message = mSession->createTextMessage(message_body);
		mProducer->send(message);
		incrementSentCount();
		return true;
	}
	else
		return false;
}

bool MessageCountingFileSender::send_bytes(int msg_delay_ms)
{
	auto message_body = createMessageBody();
	if (message_body.empty())
		return false;

	if (mSession && mProducer)
	{
		auto message = mSession->createBytesMessage((const unsigned char*)message_body.c_str(), message_body.size());
		mProducer->send(message);
		incrementSentCount();
		return true;
	}
	else
		return false;
}

bool MessageCountingFileSender::send_stream(int msg_delay_ms)
{
	return false;
}

bool MessageCountingFileSender::send_map(int msg_delay_ms)
{
	return false;
}

std::string MessageCountingFileSender::createMessageBody()
{
	return getMessage();
}

