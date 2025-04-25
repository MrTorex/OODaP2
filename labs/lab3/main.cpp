
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void convert_string_to_time(const std::string& string, int& day, int& month, int& year)
{
	tm tm;

	std::istringstream stream(string);

	stream >> std::get_time(&tm, "%d.%m.%Y");

	day = tm.tm_mday;
	month = tm.tm_mon;
	year = tm.tm_year;
}

void clear_file()
{
	std::fstream file;
	file.open("lab3_logs.txt", std::ofstream::out | std::ofstream::trunc);
	file.close();
}

bool is_older(const std::string& first, const std::string& second)
{
	int day1, day2, month1, month2, year1, year2;

	convert_string_to_time(first, day1, month1, year1);
	convert_string_to_time(second, day2, month2, year2);

	if (year1 < year2)
	{
		return true;
	}
	if (year1 == year2)
	{
		if (month1 < month2)
		{
			return true;
		}
		if (month1 == month2)
		{
			if (day1 < day2)
			{
				return true;
			}
		}
	}

	return false;
}

class book
{
protected:
	std::string name_;
	std::string author_;
	std::string date_;

public:
	book();

	book(const std::string& name, const std::string& author, const std::string& date);

	void set_name();

	void set_author();

	void set_date();

	void print_book() const;

	void print_given_book() const;

	void set_book();

	std::string get_name() const;

	std::string get_author() const;

	std::string get_date() const;
};

std::string book::get_name() const
{
	return name_;
}

std::string book::get_author() const
{
	return author_;
}

std::string book::get_date() const
{
	return date_;
}

void book::set_name()
{
	std::string name;

	std::cout << "Enter name of book: ";
	std::cin >> name;

	name_ = name;
}

void book::set_author()
{
	std::string author;

	std::cout << "Enter author of book: ";
	std::cin >> author;

	author_ = author;
}

void book::set_date()
{
	std::string date;

	std::cout << "Enter date to return of book: ";
	std::cin >> date;

	date_ = date;
}

void book::print_book() const
{
	std::cout << "Name: " << name_ << ", Author: " << author_ << '\n';
}

void book::print_given_book() const
{
	std::cout << "Name: " << name_ << ", Author: " << author_ << ", Date to return: " << date_ << '\n';
}

book::book()
{
	name_ = "Unnamed";
	author_ = "Unknown";
	date_ = "01.01.2020";
}

book::book(const std::string& name, const std::string& author, const std::string& date)
{
	name_ = name;
	author_ = author;
	date_ = date;
}

void book::set_book()
{
	int choice = 0;

	std::cout << "Enter your choice\n1 - name only\n2 - author only\n3 - name and author\nany else - default: ";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		set_name();
		break;
	case 2:
		set_author();
		break;
	case 3:
		set_name();
		set_author();
		break;
	default:
		break;
	}
}

class section : protected book
{
protected:
	std::vector<book> books_section_;

	std::string section_name_;

	int size_;

public:
	section();

	section(const std::string& name, int size);

	explicit section(const std::string& name);

	explicit section(int size);

	void set_section_name();

	void set_section_size();

	void print_section() const;

	void print_given_section() const;

	void set_section();

	void print_outdated_books() const;

	std::string get_section_name() const;

	int& get_section_size();

	std::vector<book>& get_section_vector();
};

std::string section::get_section_name() const
{
	return section_name_;
}

int& section::get_section_size()
{
	return size_;
}

std::vector<book>& section::get_section_vector()
{
	return books_section_;
}

void section::print_section() const
{
	std::cout << "Section " << section_name_ << ":\n";

	for (const book& book : books_section_)
		book.print_book();
}

void section::print_given_section() const
{
	std::cout << "Section " << section_name_ << ":\n";

	for (const book& book : books_section_)
		book.print_given_book();
}

section::section()
{
	section_name_ = "Unnamed section";
	size_ = 5;
}

section::section(const int size)
{
	section_name_ = "Unnamed section";
	size_ = size;
}

section::section(const std::string& name)
{
	section_name_ = name;
	size_ = 5;
}

section::section(const std::string& name, const int size)
{
	section_name_ = name;
	size_ = size;
}

void section::set_section_name()
{
	std::string name;

	std::cout << "Enter name of section: ";
	std::cin >> name;

	section_name_ = name;
}

void section::set_section_size()
{
	int size;

	std::cout << "Enter size of section: ";
	std::cin >> size;

	size_ = size;
}

void section::set_section()
{
	int choice = 0;

	std::cout << "Enter your choice\n1 - size only\n2 - name only\n3 - size and name\nany else - default: ";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		set_section_size();
		break;
	case 2:
		set_section_name();
		break;
	case 3:
		set_section_name();
		set_section_size();
		break;
	default:
		break;
	}

	for (int i = 0; i < size_; i++)
	{
		book book_to_push;
		book_to_push.set_book();
		books_section_.push_back(book_to_push);
	}
}

