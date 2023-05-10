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

#include <Verifier/BaseVerifier.h>
#include "TestEventWrapper/MessageWrapper.h"
#include  "MessageContentVerifiers/ExpectedField.h"

#include <functional>

#include <Configuration/TestCaseMessageReceiverConfiguration.h>
#include <MessageContentVerifiers/VerifierStatus.h>


class MessageVerifier : public BaseVerifier, public std::enable_shared_from_this<MessageVerifier>
{
public:
	MessageVerifier(const std::string& verifier_id, const std::string  msg_destination_type, const std::string msg_destination_address);
	MessageVerifier(TestCaseMessageReceiverConfiguration& config);
	void addFieldVerifier(IExpectedField* fieldVerifier);

	EventStatus trigger(const EventWrapper* event) override;
	void expectCount(int count);
	int expectCount() const;


private:
	VerifierStatus* mStatus{nullptr};

	int mExpectedMessageCount{ -1 };
	int mMessageCount{ 0 };
	cms::Destination::DestinationType mMsgDestType;
	std::string mDestinationAddress;

	std::list<IExpectedField*> mFieldVerifiers;
};
