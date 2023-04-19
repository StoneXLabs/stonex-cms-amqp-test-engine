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

#include <UnitUnderTest/ProducerTestUnit.h>

ProducerTestUnit::ProducerTestUnit(const ProducerConfiguration & params, cms::Session * session)
	:ClientTestUnit(params.key(), params.address(), params.type(), params.destType(), session, params.getTerminationMode())
{
	if(session)
		mProducer = session->createProducer(mDestination);
	else
		throw cms::CMSException("Session used to create producer do not exist");
}

ProducerTestUnit::ProducerTestUnit(ProducerTestUnit && other)
	: ClientTestUnit(std::move(other)),
	mProducer{ other.mProducer }
{
	other.mProducer = nullptr;
}

ProducerTestUnit::~ProducerTestUnit()
{
	close();
	delete mProducer;
}

void ProducerTestUnit::send(cms::Message * mes)
{
	if (mProducer)
		mProducer->send(mes);
}

void ProducerTestUnit::send(cms::Message * mes, cms::AsyncCallback * callback)
{
	if (mProducer)
		mProducer->send(mes, callback);
}

void ProducerTestUnit::send(cms::Message * mes, int deliveryMode, int priority, long long timeToLive)
{
	if (mProducer)
		mProducer->send(mes, deliveryMode, priority, timeToLive);
}

void ProducerTestUnit::send(cms::Message * mes, int deliveryMode, int priority, long long timeToLive, cms::AsyncCallback * callback)
{
	if (mProducer)
		mProducer->send(mes, deliveryMode, priority, timeToLive, callback);
}

void ProducerTestUnit::send(const cms::Destination * destination, cms::Message * mes, int deliveryMode, int priority, long long timeToLive)
{
	if (mProducer)
		mProducer->send(destination, mes, deliveryMode, priority, timeToLive);
}

void ProducerTestUnit::send(const cms::Destination * destination, cms::Message * mes, int deliveryMode, int priority, long long timeToLive, cms::AsyncCallback * callback)
{
	if (mProducer)
		mProducer->send(destination, mes, deliveryMode, priority, timeToLive, callback);
}

void ProducerTestUnit::send(const cms::Destination * destination, cms::Message * mes, cms::AsyncCallback * callback)
{
	if (mProducer)
		mProducer->send(destination, mes, callback);
}

void ProducerTestUnit::send(const cms::Destination * destination, cms::Message * mes)
{
	if (mProducer)
		mProducer->send(destination, mes);
}

void ProducerTestUnit::setDeliveryMode(int mode)
{
	if (mProducer)
		mProducer->setDeliveryMode(mode);
}

int ProducerTestUnit::getDeliveryMode() const
{
	if (mProducer)
		return mProducer->getDisableMessageID();
	else
		return 0;
}

void ProducerTestUnit::setDisableMessageID(bool value)
{
	if (mProducer)
		mProducer->setDisableMessageID(value);
}

bool ProducerTestUnit::getDisableMessageID() const
{
	if (mProducer)
		return mProducer->getDisableMessageID();
	else
		return false;
}

void ProducerTestUnit::setDisableMessageTimeStamp(bool value)
{
	if (mProducer)
		mProducer->setDisableMessageTimeStamp(value);
}

bool ProducerTestUnit::getDisableMessageTimeStamp() const
{
	if (mProducer)
		return mProducer->getDisableMessageTimeStamp();
	else
		return false;
}

void ProducerTestUnit::setPriority(int priority)
{
	if (mProducer)
		mProducer->setPriority(priority);
}

int ProducerTestUnit::getPriority() const
{
	if (mProducer)
		return mProducer->getPriority();
	else
		return 0;
}

void ProducerTestUnit::setTimeToLive(long long time)
{
	if (mProducer)
		mProducer->setTimeToLive(time);
}

long long ProducerTestUnit::getTimeToLive() const
{
	if (mProducer)
		return mProducer->getTimeToLive();
	else
		return 0;
}

void ProducerTestUnit::setMessageTransformer(cms::MessageTransformer * transformer)
{
	if (mProducer)
		mProducer->setMessageTransformer(transformer);
}

cms::MessageTransformer * ProducerTestUnit::getMessageTransformer() const
{
	if (mProducer)
		return mProducer->getMessageTransformer();
	else
		return nullptr;
}

void ProducerTestUnit::close()
{
	if (mProducer)
		mProducer->close();
}




