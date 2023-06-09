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
#include <TestSuite/TestCaseStatus.h>

std::ostream & operator<<(std::ostream & os, const TEST_CASE_STATUS & ts)
{

	switch (ts)
	{
	case TEST_CASE_STATUS::FINISHED:
		os << "FINISHED";
		break;
	case TEST_CASE_STATUS::FAILED:
		os << "FAILED";
		break;
	case TEST_CASE_STATUS::DISABLED:
		os << "DISABLED";
		break;
	case TEST_CASE_STATUS::SEND_ERROR:
		os << "SEND_ERROR";
		break;
	case TEST_CASE_STATUS::UNKNOWN:
		os << "UNKNOWN";
		break;
	case TEST_CASE_STATUS::NOT_REGISTERED:
		os <<  "NOT_REGISTERED";
		break;
	defalut:
		os << "NOT DEFINED STATUS";
		break;
	}


	return os;
}

 std::string to_string(const TEST_CASE_STATUS & ts)
 {
	 std::stringstream ss;
	 ss << ts;
	 return ss.str();
 }
