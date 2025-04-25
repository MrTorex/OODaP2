
#include <fstream>
#include <iostream>
#include <string>

class currency
{
protected:
    std::string code_;
    double in_usd_;
public:
    currency();

    explicit currency(const std::string&);

    currency(const std::string&, double);

    currency(const currency&);

    ~currency() = default;

    std::string get_code() const { return code_; }
    double get_in_usd() const { return in_usd_; }

    void set_code(const std::string& code) { code_ = code; }
    void set_in_usd(const double in_usd) { in_usd_ = in_usd; }
};

currency::currency()
{
    code_ = "USD";
    in_usd_ = 1;
}

currency::currency(const std::string& code)
{
    code_ = code;
    in_usd_ = 1;
}

currency::currency(const std::string& code, const double in_usd)
{
    code_ = code;
    in_usd_ = in_usd;
}

currency::currency(const currency& obj)
{
    code_ = obj.code_;
    in_usd_ = obj.in_usd_;
}

class usd : public currency
{
public:
    usd() = default;
};

class eur : public currency
{
public:
    eur() : currency("EUR", 1.086) {}
};

class byn : public currency
{
public:
	byn() : currency("BYN", 0.3072) {}
};

class converter
{
public:
    template <class T1, class T2>
    static double convert(T1&, T2&, double);

    template <class T1, class T2>
    static void add_to_file(T1&, T2&, double, double, const std::string&);
};

template <class T1, class T2>
double converter::convert(T1& from_currency, T2& to_currency, const double amount)
{
	const double from_rate = from_currency.get_in_usd();
	const double to_rate = to_currency.get_in_usd();

    const double result = amount * from_rate / to_rate;

    add_to_file(from_currency, to_currency, amount, result, "user.txt");
    add_to_file(from_currency, to_currency, amount, result, "manager.txt");

    return result;
}

template <class T1, class T2>
void converter::add_to_file(T1& from_currency, T2& to_currency, const double amount, const double result, const std::string& name)
{
    std::fstream file(name, std::ios::app);

    file << "Converted " << amount << ' ' << from_currency.get_code() << " to " << result << ' ' << to_currency.get_code() << '\n';

    file.close();
}

void clear_file()
{
    std::fstream file("user.txt", std::ios::out | std::ios::trunc);
    file.close();
}

void clear()
{
    system("pause");
    system("cls");
}

void menu(const usd& usd, const eur& eur, const byn& byn)
{
    int choice = 0;

    do
    {
        std::fstream file("user.txt", std::ios::in);
        std::string buf;
        while (std::getline(file, buf))
            std::cout << buf << '\n';
        file.close();

        std::cout << "Currency Converter (info from myfin.by estimate 05.04.2024)\nEnter your choice:\n1 - convert one currency to another one\n2 - see all operations (manager only)\n-1 - exit: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
	        {
				int currency1_choice;
				int currency2_choice;
                std::string currency1_code, currency2_code;
                double amount;
                const currency* currency1;
                const currency* currency2;

                std::cout << "Enter first currency (0 - usd, 1 - eur, 2 - byn): ";
                std::cin >> currency1_choice;

                std::cout << "Enter second currency (0 - usd, 1 - eur, 2 - byn): ";
                std::cin >> currency2_choice;

                std::cout << "Enter amount to convert: ";
                std::cin >> amount;

                switch (currency1_choice)
                {
                case 0:
                    currency1 = &usd;
                    currency1_code = usd.get_code();
                    break;
                case 1:
                    currency1 = &eur;
                    currency1_code = eur.get_code();
                    break;
                case 2:
                    currency1 = &byn;
                    currency1_code = byn.get_code();
                    break;
                default:
                    std::cout << "You have entered wrong currency!\n";
                    clear();
                    continue;
                }

                switch (currency2_choice)
                {
                case 0:
                    currency2 = &usd;
                    currency2_code = usd.get_code();
                    break;
                case 1:
                    currency2 = &eur;
                    currency2_code = eur.get_code();
                    break;
                case 2:
                    currency2 = &byn;
                    currency2_code = byn.get_code();
                    break;
                default:
                    std::cout << "You have entered wrong currency!\n";
                    clear();
                    continue;
                }

				const double converted = converter::convert(*currency1, *currency2, amount);

				std::cout << "You have converted " << amount << ' ' << currency1_code << " to " << converted << ' ' << currency2_code << "!\n";
                clear();
                break;
	        }
        case 2:
	        {
				file.open("manager.txt", std::ios::in);
                while (std::getline(file, buf))
                    std::cout << buf << '\n';
                file.close();
                clear();
                break;
	        }
        case -1:
            break;
        default:
            std::cout << "You have entered wrong currency!\n";
            clear();
        }
    } while (choice != -1);
}

int main()
{
	const usd usd;
	const eur eur;
	const byn byn;

    clear_file();

    menu(usd, eur, byn);

    std::cout << "Have a nice day!\n";
}