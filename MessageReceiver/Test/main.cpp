
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include <ConfigurationParser/TestCaseMessageReceiverConfigurationParser.h>

#include <Notifier/EventStatusObserver.h>
#include <Notifier/TestNotifier.h>

#include <StdOutLogger/StdOutLogger.h>

#include <Wrapper/CMSClientTestUnit.h>
#include <MessageReceiver/TestMessageReceiver.h>

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
	TestCaseMessageReceiverConfigurationParser parser;
	
	{
		boost::json::object::value_type message_sender_config_json = *valueFromFile("test_message_receiver.config").as_object().cbegin();
		auto receiver = parser.createTestReceiverConfig(message_sender_config_json.key_c_str(), message_sender_config_json.value().as_object());
		auto receiver_config = TestCaseMessageReceiverConfiguration("connection1", "session1", "consumer1");

		assert(receiver != nullptr);
		assert(*receiver == receiver_config);
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
		EventStatusObserver event_observer(event_notifier);

		TestCaseMessageReceiverConfiguration test_consumer_config("connection1","session1","consumer1");
		

		TestMessageReceiver receiver(test_consumer_config, test_client, event_notifier);
	
	}
}





