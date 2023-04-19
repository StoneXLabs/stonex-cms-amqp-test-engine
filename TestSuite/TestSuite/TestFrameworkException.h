#pragma once
#include <cms/CMSException.h>

class TestFrameworkException : public cms::CMSException
{
public:
	TestFrameworkException(const std::string& message);
};

