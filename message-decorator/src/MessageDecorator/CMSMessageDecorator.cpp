#include "..\..\include\MessageDecorator\CMSMessageDecorator.h"
#include "..\..\include\MessageDecorator\CMSMessageDecorator.h"
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

#include <MessageDecorator/CMSMessageDecorator.h>

CMSMessageDecorator::CMSMessageDecorator(const MessageField& messageField)
	:MessageField(messageField)
{
}

CMSMessageDecorator::CMSMessageDecorator(const CMSMessageDecorator& other)
	: MessageField(other),
	mNext{ other.mNext }
{
}

CMSMessageDecorator::CMSMessageDecorator(CMSMessageDecorator&& other)
	: MessageField(other),
	mNext{ other.mNext }
{
	other.mNext = nullptr;
}

void CMSMessageDecorator::decorate(cms::Message * mes, cms::Session * sess) const
{
	if (mNext)
		mNext->decorate(mes, sess);
}

void CMSMessageDecorator::addNext(CMSMessageDecorator * next)
{
	if (!mNext)
		mNext = next;
	else
		mNext->addNext(next);
}

bool operator==(const CMSMessageDecorator & lhs, const CMSMessageDecorator & rhs)
{
	bool equal{ false };
	if (lhs.mName == rhs.mName &&
		lhs.mFieldType == rhs.mFieldType)
	{
		switch (lhs.mFieldType)
		{
		case FIELD_TYPE::BOOLEANPROPERTY:
			equal =  std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::BYTEPROPERTY:
			equal = lhs.mValueString == rhs.mValueString;
			break;
		case FIELD_TYPE::DOUBLEPROPERTY:
			equal = std::stod(lhs.mValueString.c_str()) == std::stod(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::FLOATPROPERTY:
			equal = std::stof(lhs.mValueString.c_str()) == std::stof(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::INTPROPERTY:
			equal = std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::LONGPROPERTY:
			equal = std::stod(lhs.mValueString.c_str()) == std::stod(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::SHORTPROPERTY:
			equal = std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::STRINGPROPERTY:
			equal = lhs.mValueString == rhs.mValueString;
			break;
		default:
			return false;
			break;
		}

		if (equal)
		{
			if (lhs.mNext == nullptr && rhs.mNext == nullptr)
				return true;
			else if (lhs.mNext == nullptr || rhs.mNext == nullptr)
				return false;
			else {
				return *lhs.mNext == *rhs.mNext;
			}
		}
		else
			return false;
	}
	else
		return false;
}
