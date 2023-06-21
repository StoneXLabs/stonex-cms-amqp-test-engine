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
                                                                                                                                                                                  
#include <functional>
#include <boost/json.hpp>
#include <ostream>
#include <chrono>
#include <cms/Destination.h>
#include <cms/CMSException.h>
#include <MessageContent/MessageProperties.h>


std::ostream& operator<<(std::ostream& os, const FIELD_TYPE& ft);
std::string fieldTypeToString(const FIELD_TYPE& ft);

class IExpectedField
{
public:
	virtual FIELD_TYPE expectedField() const = 0;
	virtual ~IExpectedField() = default;
	virtual bool reportStatus() const = 0;
	virtual std::string fieldName() const = 0;
};

template<class T>
class ExpectedField : public IExpectedField
{
public:
	ExpectedField(FIELD_TYPE field_type, bool check_existance, bool check_value, T value = T(), const std::string& msg_property = "")
		:mVerifiedField{ field_type },
		mCheckIfExists{ check_existance },
		mCheckValue{ check_value },
		mExpectedValue{ value },
		mMsgProperty{ msg_property }
	{

	}

	void setExpectedValue(const T& value)
	{
		mExpectedValue = value;
	}

	T getExpectedValue() const
	{
		return mExpectedValue;
	}

	std::string fieldName() const override { return mMsgProperty; }

	FIELD_TYPE expectedField() const override { return mVerifiedField; }

	bool reportStatus() const override { return mLossCount == 0; }


	

private:
	FIELD_TYPE mVerifiedField;
	bool mCheckIfExists;
	bool mCheckValue;
	T mExpectedValue;
	std::string mMsgProperty;
	int mLossCount{ 0 };
};

template<>
class ExpectedField<const cms::Destination*> : public IExpectedField
{
public:
	ExpectedField(FIELD_TYPE field_type, bool check_existance, bool check_value, const cms::Destination* value = nullptr, const std::string& msg_property = "")
		:mVerifiedField{ field_type },
		mCheckIfExists{ check_existance },
		mCheckValue{ check_value },
		mExpectedValue{ value },
		mMsgProperty{ msg_property }
	{
		if (!value)
			throw cms::CMSException("ExpectedField cms::Destination not initialized ");

	}

	void setExpectedValue(const cms::Destination*& value)
	{
		mExpectedValue = value;
	}

	const cms::Destination* getExpectedValue() const
	{
		return mExpectedValue;
	}

	std::string fieldName() const override { return mMsgProperty; }

	FIELD_TYPE expectedField() const override { return mVerifiedField; }

	bool reportStatus() const override { return mLossCount == 0; }




private:
	FIELD_TYPE mVerifiedField;
	bool mCheckIfExists;
	bool mCheckValue;
	const cms::Destination* mExpectedValue;
	std::string mMsgProperty;
	int mLossCount{ 0 };
};
