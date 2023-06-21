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

#pragma once

#include <logger/StoneXLogger.h>
#include "ClientTestUnit.h"
#include "../Configuration/ProducerConfiguration.h"


class ProducerTestUnit : public ClientTestUnit, public cms::MessageProducer
{
public:
	ProducerTestUnit(const ProducerConfiguration& params, std::shared_ptr<StonexLogger> logger, cms::Session* session);
	ProducerTestUnit(ProducerTestUnit&& other);
	ProducerTestUnit(const ProducerTestUnit& other) = delete;
	~ProducerTestUnit();

	void send(cms::Message* mes) override;
	void send(cms::Message* mes, cms::AsyncCallback* callback) override;
	void send(cms::Message* mes, int deliveryMode, int priority, long long timeToLive) override;
	void send(cms::Message* mes, int deliveryMode, int priority, long long timeToLive, cms::AsyncCallback* callback) override;

	void send(const cms::Destination* destination, cms::Message* mes, int deliveryMode, int priority, long long timeToLive) override;

	void send(const cms::Destination* destination, cms::Message* mes, int deliveryMode, int priority, long long timeToLive, cms::AsyncCallback* callback) override;
	void send(const cms::Destination* destination, cms::Message* mes, cms::AsyncCallback* callback) override;
	void send(const cms::Destination* destination, cms::Message* mes) override;

	void setDeliveryMode(int mode) override;
	int getDeliveryMode() const override;

	void setDisableMessageID(bool value) override;
	bool getDisableMessageID() const override;

	void setDisableMessageTimeStamp(bool value) override;
	bool getDisableMessageTimeStamp() const override;

	void setPriority(int priority) override;
	int getPriority() const override;

	void setTimeToLive(long long time) override;
	long long getTimeToLive() const override;

	void setMessageTransformer(cms::MessageTransformer* transformer) override;
	cms::MessageTransformer* getMessageTransformer() const override;

	void close() override;

private:
	cms::MessageProducer* mProducer{ nullptr };
};

