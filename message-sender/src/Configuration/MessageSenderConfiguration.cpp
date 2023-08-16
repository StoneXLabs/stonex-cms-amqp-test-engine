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

#include <Configuration/MessageSenderConfiguration.h>

MessageSenderConfiguration::MessageSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& messageType, const std::string& senderType)
	:mConnectionId{ connectionId },
	mSessionId{ sessionId },
	mProducerId{ producerId },
	mMessageType{ messageType },
	mSenderType{ senderType }
{}

std::string MessageSenderConfiguration::connectionId() const
{
	return mConnectionId;
}
std::string MessageSenderConfiguration::sessionId() const
{
	return mSessionId;
}
std::string MessageSenderConfiguration::producerId() const 
{ 
	return mProducerId; 
}

std::string MessageSenderConfiguration::messageType() const
{
	return mMessageType;
}

std::string MessageSenderConfiguration::senderType() const
{
	return mSenderType;
}


bool operator==(const MessageSenderConfiguration & lhs, const MessageSenderConfiguration & rhs)
{
	return lhs.mConnectionId == rhs.mConnectionId &&
		lhs.mSessionId == rhs.mSessionId &&
		lhs.mProducerId == rhs.mProducerId &&
		lhs.mMessageType == rhs.mMessageType &&
		lhs.mSenderType == rhs.mSenderType;
		
}
