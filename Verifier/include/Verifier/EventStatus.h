#pragma once
#include <string>

class EventStatus
{
public:
	EventStatus(bool status, const std::string& eventSource, const std::string& errorMessage);

	bool correct() const;

	std::string eventSource() const;

	std::string errorMessage() const;

	friend std::ostream& operator<<(std::ostream& os, const EventStatus& obj);

private:
	bool mMessageCorrect;
	std::string mEventSource{};
	std::string mErrorMessage{};

};
