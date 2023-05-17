#pragma once
#include "MessageSenderConfiguration.h"
#include <utils/MessageFile.h>
#include <Configuration/MessageDecoratorConfiguration.h>

class FileMessageDecoratingSenderConfiguration : public MessageSenderConfiguration, public MessageFile, public MessageDecoratorConfiguration
{
public:
	FileMessageDecoratingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& message_file, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const FileMessageDecoratingSenderConfiguration& lhs, const FileMessageDecoratingSenderConfiguration& rhs);

};
