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

#pragma once

#include <iostream>
#include <cms/Message.h>
#include "ExpectedField.h"


class FieldVerifierFactory
{
public:
	IExpectedField* create(FIELD_TYPE ft, bool check_existance, bool check_value, const boost::json::value& value = boost::json::value(), const std::string& msg_property = "");
	IExpectedField* create(FIELD_TYPE ft, bool check_existance, bool check_value, const std::string& value = {}, const std::string& msg_property = "");
	IExpectedField* create(const cms::Message* message, const IExpectedField* other) const;

	
};

