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

#include <string>
#include <functional>
#include <mutex>
#include <utils/EventCounter.h>
#include <Notifier/Notifier.h>


class ReceivedMessageCounter : public EventCounter
{
public:
	ReceivedMessageCounter(const std::string &id, long long expected_message_count, Notifier & parent);
	ReceivedMessageCounter(const ReceivedMessageCounter& other);
	ReceivedMessageCounter(ReceivedMessageCounter&& other);
	virtual ~ReceivedMessageCounter();
	long long receivedMessageCount() const;
	void incrementReceivedCount();
	void registerCallback(std::function<void(void)> callback);
private:
	long long mReceivedMessagesCount{ 0 };
	const std::string mId;
	Notifier &mParent;
	std::function<void(void)> mReceivedAllCallback = []() {};
	mutable std::mutex mCounterMutex;
};

