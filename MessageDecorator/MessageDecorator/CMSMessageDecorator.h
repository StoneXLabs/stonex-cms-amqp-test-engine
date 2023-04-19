#pragma once

#include <string>
#include <MessageContent/MessageTestField.h>

namespace cms {

	class Message;
	class Session;
}

class CMSMessageDecorator : protected MessageTestField
{
public:
	CMSMessageDecorator(MessageTestField other);
	virtual void decorate(cms::Message* mes, cms::Session* sess) const;
	void addNext(CMSMessageDecorator* next);


private:
	CMSMessageDecorator* mNext{ nullptr };
};
