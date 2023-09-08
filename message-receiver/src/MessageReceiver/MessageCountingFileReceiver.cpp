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

#include <MessageReceiver/MessageCountingFileReceiver.h>

MessageCountingFileReceiver::MessageCountingFileReceiver(const FileMessageCountingReceiverConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageReceiver(config, client_params),
	ReceivedMessageCounter(id(), config.expectedEventCount(), parent),
	MessageFileDestination(config.filePath())
{
	registerCallback(std::bind(&MessageCountingFileReceiver::closeConsumer, this));
}


void MessageCountingFileReceiver::onMessage(const cms::Message* message)
{
	getMessage(message);
	incrementReceivedCount();

	if (mListener)
		mListener->onMessage(message);
	else
		delete message;

}

void MessageCountingFileReceiver::waitForMessage(long long millis) const
{
	if (!mConsumer)
		return;

	if (millis == 0) //wait forever  
	{
		while (receivedMessageCount() < expectedEventCount());
	}
	else {
		std::this_thread::sleep_for(std::chrono::milliseconds(millis));
	}
}
