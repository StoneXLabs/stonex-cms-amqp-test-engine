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

#include <string>
#include <filesystem>
#include <utils/MessageSource.h>

MessageFileSource::MessageFileSource(const std::string & file)
	:mFile(file)
{
	fHandler.open(mFile);
	if (fHandler.is_open())
		mInitialized = true;
}

MessageFileSource::MessageFileSource(const MessageFileSource& other)
	:mFile(other.mFile)
{
	fHandler.open(mFile);
	if (fHandler.is_open())
		mInitialized = true;
}

MessageFileSource::MessageFileSource(MessageFileSource&& other)
	:mFile(other.mFile)
{
	fHandler.swap(other.fHandler);
	mInitialized = other.mInitialized;
	other.mInitialized = false;
}


bool MessageFileSource::closeFHandler()
{
	fHandler.close();
	mInitialized = false;
	return true;
}

void MessageFileSource::reset()
{
	fHandler.clear();
	fHandler.seekg(0);
}

std::string MessageFileSource::getMessage()
{
	if (mInitialized)
	{
		std::string line;
		if (std::getline(fHandler, line))
			return line;
		else
			throw std::out_of_range("no more data");

	}
	else
		return "";
}

bool MessageFileSource::operator==(const MessageFileSource& other)
{
	return mFile == other.mFile;
}
