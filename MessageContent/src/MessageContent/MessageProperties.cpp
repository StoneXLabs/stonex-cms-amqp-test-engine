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

#include <MessageContent/MessageProperties.h>


FIELD_TYPE from_boost_value_kind(const boost::json::kind& kind) {
	switch (kind)
	{
	case boost::json::kind::bool_:
		return FIELD_TYPE::BOOLEANPROPERTY;
		break;
	case boost::json::kind::double_:
		return FIELD_TYPE::DOUBLEPROPERTY;
		break;
	case boost::json::kind::int64:
		return FIELD_TYPE::INTPROPERTY;
		break;
	case boost::json::kind::string:
		return FIELD_TYPE::STRINGPROPERTY;
		break;
	case boost::json::kind::uint64:
		return FIELD_TYPE::INTPROPERTY;
		break;
	default:
		return FIELD_TYPE::UNKNOWN;
		break;
	}
}

const std::string values_string(const boost::json::value &val)
{

	switch (val.kind())
	{
	case boost::json::kind::bool_:
		return val.as_bool() == true ? "true" : "false";
		break;
	case boost::json::kind::double_:
		return std::to_string(val.as_double());
		break;
	case boost::json::kind::int64:
		return std::to_string(val.as_int64());
		break;
	case boost::json::kind::string:
		return val.as_string().c_str();
		break;
	case boost::json::kind::uint64:
		return std::to_string(val.as_uint64());
		break;
	case boost::json::kind::object:
		return "JSON_OBJECT";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

FIELD_TYPE fromString(const std::string field_string)
{
	FIELD_TYPE type{ FIELD_TYPE::UNKNOWN };

	if (field_string == "correlation_id")
	{
		type = FIELD_TYPE::CMS_CORRELATION_ID;
	}
	else if (field_string == "delivery_mode")
	{
		type = FIELD_TYPE::CMS_DELIVERY_MODE;
	}
	else if (field_string == "destination")
	{
		type = FIELD_TYPE::CMS_DESTINATION;
	}
	else if (field_string == "expiration")
	{
		type = FIELD_TYPE::CMS_EXPIRATION;
	}
	else if (field_string == "message_id")
	{
		type = FIELD_TYPE::CMS_MESSAGE_ID;
	}
	else if (field_string == "priority")
	{
		type = FIELD_TYPE::CMS_PRIORITY;
	}
	else if (field_string == "redelivered")
	{
		type = FIELD_TYPE::CMS_REDELIVERED;
	}
	else if (field_string == "reply_to")
	{
		type = FIELD_TYPE::CMS_REPLY_TO;
	}
	else if (field_string == "timestamp")
	{
		type = FIELD_TYPE::CMS_TIMESTAMP;
	}
	else if (field_string == "type")
	{
		type = FIELD_TYPE::CMS_TYPE;
	}
	else
		type = FIELD_TYPE::PROPERTY;

	return type;
}


FIELD_TYPE fromKeyValue(const std::string key, const boost::json::value &val)
{
	if (auto fieldType = fromString(key); fieldType == FIELD_TYPE::PROPERTY)
		return from_boost_value_kind(val.kind());
	else
		return fieldType;
}
