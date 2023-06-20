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

#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include <ConfigurationParser/MessageFieldConfigParser.h>
#include <limits>
#include <iostream>

boost::json::value valueFromFile(const std::string& configFile)
{
	std::ifstream config_file(configFile);

	boost::json::stream_parser p;
	boost::json::error_code ec;
	do
	{
		char buf[4096];
		config_file.read(buf, sizeof(buf));
		p.write(buf, config_file.gcount(), ec);
	} while (!config_file.eof());

	p.finish(ec);

	return  p.release();
}



int main()
{

	MessageFieldConfigParser parser;
	
	{
		std::cout << "##teamcity[testSuiteStarted name='message-content FIELD_TYPE::BOOLEANPROPERTY']" << std::endl;

		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_bool.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageField(FIELD_TYPE::BOOLEANPROPERTY,"property","false");

		std::cout << "##teamcity[testStarted name='FIELD_TYPE::BOOLEANPROPERTY']" << std::endl;
		std::cout<<"##teamcity["<<((property != nullptr) ? "testFinished" : "testFailed")<<" name='FIELD_TYPE::BOOLEANPROPERTY']"<<std::endl;


		std::cout << "##teamcity[testStarted name='FIELD_TYPE::BOOLEANPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property->valueString() == property_config.valueString()) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::BOOLEANPROPERTY']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='message-content FIELD_TYPE::BOOLEANPROPERTY']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='message-content FIELD_TYPE::BYTEPROPERTY']" << std::endl;

		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_byte.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageField(FIELD_TYPE::BYTEPROPERTY, "property", "127");

		std::cout << "##teamcity[testStarted name='FIELD_TYPE::BYTEPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property != nullptr) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::BYTEPROPERTY']" << std::endl;


		std::cout << "##teamcity[testStarted name='FIELD_TYPE::BYTEPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property->valueString() == property_config.valueString()) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::BYTEPROPERTY']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='message-content FIELD_TYPE::BYTEPROPERTY']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='message-content FIELD_TYPE::DOUBLEPROPERTY']" << std::endl;

		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_double.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageField(FIELD_TYPE::DOUBLEPROPERTY, "property", "127");

		std::cout << "##teamcity[testStarted name='FIELD_TYPE::DOUBLEPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property != nullptr) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::DOUBLEPROPERTY']" << std::endl;


		std::cout << "##teamcity[testStarted name='FIELD_TYPE::DOUBLEPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property->valueString() == property_config.valueString()) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::DOUBLEPROPERTY']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='message-content FIELD_TYPE::DOUBLEPROPERTY']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='message-content FIELD_TYPE::FLOATPROPERTY']" << std::endl;

		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_float.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageField(FIELD_TYPE::FLOATPROPERTY, "property", "127.11");

		std::cout << "##teamcity[testStarted name='FIELD_TYPE::FLOATPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property != nullptr) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::FLOATPROPERTY']" << std::endl;


		std::cout << "##teamcity[testStarted name='FIELD_TYPE::FLOATPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property->valueString() == property_config.valueString()) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::FLOATPROPERTY']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='message-content FIELD_TYPE::FLOATPROPERTY']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='message-content FIELD_TYPE::INTPROPERTY']" << std::endl;

		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_int.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageField(FIELD_TYPE::INTPROPERTY, "property", "127");

		std::cout << "##teamcity[testStarted name='FIELD_TYPE::INTPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property != nullptr) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::INTPROPERTY']" << std::endl;


		std::cout << "##teamcity[testStarted name='FIELD_TYPE::INTPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property->valueString() == property_config.valueString()) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::INTPROPERTY']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='message-content FIELD_TYPE::INTPROPERTY']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='message-content FIELD_TYPE::LONGPROPERTY']" << std::endl;

		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_long.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageField(FIELD_TYPE::LONGPROPERTY, "property", "127");

		std::cout << "##teamcity[testStarted name='FIELD_TYPE::LONGPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property != nullptr) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::LONGPROPERTY']" << std::endl;


		std::cout << "##teamcity[testStarted name='FIELD_TYPE::LONGPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property->valueString() == property_config.valueString()) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::LONGPROPERTY']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='message-content FIELD_TYPE::LONGPROPERTY']" << std::endl;
	}

	{
		std::cout << "##teamcity[testSuiteStarted name='message-content FIELD_TYPE::SHORTPROPERTY']" << std::endl;

		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_short.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageField(FIELD_TYPE::SHORTPROPERTY, "property", "127");

		std::cout << "##teamcity[testStarted name='FIELD_TYPE::SHORTPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property != nullptr) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::SHORTPROPERTY']" << std::endl;


		std::cout << "##teamcity[testStarted name='FIELD_TYPE::SHORTPROPERTY']" << std::endl;
		std::cout << "##teamcity[" << ((property->valueString() == property_config.valueString()) ? "testFinished" : "testFailed") << " name='FIELD_TYPE::SHORTPROPERTY']" << std::endl;

		std::cout << "##teamcity[testSuiteFinished name='message-content FIELD_TYPE::SHORTPROPERTY']" << std::endl;
	}

}





