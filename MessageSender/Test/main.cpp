
#include "Wrapper/CMSClientTestUnit.h"
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>
#include <Configuration/CountingCaseProducerConfiguration.h>
#include <Configuration/FileTestCaseProducerConfiguration.h>
#include <Configuration/FileCountingTestCaseProducerConfiguration.h>


#include "Wrapper/CMSClientTestUnit.h"
#include <MessageSender/MessageSender.h>
#include "StdOutLogger/StdOutLogger.h"

#include <Notifier/EventStatusObserver.h>
#include <Notifier/TestNotifier.h>

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


class TestMessageSender : public MessageSender
{
public:
	TestMessageSender(const TestCaseProducerConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
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

int main()
{
	TestCaseProducerConfigurationParser parser;

	{
		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_sender.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = TestCaseProducerConfiguration("connection1", "session1", "producer1");

		assert(producer != nullptr);
		assert(*producer == producer_config);
	}

	{
		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_counting_sender.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = CountingCaseProducerConfiguration("connection1", "session1", "producer1", 1);

		assert(producer != nullptr);
		assert(dynamic_cast<CountingCaseProducerConfiguration*>(producer) != nullptr);
		assert(*dynamic_cast<CountingCaseProducerConfiguration*>(producer) == producer_config);

	}

	{
		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_sender_from_file.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = FileTestCaseProducerConfiguration("connection1", "session1", "producer1", "test_messages.txt");


		assert(producer != nullptr);
		assert(dynamic_cast<FileTestCaseProducerConfiguration*>(producer) != nullptr);
		assert(*dynamic_cast<FileTestCaseProducerConfiguration*>(producer) == producer_config);
	}

	{
		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_counting_sender_from_file.config").as_object().cbegin();
		auto producer = parser.createTestCaseProducerConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto producer_config = FileCountingTestCaseProducerConfiguration("connection1", "session1", "producer1", "test_messages.txt", 1);

		assert(producer != nullptr);
		assert(dynamic_cast<FileCountingTestCaseProducerConfiguration*>(producer) != nullptr);
		assert(*dynamic_cast<FileCountingTestCaseProducerConfiguration*>(producer) == producer_config);
	}

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

		auto test_producer_config = FileCountingTestCaseProducerConfiguration("connection1", "session1", "producer1", "test_messages.txt", 1);
		TestMessageSender sender(test_producer_config, test_client, event_observer);
		sender.send();
	}


	
}





