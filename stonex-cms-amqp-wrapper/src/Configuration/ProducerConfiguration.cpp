/*
 * Copyright 2023 StoneX Financial Ltd.
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

#include <sstream>
#include <Configuration/ProducerConfiguration.h>

ProducerConfiguration::ProducerConfiguration(const std::string & key, const std::string dest_type, const std::string & address, std::map<std::string, std::string> properties)
	:ClientConfiguration(key, "producer", dest_type, address, DefaultTerminationMode::CloseOnDestruction)
{}

std::ostream & operator<<(std::ostream & os, const ProducerConfiguration & other)
{
	os << "Producer id:" << other.key() << "\n";
	os << "type" << "other.destType()" << " address : " << other.address();
	return os;
	// TODO: insert return statement here
}

bool operator==(const ProducerConfiguration & lhs, const ProducerConfiguration & rhs)
{
	return lhs.key() == rhs.key() &&
		lhs.address() == rhs.address() &&
		lhs.destType() == rhs.destType() &&
		lhs.getTerminationMode() == rhs.getTerminationMode() &&
		lhs.type() == rhs.type();
}
