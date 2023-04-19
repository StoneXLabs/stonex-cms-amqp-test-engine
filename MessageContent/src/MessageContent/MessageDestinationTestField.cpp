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

#include <MessageContent/MessageDestinationTestField.h>

MessageDestinationTestField::MessageDestinationTestField(FIELD_TYPE ft, const std::string & dest_type, const std::string & dest_address)
	:MessageTestField(ft, {}, {}),
	mDestType(FIELD_TYPE::STRINGPROPERTY, "dest_type", dest_type),
	mAddress(FIELD_TYPE::STRINGPROPERTY, "address", dest_address)
{

}

std::string MessageDestinationTestField::name() const
{
	return mAddress.valueString();
}

std::string MessageDestinationTestField::valueString() const
{ 
	return mDestType.valueString();
}
