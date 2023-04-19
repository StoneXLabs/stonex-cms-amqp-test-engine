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

#include <Configuration\TestCaseMessageReceiverConfiguration.h>

TestCaseMessageReceiverConfiguration::TestCaseMessageReceiverConfiguration(const std::string consumerId, const std::string& destination_type, const std::string& destination_address)
	:mConsumerId{ consumerId },
	mDestinationType{destination_type},
	mDestinationAddress{destination_address}
{}

const std::string TestCaseMessageReceiverConfiguration::consumerId() const 
{ 
	return mConsumerId;
}

const std::string TestCaseMessageReceiverConfiguration::destinationType() const
{
	return mDestinationType;
}

const std::string TestCaseMessageReceiverConfiguration::destinationAddress() const
{
	return mDestinationAddress;
}