#pragma once
#include "MessageReceiverConfiguration.h"
#include <utils/MessageFile.h>
#include <Configuration/MessageDecoratorConfiguration.h>

class FileMessageDecoratingReceiverConfiguration : public MessageReceiverConfiguration, public MessageFile, public MessageDecoratorConfiguration
{
public:
	FileMessageDecoratingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string& message_file, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const FileMessageDecoratingReceiverConfiguration& lhs, const FileMessageDecoratingReceiverConfiguration& rhs);

};
