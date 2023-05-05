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

#include <UnitUnderTest/SessionTestUnit.h>
#include <algorithm>

#include <Configuration/SessionConfiguration.h>
#include <logger/StonexLogSource.h>

SessionTestUnit::SessionTestUnit(const SessionConfiguration* params, std::shared_ptr<StonexLogger> logger, cms::Connection* conn, cms::ExceptionListener* exceptionListener)
	:CMSExceptionListenerTestUnit(params->key()),
	mId{params->key()}
{
	if (conn) {
		mSession = conn->createSession(params->autoAck() == true ? cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE : cms::Session::AcknowledgeMode::CLIENT_ACKNOWLEDGE);
		
		if (auto log_source = dynamic_cast<StonexLogSource*>(mSession); log_source != nullptr)
			logger->attach("session", log_source);
	}
	else
	{
		mSession = nullptr;
		throw cms::CMSException("Connection used to create session do not exist");
	}
		
	attachListener(exceptionListener);


	std::for_each(std::cbegin(params->consumerConfiguration()), std::cend(params->consumerConfiguration()), [this, logger](const ConsumerConfiguration& item) {
		try
		{
			mConsumers.push_back(ConsumerTestUnit(item, logger, mSession));
		}
		catch (const cms::CMSException & ex)
		{
			onException(ex);
		}
	});

	std::for_each(std::cbegin(params->producerConfiguration()), std::cend(params->producerConfiguration()), [this, logger](const ProducerConfiguration& item) {
		try
		{
			mProducers.push_back(ProducerTestUnit(item, logger, mSession));
		}
		catch (const cms::CMSException & ex)
		{
			onException(ex);
		}
	});

}

SessionTestUnit::SessionTestUnit(SessionTestUnit && other)
	:CMSExceptionListenerTestUnit(other),
	mId{std::move(other.mId)},
	mSession{other.mSession},
	mConsumers{std::move(other.mConsumers)},
	mProducers{ std::move(other.mProducers) }
{
	other.mSession = nullptr;
}


SessionTestUnit::~SessionTestUnit()
{
	if (mSession)
	{
		mConsumers.clear();
		mProducers.clear();
		mSession->close();
		delete mSession;
	}
}


std::string SessionTestUnit::id() const
{
	return mId;
}


ConsumerTestUnit * const SessionTestUnit::consumer(const std::string& id)
{
	ConsumerTestUnit* found{ nullptr };


	auto found_connection = std::find_if(std::begin(mConsumers), std::end(mConsumers), [&id](const ConsumerTestUnit& item) {
		return item.key() == id;
	});

	if (found_connection != std::end(mConsumers))
		found = &*found_connection;

	return found;
}

ProducerTestUnit * const SessionTestUnit::producer(const std::string& id)
{
	ProducerTestUnit* found{ nullptr };


	auto found_connection = std::find_if(std::begin(mProducers), std::end(mProducers), [&id](const ProducerTestUnit& item) {
		return item.key() == id;
	});

	if (found_connection != std::end(mProducers))
		found = &*found_connection;

	return found;
}

void SessionTestUnit::close()
{
	if(mSession)
		mSession->close();
}

void SessionTestUnit::commit()
{
	if (mSession)
		mSession->close();
}

void SessionTestUnit::rollback()
{
	if (mSession)
		mSession->close();
}

void SessionTestUnit::recover()
{
	if (mSession)
		mSession->close();
}

void SessionTestUnit::start()
{
	if (mSession)
		mSession->close();
}

void SessionTestUnit::stop()
{
	if (mSession)
		mSession->close();
}

cms::MessageConsumer * SessionTestUnit::createConsumer(const cms::Destination * destination)
{
	if (mSession)
		return mSession->createConsumer(destination);
	else
		return nullptr;
}

cms::MessageConsumer * SessionTestUnit::createConsumer(const cms::Destination * destination, const std::string & selector)
{
	if (mSession)
		return mSession->createConsumer(destination, selector);
	else
		return nullptr;
}

