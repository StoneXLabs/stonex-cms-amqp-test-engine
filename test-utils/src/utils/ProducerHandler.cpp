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

#include <stdexcept>
#include <utils/ProducerHandler.h>

ProducerHandler::ProducerHandler(cms::MessageProducer * object)
	:mObject(object)
{
}

int ProducerHandler::getDeliveryMode() const
{
	if (mObject)
		return mObject->getDeliveryMode();
	else
		throw std::logic_error("hendeled object is nullptr");
}

void ProducerHandler::setDeliveryMode(int mode)
{
	if (mObject)
		mObject->setDeliveryMode(mode);
	else
		throw std::logic_error("hendeled object is nullptr");
}

void ProducerHandler::setDisableMessageID(bool value)
{
	if (mObject)
		mObject->setDisableMessageID(value);
	else
		throw std::logic_error("hendeled object is nullptr");;
}

bool ProducerHandler::getDisableMessageID() const
{
	if (mObject)
		return mObject->getDisableMessageID();
	else
		throw std::logic_error("hendeled object is nullptr");
}

void ProducerHandler::setDisableMessageTimeStamp(bool value)
{
	if (mObject)
		mObject->setDisableMessageTimeStamp(value);
	else
		throw std::logic_error("hendeled object is nullptr");
}

bool ProducerHandler::getDisableMessageTimeStamp() const
{
	if (mObject)
		return mObject->getDisableMessageTimeStamp();
	else
		throw std::logic_error("hendeled object is nullptr");

}

void ProducerHandler::setPriority(int priority)
{
	if (mObject)
		mObject->setPriority(priority);
	else
		throw std::logic_error("hendeled object is nullptr");
}

int ProducerHandler::getPriority() const
{
	if (mObject)
		return mObject->getPriority();
	else
		throw std::logic_error("hendeled object is nullptr");
}

void ProducerHandler::setTimeToLive(long long time)
{
	if (mObject)
		mObject->setTimeToLive(time);
	else
		throw std::logic_error("hendeled object is nullptr");
}

long long ProducerHandler::getTimeToLive() const
{
	if (mObject)
		return mObject->getTimeToLive();
	else
		throw std::logic_error("hendeled object is nullptr");
}
