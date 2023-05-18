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

#include <algorithm>
#include <Wrapper/ConnectionTestUnit.h>
#include <API/CMSConnectionFactory.h>

ConnectionTestUnit::ConnectionTestUnit(const ConnectionConfiguration& params, std::shared_ptr<StonexLogger> logger, cms::ExceptionListener* factoryExceptionListener, cms::ExceptionListener* connectionExceptionListener, cms::ExceptionListener* sessionExceptionListener)
	:CMSExceptionListenerTestUnit(params.key()),
	mConnectionExceptionListener{connectionExceptionListener},
	mId{params.key()}
{
	if (!params.user().empty() && !params.password().empty())
	{

		auto factory = cms::amqp::CMSConnectionFactory::createCMSConnectionFactory(params.url());
		
		if (auto log_source = dynamic_cast<StonexLogSource*>(factory); log_source != nullptr && logger != nullptr)
			logger->attach("connection factory", log_source);
		
			


		if (factoryExceptionListener)
		{
			attachListener(factoryExceptionListener);
			factory->setExceptionListener(this);
		}
			

			if (params.id().empty())
				mConnection = factory->createConnection(params.user(), params.password());
			else
				mConnection = factory->createConnection(params.user(), params.password(), params.id());

			delete factory;

			if (mConnection) {

				if (auto log_source = dynamic_cast<StonexLogSource*>(mConnection); log_source != nullptr && logger != nullptr)
					logger->attach("connection", log_source);

				mConnection->setExceptionListener(this);
			}

			if (mConnectionExceptionListener)
				attachListener(mConnectionExceptionListener);
			

			std::transform(std::cbegin(params.sessionConfiguration()), std::cend(params.sessionConfiguration()), std::back_inserter(mSessions), [this, sessionExceptionListener,logger](const SessionConfiguration& item) {
				try
				{
					return SessionTestUnit(&item, logger, mConnection, sessionExceptionListener);
				}
				catch (const std::exception& ex)
				{
					if (mConnectionExceptionListener)
						mConnectionExceptionListener->onException(cms::CMSException(ex.what()));
				}
			});





	

//		std::for_each(std::begin(mSessions), std::end(mSessions), [this](SessionTestUnit* item) {concatenateExceptions(item); });

		
	}
}

ConnectionTestUnit::ConnectionTestUnit(ConnectionTestUnit&& other)
	:CMSExceptionListenerTestUnit(other),
	mId{other.mId},
	mSessions{std::move(other.mSessions)},
	mConnection{other.mConnection},
	mConnectionExceptionListener{other.mConnectionExceptionListener},
	mFactoryExceptionListener{other.mFactoryExceptionListener}
{
	other.mConnection = nullptr;
	other.mConnectionExceptionListener = nullptr;
	other.mFactoryExceptionListener = nullptr;
}

ConnectionTestUnit::~ConnectionTestUnit()
{
	mSessions.clear();
	if(mConnection)
		mConnection->close();
	delete mConnection;
	mConnectionExceptionListener = nullptr;
	mFactoryExceptionListener = nullptr;
}

std::vector<SessionTestUnit>& ConnectionTestUnit::sessions()
{
	return mSessions;
}

std::string ConnectionTestUnit::id() const
{
	return mId;
}

void ConnectionTestUnit::close()
{
	if (mConnection)
		mConnection->close();
}

void ConnectionTestUnit::start()
{
	if (mConnection)
		mConnection->start();
}

void ConnectionTestUnit::stop()
{
	if (mConnection)
		mConnection->stop();
}

const cms::ConnectionMetaData * ConnectionTestUnit::getMetaData() const
{
	if (mConnection)
		return mConnection->getMetaData();
}

cms::Session * ConnectionTestUnit::createSession()
{
	if (mConnection)
		return mConnection->createSession();
	else
		return nullptr;
}

cms::Session * ConnectionTestUnit::createSession(cms::Session::AcknowledgeMode ackMode)
{
	if (mConnection)
		return mConnection->createSession(ackMode);
	else
		return nullptr;
}

std::string ConnectionTestUnit::getClientID() const
{
	if (mConnection)
		return mConnection->getClientID();
	else
		return "";
}

void ConnectionTestUnit::setClientID(const std::string & clientID)
{
	if (mConnection)
		mConnection->setClientID(clientID);
}

cms::ExceptionListener * ConnectionTestUnit::getExceptionListener() const
{
	if (mConnection)
		return mConnection->getExceptionListener();
	else
		return nullptr;
}

void ConnectionTestUnit::setExceptionListener(cms::ExceptionListener * listener)
{

	attachListener(listener);
	if (mConnection)
		mConnection->setExceptionListener(this);
}

void ConnectionTestUnit::setMessageTransformer(cms::MessageTransformer * transformer)
{
	if (mConnection)
		mConnection->setMessageTransformer(transformer);
}

cms::MessageTransformer * ConnectionTestUnit::getMessageTransformer() const
{
	if (mConnection)
		return mConnection->getMessageTransformer();
	else
		return nullptr;
}



SessionTestUnit* const ConnectionTestUnit::session(const std::string &id) {
	
	SessionTestUnit* found{ nullptr };

	auto found_session = std::find_if(std::begin(mSessions), std::end(mSessions), [&id](const SessionTestUnit& item) {
		return item.id() == id;
	});

	if (found_session != std::end(mSessions))
		found = &*found_session;

	return found;
}

ConsumerTestUnit* const ConnectionTestUnit::consumer(const std::string &id) {

	ConsumerTestUnit* found{ nullptr };

	for (auto &it : mSessions)
	{
		if (auto item = it.consumer(id)) {
			found = item;
			break;
		}
	}

	return found;
}

ProducerTestUnit* const ConnectionTestUnit::producer(const std::string &id) {

	ProducerTestUnit* found{ nullptr };

	for (auto &it : mSessions)
	{
		if (auto item = it.producer(id)) {
			found = item;
			break;
		}
	}

	return found;
}