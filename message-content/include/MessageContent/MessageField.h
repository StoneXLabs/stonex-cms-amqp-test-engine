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

#pragma once

#include "MessageProperties.h"

class MessageField
{
public:
	MessageField(FIELD_TYPE ft, const std::string& name, const std::string& valueString);
	MessageField(const MessageField& other);
	MessageField(MessageField&& other);

	MessageField& operator =(const MessageField& other) = delete;
	MessageField& operator =(MessageField&& other) = delete;
	friend bool operator== (const MessageField& lhs, const MessageField& rhs);

public:
	FIELD_TYPE type() const;
	virtual std::string name() const;
	virtual std::string valueString() const;

protected:
	FIELD_TYPE mFieldType{ FIELD_TYPE::UNKNOWN };
	const std::string mValueString{};
	const std::string mName{};
};