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

#include <fstream>
#include <cms/Message.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/StreamMessage.h>
#include <cms/MapMessage.h>

class MessageDestination {
public:
	virtual void getMessage(const cms::Message* message) = 0;
protected:
};

std::ostream& operator<<(std::ostream& os, const cms::Message* message);
std::ostream& operator<<(std::ostream& os, const cms::TextMessage& message);
std::ostream& operator<<(std::ostream& os, const cms::MapMessage& message);
std::ostream& operator<<(std::ostream& os, const cms::StreamMessage& message);
std::ostream& operator<<(std::ostream& os, const cms::BytesMessage& message);



class MessageFileDestination : public MessageDestination
{
public:
	MessageFileDestination(const std::string& file);
	virtual ~MessageFileDestination() = default;
	std::ofstream fHandler;

	bool closeFHandler();
	void reset();
	void getMessage(const cms::Message* message) override;
	bool mInitialized{ false };
};


