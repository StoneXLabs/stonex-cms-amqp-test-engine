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

 void TestCasePerformer::sendAll(int msg_delay_ms, const std::string &producerId, const std::string &sessionId)
{
	 if (producerId.empty() == true && sessionId.empty() == true)
	 {
		 int _continueSend{ 0 };
		 do {
			 _continueSend = 0;
			 _continueSend = std::count_if(std::begin(mSenders), std::end(mSenders), [this, msg_delay_ms](MessageSender* sender) {
				 if (sender)
					return sender->sendMessage();
				 else
					return false;
			 });

		 } while (_continueSend > 0);


	 }
	 else if (producerId.empty())
	 {
		 int _continueSend{ 0 };
		 do {
			 _continueSend = 0;
			 _continueSend = std::count_if(std::begin(mSenders), std::end(mSenders), [this, msg_delay_ms, sessionId](MessageSender* sender) {
				 if (sender) {
					 if (sender->sessionId() == sessionId)
						 return sender->sendMessage();
					 else
						 return false;
				 }
				 else
					 return false;
			 });

		 } while (_continueSend > 0);

		
	 }
	 else if (sessionId.empty())
	 {
		 int _continueSend{ 0 };
		 do {
			 _continueSend = 0;
			 _continueSend = std::count_if(std::begin(mSenders), std::end(mSenders), [this, msg_delay_ms, producerId](MessageSender* sender) {
				 if (sender) {
					 if (sender->id() == producerId)
						 return sender->sendMessage();
					 else
						 return false;
				 }
				 else
					 return false;
			 });

		 } while (_continueSend > 0);


	 }
	 else 
	 {
		 int _continueSend{ 0 };
		 do {
			 _continueSend = 0;
			 _continueSend = std::count_if(std::begin(mSenders), std::end(mSenders), [this, msg_delay_ms, producerId, sessionId](MessageSender* sender) {
				 if (sender) {
					 if (sender->id() == producerId && sender->sessionId() == sessionId)
						 return sender->sendMessage();
					 else
						 return false;
				 }
				 else
					 return false;
			 });

		 } while (_continueSend > 0);

	 }



}

 SessionHandler * TestCasePerformer::getSessionHandler(const std::string &session_id)
 {
	 auto object_ptr = std::find_if(std::begin(mSenders), std::end(mSenders), [&session_id](MessageSender *item) {
		 if (item)
			 return item->getSessionHandler(session_id) != nullptr;
		 else
			 return false;
	 });

	 if (object_ptr != std::end(mSenders) && *object_ptr)
		 return (*object_ptr)->getSessionHandler(session_id);
	 else
		 return nullptr;
 }

 ProducerHandler * TestCasePerformer::getProducerHandler(const std::string &session_id, const std::string &producer_id)
 {
	 auto object_ptr = std::find_if(std::begin(mSenders), std::end(mSenders), [&session_id](MessageSender *item) {
		 if (item)
			 return item->id() == session_id;
		 else
			 return false;
	 });

	 if (object_ptr != std::end(mSenders) && *object_ptr) 
	 {	
		 if((*object_ptr)->id() == producer_id)
			return (*object_ptr)->getProducerHandler();
		 else 
			 return nullptr;
	 }
	 else
		 return nullptr;
 }

 bool TestCasePerformer::stopSend(int stopAfter)
 {
	 return true;
 }



