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

#include <TestSuite/TestCaseVerifier.h>
#include <Configuration/MessageReceiverConfiguration.h>
#include <MessageReceiver/MessageReceiverFactory.h>

TestCaseVerifier::TestCaseVerifier(const TestCaseVerifierConfiguration & params, CMSClientTestUnit & client_params, Notifier & notifier)
{
	MessageReceiverFactory receiverFactory;
	std::transform(std::cbegin(params.messageExpectations()), std::cend(params.messageExpectations()), std::back_inserter(mReceivers), [this, &client_params,&receiverFactory,&notifier](const MessageReceiverConfiguration* item) {
		auto receiver = receiverFactory.create(*item, client_params, notifier);
		auto consumer = client_params.consumer(item->connectionId(), item->sessionId(), item->consumerId());		
		if(consumer)
			consumer->setMessageListener(receiver);
		return receiver;
	});

}

TestCaseVerifier::~TestCaseVerifier() 
{
	std::for_each(std::begin(mReceivers), std::end(mReceivers), [](MessageReceiver* item) {delete item; item = nullptr; });
}