
#include <fstream>
#include <iostream>
#include <string>
#include "set.h"
#include "checked_input.h"

void print_set(const set& set)
{
	std::cout << "Set \"" << set.name_ << "\": ";

	for (int i = 0; i < set.size_; i++)
		std::cout << set.array_[i] << ' ';

	std::cout << '\n';
}

set operator&(const set& left_operand, const set& right_operand)
{
	int return_size = 0;

	const std::string return_name = left_operand.name_ + '&' + right_operand.name_;

	for (int i = 0; i < left_operand.size_; i++)
	{
		bool temp = false;

		for (int j = 0; j < right_operand.size_; j++)
		{
			if (left_operand.array_[i] == right_operand.array_[j])
			{
				temp = true;
				break;
			}
		}

		if (!temp)
			return_size++;
	}

	return_size += right_operand.size_;

	set return_set(return_size, return_name);

	int temp_it = 0;

	for (int i = 0; i < left_operand.size_; i++)
	{
		bool temp = false;

		for (int j = 0; j < right_operand.size_; j++)
		{
			if (left_operand.array_[i] == right_operand.array_[j])
			{
				temp = true;
				break;
			}
		}

		if (!temp)
		{
			return_set.array_[temp_it] = left_operand.array_[i];
			temp_it++;
		}
	}

	for (int i = temp_it, j = 0; i < return_size; i++, j++)
		return_set.array_[i] = right_operand.array_[j];

	sort(return_set);

	return return_set;
}

set operator|(const set& left_operand, const set& right_operand)
{
	int return_size = 0;

	const std::string return_name = left_operand.name_ + '|' + right_operand.name_;

	for (int i = 0; i < left_operand.size_; i++)
	{
		bool temp = false;

		for (int j = 0; j < right_operand.size_; j++)
		{
			if (left_operand.array_[i] == right_operand.array_[j])
			{
				temp = true;
				break;
			}
		}

		if (temp)
			return_size++;
	}

	set return_set(return_size, return_name);

	int temp_it = 0;

	for (int i = 0; i < left_operand.size_; i++)
	{
		for (int j = 0; j < right_operand.size_; j++)
		{
			if (left_operand.array_[i] == right_operand.array_[j])
			{
				return_set.array_[temp_it] = left_operand.array_[i];
				temp_it++;
				break;
			}
		}
	}

	sort(return_set);

	return return_set;
}

void sort(const set& set)
{
	for (int i = 0; i < set.size_ - 1; i++)
		for (int j = 0; j < set.size_ - i - 1; j++)
			if (set.array_[j] > set.array_[j + 1])
				std::swap(set.array_[j], set.array_[j + 1]);
}

void end_of_function()
{
	system("pause");
	system("cls");
}

void write_to_file(const set& set)
{
	std::fstream file;

	file.open("lab2_logs.txt", std::ios::app);

	file << "Set \"" << set.name_ << "\": ";

	for (int i = 0; i < set.size_; i++)
		file << set.array_[i] << ' ';

	file << '\n';

	file.close();
}

void clear_file()
{
	std::fstream file;
	file.open("lab2_logs.txt", std::ofstream::out | std::ofstream::trunc);
	file.close();
}

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	clear_file();

	const set set1;
	write_to_file(set1);

	int size_set2;
	std::cout << "Enter size of set No2: ";
	checked_int_input(size_set2);

	const set set2(size_set2, true);
	write_to_file(set2);

	int size_set3;
	std::cout << "Enter size of set No3: ";
	checked_int_input(size_set3);
	clear_input();

	std::string name_set3;
	std::cout << "Enter name of set No3: ";
	std::getline(std::cin, name_set3, '\n');

	const set set3(size_set3, name_set3, false);
	write_to_file(set3);

	int choice = 0;

	do
	{
		choice = 0;

		print_set(set1);
		print_set(set2);
		print_set(set3);

		std::cout << "Choose your option:\n1 - make an intersections of sets\n2 - make an union of sets\n-1 - exit: ";

		while (choice != -1 && !(choice > 0 && choice < 3))
		{
			checked_int_input(choice);
			if (choice != -1 && !(choice > 0 && choice < 3))
				std::cout << "Enter valid input: ";
		}

		switch (choice)
		{
		case -1:
			break;
		case 1:
			print_set(set1 & set2);
			print_set(set1 & set3);
			print_set(set2 & set3);

			write_to_file(set1 & set2);
			write_to_file(set1 & set3);
			write_to_file(set2 & set3);

			end_of_function();
			break;
		case 2:
			print_set(set1 | set2);
			print_set(set1 | set3);
			print_set(set2 | set3);

			write_to_file(set1 | set2);
			write_to_file(set1 | set3);
			write_to_file(set2 | set3);

			end_of_function();
			break;
		}
	} while (choice != -1);

	std::cout << "Have a nice day!\n";

	return 0;
}