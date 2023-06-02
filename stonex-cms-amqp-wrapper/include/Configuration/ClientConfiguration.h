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
#include <iostream>
#include <Configuration/DefaultTerminationType.h>


enum class ClientType {
	CONSUMER,
	PRODUCER
};

std::ostream & operator<<(std::ostream & os, const ClientType & other);

enum class DestinationType {
	ANONYMOUS,
	QUEUE,
	TOPIC,
	TEMPORARY_QUEUE,
	TEMPORARY_TOPIC
};

std::ostream & operator<<(std::ostream & os, const DestinationType & other);


class ClientConfiguration : public DefaultTerminationConfiguration
{
public:
	ClientConfiguration(const std::string& key, const std::string& client_type, const std::string dest_type, const std::string& address, const std::string& termination_method);
	ClientConfiguration(const std::string& key, const std::string& client_type, const std::string dest_type, const std::string& address, DefaultTerminationMode termination_method);

	ClientConfiguration& operator=(const ClientConfiguration& other);

	 std::string key() const;
	 ClientType type() const;
	 DestinationType destType() const;
	 std::string address() const;

	 friend std::ostream& operator<<(std::ostream& os, const ClientConfiguration& other);
private:
	std::string mKey;
	ClientType mClientType{ ClientType::CONSUMER };
	DestinationType mDestType{ DestinationType::ANONYMOUS };
	std::string mAddress;


};
