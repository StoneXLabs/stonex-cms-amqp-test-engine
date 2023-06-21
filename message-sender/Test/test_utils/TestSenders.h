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

#pragma once

#include <MessageSender/MessageSender.h>
#include <MessageSender/MessageFileSender.h>
#include <MessageSender/MessageCountingSender.h>
#include <MessageSender/MessageDecoratingSender.h>
#include <MessageSender/MessageCountingFileSender.h>
#include <MessageSender/MessageDecoratingFileSender.h>
#include <MessageSender/MessageCountingDecoratingSender.h>
#include <MessageSender/MessageCountingDecoratingFileSender.h>

class TestMessageSender : public MessageSender
{
public:
	TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit& client_params, Notifier& parent)
		:MessageSender(params, client_params, parent)
	{
	}


	std::string createMessageBody() override {
		return "test message";
	}
};

class TestMessageCountingSender : public MessageCountingSender
{
public:
	TestMessageCountingSender(const MessageCountingSenderConfiguration& params, CMSClientTestUnit& client_params, Notifier& parent)
		:MessageCountingSender(params, client_params, parent)
	{
	}


	std::string createMessageBody() override {
		return "test message";
	}
};

class TestMessageDecoratingSender : public MessageDecoratingSender
{
public:
	TestMessageDecoratingSender(const MessageDecoratingSenderConfiguration& params, CMSClientTestUnit& client_params, Notifier& parent)
		:MessageDecoratingSender(params, client_params, parent)
	{
	}


	std::string createMessageBody() override {
		return "test message";
	}
};

class TestMessageCountingDecoratingSender : public MessageCountingDecoratingSender
{
public:
	TestMessageCountingDecoratingSender(const MessageCountingDecoratingSenderConfiguration& params, CMSClientTestUnit& client_params, Notifier& parent)
		:MessageCountingDecoratingSender(params, client_params, parent)
	{
	}


	std::string createMessageBody() override {
		return "test message";
	}
};