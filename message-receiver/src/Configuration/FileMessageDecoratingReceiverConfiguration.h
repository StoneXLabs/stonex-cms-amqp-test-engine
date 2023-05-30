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

#include <utils/MessageFile.h>
#include <Configuration/MessageDecoratorConfiguration.h>
#include <Configuration/MessageReceiverConfiguration.h>

class FileMessageDecoratingReceiverConfiguration : public MessageReceiverConfiguration, public MessageFile, public MessageDecoratorConfiguration
{
public:
	FileMessageDecoratingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string& messageType, const std::string& receiverType, const std::string& message_file, const std::vector<MessageField*>& decorations);
	friend bool operator== (const FileMessageDecoratingReceiverConfiguration& lhs, const FileMessageDecoratingReceiverConfiguration& rhs);

};
