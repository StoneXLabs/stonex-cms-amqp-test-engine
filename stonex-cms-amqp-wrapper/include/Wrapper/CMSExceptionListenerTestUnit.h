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

#include <cms/ExceptionListener.h>

class CMSExceptionTestUnit : public cms::CMSException
{
public:
	CMSExceptionTestUnit(const std::string &sourceId)
		:CMSException(),
		mSourceId{sourceId}
		{};

	CMSExceptionTestUnit(const std::string& sourceId, const CMSException& ex)
		:CMSException(ex),
		mSourceId{ sourceId }
		{};

	CMSExceptionTestUnit(const std::string& sourceId, const std::string& message)
		:CMSException(message),
		mSourceId{ sourceId }
		{};

	CMSExceptionTestUnit(const std::string& sourceId, const std::string& message, const std::exception* cause)
		:CMSException(message, cause),
		mSourceId{ sourceId }
		{};

	CMSExceptionTestUnit(const std::string& sourceId, const std::string& message, const std::exception* cause,
		const std::vector<std::pair<std::string, int> >& stackTrace)
		:CMSException(message, cause, stackTrace),
		mSourceId{ sourceId }
		{};

		std::string getMessage() const  override
		{
			return "[" + mSourceId + "] " + CMSException::getMessage();
		};

		std::string id() const { return mSourceId; };

private:
	const std::string mSourceId;
};

class CMSExceptionListenerTestUnit : public cms::ExceptionListener
{
public:
	explicit CMSExceptionListenerTestUnit(const std::string& id);
	CMSExceptionListenerTestUnit(CMSExceptionListenerTestUnit&& other);
	CMSExceptionListenerTestUnit(const CMSExceptionListenerTestUnit& other);
	void onException(const cms::CMSException& ex) override;
	void attachListener(cms::ExceptionListener* listener);
	std::string id() const;
private:
	const std::string mId;
	cms::ExceptionListener* mListener{ nullptr };
};

