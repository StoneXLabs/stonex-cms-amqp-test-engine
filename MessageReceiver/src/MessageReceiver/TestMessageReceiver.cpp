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

#include <MessageReceiver/TestMessageReceiver.h>
#include <Configuration/TestCaseMessageReceiverConfiguration.h>
#include <algorithm>

TestMessageReceiver::TestMessageReceiver(const TestCaseMessageReceiverConfiguration& config, CMSClientTestUnit & client_params, Notifier& notifier)
	:EventStatusObserver(notifier)
{
	auto cms_consumer = client_params.consumer(config.connectionId(), config.sessionId(), config.consumerId());
	if (cms_consumer)
		cms_consumer->setMessageListener(this);
}

TestMessageReceiver::~TestMessageReceiver()
{
}

#include <iostream>

void TestMessageReceiver::onMessage(const cms::Message* message) {
	std::cout << "LISTENER on message" << std::endl;
}

//
//void TestMessageReceiver::initialize(CMSClientTestUnit & UUT, const CMSWrapperConfiguration & config)
//{
//	std::for_each(std::begin(config.config()), std::end(config.config()), [&UUT, this](const ConnectionConfiguration& connection_item) {
//
//		std::for_each(std::begin(connection_item.sessionConfiguration()), std::end(connection_item.sessionConfiguration()), [&UUT, this](const SessionConfiguration& session_item) {
//
//			std::for_each(std::begin(session_item.consumerConfiguration()), std::end(session_item.consumerConfiguration()),  [&UUT, this](const ConsumerConfiguration& consumer_item) {
//
//				if (auto cms_consumer = UUT.consumer(consumer_item.key())) {
//					cms_consumer->setMessageListener(mListenerFactory->create(consumer_item.key(), this));
//					mMessageListeners.push_back(cms_consumer->getMessageListener());
//				}
//
//			
//			});
//		});
//	});
//}
//
//void TestMessageReceiver::onMessageReceived(EventStatus status)
//{
//	mNotifier.testEvent(status);
//	received(status);
//}