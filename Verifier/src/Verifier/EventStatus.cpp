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


#include <Verifier/EventStatus.h>
#include <iomanip>


EventStatus::EventStatus(bool status, const std::string& eventSource, const std::string &errorMessage)
	:mMessageCorrect{ status },
	mEventSource{eventSource},
	mErrorMessage(errorMessage)
{
}

bool EventStatus::correct() const {
	return mMessageCorrect;
}

std::string EventStatus::eventSource() const
{
	return mEventSource;
}

std::string EventStatus::errorMessage() const
{
	return mErrorMessage;
}

std::ostream& operator<<(std::ostream& os, const EventStatus& obj)
{
	os << "status : " << std::boolalpha << obj.correct();
	if (!obj.correct())
		os << " reason : " << obj.errorMessage();
	return os;
}
