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

#include <MessageContent/MessageDestinationTestField.h>

MessageDestinationTestField::MessageDestinationTestField(FIELD_TYPE ft, const std::string & dest_type, const std::string & dest_address)
	:MessageField(ft, {}, { dest_address })
{
	if (dest_type == "queue")
		mDestType = FIELD_TYPE::CMS_QUEUE;
	else if (dest_type == "temporary-queue")
		mDestType = FIELD_TYPE::CMS_TEMPORARY_QUEUE;
	else if (dest_type == "topic")
		mDestType = FIELD_TYPE::CMS_TOPIC;
	else if (dest_type == "temporary-topic")
		mDestType = FIELD_TYPE::CMS_TEMPORARY_TOPIC;
}

std::string MessageDestinationTestField::name() const
{
	std::string _name;
		switch (mDestType)
		{
		case FIELD_TYPE::CMS_QUEUE:
			_name = "queue";
			break;
		case FIELD_TYPE::CMS_TEMPORARY_QUEUE:
			_name = "temporary-queue";
			break;
		case FIELD_TYPE::CMS_TOPIC:
			_name = "topic";
			break;
		case FIELD_TYPE::CMS_TEMPORARY_TOPIC:
			_name = "temporary-topic";
			break;
		}
	return _name;
}


FIELD_TYPE MessageDestinationTestField::destType() const
{
	return mDestType;
}

std::string MessageDestinationTestField::destAddress() const
{
	return mAddress;
}

bool operator==(const MessageDestinationTestField & lhs, const MessageDestinationTestField & rhs)
{
	return lhs.mName == rhs.mName &&
		lhs.mFieldType == rhs.mFieldType &&
		lhs.mValueString == rhs.mValueString &&
		lhs.mDestType == rhs.mDestType &&
		lhs.mAddress == rhs.mAddress;
}
