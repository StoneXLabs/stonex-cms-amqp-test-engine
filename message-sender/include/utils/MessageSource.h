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

#include <fstream>

class MessageSource {
public:
	virtual std::string getMessage() = 0;
};




class MessageFileSource : public MessageSource
{
public:
	MessageFileSource(const std::string& file);
	MessageFileSource(const MessageFileSource& other);
	MessageFileSource(MessageFileSource&& other);

	std::ifstream fHandler;

	bool closeFHandler();
	void reset();
	std::string getMessage() override;
	bool mInitialized{ false };

	bool operator == (const MessageFileSource& other);

private:
	const std::string mFile;
};


