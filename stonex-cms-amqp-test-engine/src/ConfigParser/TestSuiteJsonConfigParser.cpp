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

#include <ConfigParser/TestSuiteJsonConfigParser.h>

#include <fstream>

TestSuiteJsonConfigParser::TestSuiteJsonConfigParser(const std::string& configFile)
	:mConfigFilePath{ configFile }
{
}

TestSuiteConfiguration TestSuiteJsonConfigParser::createConfiguration() const
{
	

	if (auto jsonConfig = fromFile(); jsonConfig.is_object())
	{
		std::list<TestCaseConfiguration> configuration;

		std::transform(std::cbegin(jsonConfig.as_object()), std::cend(jsonConfig.as_object()), std::back_inserter(configuration), [this](const boost::json::object::value_type obj) {
			return createTestCaseConfig(obj.key_c_str(), obj.value());
		});

		return TestSuiteConfiguration(mConfigFilePath, configuration);
	}
	else return TestSuiteConfiguration(mConfigFilePath, {});
}

boost::json::value TestSuiteJsonConfigParser::fromFile() const
{
	std::ifstream config_file(mConfigFilePath);

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

TestCaseConfiguration TestSuiteJsonConfigParser::createTestCaseConfig(const std::string& configName, const boost::json::value & json) const
{
	bool enabled{ false };
	std::string test_name{ "not initialized" };
	boost::json::value configJson;


	if (json.is_object())
	{
		auto configJson = json.as_object();
		if (auto test_name_val = configJson.if_contains("test_name"); test_name_val != nullptr && test_name_val->is_string())
			test_name = test_name_val->as_string().c_str();

		if (auto test_params_val = configJson.if_contains("cms_configuration"); test_params_val != nullptr && test_params_val->is_object())
		{
			if (auto test_enabled_val = configJson.if_contains("enabled"); test_enabled_val != nullptr && test_enabled_val->is_bool())
				enabled = test_enabled_val->as_bool();
		}
		
	}

	return TestCaseConfiguration(configName, test_name, enabled, createCMSConfig(json), createTestPerformerConfig(json), createTestVerifierConfig(json));
}

CMSClientTestConfiguration TestSuiteJsonConfigParser::createCMSConfig(const boost::json::value & json) const
{
	
	if (json.is_object())
	{
		if (auto config_obj = json.as_object().if_contains("cms_configuration"); config_obj != nullptr && config_obj->is_object())
		{
			std::vector<ConnectionConfiguration> configuration;

			std::transform(std::begin(config_obj->as_object()), std::end(config_obj->as_object()), std::back_inserter(configuration), [this](const boost::json::object::value_type& item) {
				return createConnectionConfig(item.key_c_str(), item.value());
			});

			return CMSClientTestConfiguration(configuration);
		}
	}
	return CMSClientTestConfiguration();
}

TestCasePerformerConfiguration TestSuiteJsonConfigParser::createTestPerformerConfig(const boost::json::value & json) const
{
	TestCasePerformerConfiguration par;

	if (json.is_object())
	{
		if (auto test_params_val = json.as_object().if_contains("message_parameters"); test_params_val != nullptr && test_params_val->is_object())
		{		
			std::for_each(std::begin(test_params_val->as_object()), std::end(test_params_val->as_object()), [&par, this](const boost::json::object::value_type item) {
				auto prod_params = createTestCaseProducerConfig(item.key_c_str(), item.value());
				par.addProducerMessagesParameter(prod_params);
			});
		}
	}

	return par;
}

TestCaseVerifierConfiguration TestSuiteJsonConfigParser::createTestVerifierConfig(const boost::json::value & json) const
{
	std::vector<TestCaseMessageReceiverConfiguration*> receiverConfigs;
	std::vector<CMSExceptionsConfiguration*> exceptionsConfig;

	if (json.is_object())
	{
		if (auto test_expected_val = json.as_object().if_contains("expected"); test_expected_val != nullptr && test_expected_val->is_object())
		{
			if (auto test_expected_messages_val = test_expected_val->as_object().if_contains("messages"); test_expected_messages_val != nullptr && test_expected_messages_val->is_object())
			{
				std::transform(std::cbegin(test_expected_messages_val->as_object()), std::cend(test_expected_messages_val->as_object()), std::back_inserter(receiverConfigs), [this](const boost::json::object::value_type& obj) {
					return createTestReceiverConfig(obj.key_c_str(), obj.value());
				});
			}

			if (auto test_expected_exceptions_val = test_expected_val->as_object().if_contains("exceptions"); test_expected_exceptions_val != nullptr && test_expected_exceptions_val->is_object())
			{
				std::transform(std::cbegin(test_expected_exceptions_val->as_object()), std::cend(test_expected_exceptions_val->as_object()), std::back_inserter(exceptionsConfig), [this](const boost::json::object::value_type& obj) {
					return createTestExceptionConfig(obj.key_c_str(), obj.value());
				});
			}
		}
	}

	
		return TestCaseVerifierConfiguration(receiverConfigs, exceptionsConfig);
}



 ConnectionConfiguration TestSuiteJsonConfigParser::createConnectionConfig(const std::string& configName, const boost::json::value & json) const
{
	try
	{
		std::string url;
		std::string user;
		std::string password;
		std::string id;

		if (json.is_object()) {

			auto val_obj = json.as_object();

			if (auto entry = val_obj.if_contains("broker"); entry)
				url = entry->as_string();
			if (auto entry = val_obj.if_contains("username"); entry)
				user = entry->as_string();
			if (auto entry = val_obj.if_contains("password"); entry)
				password = entry->as_string();
			if (auto entry = val_obj.if_contains("id"); entry)
				id = entry->as_string();

			std::vector<SessionConfiguration> sessionConfiguration;


			if (auto sess_val_obj = val_obj.if_contains("session");  sess_val_obj != nullptr && sess_val_obj->is_object()) {

				auto sess = sess_val_obj->as_object();

				std::transform(std::begin(sess), std::end(sess), std::back_inserter(sessionConfiguration), [this](boost::json::object::value_type& item) {
					return createSessionConfig(item.key_c_str(), item.value());
				});
			}

			return { configName, url, user, password, id, sessionConfiguration };
		}
	}
	catch (const std::exception& ex)
	{
	}
}

 SessionConfiguration TestSuiteJsonConfigParser::createSessionConfig(const std::string& configName, const boost::json::value & json) const
{
	bool autoAck{ false };
	bool isTransacted{ false };

	if (json.is_object()) {

		auto val_obj = json.as_object();

		if (auto val = val_obj.if_contains("auto_ack"))
			autoAck = val->as_bool();

		if (auto val = val_obj.if_contains("is_transacted"))
			isTransacted = val->as_bool();

		if (auto clients = val_obj.if_contains("clients"); clients != nullptr  && clients->is_object())
		{
			std::vector<ConsumerConfiguration> consumerConfiguration;
			std::vector<ProducerConfiguration> producerConfiguration;

			if (auto consumers = clients->as_object().if_contains("consumers"); consumers != nullptr  && consumers->is_object())
			{

				std::transform(std::cbegin(consumers->as_object()), std::cend(consumers->as_object()), std::back_inserter(consumerConfiguration), [this](const boost::json::object::value_type& item) {
					return createConsumerConfig(item.key_c_str(), item.value());
				});
			}

			if (auto producers = clients->as_object().if_contains("producers"); producers != nullptr  && producers->is_object())
			{
				std::transform(std::cbegin(producers->as_object()), std::cend(producers->as_object()), std::back_inserter(producerConfiguration), [this](const boost::json::object::value_type& item) {
					return createProducerConfig(item.key_c_str(), item.value());
				});
			}


			return SessionConfiguration(configName, autoAck, isTransacted, consumerConfiguration, producerConfiguration);
		}
		else
			return SessionConfiguration(configName, autoAck, isTransacted, {}, {});

	}
	else
		return SessionConfiguration(configName);
}

ConsumerConfiguration TestSuiteJsonConfigParser::createConsumerConfig(const std::string& configName, const boost::json::value & json) const
{

	std::string dest_type;
	std::string address;
	std::string selector;

	//durable topic parameters
	bool durable{ false };
	std::string durable_subscription_name{};
	
	//consumer close or detatch on destructor call
	std::string terminate_method{ "close" };

	if (json.is_object()) {

		auto val_obj = json.as_object();

		if (auto dest = val_obj.if_contains("dest_type"))
			dest_type = dest->as_string();
		if (auto address_string = val_obj.if_contains("address"))
			address = address_string->as_string();
		if (auto selector_string = val_obj.if_contains("selector"))
			selector = selector_string->as_string();

		//durable topic parameters
		if (auto durable_flag = val_obj.if_contains("durable"))
			durable = durable_flag->as_bool();
		if (auto subscription_name = val_obj.if_contains("subscription_name"))
			durable_subscription_name = subscription_name->as_string();

		//consumer close or detatch on destructor call

		if (auto consumer_terminate_method = val_obj.if_contains("terminate_method"))
			terminate_method = consumer_terminate_method->as_string();
	}

	//TO DO config error

	return { configName,dest_type,address,terminate_method,selector,durable,durable_subscription_name };
}

ProducerConfiguration TestSuiteJsonConfigParser::createProducerConfig(const std::string& configName, const boost::json::value & json) const
{
	std::string dest_type;
	std::string address;

	if (json.is_object()) {

		auto val_obj = json.as_object();

		if (auto dest = val_obj.if_contains("dest_type"))
			dest_type = dest->as_string();
		if (auto address_string = val_obj.if_contains("address"))
			address = address_string->as_string();
	}

	//TO DO config error

	return { configName,dest_type,address };
}

TestCaseProducerConfiguration* TestSuiteJsonConfigParser::createTestCaseProducerConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		std::string message_file;
		std::string message_factory;
		int message_count{ -1 };

		if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			message_count = tmp_message_count->as_int64();

		if (auto tmp_message_file = json.as_object().if_contains("message_factory"); tmp_message_file && tmp_message_file->is_string())
			message_factory = tmp_message_file->as_string().c_str();

		if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string())
			message_file = tmp_message_file->as_string().c_str();
		
		return new TestCaseProducerConfiguration(configName, message_factory, message_file, message_count);

	}
	else
		return new TestCaseProducerConfiguration(configName, {}, {}, -1);
}

