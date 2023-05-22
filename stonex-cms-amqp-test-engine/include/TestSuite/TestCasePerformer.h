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

#include <algorithm>
#include <thread>
#include <map>
#include <cms\MessageProducer.h>
#include <cms\Session.h>
#include <Wrapper/CMSClientTestUnit.h>
#include <Configuration/MessageSenderConfiguration.h>
#include <MessageSender/MessageSenderFactory.h>
#include <utils/SessionHandler.h>
#include <utils/ProducerHandler.h>
#include "../Configuration/TestCasePerformerConfiguration.h"

class TestCasePerformer
{
public:
	TestCasePerformer(const TestCasePerformerConfiguration& params, CMSClientTestUnit& client_params, Notifier& notifier, MessageSenderFactory* senderFactory);
	void sendAll(int msg_delay_ms = 0, const std::string &producerId = "", const std::string &sessionId = "");
	void send(int message_count = 0,int msg_delay_ms = 0, const std::string &producerId = "", const std::string &sessionId = "");
	SessionHandler* getSessionHandler(const std::string &session_id);
	ProducerHandler* getProducerHandler(const std::string &session_id,const std::string &producer_id);
private:
	bool stopSend(int stopAfter);
private:
	std::vector<MessageSender*> mSenders;
};

