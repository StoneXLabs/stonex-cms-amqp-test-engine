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

#include <MessageDecorator/CMSDestinationDecorator.h>
#include <MessageContent/MessageDestinationTestField.h>


CMSDestinationDecorator::CMSDestinationDecorator(const MessageField & field)
	:CMSMessageDecorator(field)
{
	if (auto _field = dynamic_cast<const MessageDestinationTestField*>(&field)) {
		mDestType = _field->destType();
	}
}

void CMSDestinationDecorator::decorate(cms::Message * mes, cms::Session * sess) const
{
	cms::Destination* _destination{ nullptr };

	if (sess == nullptr || mes == nullptr)
		CMSMessageDecorator::decorate(mes, sess);

	switch (mDestType)
	{
	case FIELD_TYPE::CMS_QUEUE:
		_destination = sess->createQueue(mValueString);
		break;
	case FIELD_TYPE::CMS_TEMPORARY_QUEUE:
		_destination = sess->createTemporaryQueue();
		break;
	case FIELD_TYPE::CMS_TOPIC:
		_destination = sess->createTopic(mValueString);
		break;
	case FIELD_TYPE::CMS_TEMPORARY_TOPIC:
		_destination = sess->createTemporaryTopic();
		break;
	}

	if(!_destination)
		CMSMessageDecorator::decorate(mes, sess);

	switch (mFieldType)
	{
	case FIELD_TYPE::CMS_DESTINATION:
		mes->setCMSDestination(_destination);
		break;
	case FIELD_TYPE::CMS_REPLY_TO:
		mes->setCMSReplyTo(_destination);
		break;
	}

	delete _destination;

	CMSMessageDecorator::decorate(mes, sess);

}
