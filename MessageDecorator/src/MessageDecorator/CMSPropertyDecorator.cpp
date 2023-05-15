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

#include <MessageDecorator/CMSPropertyDecorator.h>

#include <API/CMSMessage.h>
#include <API/CMSSession.h>

CMSPropertyDecorator::CMSPropertyDecorator(const MessageTestField & field)
	:CMSMessageDecorator(field)
{
}

void CMSPropertyDecorator::decorate(cms::Message * mes, cms::Session * sess) const
{
	switch (mFieldType)
	{
	case FIELD_TYPE::CMS_CORRELATION_ID:
		mes->setCMSCorrelationID(mValueString);
		break;
	case FIELD_TYPE::CMS_DELIVERY_MODE:
		mes->setCMSDeliveryMode(std::atoi(mValueString.c_str()));  //to do enum
		break;
	case FIELD_TYPE::CMS_DESTINATION:
		if (auto dest = destinationFromValueString(sess); dest != nullptr)
			mes->setCMSDestination(dest);
		break;
	case FIELD_TYPE::CMS_EXPIRATION:
		mes->setCMSExpiration(std::atoll(mValueString.c_str()));
		break;
	case FIELD_TYPE::CMS_MESSAGE_ID:
		mes->setCMSMessageID(mValueString.c_str());
		break;
	case FIELD_TYPE::CMS_PRIORITY:
		mes->setCMSPriority(std::atoi(mValueString.c_str())); //refactor
		break;
	case FIELD_TYPE::CMS_REDELIVERED:
		mes->setCMSRedelivered(std::atoi(mValueString.c_str()));
		break;
	case FIELD_TYPE::CMS_REPLY_TO:
		if (auto dest = destinationFromValueString(sess); dest != nullptr)
			mes->setCMSReplyTo(dest);
		break;
	case FIELD_TYPE::CMS_TIMESTAMP:
		mes->setCMSTimestamp(atoll(mValueString.c_str()));
		break;
	case FIELD_TYPE::CMS_TYPE:
		break;
	default:
		break;
	}


	CMSMessageDecorator::decorate(mes, sess);
}

cms::Destination * CMSPropertyDecorator::destinationFromValueString(cms::Session * sess) const {
	auto it = mValueString.find(":");
	auto type = mValueString.substr(0, it);
	it += 2;
	auto address = mValueString.substr(it);
	return nullptr;
}
