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

#include <list>

#include <cms/MessageListener.h>

#include <Wrapper/CMSClientTestUnit.h>
#include "CMSMessageListenerFactory.h"
#include <Configuration/CMSWrapperConfiguration.h>

#include <Notifier/EventStatusObserver.h>

class EventStatus;

class TestMessageReceiver : public EventStatusObserver
{
public:
	TestMessageReceiver(CMSMessageListenerFactory* messageListenerFactory, Notifier& notifier);
	virtual ~TestMessageReceiver();

	virtual void initialize(CMSClientTestUnit & UUT, const CMSWrapperConfiguration & config);

	virtual void wait() = 0;


	void onMessageReceived(EventStatus status);

protected:
	virtual void received(EventStatus status) = 0;

protected:
	std::list<cms::MessageListener*> mMessageListeners;
	CMSMessageListenerFactory * mListenerFactory;
};

