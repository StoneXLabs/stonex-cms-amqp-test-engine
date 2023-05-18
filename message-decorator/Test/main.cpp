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
#include <ConfigurationParser/MessageDecoratorConfigurationParser.h>
#include <MessageDecorator/MessageDecoratorFactory.h>

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
	MessageDecoratorConfigurationParser parser;

	{

		auto bool_config = new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY, "property_bool", "false");
		auto int_config = new MessageTestField(FIELD_TYPE::INTPROPERTY, "property_int", "123");
		auto double_config = new MessageTestField(FIELD_TYPE::DOUBLEPROPERTY, "property_double", "123.123");

		MessageDecoratorConfiguration decorator({ bool_config, int_config, double_config });

		MessageDecoratorFactory decorator_factory;

		auto decorator1 = decorator_factory.create(MessageDecoratorConfiguration({ bool_config, int_config, double_config }));
		auto decorator2 = decorator_factory.create(MessageDecoratorConfiguration({ bool_config, int_config, double_config }));


		assert(decorator1 != nullptr);
		assert(*decorator1 == *decorator2);


		auto decorator3 = decorator_factory.create(MessageDecoratorConfiguration({ bool_config, int_config }));

		assert(!(*decorator1 == *decorator3));

		auto decorator4 = decorator_factory.create(MessageDecoratorConfiguration({ bool_config, int_config, int_config }));

		assert(!(*decorator1 == *decorator4));
	}
	
	{
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_decorator.config").as_object().cbegin();
		auto property = parser.createMessgeDecoratorConfiguration(message_content_config_json.key_c_str(), message_content_config_json.value());

		auto bool_config = new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property_bool","false");
		auto int_config = new MessageTestField(FIELD_TYPE::INTPROPERTY, "property_int", "123");
		auto double_config = new MessageTestField(FIELD_TYPE::DOUBLEPROPERTY, "property_double", "123.123");

		MessageDecoratorConfiguration compare({ bool_config, int_config, double_config });

		assert(property == compare);

		MessageDecoratorFactory decorator_factory;

		auto decorator = decorator_factory.create(property);

		assert(decorator != nullptr);


	}


}





