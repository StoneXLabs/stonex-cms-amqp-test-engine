#include "CMSMessageDecorator.h"

CMSMessageDecorator::CMSMessageDecorator(MessageTestField other)
	:MessageTestField(other)
{
}

void CMSMessageDecorator::decorate(cms::Message * mes, cms::Session * sess) const
{
	if (mNext)
		mNext->decorate(mes, sess);
}

void CMSMessageDecorator::addNext(CMSMessageDecorator * next)
{
	if (!mNext)
		mNext = next;
	else
		mNext->addNext(next);
}
