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

#include <Configuration\TestCaseProducerConfiguration.h>



TestCaseProducerConfiguration::TestCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId)
	:mConnectionId{ sessionId },
	mSessionId{ sessionId },
	mProducerId{ producerId }
{}

std::string TestCaseProducerConfiguration::connectionId() const
{
	return mConnectionId;
}
std::string TestCaseProducerConfiguration::sessionId() const
{
	return mSessionId;
}
std::string TestCaseProducerConfiguration::producerId() const 
{ 
	return mProducerId; 
}


bool operator==(const TestCaseProducerConfiguration & lhs, const TestCaseProducerConfiguration & rhs)
{
	return lhs.connectionId() == rhs.connectionId() &&
		lhs.sessionId() == rhs.sessionId() &&
		lhs.producerId() == rhs.producerId();
		
}
