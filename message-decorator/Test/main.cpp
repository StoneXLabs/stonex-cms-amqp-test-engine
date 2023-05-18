
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





