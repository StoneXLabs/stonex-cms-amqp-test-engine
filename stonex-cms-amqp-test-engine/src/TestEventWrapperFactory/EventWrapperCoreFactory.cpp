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


#include <TestEventWrapperFactory/EventWrapperCoreFactory.h>

#include <cms/Message.h>

#include <TestEventWrapper/MessageWrapper.h>
#include <TestEventWrapper/ExceptionWrapper.h>
#include <TestEventWrapper/STDExceptionWrapper.h>


EventWrapper * EventWrapperCoreFactory::create(const cms::Message * mes)
{
	return new MessageWrapper(mes);
}

EventWrapper * EventWrapperCoreFactory::create(const cms::CMSException & ex)
{
	return new ExceptionWrapper(ex);
}

EventWrapper * EventWrapperCoreFactory::create(const std::exception & ex)
{
	return new STDExceptionWrapper(ex);
}