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

#include <string>
#include <Notifier/NotifyMessage.h>

std::ostream & operator<<(std::ostream & os, const REPORT_MESSAGE_SEVERITY & vr)
{
	switch (vr)
	{
	case REPORT_MESSAGE_SEVERITY::INFO:
		os << "INFO";
		break;
	case REPORT_MESSAGE_SEVERITY::WARNING:
		os << "WARNING";
		break;
	case REPORT_MESSAGE_SEVERITY::ERROR:
		os << "ERROR";
		break;
	case REPORT_MESSAGE_SEVERITY::CRITICAL:
		os << "CRITICAL";
		break;
	case REPORT_MESSAGE_SEVERITY::DEBUG:
		os << "DEBUG";
		break;
	case REPORT_MESSAGE_SEVERITY::TRACE:
		os << "TRACE";
		break;
	case REPORT_MESSAGE_SEVERITY::STATUS:
		os << "STATUS";
		break;
	default:
		os << "UNKNOWN STATUS";
		break;
	}

	return os;
}

std::ostream & operator<<(std::ostream & os, const REPORT_MESSAGE_TYPE & mt)
{
	switch (mt)
	{
	case REPORT_MESSAGE_TYPE::TEST_SUITE_START:
		os << "TEST_SUITE_START";
		break;
	case REPORT_MESSAGE_TYPE::TEST_SUITE_END:
		os << "TEST_SUITE_END";
		break;
	case REPORT_MESSAGE_TYPE::TEST_START:
		os << "TEST_START";
		break;
	case REPORT_MESSAGE_TYPE::TEST_END:
		os << "TEST_END";
		break;
	case REPORT_MESSAGE_TYPE::TEST_ERROR:
		os << "TEST_ERROR";
		break;
	case REPORT_MESSAGE_TYPE::TEST_SUCCESS:
		os << "TEST_SUCCESS";
		break;
	case REPORT_MESSAGE_TYPE::EXCEPTION:
		os << "EXCEPTION";
		break;
	case REPORT_MESSAGE_TYPE::GENERAL:
		os << "GENERAL";
		break;
	default:
		break;
	}

	return os;
}



NotifyMessage::NotifyMessage(REPORT_MESSAGE_SEVERITY severity, REPORT_MESSAGE_TYPE messageType, const std::string source, const std::string& body)
	:mSeverity{ severity },
	mMessageType{messageType},
	mSource{ source },
	mBody{ body }
{}

NotifyMessage::NotifyMessage(const std::exception& ex, const std::string& source)
	:NotifyMessage(REPORT_MESSAGE_SEVERITY::WARNING,REPORT_MESSAGE_TYPE::EXCEPTION, source,ex.what())
{}


REPORT_MESSAGE_SEVERITY NotifyMessage::severity() const
{
	return mSeverity;
}

REPORT_MESSAGE_TYPE NotifyMessage::messageType() const
{
	return mMessageType;
}

std::string NotifyMessage::source() const
{
	return mSource;
}

std::string NotifyMessage::message() const
{
	return mBody;
}

std::ostream & operator<<(std::ostream & os, const NotifyMessage & vr)
{
	os << "[" << vr.mSeverity << "]" << " " <<vr.messageType()<<" "<< vr.source() << " " << vr.mBody;
	return os;
}
