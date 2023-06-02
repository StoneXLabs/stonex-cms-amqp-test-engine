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

#include <Wrapper/ClientTestUnit.h>

ClientTestUnit::ClientTestUnit(const std::string & key, const std::string & address, const ClientType clientType, const DestinationType destinationType, cms::Session * session, DefaultTerminationMode termination_method)
	:DefaultTerminationConfiguration(termination_method),
	mKey{ key },
	mAddress{ address },
	mClientType{ clientType },
	mDestinationType{ destinationType },
	mSession{ session }
{
	initializeDestination();
}

ClientTestUnit::ClientTestUnit(ClientTestUnit && other)
	:DefaultTerminationConfiguration(other.getTerminationMode()),
	mKey{other.mKey},
	mAddress{other.mAddress},
	mClientType{other.mClientType},
	mDestinationType{other.mDestinationType},
	mSession{other.mSession},
	mDestination{other.mDestination}
{
	mSession = nullptr;
	mDestination = nullptr;
}

const std::string ClientTestUnit::key() const
{
	return mKey;
}

const std::string ClientTestUnit::address() const
{
	return mAddress;
}

void ClientTestUnit::initializeDestination()
{
	if (mSession) 
	{
		switch (mDestinationType) 
		{
		case DestinationType::ANONYMOUS:
			break;
		case DestinationType::QUEUE:
			mDestination = mSession->createQueue(mAddress);
			break;
		case DestinationType::TOPIC:
			mDestination = mSession->createTopic(mAddress);
			break;
		case DestinationType::TEMPORARY_QUEUE:
			mDestination = mSession->createTemporaryQueue();
			break;
		case DestinationType::TEMPORARY_TOPIC:
			mDestination = mSession->createTemporaryTopic();
			break;
		}
	}
}
