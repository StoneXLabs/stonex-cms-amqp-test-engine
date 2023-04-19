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

#include <Verifier/CMSAMQPWrapperVerifier.h>
#include <Verifier/ExceptionVerifier.h>

#include <Configuration/CMSExceptionsConfiguration.h>

CMSAMQPWrapperVerifier::CMSAMQPWrapperVerifier(const TestCaseConfiguration& config)
	: mName{ config.testName() }
{
	if (!config.verifierConfig().exceptionsExpectations().empty())
	{
		std::transform(std::cbegin(config.verifierConfig().exceptionsExpectations()), std::cend(config.verifierConfig().exceptionsExpectations()), std::back_inserter(mVerifiers), [this](CMSExceptionsConfiguration* item) {
			return std::make_shared<ExceptionVerifier>(*item);
		});


	}
}

CMSAMQPWrapperVerifier::~CMSAMQPWrapperVerifier()
{
}

std::shared_ptr<BaseVerifier> CMSAMQPWrapperVerifier::getVerifier(const std::string& id)
{
	auto item = std::find_if(std::begin(mVerifiers), std::end(mVerifiers), [id](std::shared_ptr<BaseVerifier> item) {return id == item->id(); });
	if (item != std::end(mVerifiers))
		return *item;
	else
		return {};
}

std::list<std::shared_ptr<BaseVerifier>>& CMSAMQPWrapperVerifier::verifiers()
{
	return mVerifiers;
}
