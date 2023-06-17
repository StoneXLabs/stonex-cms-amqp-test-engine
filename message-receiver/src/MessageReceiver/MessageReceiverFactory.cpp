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

#include <MessageReceiver/MessageReceiverFactory.h>
#include <MessageReceiver/MessageCountingReceiver.h>
#include <MessageReceiver/MessageDecoratingReceiver.h>
#include <MessageReceiver/MessageFileReceiver.h>
#include <MessageReceiver/MessageCountingFileReceiver.h>
#include <MessageReceiver/MessageDecoratingFileReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingFileReceiver.h>
#include <Configuration/MessageCountingReceiverConfiguration.h>
#include <Configuration/MessageDecoratingReceiverConfiguration.h>
#include <Configuration/FileMessageReceiverConfiguration.h>
#include <Configuration/FileMessageCountingReceiverConfiguration.h>
#include <Configuration/FileMessageDecoratingReceiverConfiguration.h>
#include <Configuration/MessageCountingDecoratingReceiverConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingReceiverConfiguration.h>

MessageReceiverFactory::MessageReceiverFactory()
	:mConsumerType("engine")
{
}

MessageReceiver * MessageReceiverFactory::create(const MessageReceiverConfiguration & receiver_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const
{

	if (receiver_configuration.receiverType() == mConsumerType)
	{
		if (auto concrete_configuration = dynamic_cast<const MessageCountingReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageCountingReceiver(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageDecoratingReceiver(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageCountingDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageCountingDecoratingReceiver(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageFileReceiver(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageCountingFileReceiver(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageDecoratingFileReceiver(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageCountingDecoratingFileReceiver(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageReceiverConfiguration*>(&receiver_configuration)) {
			return new MessageReceiver(*concrete_configuration, client_configuration);
		}
		else
			return nullptr;
	}
	else
		return create_receiver(receiver_configuration, client_configuration, parent);


		
	
	
}

MessageReceiver * MessageReceiverFactory::create_receiver(const MessageReceiverConfiguration & receiver_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const
{
	return nullptr;
}