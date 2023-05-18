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

#include <cms/Connection.h>
#include <logger/StoneXLogger.h>
#include "../Configuration/ConnectionConfiguration.h"
#include "SessionTestUnit.h"
#include "CMSExceptionListenerTestUnit.h"


class ConnectionTestUnit :  public cms::Connection, public CMSExceptionListenerTestUnit
{
public:
	ConnectionTestUnit(const ConnectionConfiguration& params, std::shared_ptr<StonexLogger> logger, cms::ExceptionListener* factoryExceptionListener, cms::ExceptionListener* connectionExceptionListener, cms::ExceptionListener* sessionExceptionListener);
	ConnectionTestUnit(ConnectionTestUnit&& other);
	~ConnectionTestUnit();
	
	std::string id() const;
	std::vector<SessionTestUnit>& sessions();


	void close() override;
	void start() override;
	void stop() override;

	const cms::ConnectionMetaData* getMetaData() const override;

	cms::Session* createSession() override;
	cms::Session* createSession(cms::Session::AcknowledgeMode ackMode) override;

	std::string getClientID() const override;
	void setClientID(const std::string& clientID) override;

	cms::ExceptionListener* getExceptionListener() const override;
	void setExceptionListener(cms::ExceptionListener* listener) override;

	void setMessageTransformer(cms::MessageTransformer* transformer) override;
	cms::MessageTransformer* getMessageTransformer() const override;

	SessionTestUnit* const session(const std::string &id);
	ConsumerTestUnit* const consumer(const std::string &id);
	ProducerTestUnit* const producer(const std::string &id);

private:
	const std::string mId;
	cms::Connection* mConnection{nullptr};
	std::vector<SessionTestUnit> mSessions;
	cms::ExceptionListener* mFactoryExceptionListener{ nullptr };
	cms::ExceptionListener* mConnectionExceptionListener{ nullptr };
};

