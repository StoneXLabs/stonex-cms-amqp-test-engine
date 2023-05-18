#include "MessageDestination.h"

std::ostream & operator<<(std::ostream & os, const cms::Message* message)
{
	if (auto mes = dynamic_cast<const cms::TextMessage*>(message))
		os << *mes;
	else if (auto mes = dynamic_cast<const cms::MapMessage*>(message))
		os << *mes;
	else if (auto mes = dynamic_cast<const cms::StreamMessage*>(message))
		os << *mes;
	else if (auto mes = dynamic_cast<const cms::BytesMessage*>(message))
		os << *mes;
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::TextMessage & message)
{
	os << message.getText();
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::MapMessage & message)
{
	os << "MapMessage << operator not implemented";
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::StreamMessage & message)
{
	os << "StreamMessage << operator not implemented";
	return os;
}

std::ostream & operator<<(std::ostream & os, const cms::BytesMessage & message)
{
	os << "BytesMessage << operator not implemented";
	return os;
}


MessageFileDestination::MessageFileDestination(const std::string & file)
{
	fHandler.open(file);
	if (fHandler.is_open())
		mInitialized = true;
}


bool MessageFileDestination::closeFHandler()
{
	fHandler.close();
	mInitialized = false;
	return true;
}

void MessageFileDestination::reset()
{
	fHandler.clear();
	//	fHandler.seekg(0);
}
void MessageFileDestination::getMessage(const cms::Message * message)
{
	if (mInitialized)
	{
		fHandler << message << std::endl;
		/*std::string line;
		if (std::getline(fHandler, line))
			return line;
		else
			throw std::out_of_range("no more data");*/

	}
	else
		std::cout << "MESSAGE WRITE ERROR msg: " << message << std::endl;
