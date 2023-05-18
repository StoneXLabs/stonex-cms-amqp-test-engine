#pragma once
#include "MessageSenderConfiguration.h"
#include <utils/MessageFile.h>
class FileMessageSenderConfiguration : public MessageSenderConfiguration, public MessageFile
{
public:
	FileMessageSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& message_file);
	friend bool operator== (const FileMessageSenderConfiguration& lhs, const FileMessageSenderConfiguration& rhs);

};

