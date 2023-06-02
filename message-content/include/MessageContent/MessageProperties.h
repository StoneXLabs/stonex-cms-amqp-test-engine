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

#pragma once

#include <boost/json/value.hpp>

enum class FIELD_TYPE
{
	PROPERTY,
	BOOLEANPROPERTY,
	BYTEPROPERTY,
	DOUBLEPROPERTY,
	FLOATPROPERTY,
	INTPROPERTY,
	LONGPROPERTY,
	SHORTPROPERTY,
	STRINGPROPERTY,
	HEADER,
	CMS_CORRELATION_ID,
	CMS_DELIVERY_MODE,
	CMS_DESTINATION,
	CMS_EXPIRATION,
	CMS_MESSAGE_ID,
	CMS_PRIORITY,
	CMS_REDELIVERED,
	CMS_REPLY_TO,
	CMS_TIMESTAMP,
	CMS_TYPE,
	CMS_QUEUE,
	CMS_TEMPORARY_QUEUE,
	CMS_TOPIC,
	CMS_TEMPORARY_TOPIC,
	UNKNOWN
};

FIELD_TYPE from_boost_value_kind(const boost::json::kind& kind);
const std::string values_string(const boost::json::value &val);
FIELD_TYPE fromString(const std::string field_string);
FIELD_TYPE fromKeyValue(const std::string key, const boost::json::value &val);

std::string to_string(FIELD_TYPE ft);

std::ostream& operator<< (std::ostream &os, const FIELD_TYPE& ob);
