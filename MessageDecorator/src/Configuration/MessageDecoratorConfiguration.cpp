
#include <Configuration/MessageDecoratorConfiguration.h>
#include <algorithm>

MessageDecoratorConfiguration::MessageDecoratorConfiguration(const std::vector<MessageTestField*>& decorations)
	:mMessageDecorations(std::move(decorations))
{
}

const std::vector<MessageTestField*>& MessageDecoratorConfiguration::decorations() const
{
	return mMessageDecorations;
}

bool operator==(const MessageDecoratorConfiguration & lhs, const MessageDecoratorConfiguration & rhs)
{
	return std::equal(std::cbegin(lhs.mMessageDecorations), std::cend(lhs.mMessageDecorations), std::cbegin(rhs.mMessageDecorations), std::cend(rhs.mMessageDecorations), [](const MessageTestField* lhs_item,const MessageTestField* rhs_item) {return *lhs_item == *rhs_item;});
}
