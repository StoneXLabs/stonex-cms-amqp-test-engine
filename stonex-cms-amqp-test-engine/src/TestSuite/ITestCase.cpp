
#include <TestSuite/ITestCase.h>

ITestCase::ITestCase(const std::string& testName, TestObserver * observer)
	:mTestName{ testName },
	Notifier(observer)
{

	TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_START, mTestName, ""));
}

ITestCase::~ITestCase() {
	if (mTestSuccess)
		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_SUCCESS, mTestName, ""));
	else
		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, mTestName, "test failed"));

	TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_END, mTestName, std::to_string(mTestDuration.count()) + " [ms]"));

}

void ITestCase::testEvent(const EventStatus & event)
{
	Notifier::testEvent(event);
	if (mTestSuccess)
		mTestSuccess = event.correct();
}
