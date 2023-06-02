#include "..\..\include\MessageSender\MessageSenderFactory.h"
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

#include <Configuration/MessageCountingSenderConfiguration.h>
#include <Configuration/MessageDecoratingSenderConfiguration.h>
#include <Configuration/FileMessageSenderConfiguration.h>
#include <Configuration/FileMessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageDecoratingSenderConfiguration.h>
#include <Configuration/MessageCountingDecoratingSenderConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h>
#include <MessageSender/MessageSenderFactory.h>
#include <MessageSender/MessageCountingSender.h>
#include <MessageSender/MessageDecoratingSender.h>
#include <MessageSender/MessageFileSender.h>
#include <MessageSender/MessageCountingFileSender.h>
#include <MessageSender/MessageDecoratingFileSender.h>
#include <MessageSender/MessageCountingDecoratingSender.h>
#include <MessageSender/MessageCountingDecoratingFileSender.h>

MessageSenderFactory::MessageSenderFactory()
	:mProduceType("engine")
{
}

MessageSender * MessageSenderFactory::create(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const
{
	if (sender_configuration.senderType() == mProduceType)
	{
		if (auto concrete_configuration = dynamic_cast<const FileMessageSenderConfiguration*>(&sender_configuration)) {
			return new MessageFileSender(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingSenderConfiguration*>(&sender_configuration)) {
			return new MessageCountingFileSender(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageDecoratingSenderConfiguration*>(&sender_configuration)) {
			return new MessageDecoratingFileSender(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingDecoratingSenderConfiguration*>(&sender_configuration)) {
			return new MessageCountingDecoratingFileSender(*concrete_configuration, client_configuration, parent);
		}
	}	
	else
		return create_sender(sender_configuration, client_configuration, parent);
}

MessageSender * MessageSenderFactory::create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const
{
	return nullptr;
}

