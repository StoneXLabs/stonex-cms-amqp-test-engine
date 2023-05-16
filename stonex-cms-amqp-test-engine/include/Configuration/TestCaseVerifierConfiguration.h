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
#include <Configuration/MessageReceiverConfiguration.h>
#include <Configuration/ExceptionsConfiguration.h>

class TestCaseVerifierConfiguration
{
public:
	TestCaseVerifierConfiguration(const std::vector<MessageReceiverConfiguration*>& receivers_config, const std::vector<ExceptionsConfiguration*>& exceptions_config);
	const std::vector<MessageReceiverConfiguration*>& messageExpectations() const;
	const std::vector<ExceptionsConfiguration*>& exceptionsExpectations() const;

	TestCaseVerifierConfiguration& operator=(const TestCaseVerifierConfiguration& other);
	friend bool operator==(const TestCaseVerifierConfiguration & lhs, const TestCaseVerifierConfiguration & rhs);
private:
	std::vector<MessageReceiverConfiguration*> mReceiversConfig;
	std::vector<ExceptionsConfiguration*> mExceptionsConfig;

	
};

