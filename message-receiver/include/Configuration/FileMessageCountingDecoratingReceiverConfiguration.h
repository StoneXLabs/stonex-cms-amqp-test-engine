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

#include <utils/EventCounter.h>
#include <utils/MessageFile.h>
#include <Configuration/MessageDecoratorConfiguration.h>
#include <Configuration/MessageReceiverConfiguration.h>

class FileMessageCountingDecoratingReceiverConfiguration : public MessageReceiverConfiguration, public MessageFile, public EventCounter, public MessageDecoratorConfiguration
{
public:
	FileMessageCountingDecoratingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string& messageType, const std::string& receiverType, const std::string& file_path, long long message_count, const std::vector<MessageField*>& decorations);
	friend bool operator== (const FileMessageCountingDecoratingReceiverConfiguration& lhs, const FileMessageCountingDecoratingReceiverConfiguration& rhs);

};

