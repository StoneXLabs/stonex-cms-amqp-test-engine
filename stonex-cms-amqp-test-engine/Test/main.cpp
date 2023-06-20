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
#include <test_utils/TestSenderFactory.h>
#include <Configuration/MessageSenderConfiguration.h>
#include <Configuration/FileMessageSenderConfiguration.h >
#include <Configuration/MessageCountingSenderConfiguration.h >
#include <Configuration/MessageDecoratingSenderConfiguration.h >
#include <Configuration/FileMessageCountingSenderConfiguration.h >
#include <Configuration/FileMessageDecoratingSenderConfiguration.h >
#include <Configuration/MessageCountingDecoratingSenderConfiguration.h >
#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h >


#include <MessageReceiver/MessageReceiver.h>
#include <MessageReceiver/MessageFileReceiver.h>
#include <MessageReceiver/MessageCountingReceiver.h>
#include <MessageReceiver/MessageDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingFileReceiver.h>
#include <MessageReceiver/MessageDecoratingFileReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingFileReceiver.h>
#include <ConfigurationParser/TestSuiteJsonConfigParser.h>
#include <TestSuite/TestCase.h>
#include <TestSuite/TestCasePerformer.h>
#include <TestSuite/TestCaseVerifier.h>
#include <TestSuite/TestRunner.h>
#include <Notifier/Notifier.h>
#include <Notifier/StdOutTestObserver.h>
#include <StdOutLogger/StdOutLogger.h>

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

		MessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1", "text", "engine");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		assert(verifier_config == test_case_verifier);
	}

	{
		TestCaseConfigurationParser parser;
		boost::json::object::value_type test_case_performer_config_json = *valueFromFile("test_case.config").as_object().cbegin();
		auto test_case_performer = parser.createTestCaseConfig(test_case_performer_config_json.key_c_str(), test_case_performer_config_json.value().as_object()).performerConfig();

		MessageSenderConfiguration producer_config("connection1", "session1", "producer1", "text", "engine");
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

		MessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1", "text", "engine");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		MessageSenderConfiguration sender_config("connection1", "session1", "producer1", "text", "engine");
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

		MessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1", "text", "engine");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		MessageSenderConfiguration sender_config("connection1", "session1", "producer1", "text", "engine");
		TestCasePerformerConfiguration test_performer_config({ &sender_config });

		TestCaseConfiguration test_case_config("test_case_1", "test_function_1", true, wrapper_config, test_performer_config, verifier_config);

		TestSuiteConfiguration test_suite_config("test_suite.config", { test_case_config });

		assert(suite_config == test_suite_config);
	}

	{
		TestSuiteJsonConfigParser parser("test_case_all.config");
		auto suite_config = parser.createConfiguration();

		auto consumer1_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE_1", "close", "");
		auto consumer2_config = ConsumerConfiguration("consumer2", "queue", "CMS_CLIENT_QUEUE_2", "close", "");
		auto consumer3_config = ConsumerConfiguration("consumer3", "queue", "CMS_CLIENT_QUEUE_3", "close", "");
		auto consumer4_config = ConsumerConfiguration("consumer4", "queue", "CMS_CLIENT_QUEUE_4", "close", "");
		auto consumer5_config = ConsumerConfiguration("consumer5", "queue", "CMS_CLIENT_QUEUE_5", "close", "");
		auto consumer6_config = ConsumerConfiguration("consumer6", "queue", "CMS_CLIENT_QUEUE_6", "close", "");
		auto consumer7_config = ConsumerConfiguration("consumer7", "queue", "CMS_CLIENT_QUEUE_7", "close", "");
		auto consumer8_config = ConsumerConfiguration("consumer8", "queue", "CMS_CLIENT_QUEUE_8", "close", "");
		auto consumer9_config = ConsumerConfiguration("consumer9", "queue", "CMS_CLIENT_QUEUE_9", "close", "FEATURE='C'");
		auto consumer10_config = ConsumerConfiguration("consumer10", "queue", "CMS_CLIENT_QUEUE_9", "close", "FEATURE='D'");
		auto consumer11_config = ConsumerConfiguration("consumer11", "queue", "CMS_CLIENT_QUEUE_9", "close", "FEATURE='F'");
		auto consumer12_config = ConsumerConfiguration("consumer12", "queue", "CMS_CLIENT_QUEUE_9", "close", "FEATURE='CD'");
		auto consumer13_config = ConsumerConfiguration("consumer13", "queue", "CMS_CLIENT_QUEUE_9", "close", "FEATURE='CF'");
		auto consumer14_config = ConsumerConfiguration("consumer14", "queue", "CMS_CLIENT_QUEUE_9", "close", "FEATURE='DF'");
		auto consumer15_config = ConsumerConfiguration("consumer15", "queue", "CMS_CLIENT_QUEUE_9", "close", "FEATURE='CDF'");

		auto producer1_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE_1", {});
		auto producer2_config = ProducerConfiguration("producer2", "queue", "CMS_CLIENT_QUEUE_2", {});
		auto producer3_config = ProducerConfiguration("producer3", "queue", "CMS_CLIENT_QUEUE_3", {});
		auto producer4_config = ProducerConfiguration("producer4", "queue", "CMS_CLIENT_QUEUE_4", {});
		auto producer5_config = ProducerConfiguration("producer5", "queue", "CMS_CLIENT_QUEUE_5", {});
		auto producer6_config = ProducerConfiguration("producer6", "queue", "CMS_CLIENT_QUEUE_6", {});
		auto producer7_config = ProducerConfiguration("producer7", "queue", "CMS_CLIENT_QUEUE_7", {});
		auto producer8_config = ProducerConfiguration("producer8", "queue", "CMS_CLIENT_QUEUE_8", {});
		auto producer9_config = ProducerConfiguration("producer9", "queue", "CMS_CLIENT_QUEUE_9", {});
		auto producer10_config = ProducerConfiguration("producer10", "queue", "CMS_CLIENT_QUEUE_9", {});
		auto producer11_config = ProducerConfiguration("producer11", "queue", "CMS_CLIENT_QUEUE_9", {});
		auto producer12_config = ProducerConfiguration("producer12", "queue", "CMS_CLIENT_QUEUE_9", {});
		auto producer13_config = ProducerConfiguration("producer13", "queue", "CMS_CLIENT_QUEUE_9", {});
		auto producer14_config = ProducerConfiguration("producer14", "queue", "CMS_CLIENT_QUEUE_9", {});
		auto producer15_config = ProducerConfiguration("producer15", "queue", "CMS_CLIENT_QUEUE_9", {});

		auto session_config = SessionConfiguration("session1", true, false, 
			{ consumer1_config, consumer2_config, consumer3_config, consumer4_config, consumer5_config, consumer6_config, consumer7_config, consumer8_config, consumer9_config,  consumer10_config, consumer11_config, consumer12_config, consumer13_config, consumer14_config, consumer15_config, },
			{ producer1_config, producer2_config, producer3_config, producer4_config, producer5_config, producer6_config, producer7_config, producer8_config, producer9_config,  producer10_config, producer11_config, producer12_config, producer13_config, producer14_config, producer15_config, });


		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));


		MessageReceiverConfiguration receiver1_config("connection1", "session1", "consumer1", "text", "engine");
		MessageCountingReceiverConfiguration receiver2_config("connection1", "session1", "consumer2", "text", "engine", 1);
		FileMessageReceiverConfiguration receiver3_config("connection1", "session1", "consumer3", "text", "engine", "test_messages_received.txt");
		MessageDecoratingReceiverConfiguration receiver4_config("connection1", "session1", "consumer4", "text", "engine", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingReceiverConfiguration receiver5_config("connection1", "session1", "consumer5", "text", "engine", "test_messages_received.txt", 1);
		MessageCountingDecoratingReceiverConfiguration receiver6_config("connection1", "session1", "consumer6", "text", "engine", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageDecoratingReceiverConfiguration receiver7_config("connection1", "session1", "consumer7", "text", "engine", "test_messages_received.txt", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingDecoratingReceiverConfiguration receiver8_config("connection1", "session1", "consumer8", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingDecoratingReceiverConfiguration receiver9_config("connection1", "session1", "consumer9", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","C") });
		FileMessageCountingDecoratingReceiverConfiguration receiver10_config("connection1", "session1", "consumer10", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","D") });
		FileMessageCountingDecoratingReceiverConfiguration receiver11_config("connection1", "session1", "consumer11", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","F") });
		FileMessageCountingDecoratingReceiverConfiguration receiver12_config("connection1", "session1", "consumer12", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","CD") });
		FileMessageCountingDecoratingReceiverConfiguration receiver13_config("connection1", "session1", "consumer13", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","CF") });
		FileMessageCountingDecoratingReceiverConfiguration receiver14_config("connection1", "session1", "consumer14", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","DF") });
		FileMessageCountingDecoratingReceiverConfiguration receiver15_config("connection1", "session1", "consumer15", "text", "engine", "test_messages_received.txt", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","CDF") });



		ExceptionsConfiguration exception_config("connection1", 0);
	
	
		MessageSenderConfiguration sender1_config("connection1", "session1", "producer1", "text", "engine-test");
		MessageCountingSenderConfiguration sender2_config("connection1", "session1", "producer2", "text", "engine-test", 1);
		MessageDecoratingSenderConfiguration sender3_config("connection1", "session1", "producer3", "text", "engine-test", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageSenderConfiguration sender4_config("connection1", "session1", "producer4", "text", "engine", "test_message_file1.txt");
		MessageCountingDecoratingSenderConfiguration sender5_config("connection1", "session1", "producer5", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingSenderConfiguration sender6_config("connection1", "session1", "producer6", "text", "engine", "test_message_file1.txt", 1);
		FileMessageDecoratingSenderConfiguration sender7_config("connection1", "session1", "producer7", "text", "engine", "test_message_file1.txt", { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingDecoratingSenderConfiguration sender8_config("connection1", "session1", "producer8", "text", "engine", "test_message_file1.txt", 1, { new MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		MessageCountingDecoratingSenderConfiguration sender9_config("connection1", "session1", "producer9", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","C") });
		MessageCountingDecoratingSenderConfiguration sender10_config("connection1", "session1", "producer10", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","D") });
		MessageCountingDecoratingSenderConfiguration sender11_config("connection1", "session1", "producer11", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","F") });
		MessageCountingDecoratingSenderConfiguration sender12_config("connection1", "session1", "producer12", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","CD") });
		MessageCountingDecoratingSenderConfiguration sender13_config("connection1", "session1", "producer13", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","CF") });
		MessageCountingDecoratingSenderConfiguration sender14_config("connection1", "session1", "producer14", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","DF") });
		MessageCountingDecoratingSenderConfiguration sender15_config("connection1", "session1", "producer15", "text", "engine-test", 1, { new MessageField(FIELD_TYPE::STRINGPROPERTY,"FEATURE","CDF") });
		

		TestCaseVerifierConfiguration verifier_config({ &receiver1_config, &receiver2_config, &receiver3_config, &receiver4_config, &receiver5_config, &receiver6_config, &receiver7_config, &receiver8_config, &receiver9_config, &receiver10_config, &receiver11_config, &receiver12_config, &receiver13_config, &receiver14_config, &receiver15_config }, { &exception_config });

		TestCasePerformerConfiguration test_performer_config({ &sender1_config, &sender2_config, &sender3_config, &sender4_config, &sender5_config, &sender6_config, &sender7_config, &sender8_config, &sender9_config, &sender10_config, &sender11_config, &sender12_config, &sender13_config, &sender14_config, &sender15_config });

		TestCaseConfiguration test_case_config("test_case_1", "test_function_1", true, wrapper_config, test_performer_config, verifier_config);

		TestSuiteConfiguration test_suite_config("test_case_all.config", { test_case_config });

		assert(suite_config.testsBegin()->uutConfig() == wrapper_config);

		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(0) == receiver1_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(1) == receiver2_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(2) == receiver3_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(3) == receiver4_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(4) == receiver5_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(5) == receiver6_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(6) == receiver7_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(7) == receiver8_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(8) == receiver9_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(9) == receiver10_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(10) == receiver11_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(11) == receiver12_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(12) == receiver13_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(13) == receiver14_config);
		assert(*suite_config.testsBegin()->verifierConfig().messageExpectations().at(14) == receiver15_config);

		assert(suite_config.testsBegin()->verifierConfig() == verifier_config);
		assert(suite_config.testsBegin()->performerConfig() == test_performer_config);
		assert(*suite_config.testsBegin() == test_case_config);
		assert(suite_config == test_suite_config);
	}
	////////////////// current
	{
		TestSuiteJsonConfigParser parser("test_case_all_senders.config");
		auto suite_config = parser.createConfiguration();
		
		
		TestExceptionListener test_exception_listener;

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(suite_config.testsBegin()->uutConfig(), logger, "", &test_exception_listener, &test_exception_listener, &test_exception_listener);

		StdOutTestObserver testObserver;
		Notifier test_notifier(&testObserver);

		auto sender_factory = new TestSenderFactory();

		TestCasePerformer test_performer(suite_config.testsBegin()->performerConfig(), test_client, test_notifier, sender_factory);
		test_performer.sendAll();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		//TO DO equality assert


	}
	/////////////////
	{

		TestSenderFactory sender_factory;
		MessageReceiverFactory receiver_factory;

		TestSuiteJsonConfigParser parser("test_case_all_receivers.config");
		auto suite_config = parser.createConfiguration();


		TestExceptionListener test_exception_listener;

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(suite_config.testsBegin()->uutConfig(), logger, "", &test_exception_listener, &test_exception_listener, &test_exception_listener);

		StdOutTestObserver testObserver;
		Notifier test_notifier(&testObserver);

		TestCaseVerifier test_verifier(suite_config.testsBegin()->verifierConfig(), test_client, test_notifier, &receiver_factory);
	
		TestCasePerformer test_performer(suite_config.testsBegin()->performerConfig(), test_client, test_notifier, &sender_factory);

		test_performer.sendAll();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	{

		TestSenderFactory sender_factory;
		MessageReceiverFactory receiver_factory;

		TestSuiteJsonConfigParser parser("test_case_all.config");
		auto suite_config = parser.createConfiguration();

		TestFunctionRegister test_register;
		test_register.registerTestFunction("test_function_1", test_fun);		
		
		StdOutTestObserver testObserver;
		Notifier test_notifier(&testObserver);

		auto logger = std::make_shared<StdOutLogger>();
	
		TestCase test_case(*suite_config.testsBegin(), &sender_factory, &receiver_factory, test_register, &testObserver, logger);
		test_case.run();
	}

	{

		TestSenderFactory sender_factory;
		MessageReceiverFactory receiver_factory;

		TestSuiteJsonConfigParser parser("durable_subscription.config");

		TestFunctionRegister test_register;
		test_register.registerTestFunction("test_function_1", test_fun);

		StdOutTestObserver testObserver;
		Notifier test_notifier(&testObserver);

		auto logger = std::make_shared<StdOutLogger>();

		TestRunner test_runner(parser, test_register, receiver_factory, sender_factory,  &testObserver, logger);
		test_runner.run();
	}

}





