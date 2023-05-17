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
