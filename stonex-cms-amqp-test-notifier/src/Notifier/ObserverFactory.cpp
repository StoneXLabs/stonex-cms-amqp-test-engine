#include <Notifier/ObserverFactory.h>
#include <Notifier/StdOutTestObserver.h>
#include <Notifier/TeamCityTestObserver.h>

TestObserver* ObserverFactory::create(const std::string& type)
{
	if (type == "terminal") {
		return new StdOutTestObserver();
	}
	else if (type == "teamcity") {
		return new TeamCityTestObserver();
	}
	else {
		return nullptr;
	}
}
