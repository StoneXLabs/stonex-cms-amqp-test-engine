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

#include <utils/SessionHandler.h>

SessionHandler::SessionHandler(cms::Session * object)
	:mObject(object)
{
}

void SessionHandler::close()
{
	if (mObject)
		mObject->close();
	else
		throw std::logic_error("hendeled object is nullptr");
}

void SessionHandler::commit()
{
	if (mObject)
		mObject->commit();
	else
		throw std::logic_error("hendeled object is nullptr");
}

void SessionHandler::rollback()
{
	if (mObject)
		mObject->rollback();
	else
		throw std::logic_error("hendeled object is nullptr");
}

void SessionHandler::recover()
{
	if (mObject)
		mObject->recover();
	else
		throw std::logic_error("hendeled object is nullptr");
}

bool SessionHandler::isTransacted() const
{
	if (mObject)
		return mObject->isTransacted();
	else
		throw std::logic_error("hendeled object is nullptr");
}

void SessionHandler::unsubscribe(const std::string & name)
{
	if (mObject)
		mObject->unsubscribe(name);
	else
		throw std::logic_error("hendeled object is nullptr");
}
