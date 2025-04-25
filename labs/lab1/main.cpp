
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "bot.h"

int main()
{
	srand(static_cast<int>(time(nullptr)));

	const auto bots = new bot[5]
	{
		bot("Bread Bot", "0.1", "simple answer bot", "Aliaksiei Tsevialiuk", true),
		bot("Lemon Bot", "1.0", "test bot", "Alex_Tsev", false),
		bot("Skuf Bot", "0.5a", "answer bot", "Aliaksiei", true),
		bot("Open Source Bot", "24w6a", "answer", "Tsevialiuk", false),
		bot()
	};

	const bot bot = bots[rand() % 5];

	int global_choice = 0;

	bot.print_info();

	do
	{
		global_choice = bot.choose_option();

		switch (global_choice)
		{
		case 1:
			bot.print_info();
			break;
		case 2:
			bot.ping();
			break;
		case 3:
			bot.echo();
			break;
		}
	} while (global_choice != -1);

	bot.say_goodbye();

	return 0;
}