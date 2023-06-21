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

#include <MessageSender/MessageSender.h>
#include <Configuration/MessageCountingSenderConfiguration.h>
#include <utils/SentMessageCounter.h>

class MessageCountingSender : public MessageSender, public SentMessageCounter
{
public:
	explicit MessageCountingSender(const MessageCountingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);
	MessageCountingSender(const MessageCountingSender& other) = delete;
	MessageCountingSender(MessageCountingSender&& other);
	virtual MESSAGE_SEND_STATUS send_text(int msg_delay_ms = 0) override;
	virtual MESSAGE_SEND_STATUS send_bytes(int msg_delay_ms = 0) override;
	virtual MESSAGE_SEND_STATUS send_stream(int msg_delay_ms = 0) override;
	virtual MESSAGE_SEND_STATUS send_map(int msg_delay_ms = 0) override;

	//bool operator == (const MessageCountingSender& other);

};

