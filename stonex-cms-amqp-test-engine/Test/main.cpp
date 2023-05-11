
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include <ConfigurationParser/TestSuiteJsonConfigParser.h>

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

		TestCaseMessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		assert(verifier_config == test_case_verifier);
	}

	{
		TestCaseConfigurationParser parser;
		boost::json::object::value_type test_case_performer_config_json = *valueFromFile("test_case.config").as_object().cbegin();
		auto test_case_performer = parser.createTestCaseConfig(test_case_performer_config_json.key_c_str(), test_case_performer_config_json.value().as_object()).performerConfig();

		TestCaseProducerConfiguration producer_config("connection1", "session1", "producer1");
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

		TestCaseMessageReceiverConfiguration receiver_config("connection1", "session1", "consumer1");
		ExceptionsConfiguration exception_config("connection1", 0);
		TestCaseVerifierConfiguration verifier_config({ &receiver_config }, { &exception_config });


		TestCaseProducerConfiguration sender_config("connection1", "session1", "producer1");
		TestCasePerformerConfiguration test_performer_config({ &sender_config });

		TestCaseConfiguration test_case_config("test_case_1", "test_function_1", true, wrapper_config, test_performer_config, verifier_config);

		assert(test_case == test_case_config);
	}

	{
		TestSuiteJsonConfigParser parser("test_suite.config");
		auto conf = parser.createConfiguration();
	}
}





