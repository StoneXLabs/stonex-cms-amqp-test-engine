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

#include <logger/StoneXLogger.h>
#include <cms/ExceptionListener.h>
#include "ConnectionTestUnit.h"
#include "../Configuration/WrapperConfiguration.h"
#include "CMSExceptionListenerTestUnit.h"

class CMSClientTestUnit
{
public:
	explicit CMSClientTestUnit(const std::string userIdentifier = "");
	CMSClientTestUnit(const WrapperConfiguration &config, std::shared_ptr<StonexLogger> logger, const std::string userIdentifier = "", cms::ExceptionListener* factoryExceptionListener = nullptr, cms::ExceptionListener* connectionExceptionListener = nullptr, cms::ExceptionListener* sessionExceptionListener = nullptr);
	CMSClientTestUnit(CMSClientTestUnit&& other) = delete;
	CMSClientTestUnit(const CMSClientTestUnit& other) = delete;
	~CMSClientTestUnit();

	void addConnection(const ConnectionConfiguration* params, std::shared_ptr<StonexLogger> logger, cms::ExceptionListener* factoryExceptionListener, cms::ExceptionListener* connectionExceptionListener, cms::ExceptionListener* sessionExceptionListener);
	void startConnection(const std::string& id);
	void closeConnection(const std::string& id);
	void startConnections();
	void closeConnections();

	void closeSessions();

	std::vector<ConnectionTestUnit>& connections();
	ConnectionTestUnit* const connection(const std::string &id);
	SessionTestUnit* const session(const std::string &connectionId, const std::string &id);
	ConsumerTestUnit* const consumer(const std::string &connectionId,const std::string &sessionId,const std::string &id);
	ProducerTestUnit* const producer(const std::string &connectionId,const std::string &sessionId,const std::string &id);
	
private:
	std::vector<ConnectionTestUnit> mConnections;
};

