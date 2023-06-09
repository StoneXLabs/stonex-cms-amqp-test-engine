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

#include <Configuration/MessageDecoratorConfiguration.h>
#include <cms/Session.h>
#include <cms/Message.h>

class CMSMessageDecorator;

class MessageDecorator
{
public:
	explicit MessageDecorator(const MessageDecoratorConfiguration& decoratorConfig);
	MessageDecorator(const MessageDecorator& other) = delete;
	MessageDecorator(MessageDecorator&& other);
	void decorate(cms::Message* message, cms::Session* session) const;

	bool operator == (const MessageDecorator& other);
protected:
	CMSMessageDecorator *mDecorator{ nullptr };
};

