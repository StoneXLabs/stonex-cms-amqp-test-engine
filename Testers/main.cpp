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

#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <Wrapper/CMSClientTestUnit.h>
#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>
#include <ConfigurationParser/TestCaseReceiverConfigurationParser.h>
#include <Configuration/MessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageSenderConfiguration.h>
#include <Configuration/FileMessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h>
#include <Configuration/MessageCountingReceiverConfiguration.h>
#include <Configuration/FileMessageReceiverConfiguration.h>
#include <Configuration/FileMessageCountingReceiverConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingReceiverConfiguration.h>
#include <Configuration/MessageDecoratingReceiverConfiguration.h>
#include <MessageSender/MessageSender.h>
#include <MessageSender/MessageFileSender.h>
#include <MessageSender/MessageCountingSender.h>
#include <MessageSender/MessageDecoratingSender.h>
#include <MessageSender/MessageCountingFileSender.h>
#include <MessageSender/MessageDecoratingFileSender.h>
#include <MessageSender/MessageCountingDecoratingSender.h>
#include <MessageSender/MessageCountingDecoratingFileSender.h>
#include <MessageReceiver/MessageReceiver.h>
#include <MessageReceiver/MessageFileReceiver.h>
#include <MessageReceiver/MessageCountingReceiver.h>
#include <MessageReceiver/MessageDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingFileReceiver.h>
#include <MessageReceiver/MessageDecoratingFileReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingFileReceiver.h>
#include <Notifier/EventStatusObserver.h>
#include <Notifier/Notifier.h>
#include <StdOutLogger/StdOutLogger.h>

class TestMessageSender : public MessageSender
{
public:
	TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent)
		:MessageSender(params, client_params, parent)
	{
	}

	bool send(int msg_delay_ms = 0) {
		if (mSession && mProducer)
		{
			auto mes = mSession->createTextMessage("hello");
			mProducer->send(mes);
			return true;
		}
		return false;

	};
};

class TestMessageListener : public cms::MessageListener
{
public:
	void onMessage(const cms::Message* message) override {
		std::cout << "Message Received"<<std::endl;
		mMessageReceived = true;
	}

	bool check() const 
	{
		return mMessageReceived;
	}

private:
	bool mMessageReceived{false};
};

int main()
{

	{

		auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto session_config = SessionConfiguration("session1", true, false, { consumer_config }, { producer_config });
		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

		auto logger = std::make_shared<StdOutLogger>();

		Notifier event_notifier(nullptr);
		EventStatusObserver event_observer(event_notifier);

		{

			CMSClientTestUnit test_client(wrapper_config, logger);

			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");
			TestMessageSender sender(test_producer_config, test_client, event_notifier);

			auto test_consumer_config = MessageReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine");
			MessageReceiver receiver(test_consumer_config, test_client);

			TestMessageListener test_listener;
			receiver.setMessageListener(&test_listener);

			assert(test_listener.check() == false);
			sender.sendMessage();
			receiver.waitForMessage(500);
			assert(test_listener.check() == true);

		}

		{

			CMSClientTestUnit test_client(wrapper_config, logger);

			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");
			TestMessageSender sender(test_producer_config, test_client, event_notifier);

			auto test_consumer_config = MessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", 1);
			MessageCountingReceiver receiver(test_consumer_config, test_client, event_notifier);


			assert(receiver.receivedMessageCount() == 0);
			sender.sendMessage();
			receiver.waitForMessage();
			assert(receiver.receivedMessageCount() == receiver.expectedEventCount());

		}

		{

			CMSClientTestUnit test_client(wrapper_config, logger);

			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");
			TestMessageSender sender(test_producer_config, test_client, event_notifier);

			auto test_consumer_config = FileMessageReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "test_message_out.txt");
			MessageFileReceiver receiver(test_consumer_config, test_client, event_notifier);

			
			TestMessageListener test_listener;
			receiver.setMessageListener(&test_listener);

			assert(test_listener.check() == false);
			sender.sendMessage();
			receiver.waitForMessage(500);
			assert(test_listener.check() == true);

		}

		{

			CMSClientTestUnit test_client(wrapper_config, logger);

			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");
			TestMessageSender sender(test_producer_config, test_client, event_notifier);

			auto test_consumer_config = FileMessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "test_message_out.txt", 1);
			MessageCountingFileReceiver receiver(test_consumer_config, test_client, event_notifier);

			assert(receiver.receivedMessageCount() == 0);
			sender.sendMessage();
			receiver.waitForMessage();
			assert(receiver.receivedMessageCount() == receiver.expectedEventCount());

		}

		{

			CMSClientTestUnit test_client(wrapper_config, logger);

			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");
			TestMessageSender sender(test_producer_config, test_client, event_notifier);

			auto test_consumer_config = FileMessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "test_message_out.txt", 1, {new MessageField(FIELD_TYPE::BOOLEANPROPERTY, "property", "false")});
			MessageCountingDecoratingFileReceiver receiver(test_consumer_config, test_client, event_notifier);

			assert(receiver.receivedMessageCount() == 0);
			sender.sendMessage();
			receiver.waitForMessage();
			assert(receiver.receivedMessageCount() == receiver.expectedEventCount());

		}
	}

	return 0;
}