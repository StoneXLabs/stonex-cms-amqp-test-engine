
#include <ConfigurationParser/MessageFieldConfigParser.h>
#include <Configuration/MessageDecoratorConfiguration.h>
#include <boost/json.hpp>

class MessageDecoratorConfigurationParser : public MessageFieldConfigParser
{
public:
	MessageDecoratorConfiguration createMessgeDecoratorConfiguration(const std::string & configName, const boost::json::value & json) const;
};