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

#include <Verifier/MessageReceiverVerifier.h>
#include <algorithm>

#include <Verifier/MessageVerifier.h>


MessageReceiverVerifier::MessageReceiverVerifier(std::vector<TestCaseMessageReceiverConfiguration*>& config)//	: mName{ config.testName() }
{
	std::transform(std::cbegin(config), std::cend(config),std::back_inserter(mVerifiers), [this](TestCaseMessageReceiverConfiguration* item) {
		return std::make_shared<MessageVerifier>(*item);
	});
}

MessageReceiverVerifier::~MessageReceiverVerifier()
{
}

std::shared_ptr<BaseVerifier> MessageReceiverVerifier::getVerifier(const std::string& id)
{
	auto item = std::find_if(std::begin(mVerifiers), std::end(mVerifiers), [id](std::shared_ptr<BaseVerifier> item) {return id == item->id(); });
	if (item != std::end(mVerifiers))
		return *item;
	else
		return {};
}

std::list<std::shared_ptr<BaseVerifier>>& MessageReceiverVerifier::verifiers()
{
	return mVerifiers;
}