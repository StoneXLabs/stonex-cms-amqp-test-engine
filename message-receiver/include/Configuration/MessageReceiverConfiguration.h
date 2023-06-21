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
#include <vector>


class MessageReceiverConfiguration 
{
public:
	MessageReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string& messageType, const std::string& receiverType);
	virtual ~MessageReceiverConfiguration() = default;
	std::string connectionId() const;
	std::string sessionId() const;
	std::string consumerId() const;
	std::string messageType() const;
	std::string receiverType() const;
	friend bool operator== (const MessageReceiverConfiguration& lhs, const MessageReceiverConfiguration& rhs);
	
private:
	const std::string mConnectionId;
	const std::string mSessionId;
	const std::string mConsumerId;
	const std::string mMessageType;
	const std::string mReceiverType;
};

