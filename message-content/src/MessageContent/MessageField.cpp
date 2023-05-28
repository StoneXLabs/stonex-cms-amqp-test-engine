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

#include <MessageContent/MessageField.h>

MessageField::MessageField(FIELD_TYPE ft, const std::string & name, const std::string & valueString)
	:mFieldType{ ft },
	mName{ name },
	mValueString{ valueString }
{
}

MessageField::MessageField(const MessageField& other)
	:mFieldType{other.mFieldType},
	mName{other.mName},
	mValueString{other.mValueString}
{
}

MessageField::MessageField(MessageField&& other)
	:mFieldType{ std::move(other.mFieldType) },
	mName{ std::move(other.mName) },
	mValueString{ std::move(other.mValueString) }
{
}


FIELD_TYPE MessageField::type() const
{
	return mFieldType;
}

std::string MessageField::name() const
{
	return mName;
}

std::string MessageField::valueString() const
{
	return mValueString; 
}