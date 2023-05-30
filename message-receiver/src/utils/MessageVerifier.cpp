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

#include <utils/MessageVerifier.h>
#include <MessageDecorator/MessageDecoratorFactory.h>
#include <fmt/format.h>

MessageVerifier::MessageVerifier(const std::string &id, const MessageDecoratorConfiguration & decoratorConfig, Notifier & parent)
	:mId{ id },
	mParent{ parent }
{
	

	std::transform(std::cbegin(decoratorConfig.decorations()), std::cend(decoratorConfig.decorations()), std::back_inserter(mVerifiers), 
		[this](MessageField* item) {
		return mVerifierFactory.create(item->type(), true, false, item->valueString(), item->name());
	});

}

void MessageVerifier::verify(const cms::Message* message) const
{
	

	std::for_each(std::cbegin(mVerifiers), std::end(mVerifiers), [this, message](IExpectedField* item)
	{
		if (item) 
		{
			auto t = mVerifierFactory.create(message, item);
			if (!t)
				mParent.testEvent(EventStatus(false, mId, fmt::format("expected message field missing {} {}", to_string(item->expectedField()), item->fieldName())));
			else
				delete t;
		}
		else 
			mParent.testEvent(EventStatus(false, mId, fmt::format("not initialized verifier")));

	});
}
