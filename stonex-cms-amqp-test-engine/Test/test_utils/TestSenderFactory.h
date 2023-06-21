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

#pragma once

#include <MessageSender/MessageSender.h>
#include <MessageSender/MessageFileSender.h>
#include <MessageSender/MessageCountingSender.h>
#include <MessageSender/MessageDecoratingSender.h>
#include <MessageSender/MessageCountingFileSender.h>
#include <MessageSender/MessageDecoratingFileSender.h>
#include <MessageSender/MessageCountingDecoratingSender.h>
#include <MessageSender/MessageCountingDecoratingFileSender.h>
#include <MessageSender/MessageSenderFactory.h>

class TestMessageSender : public MessageSender
{
public:
	TestMessageSender(const MessageSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent)
		:MessageSender(config, client_params, parent)
	{
	}
	std::string createMessageBody() { return "test message sender"; }
};
class TestMessageCountingSender : public MessageCountingSender
{
public:
	TestMessageCountingSender(const MessageCountingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent)
		:MessageCountingSender(config, client_params, parent)
	{
	}
	std::string createMessageBody() { return "test message counting sender"; }
};
class TestMessageDecoratingSender : public MessageDecoratingSender {
public:
	TestMessageDecoratingSender(const MessageDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent)
		:MessageDecoratingSender(config, client_params, parent)
	{
	}
	std::string createMessageBody() { return "test message decorating sender"; }
};
class TestMessageCountingDecoratingSender : public MessageCountingDecoratingSender
{
public:
	TestMessageCountingDecoratingSender(const MessageCountingDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent)
		:MessageCountingDecoratingSender(config, client_params, parent)
	{
	}
	std::string createMessageBody() { return "test message counting decorating sender"; }
};

class TestSenderFactory : public MessageSenderFactory
{
public:
	TestSenderFactory();
	MessageSender * create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const override
	{
		if (sender_configuration.senderType() == mProduceType)
		{
			if (auto concrete_configuration = dynamic_cast<const MessageCountingSenderConfiguration*>(&sender_configuration)) {
				return new TestMessageCountingSender(*concrete_configuration, client_configuration, parent);
			}
			else if (auto concrete_configuration = dynamic_cast<const MessageDecoratingSenderConfiguration*>(&sender_configuration)) {
				return new TestMessageDecoratingSender(*concrete_configuration, client_configuration, parent);
			}
			else if (auto concrete_configuration = dynamic_cast<const MessageCountingDecoratingSenderConfiguration*>(&sender_configuration)) {
				return new TestMessageCountingDecoratingSender(*concrete_configuration, client_configuration, parent);
			}
			else if (auto concrete_configuration = dynamic_cast<const MessageSenderConfiguration*>(&sender_configuration)) {
				return new TestMessageSender(*concrete_configuration, client_configuration, parent);
			}
		}		
		else
			return nullptr;
	}

private:
	const std::string mProduceType;
};
