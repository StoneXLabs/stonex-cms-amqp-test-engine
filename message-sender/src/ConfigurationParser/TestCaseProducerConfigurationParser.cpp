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

#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>
#include <Configuration/FileMessageSenderConfiguration.h>
#include <Configuration/MessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageCountingSenderConfiguration.h>
#include <Configuration/MessageDecoratingSenderConfiguration.h>
#include <Configuration/FileMessageDecoratingSenderConfiguration.h>
#include <Configuration/MessageCountingDecoratingSenderConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h>

MessageSenderConfiguration * TestCaseProducerConfigurationParser::createTestCaseProducerConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		if (json.as_object().size() < 4)
			return nullptr;

		std::string message_factory;
		std::string session_factory;
		std::string message_type;
		std::string sender_type;



		if (auto session_factory_id = json.as_object().if_contains("session_factory"); session_factory_id && session_factory_id->is_string())
			session_factory = session_factory_id->as_string().c_str();
		else
			return nullptr;

		if (auto message_factory_id = json.as_object().if_contains("message_factory"); message_factory_id && message_factory_id->is_string())
			message_factory = message_factory_id->as_string().c_str();
		else
			return nullptr;

		if (auto message_type_id = json.as_object().if_contains("message_type"); message_type_id && message_type_id->is_string())
			message_type = message_type_id->as_string().c_str();
		else
			return nullptr;

		if (auto sender_type_id = json.as_object().if_contains("sender_type"); sender_type_id && sender_type_id->is_string())
			sender_type = sender_type_id->as_string().c_str();
		else
			return nullptr;

		if (json.as_object().size() == 4)
		{
								
			return new MessageSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type);
		} 
		else if (json.as_object().size() == 5)
		{

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string()) {

				std::string message_file;
				message_file = tmp_message_file->as_string().c_str();
				return new FileMessageSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type, message_file);
			}
			else if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			{
				int message_count{ 0 };
				message_count = tmp_message_count->as_int64();
				return new MessageCountingSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type, message_count);
			}
			else if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
			{
				auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
				return new MessageDecoratingSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type, decorator_configuration.decorations());
			}
			else
				return nullptr;

		}
		else if (json.as_object().size() == 6)
		{
			

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string())
			{
				std::string message_file = tmp_message_file->as_string().c_str();

				if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
				{
					int message_count = tmp_message_count->as_int64();
					return new FileMessageCountingSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type, message_file, message_count);
				}
				else if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
				{
					auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
					return new FileMessageDecoratingSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type, message_file, decorator_configuration.decorations());

				}
			}
			else if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			{
				int message_count = tmp_message_count->as_int64();

				if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
				{
					auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
					return new MessageCountingDecoratingSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type, message_count, decorator_configuration.decorations());
				}
			}
			else
				return nullptr;
			}
			else if (json.as_object().size() == 7)
			{
				std::string message_file;
				int message_count{ 0 };

				if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string())
					message_file = tmp_message_file->as_string().c_str();
				else
					return nullptr;

				if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
					message_count = tmp_message_count->as_int64();
				else
					return nullptr;

				if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
				{
					auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
					return new FileMessageCountingDecoratingSenderConfiguration(session_factory, message_factory, configName, message_type, sender_type, message_file, message_count, decorator_configuration.decorations());
				}
				else
					return nullptr;
			}
			else
				return nullptr;
	}
	else
		return nullptr;
}


