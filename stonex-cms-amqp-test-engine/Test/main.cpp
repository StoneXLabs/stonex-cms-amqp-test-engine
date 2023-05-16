
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



#include <ConfigurationParser/TestSuiteJsonConfigParser.h>
#include <TestSuite/TestCasePerformer.h>

#include <Notifier/TestNotifier.h>
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
	//test_case_all_senders.config
	//{ 
	//	TestCaseConfigurationParser parser;
	//	boost::json::object::value_type test_case_performer_config_json = *valueFromFile("test_case.config").as_object().cbegin();
	//	auto test_case_performer = parser.createTestCaseConfig(test_case_performer_config_json.key_c_str(), test_case_performer_config_json.value().as_object()).performerConfig();

	//	MessageSenderConfiguration producer_config("connection1", "session1", "producer1");
	//	TestCasePerformerConfiguration test_performer_config({ &producer_config });


	//	assert(test_case_performer == test_performer_config);
	//}

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
		TestSuiteJsonConfigParser parser("test_case_all_senders.config");
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
		TestCaseVerifierConfiguration verifier_config({ &receiver1_config, &receiver2_config, &receiver3_config, &receiver4_config, &receiver5_config, &receiver6_config, &receiver7_config, &receiver8_config }, { &exception_config });

	
		MessageSenderConfiguration sender1_config("connection1", "session1", "producer1");
		MessageCountingSenderConfiguration sender2_config("connection1", "session1", "producer2", 1);
		FileMessageSenderConfiguration sender3_config("connection1", "session1", "producer3", "test_messages.txt");
		MessageDecoratingSenderConfiguration sender4_config("connection1", "session1", "producer4", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageDecoratingSenderConfiguration sender5_config("connection1", "session1", "producer5", "test_messages.txt", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingSenderConfiguration sender6_config("connection1", "session1", "producer6", "test_messages.txt", 1);
		MessageCountingDecoratingSenderConfiguration sender7_config("connection1", "session1", "producer7", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		FileMessageCountingDecoratingSenderConfiguration sender8_config("connection1", "session1", "producer8", "test_messages.txt", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
		



		TestCasePerformerConfiguration test_performer_config({ &sender1_config, &sender2_config, &sender3_config, &sender4_config, &sender5_config, &sender6_config, &sender7_config, &sender8_config });

		TestCaseConfiguration test_case_config("test_case_1", "test_function_1", true, wrapper_config, test_performer_config, verifier_config);

		TestSuiteConfiguration test_suite_config("test_case_all_senders.config", { test_case_config });

		assert(suite_config == test_suite_config);
	}

	{

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


		TestExceptionListener test_exception_listener;

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(wrapper_config, logger, "", &test_exception_listener, &test_exception_listener, &test_exception_listener);

		Notifier test_notifier(nullptr);

		TestCasePerformer test_performer(test_performer_config, test_client, test_notifier);
	}

	{

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


		TestExceptionListener test_exception_listener;

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(wrapper_config, logger, "", &test_exception_listener, &test_exception_listener, &test_exception_listener);

		Notifier test_notifier(nullptr);

		TestCasePerformer test_performer(test_performer_config, test_client, test_notifier);
	}

}





