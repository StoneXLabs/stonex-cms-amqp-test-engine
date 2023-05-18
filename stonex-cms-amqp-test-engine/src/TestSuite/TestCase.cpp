#include <TestSuite/TestCase.h>
#include <chrono>

TestCase::TestCase(const TestCaseConfiguration& test_config, MessageSenderFactory* factory, const TestFunctionRegister& functionRegister, TestObserver* observer)
	:Notifier(observer),
	mTestedObject(test_config.uutConfig(), nullptr,""),
	mTestPerformer(test_config.performerConfig(), mTestedObject,*this, factory ),
	mTestVerifier(test_config.verifierConfig(), mTestedObject,*this),
	mTestName{test_config.testName()}
{
	if (test_config.enabled()) {
		mTestFunction = functionRegister.getTestFunction(test_config.testFunctionName());
		if (!mTestFunction)
			TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, " [" + mTestName + "] ", test_config.testFunctionName() + "not found"));
	}
	else
		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, " [" + mTestName + "] ", "test disabled by configuration"));

}

void TestCase::run()
{
	if (mTestFunction) {

		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_START, mTestName, ""));

		auto start = std::chrono::high_resolution_clock::now();
		mTestFunction(&mTestedObject, &mTestPerformer);
		auto end = std::chrono::high_resolution_clock::now();

		if (mTestSuccess)
			TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_SUCCESS, " [" + mTestName + "] ", ""));
		else
			TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_ERROR, " [" + mTestName + "] ", "test failed"));

		auto test_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		TestMessage(NotifyMessage(REPORT_MESSAGE_SEVERITY::INFO, REPORT_MESSAGE_TYPE::TEST_END, " [" + mTestName + "] ",std::to_string(test_duration_ms) + " [ms]"));
	}


}

void TestCase::testEvent(const EventStatus & event)
{
	Notifier::testEvent(event);
	if (mTestSuccess)
		mTestSuccess = event.correct();
}