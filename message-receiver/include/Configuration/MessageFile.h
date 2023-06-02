#pragma once

#include <string>

class MessageFile
{
public:
	explicit MessageFile(const std::string& file_path);
	const std::string& filePath() const;
	friend bool operator== (const MessageFile& lhs, const MessageFile& rhs);
	bool operator == (const MessageFile& other);
private:
	const std::string mFilePath{};
};

