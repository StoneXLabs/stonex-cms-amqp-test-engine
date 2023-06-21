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

#include <sstream>
#include <MessageContentVerifiers/ExpectedField.h>

std::ostream& operator<<(std::ostream& os, const FIELD_TYPE& ft)
{

	{
		switch (ft)
		{
		case FIELD_TYPE::PROPERTY:
			os << "property";
			break;
		case FIELD_TYPE::HEADER:
			os << "header";
			break;
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
			os << "timestap";
			break;
		case FIELD_TYPE::CMS_TYPE:
			os << "type";
			break;
		case FIELD_TYPE::UNKNOWN:
			os << "unknown";
			break;
		}

		return os;
	}
}

std::string fieldTypeToString(const FIELD_TYPE& ft)
{
	std::stringstream os;
	os << ft;
	return os.str();
}