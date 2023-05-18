#pragma once
#include <string>
#include "MessageContent/MessageTestField.h"

class MessageFieldConfigParser
{
public:

	MessageTestField* createMessageFieldConfig(const std::string & configName, const boost::json::value & json) const;

};

