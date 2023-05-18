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
#include <ConfigurationParser/TestCaseReceiverConfigurationParser.h>
#include <Configuration/FileMessageReceiverConfiguration.h>
#include <Configuration/MessageCountingReceiverConfiguration.h>
#include <Configuration/FileMessageCountingReceiverConfiguration.h>
#include <Configuration/MessageDecoratingReceiverConfiguration.h>
#include <Configuration/FileMessageDecoratingReceiverConfiguration.h>
#include <Configuration/MessageCountingDecoratingReceiverConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingReceiverConfiguration.h>

MessageReceiverConfiguration * TestCaseReceiverConfigurationParser::createTestCaseReceiverConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		if (json.as_object().size() < 2)
			return nullptr;

		std::string session;
		std::string connection;



		if (auto connection_id = json.as_object().if_contains("connection"); connection_id && connection_id->is_string())
			connection = connection_id->as_string().c_str();
		else
			return nullptr;

		if (auto session_id = json.as_object().if_contains("session"); session_id && session_id->is_string())
			session = session_id->as_string().c_str();
		else
			return nullptr;

		if (json.as_object().size() == 2)
		{
								
			return new MessageReceiverConfiguration(connection, session, configName);
		} 
		else if (json.as_object().size() == 3)
		{

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string()) {

				std::string message_file;
				message_file = tmp_message_file->as_string().c_str();
				return new FileMessageReceiverConfiguration(connection, session, configName, message_file);
			}
			else if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			{
				int message_count{ 0 };
				message_count = tmp_message_count->as_int64();
				return new MessageCountingReceiverConfiguration(connection, session, configName, message_count);
			}
			else if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
			{
				auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
				return new MessageDecoratingReceiverConfiguration(connection, session, configName, decorator_configuration.decorations());
			}
			else
				return nullptr;

		}
		else if (json.as_object().size() == 4)
		{
			

			if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string())
			{
				std::string message_file = tmp_message_file->as_string().c_str();

				if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
				{
					int message_count = tmp_message_count->as_int64();
					return new FileMessageCountingReceiverConfiguration(connection, session, configName, message_file, message_count);
				}
				else if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
				{
					auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
					return new FileMessageDecoratingReceiverConfiguration(connection, session, configName, message_file, decorator_configuration.decorations());

				}
			}
			else if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			{
				int message_count = tmp_message_count->as_int64();

				if (auto tmp_message_properties = json.as_object().if_contains("properties"); tmp_message_properties && tmp_message_properties->is_object())
				{
					auto decorator_configuration = createMessgeDecoratorConfiguration("properties", *tmp_message_properties);
					return new MessageCountingDecoratingReceiverConfiguration(connection, session, configName, message_count, decorator_configuration.decorations());
				}
			}
			else
				return nullptr;
			}
			else if (json.as_object().size() == 5)
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
					return new FileMessageCountingDecoratingReceiverConfiguration(connection, session, configName, message_file, message_count, decorator_configuration.decorations());
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