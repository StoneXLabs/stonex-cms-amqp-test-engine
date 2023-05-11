#pragma once
#include "TestCaseProducerConfiguration.h"
#include "MessageFile.h"
class FileTestCaseProducerConfiguration : public TestCaseProducerConfiguration, public MessageFile
{
public:
	FileTestCaseProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& message_file);
	friend bool operator== (const FileTestCaseProducerConfiguration& lhs, const FileTestCaseProducerConfiguration& rhs);

};

