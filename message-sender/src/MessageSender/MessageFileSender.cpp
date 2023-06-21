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

#include <MessageSender/MessageFileSender.h>
#include <fmt/format.h>

MessageFileSender::MessageFileSender(const FileMessageSenderConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageSender(config, client_params, parent),
	MessageFileSource(config.filePath())
{
}

MessageFileSender::MessageFileSender(MessageFileSender&& other)
	: MessageSender(std::move(other)),
	MessageFileSource(std::move(other))
{
}

std::string MessageFileSender::createMessageBody()
{
	try
	{
		return getMessage();
	}
	catch (const std::exception&)
	{
		mParent.testEvent(EventStatus(false, mId, fmt::format("can not read line from file")));
	}

	return "";
}

//bool MessageFileSender::operator==(const MessageFileSender& other)
//{
//	return false;
//}