cms::MessageConsumer * SessionTestUnit::createConsumer(const cms::Destination * destination, const std::string & selector, bool noLocal)
{
	if (mSession)
		return mSession->createConsumer(destination, selector, noLocal);
	else
		return nullptr;
}

cms::MessageConsumer * SessionTestUnit::createDurableConsumer(const cms::Topic * destination, const std::string & name, const std::string & selector, bool noLocal)
{
	if (mSession)
		return mSession->createDurableConsumer(destination, name, selector, noLocal);
	else
		return nullptr;
}

cms::MessageProducer * SessionTestUnit::createProducer(const cms::Destination * destination)
{
	if (mSession)
		return mSession->createProducer(destination);
	else
		return nullptr;
}

cms::QueueBrowser * SessionTestUnit::createBrowser(const cms::Queue * queue)
{
	if (mSession)
		return mSession->createBrowser(queue);
	else
		return nullptr;
}

cms::QueueBrowser * SessionTestUnit::createBrowser(const cms::Queue * queue, const std::string & selector)
{
	if (mSession)
		return mSession->createBrowser(queue, selector);
	else
		return nullptr;
}

cms::Queue * SessionTestUnit::createQueue(const std::string & queueName)
{
	if (mSession)
		return mSession->createQueue(queueName);
	else
		return nullptr;
}

cms::Topic * SessionTestUnit::createTopic(const std::string & topicName)
{
	if (mSession)
		return mSession->createTopic(topicName);
	else
		return nullptr;
}

cms::TemporaryQueue * SessionTestUnit::createTemporaryQueue()
{
	if (mSession)
		return mSession->createTemporaryQueue();
	else
		return nullptr;
}

cms::TemporaryTopic * SessionTestUnit::createTemporaryTopic()
{
	if (mSession)
		return mSession->createTemporaryTopic();
	else
		return nullptr;
}

cms::Message * SessionTestUnit::createMessage()
{
	if (mSession)
		return mSession->createMessage();
	else
		return nullptr;
}

cms::BytesMessage * SessionTestUnit::createBytesMessage()
{
	if (mSession)
		return mSession->createBytesMessage();
	else
		return nullptr;
}

cms::BytesMessage * SessionTestUnit::createBytesMessage(const unsigned char * bytes, int bytesSize)
{
	if (mSession)
		return mSession->createBytesMessage(bytes, bytesSize);
	else
		return nullptr;
}

cms::StreamMessage * SessionTestUnit::createStreamMessage()
{
	if (mSession)
		return mSession->createStreamMessage();
	else
		return nullptr;
}

cms::TextMessage * SessionTestUnit::createTextMessage()
{
	if (mSession)
		return mSession->createTextMessage();
	else
		return nullptr;
}

cms::TextMessage * SessionTestUnit::createTextMessage(const std::string & text)
{
	if (mSession)
		return mSession->createTextMessage(text);
	else
		return nullptr;
}

cms::MapMessage * SessionTestUnit::createMapMessage()
{
	if (mSession)
		return mSession->createMapMessage();
	else
		return nullptr;
}

cms::Session::AcknowledgeMode SessionTestUnit::getAcknowledgeMode() const
{
	if (mSession)
		return mSession->getAcknowledgeMode();
	else
		return cms::Session::AcknowledgeMode();
}

bool SessionTestUnit::isTransacted() const
{
	if (mSession)
		return mSession->isTransacted();
	else
		return false;
}

void SessionTestUnit::unsubscribe(const std::string & name)
{
	if (mSession)
		mSession->unsubscribe(name);
}

void SessionTestUnit::setMessageTransformer(cms::MessageTransformer * transformer)
{
	if (mSession)
		mSession->setMessageTransformer(transformer);
}

cms::MessageTransformer * SessionTestUnit::getMessageTransformer() const
{
	if (mSession)
		return mSession->getMessageTransformer();
	else
		return nullptr;
}
