#include <utils/MessageFile.h>

MessageFile::MessageFile(const std::string & file_path)
	:mFilePath{file_path}
{
}

const std::string & MessageFile::filePath() const
{
	return mFilePath;
}

bool MessageFile::operator==(const MessageFile & other)
{
	return false;
}

bool operator==(const MessageFile & lhs, const MessageFile & rhs)
{
	return lhs.mFilePath == rhs.mFilePath;
}
