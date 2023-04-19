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

#include <set>
#include <iostream>
#include <MessageContentVerifiers/VerifierStatus.h>
#include <Verifier/EventStatus.h>

class EventWrapper;

enum class VERIFIED_ITEMS
{
	EXCEPTIONS,
	EXCEPTIONS_COUNT,
	EXCEPTIONS_TYPE,
	EXCEPTIONS_ORDER,
	MESSAGE,
	MESSAGE_COUNT,
	MESSAGE_TYPE,
	MESSAGE_ORDER,
};



class BaseVerifier
{
public:
	BaseVerifier(const std::string &verifier_id, const std::set<VERIFIED_ITEMS>& params);
	BaseVerifier(const BaseVerifier& other);

	bool operator == (const BaseVerifier& other) { return id() == other.id(); }

	virtual EventStatus trigger(const EventWrapper* event) = 0;

	std::string  id() const;
protected:
	std::set<VERIFIED_ITEMS> mParameters;
	std::string mVerifierId;
};

