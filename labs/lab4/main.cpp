
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class employee
{
protected:
	std::string full_name_;

	unsigned experience_, number_of_hours_;

	double hourly_wage_, salary_, bonus_;

	virtual void set_bonus() = 0;

public:
	virtual ~employee() = default;

	employee() = default;

	employee(const std::string& full_name, unsigned experience, unsigned number_of_hours, double hourly_wage);

	employee(const employee& obj);

	std::string get_full_name() { return full_name_; }

	unsigned get_experience() const { return experience_; }

	unsigned get_number_of_hours() const { return number_of_hours_; }

	double get_hourly_wage() const { return hourly_wage_; }

	double get_salary() const { return salary_; }

	double get_bonus() const { return bonus_; }

	void print() const;

	void print_to_file() const;
};

employee::employee(const std::string& full_name, const unsigned experience, const unsigned number_of_hours, const double hourly_wage)
{
	full_name_ = full_name;
	experience_ = experience;
	number_of_hours_ = number_of_hours;
	hourly_wage_ = hourly_wage;
	salary_ = number_of_hours * hourly_wage;
}

void employee::print() const
{
	std::cout << "Full name: " << full_name_ << ", experience: " << experience_ << ", number of hours: " << number_of_hours_ << ", hourly wage: " << hourly_wage_ << ", salary: " << salary_ << ", bonus: " << bonus_ << '\n';
}

void employee::print_to_file() const
{
	std::fstream file;
	file.open("lab4_logs.txt", std::ofstream::app);
	file << "Full name: " << full_name_ << ", experience: " << experience_ << ", number of hours: " << number_of_hours_ << ", hourly wage: " << hourly_wage_ << ", salary: " << salary_ << ", bonus: " << bonus_ << '\n';
	file.close();
}

class employee_1_y final : public employee
{
protected:
	void set_bonus() override
	{
		bonus_ = salary_ * 0.01;
	}

public:
	employee_1_y(const std::string& full_name, const unsigned experience, const unsigned number_of_hours, const double hourly_wage) : employee(full_name, experience, number_of_hours, hourly_wage) { employee_1_y::set_bonus(); }
};

class employee_3_y final : public employee
{
protected:
	void set_bonus() override
	{
		bonus_ = salary_ * 0.05;
	}

public:
	employee_3_y(const std::string& full_name, const unsigned experience, const unsigned number_of_hours, const double hourly_wage) : employee(full_name, experience, number_of_hours, hourly_wage) { set_bonus(); }
};

class employee_5_y final : public employee
{
protected:
	void set_bonus() override
	{
		bonus_ = salary_ * 0.08;
	}

public:
	employee_5_y(const std::string& full_name, const unsigned experience, const unsigned number_of_hours, const double hourly_wage) : employee(full_name, experience, number_of_hours, hourly_wage) { set_bonus(); }
};

class employee_more_5_y final : public employee
{
protected:
	void set_bonus() override
	{
		bonus_ = salary_ * 0.15;
	}

public:
	employee_more_5_y(const std::string& full_name, const unsigned experience, const unsigned number_of_hours, const double hourly_wage) : employee(full_name, experience, number_of_hours, hourly_wage) { set_bonus(); }
};

void clear_file()
{
	std::fstream file;
	file.open("lab4_logs.txt", std::ofstream::out | std::ofstream::trunc);
	file.close();
}

void clear()
{
	system("pause");
	system("cls");
}

int main()
{
	clear_file();

	std::vector<employee*> employees;

	std::string buf;

	std::cout << "Enter amount of employees: ";
	std::getline(std::cin, buf);
	const int amount = stoi(buf);

	for(int i = 0; i < amount; i++)
	{
		std::string full_name;

		std::cout << "Enter full name of employee No " << i + 1 << ": ";
		std::getline(std::cin, full_name);

		std::cout << "Enter experience in years of employee No " << i + 1 << ": ";
		std::getline(std::cin, buf);
		const unsigned experience = stoi(buf);

		std::cout << "Enter number of hours of employee No " << i + 1 << ": ";
		std::getline(std::cin, buf);
		const unsigned number_of_hours = stoi(buf);

		std::cout << "Enter hourly wage of employee No " << i + 1 << ": ";
		std::getline(std::cin, buf);
		const double hourly_wage = stoi(buf);

		if (experience < 1)
		{
			employee_1_y* push_back_employee = new employee_1_y(full_name, experience, number_of_hours, hourly_wage);
			employees.push_back(push_back_employee);
		}
		else if (experience >= 1 && experience < 3)
		{
			employee_3_y* push_back_employee = new employee_3_y(full_name, experience, number_of_hours, hourly_wage);
			employees.push_back(push_back_employee);
		}
		else if (experience >= 3 && experience < 5)
		{
			employee_5_y* push_back_employee = new employee_5_y(full_name, experience, number_of_hours, hourly_wage);
			employees.push_back(push_back_employee);
		}
		else
		{
			employee_more_5_y* push_back_employee = new employee_more_5_y(full_name, experience, number_of_hours, hourly_wage);
			employees.push_back(push_back_employee);
		}
	}

	clear();

	std::cout << "Your employee list:\n";
	
	for (const employee* employeeptr : employees)
	{
		employeeptr->print();
		employeeptr->print_to_file();
	}

	return 0;
}
