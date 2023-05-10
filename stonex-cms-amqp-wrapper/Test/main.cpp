
#include "ConfigurationParser/CMSWrapperConfigurationParser.h"
#include "Wrapper/CMSClientTestUnit.h"
#include <boost/json.hpp>
#include <fstream>
#include <vector>

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

int main()
{
	CMSWrapperConfigurationParser parser;

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
	auto wrapper = parser.createCMSConfig(wrapper_config_json);
	auto wrapper_config = CMSWrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

	assert(wrapper == wrapper_config);

	auto logger = std::make_shared<StdOutLogger>();
	CMSClientTestUnit test_client(wrapper_config, logger);
}





