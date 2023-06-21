/*
 * Copyright 2023 StoneX Financial Ltd.
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

#include <iostream>
#include <ConfigurationParser/WrapperConfigurationParser.h>


WrapperConfiguration WrapperConfigurationParser::createWrapperConfiguration(const boost::json::value & json) const
{

	if (json.is_object())
	{
		if (auto config_obj = json.as_object().if_contains("cms_configuration"); config_obj != nullptr && config_obj->is_object())
		{
			std::vector<ConnectionConfiguration> configuration;

			std::transform(std::begin(config_obj->as_object()), std::end(config_obj->as_object()), std::back_inserter(configuration), [this](const boost::json::object::value_type& item) {
				return createConnectionConfig(item.key_c_str(), item.value());
			});

			return WrapperConfiguration(configuration);
		}
	}
	return WrapperConfiguration();
}

ConnectionConfiguration WrapperConfigurationParser::createConnectionConfig(const std::string& configName, const boost::json::value & json) const
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

			return ConnectionConfiguration(configName, url, user, password, id, sessionConfiguration);
		}
	}
	catch (const std::exception& ex)
	{
	}
}

SessionConfiguration WrapperConfigurationParser::createSessionConfig(const std::string& configName, const boost::json::value & json) const
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

ConsumerConfiguration WrapperConfigurationParser::createConsumerConfig(const std::string& configName, const boost::json::value & json) const
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

	return ConsumerConfiguration( configName,dest_type,address,terminate_method,selector,durable,durable_subscription_name );
}

ProducerConfiguration WrapperConfigurationParser::createProducerConfig(const std::string& configName, const boost::json::value & json) const
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

	return ProducerConfiguration(configName,dest_type,address);
}