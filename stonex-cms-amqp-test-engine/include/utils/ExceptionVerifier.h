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
#include <utils/EventCounter.h>
#include <cms/ExceptionListener.h>
#include <Notifier/Notifier.h>

class ExceptionVerifier : public cms::ExceptionListener, public EventCounter
{
public:
	explicit ExceptionVerifier(const std::string &id, long long expected_exception_count, Notifier& parent);
	ExceptionVerifier(const ExceptionVerifier& other);
	ExceptionVerifier(ExceptionVerifier&& other);
	~ExceptionVerifier();
	long long caughtExceptionCount() const;
	void incrementCaughtExceptionCount();
	std::string id() const;

	void onException(const cms::CMSException& ex) override;

private:
	const std::string mId{};
	long long mCaughtExceptionCount{ 0 };
	Notifier& mParent;
};

