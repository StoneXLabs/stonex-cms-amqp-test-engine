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

#include <sstream>
#include <iterator>
#include <Configuration\ConnectionConfiguration.h>

ConnectionConfiguration::ConnectionConfiguration(const std::string &key, const std::string &broker_address, const std::string &username, const std::string &password, const std::string &id, const std::vector<SessionConfiguration> &sessionConfiguration)
	:DefaultTerminationConfiguration(DefaultTerminationMode::CloseOnDestruction),
	mKey{ key },
	mBrokerUrl{ broker_address },
	mConnUser{ username },
	mConnPassword{ password },
	mConnId{ id },
	mSessions{sessionConfiguration}
{
}

ConnectionConfiguration& ConnectionConfiguration::operator=(const ConnectionConfiguration& other)
{
	mKey = other.mKey;
	mBrokerUrl = other.mBrokerUrl;
	mConnUser = other.mConnUser;
	mConnPassword = other.mConnPassword;
	mConnId = other.mConnId;
	mSessions = other.mSessions;

	return *this;
}

void ConnectionConfiguration::addSession(const SessionConfiguration & params)
{
	mSessions.push_back(params);
}

std::string ConnectionConfiguration::key() const { return mKey; };
std::string ConnectionConfiguration::url() const { return mBrokerUrl; };
std::string ConnectionConfiguration::user() const { return mConnUser; };
std::string ConnectionConfiguration::password() const { return mConnPassword; };
std::string ConnectionConfiguration::id() const { return mConnId; }

const std::vector<SessionConfiguration>& ConnectionConfiguration::sessionConfiguration() const
{
	return mSessions;
}
const SessionConfiguration * ConnectionConfiguration::session(const std::string & name) const
{
	auto session = std::find_if(std::cbegin(mSessions), std::cend(mSessions), [name](const SessionConfiguration& item) {return item.key() == name; });
	if (session != mSessions.end())
		return &(*session);
	else
		return nullptr;
}

std::ostream & operator<<(std::ostream & os, const ConnectionConfiguration & other)
{
	os << "Connection id:" << other.key() << (other.mConnId.empty() ? "" : " connection ID" + other.mConnId);
	os << "\nbroker :" << other.mBrokerUrl;
	os << "\nuser :" << other.mConnUser;
	os << "\npassword :" << other.mConnPassword;
	os << "\nSessions :\n";
	std::copy(std::begin(other.mSessions), std::end(other.mSessions), std::ostream_iterator<SessionConfiguration>(os, "\n"));
	return os;
	// TODO: insert return statement here
}


bool operator==(const ConnectionConfiguration & lhs, const ConnectionConfiguration & rhs)
{
	return lhs.mKey == rhs.mKey &&
		lhs.mBrokerUrl == rhs.mBrokerUrl &&
		lhs.mConnUser == rhs.mConnUser &&
		lhs.mConnPassword == rhs.mConnPassword &&
		lhs.mConnId == rhs.mConnId &&
		lhs.mSessions.size() == rhs.mSessions.size() &&
		std::equal(std::cbegin(lhs.mSessions), std::cend(lhs.mSessions), std::cbegin(rhs.mSessions)) == true;
}