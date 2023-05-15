
#include <ConfigurationParser/MessageFieldConfigParser.h>
#include <MessageContent/MessageProperties.h>
#include <MessageContent/MessageDestinationTestField.h>

MessageTestField * MessageFieldConfigParser::createMessageFieldConfig(const std::string & configName, const boost::json::value & json) const
{

	{
		if (configName == "reply_to")
		{
			if (json.is_object())
			{
				auto dest = json.as_object();
				auto type = dest.at("dest_type").as_string().c_str();
				auto address = dest.at("address").as_string().c_str();
				return new MessageDestinationTestField(FIELD_TYPE::CMS_REPLY_TO, type, address);
			}
		}
		else if (configName == "destination")
		{
			if (json.is_object())
			{
				auto dest = json.as_object();
				auto type = dest.at("dest_type").as_string().c_str();
				auto address = dest.at("address").as_string().c_str();
				return new MessageDestinationTestField(FIELD_TYPE::CMS_DESTINATION, type, address);
			}
		}
		else
		{
			return new MessageTestField(fromKeyValue(configName, json), configName, values_string(json));
		}


		return nullptr;
	}
}
