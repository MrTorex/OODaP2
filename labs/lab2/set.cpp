
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include "checked_input.h"
#include "set.h"

set::set()
{
	this->size_ = rand() % 15 + 1;

	this->array_ = new int[size_];

	for (int i = 0; i < size_; i++)
		this->array_[i] = rand() % 100;

	this->name_ = "unknown set";
}

set::set(const int size, const bool random)
{
	this->size_ = size;

	this->array_ = new int[size];

	this->name_ = "unknown set";

	if (random)
	{
		for (int i = 0; i < size; i++)
			this->array_[i] = rand() % 100;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "Enter element of set No" << i + 1 << ": ";
			checked_int_input(this->array_[i]);
		}
	}
}

set::set(const int size, const std::string& name)
{
	this->size_ = size;

	this->array_ = new int[size];

	this->name_ = name;
}

set::set(const int size, const std::string& name, const bool random)
{
	this->size_ = size;

	this->array_ = new int[size];

	this->name_ = name;

	if (random)
	{
		for (int i = 0; i < size; i++)
			this->array_[i] = rand() % 100;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "Enter element of set \"" + this->name_ + "\" No" << i + 1 << ": ";
			checked_int_input(this->array_[i]);
		}
	}
}

set::set(const set& obj)
{
	size_ = obj.size_;

	name_ = obj.name_;

	array_ = new int[size_];

	for (int i = 0; i < size_; i++) array_[i] = obj.array_[i];
}

set::~set()
{
	delete[] array_;
}