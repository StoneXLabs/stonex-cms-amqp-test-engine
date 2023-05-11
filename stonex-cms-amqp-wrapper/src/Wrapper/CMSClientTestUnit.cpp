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

#include <Wrapper/CMSClientTestUnit.h>
#include <algorithm>
#include <Wrapper/SessionTestUnit.h>

CMSClientTestUnit::CMSClientTestUnit(const std::string userIdentifier)
{
}

CMSClientTestUnit::CMSClientTestUnit(const CMSWrapperConfiguration & config, std::shared_ptr<StonexLogger> logger, const std::string userIdentifier, cms::ExceptionListener* factoryExceptionListener, cms::ExceptionListener* connectionExceptionListener, cms::ExceptionListener* sessionExceptionListener)
{
	std::for_each(std::cbegin(config.config()), std::cend(config.config()), [this, factoryExceptionListener, connectionExceptionListener, sessionExceptionListener, logger](const ConnectionConfiguration& item) {addConnection(&item, logger, factoryExceptionListener, connectionExceptionListener, sessionExceptionListener); });


}

CMSClientTestUnit::~CMSClientTestUnit()
{
//	std::for_each(std::begin(mConnections), std::end(mConnections), [this](const ConnectionTestUnit& item) {});
	mConnections.clear();
}

void CMSClientTestUnit::addConnection(const ConnectionConfiguration* params, std::shared_ptr<StonexLogger> logger, cms::ExceptionListener* factoryExceptionListener, cms::ExceptionListener* connectionExceptionListener, cms::ExceptionListener* sessionExceptionListener)
{
	auto existing_connection = std::find_if(std::begin(mConnections), std::end(mConnections), [params, factoryExceptionListener, connectionExceptionListener, sessionExceptionListener](ConnectionTestUnit& item) {return item.id() == params->key(); });
	if (existing_connection != mConnections.end())
	{
	}
	else
	{
		try
		{
			auto connection = ConnectionTestUnit(*params,logger, factoryExceptionListener, connectionExceptionListener, sessionExceptionListener);
			mConnections.push_back(std::move(connection));

		}
		catch (const std::exception&)
		{

		}

	}
}

void CMSClientTestUnit::startConnection(const std::string& id)
{
	std::for_each(std::begin(mConnections), std::end(mConnections), [id](ConnectionTestUnit& item) { return item.id() == id; });

}

void CMSClientTestUnit::closeConnection(const std::string& id)
{
	std::for_each(std::begin(mConnections), std::end(mConnections), [id](ConnectionTestUnit& item) { return item.id() == id; });

}

void CMSClientTestUnit::startConnections()
{
	std::for_each(std::begin(mConnections), std::end(mConnections), [](ConnectionTestUnit& item) { item.start(); });
}

void CMSClientTestUnit::closeConnections()
{
	std::for_each(std::begin(mConnections), std::end(mConnections), [](ConnectionTestUnit& item) { item.close(); });
}

void CMSClientTestUnit::closeSessions()
{
	std::for_each(std::begin(mConnections), std::end(mConnections), [](ConnectionTestUnit& item) {
		std::for_each(std::begin(item.sessions()), std::end(item.sessions()), [](SessionTestUnit& session_item) {
			session_item.close();
		});
	});
}

std::vector<ConnectionTestUnit>& CMSClientTestUnit::connections()
{
	return mConnections;
}


ConnectionTestUnit* const CMSClientTestUnit::connection(const std::string &id)
{
	ConnectionTestUnit* found{ nullptr };

	auto found_connection = std::find_if(std::begin(mConnections), std::end(mConnections), [&id](const ConnectionTestUnit& item) {
		return item.id() == id;
	});

	if (found_connection != std::end(mConnections))
		found = &*found_connection;

	return found;

}

SessionTestUnit* const CMSClientTestUnit::session(const std::string &connectionId, const std::string &id)
{
	ConnectionTestUnit* foundConnection = connection(connectionId);

	if (foundConnection)
	{
		SessionTestUnit* foundSession = foundConnection->session(id);
		return foundSession;
	}
	else
		return nullptr;
}

ConsumerTestUnit* const CMSClientTestUnit::consumer(const std::string &connectionId, const std::string &sessionId, const std::string &id)
{
	ConnectionTestUnit* foundConnection = connection(connectionId);

	if (foundConnection)
	{
		SessionTestUnit* foundSession = foundConnection->session(id);
		if (foundSession)
		{
			ConsumerTestUnit* foundConsumer = foundSession->consumer(id);
			return foundConsumer;
		}
		else
			return nullptr;
	}
	else
		return nullptr;

}
ProducerTestUnit* const CMSClientTestUnit::producer(const std::string &connectionId, const std::string &sessionId, const std::string &id)
{
	ConnectionTestUnit* foundConnection = connection(connectionId);

	if (foundConnection)
	{
		SessionTestUnit* foundSession = foundConnection->session(sessionId);
		if (foundSession)
		{
			ProducerTestUnit* foundProducer = foundSession->producer(id);
			return foundProducer;
		}
		else
			return nullptr;
	}
	else
		return nullptr;
}