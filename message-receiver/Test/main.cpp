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
#include <Wrapper/CMSClientTestUnit.h>
#include <ConfigurationParser/TestCaseReceiverConfigurationParser.h>
#include <MessageReceiver/MessageReceiver.h>
#include "../src/MessageReceiver/MessageFileReceiver.h"
#include "../src/MessageReceiver/MessageCountingReceiver.h"
#include "../src/MessageReceiver/MessageDecoratingReceiver.h"
#include "../src/MessageReceiver/MessageCountingFileReceiver.h"
#include "../src/MessageReceiver/MessageDecoratingFileReceiver.h"
#include "../src/MessageReceiver/MessageCountingDecoratingReceiver.h"
#include "../src/MessageReceiver/MessageCountingDecoratingFileReceiver.h"
#include <Notifier/EventStatusObserver.h>
#include <Notifier/TestNotifier.h>
#include <StdOutLogger/StdOutLogger.h>



boost::json::value valueFromFile(const std::string& configFile)
{
	std::ifstream config_file(configFile);

	boost::json::stream_parser p;
	boost::json::error_code ec;
	do
	{
		char buf[4096];
		config_file.read(buf, sizeof(buf));
		p.write(buf, config_file.gcount(), ec);
	} while (!config_file.eof());

	p.finish(ec);

	return  p.release();
}






int main()
{
	TestCaseReceiverConfigurationParser parser;

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine");

		assert(consumer != nullptr);
		assert(*consumer == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_counting_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", 1);

		assert(consumer != nullptr);
		assert(dynamic_cast<MessageCountingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<MessageCountingReceiverConfiguration*>(consumer) == consumer_config);

	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "test_messages.txt");


		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<MessageDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<MessageDecoratingReceiverConfiguration*>(consumer) == consumer_config);
	}


	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "test_messages.txt", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageDecoratingReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_counting_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "test_messages.txt", 1);

		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageCountingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageCountingReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_counting_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine",  1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<MessageCountingDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<MessageCountingDecoratingReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_counting_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "test_messages.txt", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageCountingDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageCountingDecoratingReceiverConfiguration*>(consumer) == consumer_config);
	}
	


	

	{

		auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto session_config = SessionConfiguration("session1", true, false, { consumer_config }, { producer_config });
		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(wrapper_config, logger);

		Notifier event_notifier(nullptr);

		{
	
			auto test_consumer_config = MessageReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine");
			MessageReceiver receiver(test_consumer_config, test_client);
			
		}

		{
			auto test_consumer_config = MessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine",1);
			MessageCountingReceiver receiver(test_consumer_config, test_client, event_notifier);
			
			//assert(receiver.receivedMessageCount() == 1);
		}

		{
			auto test_consumer_config = FileMessageReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "message_file.txt");
			MessageFileReceiver receiver(test_consumer_config, test_client, event_notifier);
			
		}

		{
	
			auto test_consumer_config = MessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageDecoratingReceiver receiver(test_consumer_config, test_client, event_notifier);
			
		}

		{
			auto test_consumer_config = FileMessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "message_file.txt", 1);
			MessageCountingFileReceiver receiver(test_consumer_config, test_client, event_notifier);
			
			//assert(receiver.receivedMessageCount() == 1);
		}

		{
	
			auto test_consumer_config = MessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageCountingDecoratingReceiver receiver(test_consumer_config, test_client, event_notifier);
			
			//assert(receiver.receivedMessageCount() == 1);
		}

		{
			auto test_consumer_config = FileMessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "message_file.txt", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageDecoratingFileReceiver receiver(test_consumer_config, test_client, event_notifier);
			
		}

		{
			auto test_consumer_config = FileMessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "text", "engine", "message_file.txt", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageCountingDecoratingFileReceiver receiver(test_consumer_config, test_client, event_notifier);
			
			//assert(receiver.receivedMessageCount() == 1);
		}


		

	}

	return 0;
	
}





