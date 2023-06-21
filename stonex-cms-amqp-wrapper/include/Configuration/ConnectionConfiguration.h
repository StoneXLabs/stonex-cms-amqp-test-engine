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

#include <string>
#include <algorithm>
#include <vector>
#include <Configuration\SessionConfiguration.h>
#include <Configuration/DefaultTerminationType.h>

class ConnectionConfiguration : public DefaultTerminationConfiguration
{
public:
	ConnectionConfiguration(const std::string &key, const std::string &broker_address, const std::string &username, const std::string &password, const std::string &id, const std::vector<SessionConfiguration> &sessionConfiguration = {});

	ConnectionConfiguration& operator=(const ConnectionConfiguration& other);

public:
	void addSession(const SessionConfiguration& params);
	std::string key() const;
	std::string url() const;
	std::string user() const;
	std::string password() const;
	std::string id() const;
	const std::vector<SessionConfiguration>& sessionConfiguration() const;

	const SessionConfiguration* session(const std::string& name) const;

	friend std::ostream & operator<<(std::ostream & os, const ConnectionConfiguration & other);
	friend bool operator== (const ConnectionConfiguration& lhs, const ConnectionConfiguration& rhs);

private:
	std::string mKey{};
	std::string mBrokerUrl{};
	std::string mConnUser{};
	std::string mConnPassword{};
	std::string mConnId{};
	std::vector<SessionConfiguration> mSessions;
};
