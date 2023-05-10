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

#include <TestSuite/TestCasePerformer.h>
#include <algorithm>
#include <Notifier/EventStatus.h>


TestCasePerformer::TestCasePerformer(const TestCasePerformerConfiguration & params, CMSClientTestUnit & client_params, Notifier& notifier, const MessageSenderFactory& sender_factory)
	:EventStatusObserver(notifier)
{
		 std::transform(std::cbegin(params.senders()), std::cend(params.senders()), std::back_inserter(mSenders), [this,&client_params, &sender_factory](const TestCaseProducerConfiguration* item) { return sender_factory.create(*item, client_params, *this); });
}

 void TestCasePerformer::sendAll(int msg_delay_ms)
{
	bool needToSend{ false };

	do
	{
		needToSend = false;
		std::for_each(std::begin(mSenders), std::end(mSenders), [&needToSend, msg_delay_ms](MessageSender* sender) {
			if (sender) {
				if(sender->messageAvailable())
				{
					sender->sendMessage();
					needToSend = true;
				}
			}
			else
				needToSend = false;

		});
	} while (needToSend);


}



