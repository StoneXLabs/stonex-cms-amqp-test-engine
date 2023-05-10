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

#include "Configuration\ClientConfiguration.h"


std::ostream & operator<<(std::ostream & os, const ClientType & other)
{
	switch (other)
	{
		case ClientType::CONSUMER:
			os << "CONSUMER";
			break;
		case ClientType::PRODUCER:
			os << "PRODUCER";
			break;
	default:
		break;
	}

	return os;
}


std::ostream & operator<<(std::ostream & os, const DestinationType & other)
{
	switch (other)
	{
	case DestinationType::ANONYMOUS:
		os << "anonymous";
		break;
	case DestinationType::QUEUE:
		os << "queue";
		break;
	case DestinationType::TOPIC:
		os << "topic";
		break;
	case DestinationType::TEMPORARY_QUEUE:
		os << "temporary-queue";
		break;
	case DestinationType::TEMPORARY_TOPIC:
		os << "temporary-topic";
		break;
	default:
		break;
	}
	return os;
	// TODO: insert return statement here
}


ClientConfiguration::ClientConfiguration(const std::string& key, const std::string& client_type, const std::string dest_type, const std::string& address, const std::string& termination_method)
	:DefaultTerminationConfiguration(termination_method),
	mKey{ key },
	mAddress{ address }
{
	if (client_type == "consumer")
		mClientType = ClientType::CONSUMER;
	else if (client_type == "producer")
		mClientType = ClientType::PRODUCER;

	if (dest_type == "queue")
		mDestType = DestinationType::QUEUE;
	else if (dest_type == "topic")
		mDestType = DestinationType::TOPIC;
	else if (dest_type == "temporary-queue")
		mDestType = DestinationType::TEMPORARY_QUEUE;
	else if (dest_type == "temporary-topic")
		mDestType = DestinationType::TEMPORARY_TOPIC;
	else if (dest_type == "anonymous")
		mDestType = DestinationType::ANONYMOUS;

}

ClientConfiguration::ClientConfiguration(const std::string& key, const std::string& client_type, const std::string dest_type, const std::string& address, DefaultTerminationMode termination_method)
	:ClientConfiguration(key, client_type, dest_type, address, termination_method == DefaultTerminationMode::CloseOnDestruction ? "close" : "stop")
{
}


ClientConfiguration& ClientConfiguration::operator=(const ClientConfiguration& other)
{
	mKey = other.mKey;
	mClientType = other.mClientType;
	mDestType = other.mDestType;
	mAddress = other.mAddress;

	return *this;
}

std::string ClientConfiguration::key() const
{
	return mKey; 
}

ClientType ClientConfiguration::type() const 
{
	return mClientType; 
}

DestinationType ClientConfiguration::destType() const 
{
	return mDestType; 
}

std::string ClientConfiguration::address() const 
{ 
	return mAddress; 
}


std::ostream& operator<<(std::ostream& os, const ClientConfiguration& other) 
{
	os << other.type() << other.destType() << other.address()<< other.getTerminationMode();
	return os;
}
