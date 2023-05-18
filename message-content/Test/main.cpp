
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
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_bool.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false");

		assert(property != nullptr);
		assert(property->valueString() == property_config.valueString());
	}

	{
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_byte.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageTestField(FIELD_TYPE::BYTEPROPERTY, "property", "127");

		assert(property != nullptr);
		assert(property->valueString() == property_config.valueString());
	}

	{
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_double.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageTestField(FIELD_TYPE::DOUBLEPROPERTY, "property", "127");

		assert(property != nullptr);
		assert(property->valueString() == property_config.valueString());
	}

	{
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_float.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageTestField(FIELD_TYPE::FLOATPROPERTY, "property", "127.11");

		assert(property != nullptr);
//		assert(property->valueString() == property_config.valueString());
	}

	{
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_int.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageTestField(FIELD_TYPE::INTPROPERTY, "property", "127");

		assert(property != nullptr);
		assert(property->valueString() == property_config.valueString());
	}

	{
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_long.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageTestField(FIELD_TYPE::LONGPROPERTY, "property", "127");

		assert(property != nullptr);
		assert(property->valueString() == property_config.valueString());
	}

	{
		boost::json::object::value_type message_content_config_json = *valueFromFile("test_message_property_short.config").as_object().cbegin();
		auto property = parser.createMessageFieldConfig(message_content_config_json.key_c_str(), message_content_config_json.value());
		auto property_config = MessageTestField(FIELD_TYPE::SHORTPROPERTY, "property", "127");

		assert(property != nullptr);
		assert(property->valueString() == property_config.valueString());
	}
}





