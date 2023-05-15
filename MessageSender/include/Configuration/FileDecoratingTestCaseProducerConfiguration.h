#pragma once
#include "TestCaseProducerConfiguration.h"
#include "MessageFile.h"
#include <Configuration/MessageDecoratorConfiguration.h>

class FileDecoratingTestCaseProducerConfiguration : public TestCaseProducerConfiguration, public MessageFile, public MessageDecoratorConfiguration
{
public:
	FileDecoratingTestCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& message_file, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const FileDecoratingTestCaseProducerConfiguration& lhs, const FileDecoratingTestCaseProducerConfiguration& rhs);

};
