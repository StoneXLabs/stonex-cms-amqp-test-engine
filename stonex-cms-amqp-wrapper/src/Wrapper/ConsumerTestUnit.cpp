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

#include <Wrapper/ConsumerTestUnit.h>
#include <logger/StonexLogSource.h>

ConsumerTestUnit::ConsumerTestUnit(const ConsumerConfiguration & params, std::shared_ptr<StonexLogger> logger, cms::Session * session)
	:ClientTestUnit(params.key(), params.address(), params.type(), params.destType(), session, params.getTerminationMode())
{
	if (session) {
		if (const cms::Topic* topic = dynamic_cast<const cms::Topic*>(mDestination); params.durable() == true)
			mConsumer = session->createDurableConsumer(topic, params.subscriptionName(), params.selector());
		else
			mConsumer = session->createConsumer(mDestination, params.selector());
	
		if (auto log_source = dynamic_cast<StonexLogSource*>(mConsumer); log_source != nullptr)
			logger->attach("session", log_source);
	}
	else
		throw cms::CMSException("Session used to create consumer do not exist");
}

ConsumerTestUnit::ConsumerTestUnit(ConsumerTestUnit && other)
	:ClientTestUnit(std::move(other)),
	mConsumer{other.mConsumer}
{
	other.mConsumer = nullptr;
}

ConsumerTestUnit::~ConsumerTestUnit()
{
	if (getTerminationMode() == DefaultTerminationMode::CloseOnDestruction)
		close();
	else
		stop();

	if (auto messageListener = getMessageListener()) 
		setMessageListener(nullptr);

	delete mConsumer;
}

void ConsumerTestUnit::setMessageListener(cms::MessageListener * listener)
{
	if (mConsumer)
		return mConsumer->setMessageListener(listener);
}

cms::MessageListener * ConsumerTestUnit::getMessageListener() const
{
	if (mConsumer)
		return mConsumer->getMessageListener();
	else
		return nullptr;
}

std::string ConsumerTestUnit::getMessageSelector() const
{
	if (mConsumer)
		return mConsumer->getMessageSelector();
	else
		return "";
}

void ConsumerTestUnit::setMessageTransformer(cms::MessageTransformer * transformer)
{
	if (mConsumer)
		mConsumer->setMessageTransformer(transformer);
}

cms::MessageTransformer * ConsumerTestUnit::getMessageTransformer() const
{
	if (mConsumer)
		return mConsumer->getMessageTransformer();
	else
		return nullptr;
}

void ConsumerTestUnit::setMessageAvailableListener(cms::MessageAvailableListener * listener)
{
	if (mConsumer)
		mConsumer->setMessageAvailableListener(listener);
}

cms::MessageAvailableListener * ConsumerTestUnit::getMessageAvailableListener() const
{
	if (mConsumer)
		return mConsumer->getMessageAvailableListener();
	else
		return nullptr;
}

void ConsumerTestUnit::start()
{
	if (mConsumer)
		mConsumer->start();
}

void ConsumerTestUnit::stop()
{
	if (mConsumer)
		mConsumer->stop();
}

void ConsumerTestUnit::close()
{
	if (mConsumer)
		mConsumer->close();
}

cms::Message * ConsumerTestUnit::receive()
{
	if (mConsumer)
		return mConsumer->receive();
	else
		return nullptr;
}

cms::Message * ConsumerTestUnit::receive(int milis)
{
	if (mConsumer)
		return mConsumer->receive(milis);
	else
		return nullptr;
}

cms::Message * ConsumerTestUnit::receiveNoWait()
{
	if (mConsumer)
		return mConsumer->receiveNoWait();
	else
		return nullptr;
}
