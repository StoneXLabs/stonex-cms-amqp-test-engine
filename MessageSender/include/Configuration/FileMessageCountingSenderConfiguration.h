#pragma once

#include "MessageSenderConfiguration.h"
#include "EventCounter.h"
#include "MessageFile.h"

class FileMessageCountingSenderConfiguration : public MessageSenderConfiguration, public EventCounter, public MessageFile
{
public:
	FileMessageCountingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& messageFile, long long message_count);
	friend bool operator== (const FileMessageCountingSenderConfiguration& lhs, const FileMessageCountingSenderConfiguration& rhs);
};

