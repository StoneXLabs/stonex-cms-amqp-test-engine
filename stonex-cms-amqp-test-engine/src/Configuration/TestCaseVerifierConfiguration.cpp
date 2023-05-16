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

#include "Configuration/TestCaseVerifierConfiguration.h"
#include <algorithm>

TestCaseVerifierConfiguration::TestCaseVerifierConfiguration(const std::vector<MessageReceiverConfiguration*>& receivers_config, const std::vector<ExceptionsConfiguration*>& exceptions_config)
	:mReceiversConfig{ receivers_config },
	mExceptionsConfig{ exceptions_config }
{
}

const std::vector<MessageReceiverConfiguration*>& TestCaseVerifierConfiguration::messageExpectations() const
{
	return mReceiversConfig;
}

const std::vector<ExceptionsConfiguration*>& TestCaseVerifierConfiguration::exceptionsExpectations() const
{
	return mExceptionsConfig;
}

TestCaseVerifierConfiguration & TestCaseVerifierConfiguration::operator=(const TestCaseVerifierConfiguration & other)
{
	std::transform(std::cbegin(other.mReceiversConfig), std::cend(other.mReceiversConfig), std::back_inserter(mReceiversConfig), [](const MessageReceiverConfiguration* item) {return new MessageReceiverConfiguration(*item); });
	std::transform(std::cbegin(other.mExceptionsConfig), std::cend(other.mExceptionsConfig), std::back_inserter(mExceptionsConfig), [](const ExceptionsConfiguration* item) {return new ExceptionsConfiguration(*item); });
	
	return *this;
}

bool operator==(const TestCaseVerifierConfiguration & lhs, const TestCaseVerifierConfiguration & rhs)
{

	return std::equal(std::cbegin(lhs.mReceiversConfig), std::cend(lhs.mReceiversConfig), std::cbegin(rhs.mReceiversConfig), std::cend(rhs.mReceiversConfig), [](const MessageReceiverConfiguration* lhs, MessageReceiverConfiguration* rhs) { return *lhs == *rhs; }) == true &&
		std::equal(std::cbegin(lhs.mExceptionsConfig), std::cend(lhs.mExceptionsConfig), std::cbegin(rhs.mExceptionsConfig), std::cend(rhs.mExceptionsConfig), [](const ExceptionsConfiguration* lhs, ExceptionsConfiguration* rhs) { return *lhs == *rhs; }) == true;
}