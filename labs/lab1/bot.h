
#pragma once
#include <string>

class bot
{
private:
	std::string name_, version_, sphere_, author_;

	bool is_logging_;

public:
	bot();
	bot(const std::string& name, const std::string& version, const std::string& sphere, const std::string& author, bool is_logging);
	bot(const bot& obj);
	

	void log(const std::string& message, int format) const;

	void ping() const;

	void print_info() const;

	void echo() const;

	int choose_option() const;

	void say_goodbye() const;
};