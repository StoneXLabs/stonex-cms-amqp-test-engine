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

#include <MessageContent/MessageTestField.h>

MessageTestField::MessageTestField(FIELD_TYPE ft, const std::string & name, const std::string & valueString)
	:mFieldType{ ft },
	mName{ name },
	mValueString{ valueString }
{
}

MessageTestField::MessageTestField(const MessageTestField& other)
	:mFieldType{other.mFieldType},
	mName{other.mName},
	mValueString{other.mValueString}
{
}

MessageTestField::MessageTestField(MessageTestField&& other)
	:mFieldType{ std::move(other.mFieldType) },
	mName{ std::move(other.mName) },
	mValueString{ std::move(other.mValueString) }
{
}


FIELD_TYPE MessageTestField::type() const 
{
	return mFieldType;
}

std::string MessageTestField::name() const 
{
	return mName;
}

std::string MessageTestField::valueString() const 
{
	return mValueString; 
}

bool operator==(const MessageTestField & lhs, const MessageTestField & rhs)
{
	if (lhs.mName == rhs.mName &&
		lhs.mFieldType == rhs.mFieldType)
	{
		switch (lhs.mFieldType)
		{
		case FIELD_TYPE::BOOLEANPROPERTY:
			return  std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::BYTEPROPERTY:
			return lhs.mValueString == rhs.mValueString;
			break;
		case FIELD_TYPE::DOUBLEPROPERTY:
			return std::stod(lhs.mValueString.c_str()) == std::stod(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::FLOATPROPERTY:
			return std::stof(lhs.mValueString.c_str()) == std::stof(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::INTPROPERTY:
			return std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::LONGPROPERTY:
			return std::stod(lhs.mValueString.c_str()) == std::stod(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::SHORTPROPERTY:
			return std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::STRINGPROPERTY:
			return lhs.mValueString == rhs.mValueString;
			break;
		default:
			return false;
			break;
		}
	}
	else
		return false;
}
