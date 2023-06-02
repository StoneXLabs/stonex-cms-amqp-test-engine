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

#include <iostream>
#include <vector>


enum class REPORT_MESSAGE_SEVERITY
{
	INFO,
	WARNING,
	SEND_ERROR,
	CRITICAL,
	DEBUG,
	TRACE,
	STATUS
};

enum class REPORT_MESSAGE_TYPE
{
	TEST_SUITE_START,
	TEST_SUITE_END,
	TEST_START,
	TEST_END,
	TEST_ERROR,
	TEST_SUCCESS,
	TEST_IGNORED,
	EXCEPTION, 
	GENERAL
};


std::ostream& operator<<(std::ostream& os, const REPORT_MESSAGE_SEVERITY& vr);
std::ostream& operator<<(std::ostream& os, const REPORT_MESSAGE_TYPE& mt);

class NotifyMessage 
{
public:
	NotifyMessage(REPORT_MESSAGE_SEVERITY severity, REPORT_MESSAGE_TYPE messageType, const std::string source, const std::string& body);
	NotifyMessage(const std::exception& ex, const std::string& source);

	REPORT_MESSAGE_SEVERITY severity() const;
	REPORT_MESSAGE_TYPE messageType() const;

	std::string source() const;
	std::string message() const;

	friend std::ostream& operator<<(std::ostream& os, const NotifyMessage& vr);

private:
	REPORT_MESSAGE_SEVERITY mSeverity;
	REPORT_MESSAGE_TYPE mMessageType;
	const std::string mSource;
	const std::string mBody;


};