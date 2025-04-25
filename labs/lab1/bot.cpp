
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "bot.h"

bot::bot(const std::string& name, const std::string& version, const std::string& sphere, const std::string& author, const bool is_logging)
{
	name_ = name;
	version_ = version;
	sphere_ = sphere;
	author_ = author;
	is_logging_ = is_logging;
}

bot::bot()
{
	name_ = "NoName Bot";
	version_ = "0.0";
	sphere_ = "simple bot";
	author_ = "NoName author";
	is_logging_ = true;
}

bot::bot(const bot& obj)
{
	name_ = obj.name_;
	version_ = obj.version_;
	sphere_ = obj.sphere_;
	author_ = obj.author_;
	is_logging_ = obj.is_logging_;
}

void bot::log(const std::string& message, const int format) const
{
	if (is_logging_)
	{
		std::string format_type;

		std::ofstream out;
		out.open("lab1_logs.txt", std::ios::app);

		struct tm time;
		const time_t now = std::time(nullptr);
		localtime_s(&time, &now);

		switch (format)
		{
		case 0:
			format_type = name_;
			break;
		case 1:
			format_type = "USER";
			break;
		}

		out << "[" << std::put_time(&time, "%d-%m-%Y %H-%M-%S") << "] " << format_type << ": " << message << '\n';

		out.close();
	}
}

void bot::ping() const
{
	const std::string message = "Pong! We're on local, so your ping is 0ms.";
	std::cout << message << '\n';
	log(message, 0);
}

void bot::print_info() const
{
	std::string logging;
	if (is_logging_)
		logging = "true";
	else
		logging = "false";
	const std::string message = "Hello! My name is " + name_ + ", version " + version_ + ". My author is " + author_ + ". My sphere is " + sphere_ + ". My logging parametr is " + logging + ".";
	std::cout << message << '\n';
	log(message, 0);
}

void bot::echo() const
{
	std::string temp;
	const std::string message = "Enter your message: ";

	std::cout << message;

	log(message, 0);

	std::cin.ignore();

	std::getline(std::cin, temp);

	log(temp, 1);

	std::cout << temp << '\n';

	log(temp, 0);
}

int bot::choose_option() const
{
	int choice = 0;

	const std::string message = "Choose next options: 1 - print info 'bout me, 2 - ping me, 3 - echo bot, any else - exit: ";

	std::cout << message;

	std::cin >> choice;
	log(std::to_string(choice), 1);

	switch (choice)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	default:
		return -1;
	}
}

void bot::say_goodbye() const
{
	const std::string message = "Goodbye, see you soon!";

	std::cout << message << '\n';

	log(message, 0);
}