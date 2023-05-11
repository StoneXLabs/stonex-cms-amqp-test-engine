
#include "ConfigurationParser/WrapperConfigurationParser.h"
#include "Wrapper/CMSClientTestUnit.h"
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include "StdOutLogger/StdOutLogger.h"

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

class TestExceptionListener : public cms::ExceptionListener {
public:
	void onException(const cms::CMSException& ex) { std::cout << "EXCEPTION " << ex.what() << std::endl; }
};

int main()
{
	WrapperConfigurationParser parser;

	boost::json::object::value_type consumer_config_json = *valueFromFile("test_consumer.config").as_object().cbegin();
	auto consumer = parser.createConsumerConfig(consumer_config_json.key_c_str(), consumer_config_json.value().as_object());
	auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");

	assert(consumer == consumer_config);

	boost::json::object::value_type producer_config_json = *valueFromFile("test_producer.config").as_object().cbegin();
	auto producer = parser.createProducerConfig(producer_config_json.key_c_str(), producer_config_json.value().as_object());
	auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});

	assert(producer == producer_config);

	boost::json::object::value_type session_config_json = *valueFromFile("test_session.config").as_object().cbegin();
	auto session = parser.createSessionConfig(session_config_json.key_c_str(), session_config_json.value().as_object());
	auto session_config = SessionConfiguration("session1", true, false, { consumer_config }, { producer_config });

	assert(session == session_config);

	boost::json::object::value_type conection_config_json = *valueFromFile("test_connection.config").as_object().cbegin();
	auto connection = parser.createConnectionConfig(conection_config_json.key_c_str(), conection_config_json.value().as_object());
	auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });

	assert(connection == connection_config);

	boost::json::value wrapper_config_json = valueFromFile("test_wrapper.config");
	auto wrapper = parser.createWrapperConfiguration(wrapper_config_json);
	auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

	assert(wrapper == wrapper_config);

	TestExceptionListener test_exception_listener;

	auto logger = std::make_shared<StdOutLogger>();
	CMSClientTestUnit test_client(wrapper_config, logger, "", &test_exception_listener, &test_exception_listener, &test_exception_listener);

	assert(test_client.connection("non_existent") == nullptr);

	assert(test_client.session("connection1", "non_existent") == nullptr);
	assert(test_client.session("non_existent", "session1") == nullptr);

	assert(test_client.consumer("connection1", "session1", "non_existent") == nullptr);
	assert(test_client.consumer("connection1", "non_existent", "consumer1") == nullptr);
	assert(test_client.consumer("non_existent", "session1", "consumer1") == nullptr);


	assert(test_client.consumer("connection1", "non_existent", "non_existent") == nullptr);
	assert(test_client.consumer("non_existent", "non_existent", "consumer1") == nullptr);
	assert(test_client.consumer("non_existent", "session1", "non_existent") == nullptr);

	assert(test_client.consumer("non_existent", "non_existent", "non_existent") == nullptr);



	assert(test_client.producer("connection1", "session1", "non_existent") == nullptr);
	assert(test_client.producer("connection1", "non_existent", "producer1") == nullptr);
	assert(test_client.producer("non_existent", "session1", "producer1") == nullptr);

	assert(test_client.producer("connection1", "non_existent", "non_existent") == nullptr);
	assert(test_client.producer("non_existent", "non_existent", "producer1") == nullptr);
	assert(test_client.producer("non_existent", "session1", "non_existent") == nullptr);

	assert(test_client.producer("non_existent", "non_existent", "non_existent") == nullptr);
	



	assert(test_client.connection("connection1") != nullptr);
	assert(test_client.connection("connection1") == test_client.connection(connection_config.key()));

	assert(test_client.session("connection1","session1") != nullptr);
	assert(test_client.session("connection1","session1") == test_client.session(connection_config.key(),session_config.key()));

	assert(test_client.consumer("connection1","session1","consumer1") != nullptr);
	assert(test_client.consumer("connection1","session1","consumer1") == test_client.consumer(connection_config.key(), session_config.key(),consumer_config.key()));

	assert(test_client.producer("connection1","session1","producer1") != nullptr);
	assert(test_client.producer("connection1","session1","producer1") == test_client.producer(connection_config.key(), session_config.key(),producer_config.key()));
}





