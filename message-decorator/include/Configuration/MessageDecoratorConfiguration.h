#pragma once
#include <vector>
#include <MessageContent/MessageTestField.h>

class MessageDecoratorConfiguration
{
public:
	MessageDecoratorConfiguration(const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const MessageDecoratorConfiguration& lhs, const MessageDecoratorConfiguration& rhs);
	const std::vector<MessageTestField*>& decorations() const;
private:
	std::vector <MessageTestField*> mMessageDecorations;
};

