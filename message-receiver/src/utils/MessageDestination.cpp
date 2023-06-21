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

#include <utils/MessageDestination.h>

std::ostream & operator<<(std::ostream & os, const cms::Message* message)
{
	if (auto mes = dynamic_cast<const cms::TextMessage*>(message))
		os << *mes;
	else if (auto mes = dynamic_cast<const cms::MapMessage*>(message))
		os << *mes;
	else if (auto mes = dynamic_cast<const cms::StreamMessage*>(message))
		os << *mes;
	else if (auto mes = dynamic_cast<const cms::BytesMessage*>(message))
		os << *mes;
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::TextMessage & message)
{
	os << message.getText();
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::MapMessage & message)
{
	os << "MapMessage << operator not implemented";
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::StreamMessage & message)
{
	os << "StreamMessage << operator not implemented";
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::BytesMessage & message)
{
	//"BytesMessage << operator not implemented";
	return os;
}


MessageFileDestination::MessageFileDestination(const std::string & file)
{
	fHandler.open(file, std::ios::app);
	if (fHandler.is_open())
		mInitialized = true;
}


bool MessageFileDestination::closeFHandler()
{
	fHandler.close();
	mInitialized = false;
	return true;
}

void MessageFileDestination::reset()
{
	fHandler.clear();
	//	fHandler.seekg(0);
}
void MessageFileDestination::getMessage(const cms::Message * message)
{
	if (mInitialized)
	{
		fHandler << toString(message) << std::endl;
		/*std::string line;
		if (std::getline(fHandler, line))
			return line;
		else
			throw std::out_of_range("no more data");*/

	}
	else
		std::cout << "MESSAGE WRITE SEND_ERROR msg: " << message << std::endl;
}