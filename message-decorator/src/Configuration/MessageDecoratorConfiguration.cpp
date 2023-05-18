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

#include <Configuration/MessageDecoratorConfiguration.h>
#include <algorithm>

MessageDecoratorConfiguration::MessageDecoratorConfiguration(const std::vector<MessageTestField*>& decorations)
	:mMessageDecorations(std::move(decorations))
{
}

const std::vector<MessageTestField*>& MessageDecoratorConfiguration::decorations() const
{
	return mMessageDecorations;
}

bool operator==(const MessageDecoratorConfiguration & lhs, const MessageDecoratorConfiguration & rhs)
{
	return std::equal(std::cbegin(lhs.mMessageDecorations), std::cend(lhs.mMessageDecorations), std::cbegin(rhs.mMessageDecorations), std::cend(rhs.mMessageDecorations), [](const MessageTestField* lhs_item,const MessageTestField* rhs_item) {return *lhs_item == *rhs_item;});
}
