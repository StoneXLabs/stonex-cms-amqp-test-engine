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

#include <functional>
#include <Wrapper/CMSClientTestUnit.h>
#include <Notifier/Notifier.h>
#include <utils/EventCounter.h>
#include <utils/MessageFile.h>
#include <utils/MessageType.h>
#include <utils/SessionHandler.h>
#include <utils/ProducerHandler.h>
#include "Configuration/MessageSenderConfiguration.h"

enum class MESSAGE_SEND_STATUS {
	SUCCESS,
	FAILED,
	ALL_SENT,
	SEND_ERROR
};

class MessageSender
{
public:
	MessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, Notifier& parent);
	MessageSender(const MessageSender& other) = delete;
	MessageSender(MessageSender&& other);

	bool sendMessage();
	std::string id() const;
	std::string sessionId() const;
	SessionHandler* getSessionHandler(const std::string& session_id) const;
	ProducerHandler* getProducerHandler() const;

	//bool operator == (const MessageSender& other);

protected:
	MESSAGE_SEND_STATUS send(int msg_delay_ms = 0);
	virtual MESSAGE_SEND_STATUS send_text(int msg_delay_ms = 0);
	virtual MESSAGE_SEND_STATUS send_bytes(int msg_delay_ms = 0);
	virtual MESSAGE_SEND_STATUS send_stream(int msg_delay_ms = 0);
	virtual MESSAGE_SEND_STATUS send_map(int msg_delay_ms = 0);
	virtual std::string createMessageBody() = 0;
	MESSAGE_TYPE fromString(const std::string& message_type_string);

protected:
	SessionTestUnit* mSession{ nullptr };
	ProducerTestUnit* mProducer{ nullptr };
	const std::string mId{};
	const std::string mSessionId{};
	Notifier& mParent;
	const MESSAGE_TYPE mMessageType;
	std::function<MESSAGE_SEND_STATUS(int)> mSendFunction = [](int) {return MESSAGE_SEND_STATUS::ALL_SENT; };
};
