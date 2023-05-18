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

#include <TestSuite/TestCase.h>


#include <ConfigurationParser/TestSuiteJsonConfigParser.h>
#include <TestSuite/TestCasePerformer.h>
#include <TestSuite/TestCaseVerifier.h>

#include <Notifier/TestNotifier.h>
#include <Notifier/StdOutTestObserver.h>
#include "StdOutLogger/StdOutLogger.h"

class TestExceptionListener : public cms::ExceptionListener {
public:
	void onException(const cms::CMSException& ex) { std::cout << "EXCEPTION " << ex.what() << std::endl; }
};

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

///test fun
TEST_CASE_STATUS test_fun(CMSClientTestUnit* a, TestCasePerformer* b) {

	b->sendAll();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return TEST_CASE_STATUS::FINISHED;
};

int main()
{
	{
		TestCaseConfigurationParser parser;
		boost::json::object::value_type test_case_receiver_config_json = *valueFromFile("test_case.config").as_object().cbegin();
		auto test_case_verifier = parser.createTestCaseConfig(test_case_receiver_config_json.key_c_str(), test_case_receiver_config_json.value().as_object()).verifierConfig();

		MessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		assert(verifier_config == test_case_verifier);
	}

	{
		TestCaseConfigurationParser parser;
		boost::json::object::value_type test_case_performer_config_json = *valueFromFile("test_case.config").as_object().cbegin();
		auto test_case_performer = parser.createTestCaseConfig(test_case_performer_config_json.key_c_str(), test_case_performer_config_json.value().as_object()).performerConfig();

		MessageSenderConfiguration producer_config("connection1", "session1", "producer1");
		TestCasePerformerConfiguration test_performer_config({ &producer_config });


		assert(test_case_performer == test_performer_config);
	}

	{
		TestCaseConfigurationParser parser;
		boost::json::object::value_type test_case_config_json = *valueFromFile("test_case.config").as_object().cbegin();
		auto test_case = parser.createTestCaseConfig(test_case_config_json.key_c_str(), test_case_config_json.value().as_object());

		auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto session_config = SessionConfiguration("session1", true, false, { consumer_config }, { producer_config });
		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

		MessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		MessageSenderConfiguration sender_config("connection1", "session1", "producer1");
		TestCasePerformerConfiguration test_performer_config({ &sender_config });

		TestCaseConfiguration test_case_config("test_case_1", "test_function_1", true, wrapper_config, test_performer_config, verifier_config);

		assert(test_case == test_case_config);
	}

	{
		TestSuiteJsonConfigParser parser("test_suite.config");
		auto suite_config = parser.createConfiguration();

		auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto session_config = SessionConfiguration("session1", true, false, { consumer_config }, { producer_config });
		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

		MessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		MessageSenderConfiguration sender_config("connection1", "session1", "producer1");
		TestCasePerformerConfiguration test_performer_config({ &sender_config });

		TestCaseConfiguration test_case_config("test_case_1", "test_function_1", true, wrapper_config, test_performer_config, verifier_config);

		TestSuiteConfiguration test_suite_config("test_suite.config", { test_case_config });

		assert(suite_config == test_suite_config);
	}

	{
		TestSuiteJsonConfigParser parser("test_case_all.config");
		auto suite_config = parser.createConfiguration();

		auto consumer1_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto consumer2_config = ConsumerConfiguration("consumer2", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto consumer3_config = ConsumerConfiguration("consumer3", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto consumer4_config = ConsumerConfiguration("consumer4", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto consumer5_config = ConsumerConfiguration("consumer5", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto consumer6_config = ConsumerConfiguration("consumer6", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto consumer7_config = ConsumerConfiguration("consumer7", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto consumer8_config = ConsumerConfiguration("consumer8", "queue", "CMS_CLIENT_QUEUE", "close", "");

		auto producer1_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto producer2_config = ProducerConfiguration("producer2", "queue", "CMS_CLIENT_QUEUE", {});
		auto producer3_config = ProducerConfiguration("producer3", "queue", "CMS_CLIENT_QUEUE", {});
		auto producer4_config = ProducerConfiguration("producer4", "queue", "CMS_CLIENT_QUEUE", {});
		auto producer5_config = ProducerConfiguration("producer5", "queue", "CMS_CLIENT_QUEUE", {});
		auto producer6_config = ProducerConfiguration("producer6", "queue", "CMS_CLIENT_QUEUE", {});
		auto producer7_config = ProducerConfiguration("producer7", "queue", "CMS_CLIENT_QUEUE", {});
		auto producer8_config = ProducerConfiguration("producer8", "queue", "CMS_CLIENT_QUEUE", {});

		auto session_config = SessionConfiguration("session1", true, false, 
			{ consumer1_config, consumer2_config, consumer3_config, consumer4_config, consumer5_config, consumer6_config, consumer7_config, consumer8_config },
			{ producer1_config, producer2_config, producer3_config, producer4_config, producer5_config, producer6_config, producer7_config, producer8_config });


		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));


		MessageReceiverConfiguration receiver1_config("connection1", "session1", "consumer1");
		MessageCountingReceiverConfiguration receiver2_config("connection1", "session1", "consumer2", 1);
		FileMessageReceiverConfiguration receiver3_config("connection1", "session1", "consumer3", "message_file.txt");
		MessageDecoratingReceiverConfiguration receiver4_config("connection1", "session1", "consumer4", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingReceiverConfiguration receiver5_config("connection1", "session1", "consumer5", "message_file.txt", 1);
		MessageCountingDecoratingReceiverConfiguration receiver6_config("connection1", "session1", "consumer6", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageDecoratingReceiverConfiguration receiver7_config("connection1", "session1", "consumer7", "message_file.txt", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingDecoratingReceiverConfiguration receiver8_config("connection1", "session1", "consumer8", "message_file.txt", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });



		ExceptionsConfiguration exception_config("connection1", 0);
	
	
		MessageSenderConfiguration sender1_config("connection1", "session1", "producer1");
		MessageCountingSenderConfiguration sender2_config("connection1", "session1", "producer2", 1);
		FileMessageSenderConfiguration sender3_config("connection1", "session1", "producer3", "test_message_file1.txt");
		MessageDecoratingSenderConfiguration sender4_config("connection1", "session1", "producer4", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageDecoratingSenderConfiguration sender5_config("connection1", "session1", "producer5", "test_message_file2.txt", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingSenderConfiguration sender6_config("connection1", "session1", "producer6", "test_message_file3.txt", 1);
		MessageCountingDecoratingSenderConfiguration sender7_config("connection1", "session1", "producer7", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingDecoratingSenderConfiguration sender8_config("connection1", "session1", "producer8", "test_message_file4.txt", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		

		TestCaseVerifierConfiguration verifier_config({ &receiver1_config, &receiver2_config, &receiver3_config, &receiver4_config, &receiver5_config, &receiver6_config, &receiver7_config, &receiver8_config }, { &exception_config });

		TestCasePerformerConfiguration test_performer_config({ &sender1_config, &sender2_config, &sender3_config, &sender4_config, &sender5_config, &sender6_config, &sender7_config, &sender8_config });

		TestCaseConfiguration test_case_config("test_case_1", "test_function_1", true, wrapper_config, test_performer_config, verifier_config);

		TestSuiteConfiguration test_suite_config("test_case_all.config", { test_case_config });

		assert(suite_config == test_suite_config);
	}
	////////////////// current
	{
		TestSuiteJsonConfigParser parser("test_case_all_senders.config");
		auto suite_config = parser.createConfiguration();
		
		
		TestExceptionListener test_exception_listener;

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(suite_config.testsBegin()->uutConfig(), logger, "", &test_exception_listener, &test_exception_listener, &test_exception_listener);

		Notifier test_notifier(nullptr);

		///test impl

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
			MessageSender * create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const override
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
				else
					return nullptr;
			}
		};
		///
		auto sender_factory = new TestSenderFactory();

		TestCasePerformer test_performer(suite_config.testsBegin()->performerConfig(), test_client, test_notifier, sender_factory);
		test_performer.sendAll();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		//TO DO equality assert


	}
	/////////////////
	{

		///test impl

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
			MessageSender * create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const override
			{

				if (auto concrete_configuration = dynamic_cast<const MessageCountingSenderConfiguration*>(&sender_configuration))  {
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
				else
					return nullptr;
			}
		};
		///
		auto sender_factory = new TestSenderFactory();

		TestSuiteJsonConfigParser parser("test_case_all.config");
		auto suite_config = parser.createConfiguration();


		TestExceptionListener test_exception_listener;

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(suite_config.testsBegin()->uutConfig(), nullptr, "", &test_exception_listener, &test_exception_listener, &test_exception_listener);

		Notifier test_notifier(nullptr);

		TestCaseVerifier test_verifier(suite_config.testsBegin()->verifierConfig(), test_client, test_notifier);
	
		TestCasePerformer test_performer(suite_config.testsBegin()->performerConfig(), test_client, test_notifier, sender_factory);
	
		test_performer.sendAll();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	{

		///test impl

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
			MessageSender * create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const override
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
				else
					return nullptr;
			}
		};
		///
		auto sender_factory = new TestSenderFactory();

		TestSuiteJsonConfigParser parser("test_case_all.config");
		auto suite_config = parser.createConfiguration();

		TestFunctionRegister test_register;
		test_register.registerTestFunction("test_function_1", test_fun);		
		
		StdOutTestObserver testObserver;
	
		TestCase test_case(*suite_config.testsBegin(), sender_factory, test_register, &testObserver);
		test_case.run();
	}

}





