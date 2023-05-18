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

#include "Configuration/MessageSenderConfiguration.h"
#include <Wrapper/CMSClientTestUnit.h>
#include <Notifier/TestNotifier.h>

#include <utils/EventCounter.h>
#include <utils/MessageFile.h>
class MessageSender
{
public:
	MessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent);

	bool sendMessage();
	std::string id() const;

protected:
	virtual bool send(int msg_delay_ms = 0);
	virtual std::string createMessageBody() = 0;

protected:
	SessionTestUnit* mSession;
	ProducerTestUnit* mProducer;
	const std::string mId{};
	Notifier& mParent;
};
