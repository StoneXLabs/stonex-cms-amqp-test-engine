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

#include <Configuration/MessageCountingDecoratingSenderConfiguration.h>

MessageCountingDecoratingSenderConfiguration::MessageCountingDecoratingSenderConfiguration(const std::string & connectionId, const std::string & sessionId, const std::string & producerId, const std::string& messageType, const std::string& senderType, long long message_count, const std::vector<MessageField*>& decorations)
	:MessageSenderConfiguration(connectionId, sessionId, producerId, messageType, senderType),
	EventCounter(message_count),
	MessageDecoratorConfiguration(decorations)

{
}

bool operator==(const MessageCountingDecoratingSenderConfiguration & lhs, const MessageCountingDecoratingSenderConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId() &&
		lhs.messageType() == rhs.messageType() &&
		lhs.senderType() == rhs.senderType() &&
		rhs.expectedEventCount() == lhs.expectedEventCount() &&
		std::equal(std::cbegin(lhs.decorations()), std::cend(lhs.decorations()), std::cbegin(rhs.decorations()), std::cend(rhs.decorations()), [](const MessageField* lhs_item, const MessageField* rhs_item) {return *lhs_item == *rhs_item; });
}
