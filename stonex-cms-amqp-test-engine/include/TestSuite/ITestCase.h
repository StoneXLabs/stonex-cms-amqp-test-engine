#pragma once

#include <Notifier/Notifier.h>

class ITestCase : public Notifier
{
public:
	ITestCase(const std::string& testName, TestObserver* observer);
	~ITestCase();
	virtual void run() = 0;

protected:
	void testEvent(const EventStatus& event) override;
protected:
	const std::string mTestName;
	bool mTestSuccess{ true };
	std::chrono::milliseconds mTestDuration;
};
