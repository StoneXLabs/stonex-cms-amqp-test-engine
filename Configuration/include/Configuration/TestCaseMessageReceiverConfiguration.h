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
#include <string>
#include <vector>


class TestCaseMessageReceiverConfiguration
{
public:
	TestCaseMessageReceiverConfiguration(const std::string consumerId, const std::string& destination_type, const std::string& destination_address);
	virtual ~TestCaseMessageReceiverConfiguration() = default;
	const std::string consumerId() const;
	const std::string destinationType() const;
	const std::string destinationAddress() const;

private:
	const std::string mConsumerId;
	const std::string mDestinationType;
	const std::string mDestinationAddress;

};

