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

#include <Wrapper/CMSClientTestUnit.h>
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>

#include <MessageSender/MessageSender.h>
#include <MessageSender/MessageFileSender.h>
#include <MessageSender/MessageCountingSender.h>
#include <MessageSender/MessageDecoratingSender.h>
#include <MessageSender/MessageCountingFileSender.h>
#include <MessageSender/MessageDecoratingFileSender.h>
#include <MessageSender/MessageCountingDecoratingSender.h>
#include <MessageSender/MessageCountingDecoratingFileSender.h>
#include <MessageSender/MessageSenderFactory.h>

#include "StdOutLogger/StdOutLogger.h"

#include <Notifier/EventStatusObserver.h>
#include <Notifier/Notifier.h>

#include <test_utils/TestSenders.h>


boost::json::value valueFromFile(const std::string& configFile)
{
	std::ifstream config_file(configFile);
	if (config_file.fail()) {
		std::cerr << "missing file " << configFile << std::endl;
		return boost::json::object();
	}

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






int main(int argc, char *argv[])
{
	TestCaseProducerConfigurationParser parser;

	{
		std::cout << "##teamcity[testSuiteStarted name='MessageSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_sender.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");

		std::cout << "##teamcity[testStarted name='parserTest MessageReceiverConfiguration']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*producer == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;
		
		std::cout << "##teamcity[testSuiteFinished name='MessageSenderConfiguration']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='MessageCountingSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_counting_sender.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = MessageCountingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", 1);

		std::cout << "##teamcity[testStarted name='parserTest']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration cast']" << std::endl;
		std::cout << "##teamcity[" << ((dynamic_cast<MessageCountingSenderConfiguration*>(producer) != nullptr) ? "testFinished" : "testFailed") << " name='configuration cast']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*dynamic_cast<MessageCountingSenderConfiguration*>(producer) == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;
		
		std::cout << "##teamcity[testSuiteFinished name='MessageCountingSenderConfiguration']" << std::endl;

	}

	{
		std::cout << "##teamcity[testSuiteStarted name='FileMessageSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_sender_from_file.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = FileMessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "test_messages.txt");

		std::cout << "##teamcity[testStarted name='parserTest']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration cast']" << std::endl;
		std::cout << "##teamcity[" << ((dynamic_cast<FileMessageSenderConfiguration*>(producer) != nullptr) ? "testFinished" : "testFailed") << " name='configuration cast']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*dynamic_cast<FileMessageSenderConfiguration*>(producer) == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='FileMessageSenderConfiguration']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='MessageDecoratingSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_decorating_sender.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = MessageDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		std::cout << "##teamcity[testStarted name='parserTest']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration cast']" << std::endl;
		std::cout << "##teamcity[" << ((dynamic_cast<MessageDecoratingSenderConfiguration*>(producer) != nullptr) ? "testFinished" : "testFailed") << " name='configuration cast']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*dynamic_cast<MessageDecoratingSenderConfiguration*>(producer) == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='MessageDecoratingSenderConfiguration']" << std::endl;
	}


	{
		std::cout << "##teamcity[testSuiteStarted name='FileMessageDecoratingSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_decorating_sender_from_file.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = FileMessageDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "test_messages.txt", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		std::cout << "##teamcity[testStarted name='parserTest']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration cast']" << std::endl;
		std::cout << "##teamcity[" << ((dynamic_cast<FileMessageDecoratingSenderConfiguration*>(producer) != nullptr) ? "testFinished" : "testFailed") << " name='configuration cast']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*dynamic_cast<FileMessageDecoratingSenderConfiguration*>(producer) == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='FileMessageDecoratingSenderConfiguration']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='FileMessageCountingSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_counting_sender_from_file.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = FileMessageCountingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "test_messages.txt", 1);

		std::cout << "##teamcity[testStarted name='parserTest']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration cast']" << std::endl;
		std::cout << "##teamcity[" << ((dynamic_cast<FileMessageCountingSenderConfiguration*>(producer) != nullptr) ? "testFinished" : "testFailed") << " name='configuration cast']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*dynamic_cast<FileMessageCountingSenderConfiguration*>(producer) == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='FileMessageCountingSenderConfiguration']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='MessageCountingDecoratingSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_decorating_counting_sender.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = MessageCountingDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine",  1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		std::cout << "##teamcity[testStarted name='parserTest']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration cast']" << std::endl;
		std::cout << "##teamcity[" << ((dynamic_cast<MessageCountingDecoratingSenderConfiguration*>(producer) != nullptr) ? "testFinished" : "testFailed") << " name='configuration cast']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*dynamic_cast<MessageCountingDecoratingSenderConfiguration*>(producer) == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='MessageCountingDecoratingSenderConfiguration']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='FileMessageCountingDecoratingSenderConfiguration']" << std::endl;

		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_decorating_counting_sender_from_file.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = FileMessageCountingDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "test_messages.txt", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		std::cout << "##teamcity[testStarted name='parserTest']" << std::endl;
		std::cout << "##teamcity[" << ((producer != nullptr) ? "testFinished" : "testFailed") << " name='parserTest MessageReceiverConfiguration']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration cast']" << std::endl;
		std::cout << "##teamcity[" << ((dynamic_cast<FileMessageCountingDecoratingSenderConfiguration*>(producer) != nullptr) ? "testFinished" : "testFailed") << " name='configuration cast']" << std::endl;

		std::cout << "##teamcity[testStarted name='configuration value']" << std::endl;
		std::cout << "##teamcity[" << ((*dynamic_cast<FileMessageCountingDecoratingSenderConfiguration*>(producer) == producer_config) ? "testFinished" : "testFailed") << " name='configuration value']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='FileMessageCountingDecoratingSenderConfiguration']" << std::endl;
	}
	

	if (argc == 1)
		return 0;
	

	{

		auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto session_config = SessionConfiguration("session1", true, false, { /*consumer_config*/ }, { producer_config });
		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(wrapper_config, logger);

		Notifier event_notifier(nullptr);
		EventStatusObserver event_observer(event_notifier);

		{
			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");
			TestMessageSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{
			auto test_producer_config = MessageCountingSenderConfiguration("connection1", "session1", "producer1", "text", "engine",1);
			TestMessageCountingSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}

		{
			auto test_producer_config = FileMessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt");
			MessageFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{	
			auto test_producer_config = MessageDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			TestMessageDecoratingSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{
			auto test_producer_config = FileMessageCountingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt", 1);
			MessageCountingFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}

		{	
			auto test_producer_config = MessageCountingDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			TestMessageCountingDecoratingSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}

		{
			auto test_producer_config = FileMessageDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageDecoratingFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{
			auto test_producer_config = FileMessageCountingDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageCountingDecoratingFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}

		//factory tests
		MessageSenderFactory TestSenderFactory;

		{
			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine");
			TestMessageSender sender(test_producer_config, test_client, event_notifier);
			MessageSender* factoryProduct = TestSenderFactory.create(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{
			auto test_producer_config = MessageCountingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", 1);
			TestMessageCountingSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}

		{
			auto test_producer_config = FileMessageSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt");
			MessageFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{
			auto test_producer_config = MessageDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			TestMessageDecoratingSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{
			auto test_producer_config = FileMessageCountingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt", 1);
			MessageCountingFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}

		{
			auto test_producer_config = MessageCountingDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			TestMessageCountingDecoratingSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}

		{
			auto test_producer_config = FileMessageDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageDecoratingFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
		}

		{
			auto test_producer_config = FileMessageCountingDecoratingSenderConfiguration("connection1", "session1", "producer1", "text", "engine", "message_file.txt", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageCountingDecoratingFileSender sender(test_producer_config, test_client, event_notifier);
			sender.sendMessage();
			assert(sender.sentMessageCount() == 1);
		}
	}


	
}





