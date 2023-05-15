#include "..\..\include\ConfigurationParser\MessageDecoratorConfigurationParser.h"
#include <iostream>

MessageDecoratorConfiguration MessageDecoratorConfigurationParser::createMessgeDecoratorConfiguration(const std::string & configName, const boost::json::value & json) const
{
	if (configName == "properties")
	{
		std::vector<MessageTestField*> property_vector;
		if (json.is_object())
		{
			auto property_json = json.as_object();
			std::transform(std::cbegin(property_json), std::cend(property_json), std::back_inserter(property_vector), [this](boost::json::object::value_type item) {return createMessageFieldConfig(item.key_c_str(),item.value()); });
		}
		return MessageDecoratorConfiguration(property_vector);
	}

	return MessageDecoratorConfiguration({});
}
