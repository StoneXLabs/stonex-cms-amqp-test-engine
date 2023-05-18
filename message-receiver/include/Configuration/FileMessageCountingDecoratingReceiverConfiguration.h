#pragma once
#include <utils/EventCounter.h>
#include <utils/MessageFile.h>
#include "MessageReceiverConfiguration.h"
#include <Configuration/MessageDecoratorConfiguration.h>

class FileMessageCountingDecoratingReceiverConfiguration : public MessageReceiverConfiguration, public MessageFile, public EventCounter, public MessageDecoratorConfiguration
{
public:
	FileMessageCountingDecoratingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string& file_path, long long message_count, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const FileMessageCountingDecoratingReceiverConfiguration& lhs, const FileMessageCountingDecoratingReceiverConfiguration& rhs);

};