TestCaseMessageReceiverConfiguration* TestSuiteJsonConfigParser::createTestReceiverConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		int message_count{ -1 };
		std::string message_file;
		std::string destination_type;
		std::string destination_address;

		if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			message_count = tmp_message_count->as_int64();

		if (auto tmp_dest_type = json.as_object().if_contains("dest_type"); tmp_dest_type && tmp_dest_type->is_string())
			destination_type = tmp_dest_type->as_string().c_str();

		if (auto tmp_dest_address = json.as_object().if_contains("address"); tmp_dest_address && tmp_dest_address->is_string())
			destination_address = tmp_dest_address->as_string().c_str();

			return new TestCaseMessageReceiverConfiguration(configName, destination_type, destination_address);

	}
	else
		return new TestCaseMessageReceiverConfiguration(configName, {}, {});
}

CMSExceptionsConfiguration* TestSuiteJsonConfigParser::createTestExceptionConfig(const std::string& configName, const boost::json::value& json) const
{
	if (json.is_object())
	{
		int expected_count{ -1 };

		if (auto tmp_expected_count = json.as_object().if_contains("count"); tmp_expected_count && tmp_expected_count->is_int64())
			expected_count = tmp_expected_count->as_int64();

		return new CMSExceptionsConfiguration(configName, expected_count);

	}
	else
		return new CMSExceptionsConfiguration(configName, 0);
}
