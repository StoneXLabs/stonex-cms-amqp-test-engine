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

#include <MessageReceiver/MessageReceiver.h>

#include <algorithm>

stonex::test::performer::MessageReceiver::MessageReceiver(engine::event::handler::factory::CMSMessageListenerFactory * messageListenerFactory/*, notifier::Notifier& notifier*/)
	:/*EventStatusObserver(notifier),*/
	mListenerFactory{messageListenerFactory}
{
}

stonex::test::performer::MessageReceiver::~MessageReceiver()
{
}

void stonex::test::performer::MessageReceiver::initialize(engine::node::CMSClientWrapper & UUT, const engine::configuration::BasicClientConfiguration & config)
{
	std::for_each(std::begin(config.config()), std::end(config.config()), [&UUT, this](const engine::configuration::BasicConnectionConfiguration& connection_item) {

		std::for_each(std::begin(connection_item.sessionConfiguration()), std::end(connection_item.sessionConfiguration()), [&UUT, this](const engine::configuration::BasicSessionConfiguration& session_item) {

			std::for_each(std::begin(session_item.consumerConfiguration()), std::end(session_item.consumerConfiguration()),  [&UUT, this](const engine::configuration::BasicConsumerConfiguration& consumer_item) {

				if (auto cms_consumer = UUT.consumer(consumer_item.key())) {
					cms_consumer->setMessageListener(mListenerFactory->create(consumer_item.key(), this));
					mMessageListeners.push_back(cms_consumer->getMessageListener());
				}

			
			});
		});
	});
}

//void stonex::test::performer::MessageReceiver::onMessageReceived(verifier::status::EventStatus status)
//{
//	mNotifier.testEvent(status);
//	received(status);
//}