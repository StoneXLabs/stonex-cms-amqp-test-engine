#pragma once

#include <Notifier\TestObserver.h>

class ObserverFactory
{
public:
	static TestObserver* create(const std::string& type);
};

