
#pragma once
#include <iostream>

class set
{
private:
	int* array_;
	int size_;
	std::string name_;

public:
	set();
	set(const int size, const bool random);
	set(const int size, const std::string& name);
	set(const int size, const std::string& name, const bool random);
	set(const set& obj);
	~set();

	friend void print_set(const set& set);

	friend void sort(const set& set);
	
	friend void write_to_file(const set& set);

	friend set operator&(const set& left_operand, const set& right_operand);

	friend set operator|(const set& left_operand, const set& right_operand);
};

