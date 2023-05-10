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

#include <Configuration\SessionConfiguration.h>
#include <sstream>
#include <iterator>
#include <algorithm>

SessionConfiguration::SessionConfiguration(const std::string key, bool autoAck, bool transacted, const  std::vector<ConsumerConfiguration>& consumerConfiguration, const  std::vector<ProducerConfiguration>& producerConfiguration)
	:DefaultTerminationConfiguration(DefaultTerminationMode::CloseOnDestruction),
	mKey{ key },
	mAutoAck{ autoAck },
	mTransacted{ transacted },
	mConsumers{ consumerConfiguration },
	mProducers{ producerConfiguration }
{}

SessionConfiguration& SessionConfiguration::operator=(const SessionConfiguration& other)
{
	mKey = other.mKey;
	mAutoAck = other.mAutoAck;
	mTransacted = other.mTransacted;
	mConsumers = other.mConsumers;
	mProducers = other.mProducers;

	return *this;
}

std::string SessionConfiguration::key() const { return mKey; };

bool SessionConfiguration::autoAck() const { return mAutoAck; };
bool SessionConfiguration::isTransacted() const { return mTransacted; };

const std::vector<ConsumerConfiguration>& SessionConfiguration::consumerConfiguration() const { return mConsumers; };
const std::vector<ProducerConfiguration>& SessionConfiguration::producerConfiguration() const { return mProducers; };

void SessionConfiguration::addClientConfiguration(const ConsumerConfiguration & params)
{
	mConsumers.push_back(params);
}
void SessionConfiguration::addClientConfiguration(const ProducerConfiguration & params)
{
	mProducers.push_back(params);
}


bool operator==(const SessionConfiguration & lhs, const SessionConfiguration & rhs)
{
	return 	lhs.mKey == rhs.mKey &&
		lhs.mAutoAck == rhs.mAutoAck &&
		lhs.mTransacted == rhs.mTransacted &&
		lhs.getTerminationMode() == rhs.getTerminationMode() &&
		lhs.mConsumers.size() == rhs.mConsumers.size() &&
		std::equal(std::cbegin(lhs.mConsumers), std::cend(lhs.mConsumers), std::cbegin(rhs.mConsumers)) == true &&
		lhs.mProducers.size() == rhs.mProducers.size() &&
		std::equal(std::cbegin(lhs.mProducers), std::cend(lhs.mProducers), std::cbegin(rhs.mProducers)) == true;
}

std::ostream & operator<<(std::ostream & os, const SessionConfiguration & other)
{
	os << "Session id:" << other.mKey << " transacted : " << std::boolalpha << other.isTransacted()<<"\n";
	std::copy(std::begin(other.mConsumers), std::end(other.mConsumers), std::ostream_iterator<ConsumerConfiguration>(os, "\n"));
	os <<"\n";
	std::copy(std::begin(other.mProducers), std::end(other.mProducers), std::ostream_iterator<ProducerConfiguration>(os, "\n"));
	return os;
	// TODO: insert return statement here
}