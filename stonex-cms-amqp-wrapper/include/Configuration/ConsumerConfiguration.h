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

#include <Configuration\ClientConfiguration.h>

class ConsumerConfiguration : public ClientConfiguration
{
public:
	ConsumerConfiguration(const std::string& key, const std::string dest_type, const std::string& address, const std::string& termination_method, const std::string& selector, bool durable = false, const std::string& subscription_name = "");

	ConsumerConfiguration& operator=(const ConsumerConfiguration& other);

	std::string selector() const;

	bool durable() const;

	std::string subscriptionName() const;


	friend std::ostream & operator<<(std::ostream & os, const ConsumerConfiguration & other);
	friend bool operator== (const ConsumerConfiguration& lhs, const ConsumerConfiguration& rhs);

private:
	std::string mSelector;
	bool mDurable{ false };
	std::string mDurableSubscriptionName;
};