void section::print_outdated_books() const
{
	std::string now_date;

	clear_file();

	std::fstream file;
	file.open("lab3_logs.txt", std::ios::app);

	std::cout << "Enter today's date: ";
	std::cin >> now_date;

	bool found = false;

	std::cout << "Outdated books:\n";

	for (const book& book: books_section_)
	{
		if (is_older(book.get_date(), now_date))
		{
			found = true;
			book.print_given_book();
			file << "Name: " << book.get_name() << ", Author: " << book.get_author() << ", Date to return: " << book.get_date() << '\n';
		}
	}

	if (!found)
		std::cout << "There's no outdated given books!";

	file.close();
}


class library : protected section
{
private:
	std::vector<section> books_library_;
	int library_size_;

public:
	library();

	explicit library(int size);

	void set_library();

	void print_library() const;

	void add_book();

	void delete_book();

	void give_book(section& given_books);
};

library::library()
{
	library_size_ = 3;
}

library::library(const int size)
{
	library_size_ = size;
}

void library::set_library()
{
	int size = 0;

	std::cout << "Enter size of your library (0 = default): ";
	std::cin >> size;

	if (size != 0)
		library_size_ = size;
	else
		library_size_ = 3;

	for (int i = 0; i < library_size_; i++)
	{
		section to_push_section;
		to_push_section.set_section();
		books_library_.push_back(to_push_section);
	}
}

void library::print_library() const
{
	for (const section& section : books_library_)
		section.print_section();
}

void library::add_book()
{
	std::string section_name;

	bool found = false;

	std::cout << "Enter section name in which to add: ";
	std::cin >> section_name;

	for (section& section : books_library_)
	{
		if (section.get_section_name() == section_name)
		{
			found = true;
			book to_push_book;
			to_push_book.set_book();
			section.get_section_vector().push_back(to_push_book);
			section.get_section_size()++;
			break;
		}
	}

	if (!found)
		std::cout << "There's no section with such name!\n";
}

void library::delete_book()
{
	std::string section_name, book_name;

	bool found = false;

	std::cout << "Enter section name from which to delete: ";
	std::cin >> section_name;

	std::cout << "Enter book to delete name: ";
	std::cin >> book_name;

	for (section& section : books_library_)
	{
		if (section.get_section_name() == section_name)
		{
			found = true;
			for (int i = 0; i < section.get_section_size();)
			{
				if (section.get_section_vector()[i].get_name() == book_name)
				{
					section.get_section_vector().erase(section.get_section_vector().begin() + i);
					section.get_section_size()--;
				}
				else
					i++;
			}
			break;
		}
	}

	if (!found)
		std::cout << "There's no book with such name, or there's no section with such name!\n";
}

void library::give_book(section& given_books)
{
	std::string section_name, book_name;

	bool found = false;

	std::cout << "Enter section name from which to give: ";
	std::cin >> section_name;

	std::cout << "Enter book to give name: ";
	std::cin >> book_name;

	book book_to_give;

	for (section& section : books_library_)
	{
		if (section.get_section_name() == section_name)
		{
			found = true;
			for (int i = 0; i < section.get_section_size();)
			{
				if (section.get_section_vector()[i].get_name() == book_name)
				{
					book_to_give = section.get_section_vector()[i];
					section.get_section_vector().erase(section.get_section_vector().begin() + i);
					section.get_section_size()--;
					break;
				}
				i++;
			}
			break;
		}
	}

	if (!found)
	{
		std::cout << "There's no book with such name, or there's no section with such name!\n";
		return;
	}

	book_to_give.set_date();

	given_books.get_section_vector().push_back(book_to_give);
	given_books.get_section_size()++;
}

void clear()
{
	system("pause");
	system("cls");
}

int main()
{
	library library;

	section given_books("Given books", 0);

	library.set_library();

	clear();

	int choice = 0;

	do
	{
		library.print_library();

		std::cout << "Enter your choice:\n1 - add book to library\n2 - delete book from library\n3 - give book from library\n4 - print info about given books\n5 - print info about outdated given books\n-1 - exit: ";
		std::cin >> choice;

		switch (choice)
		{
		case -1:
			break;
		case 1:
			library.add_book();
			clear();
			break;
		case 2:
			library.delete_book();
			clear();
			break;
		case 3:
			library.give_book(given_books);
			clear();
			break;
		case 4:
			given_books.print_given_section();
			clear();
			break;
		case 5:
			given_books.print_outdated_books();
			clear();
			break;
		default:
			std::cout << "Invalid input!";
			clear();
		}
	} while (choice != -1);

	std::cout << "Have a nice day!\n";

	return 0;
}