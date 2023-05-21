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

#include <cms/BytesMessage.h>
#include <cms/TextMessage.h>
#include <utils/MessageParser.h>
#include <sstream>
#include <iomanip>
#include <fmt/format.h>

std::string MessageParser::toString(const cms::Message * message)
{
	std::stringstream ss;
	if (auto binary_message = dynamic_cast<const cms::BytesMessage*>(message))
	{
		ss << std::hex << std::setfill('0');
		auto length = binary_message->getBodyLength();
		if (length <= 0)
			return fmt::format("message length {}", length);
		unsigned char * data_ptr = binary_message->getBodyBytes();
		unsigned char * data_end = data_ptr + length;

		while (data_ptr != data_end)
		{
			ss << std::setw(2) << static_cast<int>(*data_ptr++);
		}
		return ss.str();

	}
	else if (auto text_message = dynamic_cast<const cms::TextMessage*>(message))
	{
		return text_message->getText();
	}
	else {
		ss << message;
		return ss.str();
	}
}
