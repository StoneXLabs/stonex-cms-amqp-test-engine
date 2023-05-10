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

#include "Configuration/ConsumerConfiguration.h"
#include <sstream>

ConsumerConfiguration::ConsumerConfiguration(const std::string& key, const std::string dest_type, const std::string& address, const std::string& termination_method, const std::string& selector, bool durable, const std::string& subscription_name)
	:ClientConfiguration(key, "consumer", dest_type, address, termination_method),
	mSelector{ selector },
	mDurable{durable},
	mDurableSubscriptionName{subscription_name}
{}

ConsumerConfiguration& ConsumerConfiguration::operator=(const ConsumerConfiguration& other)
{
	mSelector = other.mSelector;
	return *this;
}


std::string ConsumerConfiguration::selector() const { return mSelector; }
bool ConsumerConfiguration::durable() const { return mDurable; }

std::string ConsumerConfiguration::subscriptionName() const
{
	return mDurableSubscriptionName;
}


std::ostream & operator<<(std::ostream & os, const ConsumerConfiguration & other)
{
	os << "Consumer id:"<<other.key()<<"\n";
	os <<"type :"<< other.destType() << " address : " << other.address()<<(other.mSelector.empty() ? "" : other.mSelector);
	return os;
	// TODO: insert return statement here
}

bool operator==(const ConsumerConfiguration & lhs, const ConsumerConfiguration & rhs)
{
	return lhs.key() == rhs.key() &&
		lhs.address() == rhs.address() &&
		lhs.destType() == rhs.destType() &&
		lhs.durable() == rhs.durable() &&
		lhs.mDurableSubscriptionName == rhs.mDurableSubscriptionName &&
		lhs.getTerminationMode() == rhs.getTerminationMode() &&
		lhs.mSelector == rhs.mSelector;
}
