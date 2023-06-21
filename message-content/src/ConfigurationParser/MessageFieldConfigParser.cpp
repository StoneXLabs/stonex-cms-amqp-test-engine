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

#include <ConfigurationParser/MessageFieldConfigParser.h>
#include <MessageContent/MessageProperties.h>
#include <MessageContent/MessageDestinationTestField.h>

MessageField * MessageFieldConfigParser::createMessageFieldConfig(const std::string & configName, const boost::json::value & json) const
{

	{
		if (configName == "reply_to")
		{
			if (json.is_object())
			{
				auto dest = json.as_object();
				auto type = dest.at("dest_type").as_string().c_str();
				auto address = dest.at("address").as_string().c_str();
				return new MessageDestinationTestField(FIELD_TYPE::CMS_REPLY_TO, type, address);
			}
		}
		else if (configName == "destination")
		{
			if (json.is_object())
			{
				auto dest = json.as_object();
				auto type = dest.at("dest_type").as_string().c_str();
				auto address = dest.at("address").as_string().c_str();
				return new MessageDestinationTestField(FIELD_TYPE::CMS_DESTINATION, type, address);
			}
		}
		else
		{
			return new MessageField(fromKeyValue(configName, json), configName, values_string(json));
		}


		return nullptr;
	}
}
