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

std::string to_string(FIELD_TYPE ft)
{
	std::string ft_string;
	switch (ft)
	{
	case FIELD_TYPE::CMS_CORRELATION_ID:
		ft_string = "correlation_id";
		break;
	case FIELD_TYPE::CMS_DELIVERY_MODE:
		ft_string = "delivery_mode";
		break;
	case FIELD_TYPE::CMS_DESTINATION:
		ft_string = "destination";
		break;
	case FIELD_TYPE::CMS_EXPIRATION:
		ft_string = "expiration";
		break;
	case FIELD_TYPE::CMS_MESSAGE_ID:
		ft_string = "message_id";
		break;
	case FIELD_TYPE::CMS_PRIORITY:
		ft_string = "priority";
		break;
	case FIELD_TYPE::CMS_REDELIVERED:
		ft_string = "redelivered";
		break;
	case FIELD_TYPE::CMS_REPLY_TO:
		ft_string = "reply_to";
		break;
	case FIELD_TYPE::CMS_TIMESTAMP:
		ft_string = "timestamp";
		break;
	case FIELD_TYPE::CMS_TYPE:
		ft_string = "type";
		break;
	case FIELD_TYPE::PROPERTY:
		ft_string = "application property";
		break;
	case FIELD_TYPE::BOOLEANPROPERTY:
		ft_string = "application boolean property";
		break;
	case FIELD_TYPE::DOUBLEPROPERTY:
		ft_string = "application double property";
		break;
	case FIELD_TYPE::INTPROPERTY:
		ft_string = "application int property";
		break;
	case FIELD_TYPE::STRINGPROPERTY:
		ft_string = "application string property";
		break;
	default:
		break;
	}

	return ft_string;
}

std::ostream& operator<< (std::ostream &os, const FIELD_TYPE& ob)
{
	switch (ob)
	{
	case FIELD_TYPE::CMS_CORRELATION_ID:
		os << "correlation_id";
		break;
	case FIELD_TYPE::CMS_DELIVERY_MODE:
		os << "delivery_mode";
		break;
	case FIELD_TYPE::CMS_DESTINATION:
		os << "destination";
		break;
	case FIELD_TYPE::CMS_EXPIRATION:
		os << "expiration";
		break;
	case FIELD_TYPE::CMS_MESSAGE_ID:
		os << "message_id";
		break;
	case FIELD_TYPE::CMS_PRIORITY:
		os << "priority";
		break;
	case FIELD_TYPE::CMS_REDELIVERED:
		os << "redelivered";
		break;
	case FIELD_TYPE::CMS_REPLY_TO:
		os << "reply_to";
		break;
	case FIELD_TYPE::CMS_TIMESTAMP:
		os << "timestamp";
		break;
	case FIELD_TYPE::CMS_TYPE:
		os << "type";
		break;
	case FIELD_TYPE::PROPERTY:
		os << "application property";
		break;
	case FIELD_TYPE::BOOLEANPROPERTY:
		os << "application boolean property";
		break;
	case FIELD_TYPE::DOUBLEPROPERTY:
		os << "application double property";
		break;
	case FIELD_TYPE::INTPROPERTY:
		os << "application int property";
		break;
	case FIELD_TYPE::STRINGPROPERTY:
		os << "application string property";
		break;
	default:
		break;
	}	

	return os;
}

