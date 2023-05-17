#pragma once
#include "MessageReceiverConfiguration.h"
#include <utils/MessageFile.h>
class FileMessageReceiverConfiguration : public MessageReceiverConfiguration, public MessageFile
{
public:
	FileMessageReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string& message_file);
	friend bool operator== (const FileMessageReceiverConfiguration& lhs, const FileMessageReceiverConfiguration& rhs);

};

