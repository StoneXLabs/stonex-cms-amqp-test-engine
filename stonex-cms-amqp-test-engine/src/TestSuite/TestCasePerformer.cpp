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

#include <algorithm>
#include <TestSuite/TestCasePerformer.h>
#include <Notifier/EventStatus.h>
#include <MessageSender/MessageSenderFactory.h>


TestCasePerformer::TestCasePerformer(const TestCasePerformerConfiguration & params, CMSClientTestUnit & client_params, Notifier& notifier, MessageSenderFactory* senderFactory)
{
	if(senderFactory)
		std::transform(std::cbegin(params.senders()), std::cend(params.senders()), std::back_inserter(mSenders), [this,&client_params,&senderFactory, &notifier](const MessageSenderConfiguration* item) { return senderFactory->create(*item, client_params, notifier); });
}

 void TestCasePerformer::sendAll(int msg_delay_ms)
{

		std::for_each(std::begin(mSenders), std::end(mSenders), [ msg_delay_ms](MessageSender* sender) {
			if (sender) {
					sender->sendMessage();
			}

		});


}



