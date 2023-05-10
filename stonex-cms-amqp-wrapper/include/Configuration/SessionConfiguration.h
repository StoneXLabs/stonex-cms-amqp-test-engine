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
#include <Configuration\ConsumerConfiguration.h>
#include <Configuration\ProducerConfiguration.h>

#include <Configuration/DefaultTerminationType.h>

class SessionConfiguration : public DefaultTerminationConfiguration
{
public:
	SessionConfiguration(const std::string key, bool autoAck = false, bool transacted = false,const std::vector<ConsumerConfiguration>& consumerConfiguration = {}, const std::vector<ProducerConfiguration>& producerConfiguration = {});

	SessionConfiguration& operator=(const SessionConfiguration& other);
	friend bool operator== (const SessionConfiguration& lhs, const SessionConfiguration& rhs);
	friend std::ostream & operator<<(std::ostream & os, const SessionConfiguration & other);
	
	std::string key() const;
	bool autoAck() const;
	bool isTransacted() const;
	const std::vector<ConsumerConfiguration>& consumerConfiguration() const;
	const std::vector<ProducerConfiguration>& producerConfiguration() const;
	void addClientConfiguration(const ConsumerConfiguration& params);
	void addClientConfiguration(const ProducerConfiguration& params);
private:
	std::string mKey{};
	bool mAutoAck{ true };
	bool mTransacted{ false };
	std::vector<ConsumerConfiguration> mConsumers;
	std::vector<ProducerConfiguration> mProducers;

};