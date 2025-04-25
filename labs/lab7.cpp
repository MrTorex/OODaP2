
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Currency
{
protected:
    std::string code_;
    double in_usd_;

public:
    Currency() : code_("USD"), in_usd_(1) {}
    explicit Currency(std::string code) : code_(std::move(code)), in_usd_(1) {}
    Currency(std::string code, double in_usd) : code_(std::move(code)), in_usd_(in_usd) {}
    Currency(const Currency& obj) : code_(obj.code_), in_usd_(obj.in_usd_) {}
    ~Currency() = default;

    std::string getCode() const { return code_; }
    double getInUsd() const { return in_usd_; }

    void setCode(const std::string& code) { code_ = code; }
    void setInUsd(double in_usd) { in_usd_ = in_usd; }
};

class Transaction
{
private:
    std::string fromCurrency_;
    std::string toCurrency_;
    double amount_;
    double result_;

public:
    Transaction(std::string fromCurrency, std::string toCurrency, double amount, double result)
        : fromCurrency_(std::move(fromCurrency)), toCurrency_(std::move(toCurrency)), amount_(amount), result_(result) {}

    std::string getFromCurrency() const { return fromCurrency_; }
    std::string getToCurrency() const { return toCurrency_; }
    double getAmount() const { return amount_; }
    double getResult() const { return result_; }
};

class Converter
{
private:
    static std::vector<std::unique_ptr<Transaction>> transactions_;

public:
    static double convert(const Currency* fromCurrency, const Currency* toCurrency, double amount);

    static void addTransaction(const Transaction& transaction);
    static void rollbackLastTransaction();
    static void clearTransactions();
    static void printTransactions();
};

std::vector<std::unique_ptr<Transaction>> Converter::transactions_;

double Converter::convert(const Currency* fromCurrency, const Currency* toCurrency, double amount)
{
	const double fromRate = fromCurrency->getInUsd();
	const double toRate = toCurrency->getInUsd();
    double result = amount * fromRate / toRate;

    const auto transaction = std::make_unique<Transaction>(fromCurrency->getCode(), toCurrency->getCode(), amount, result);
    addTransaction(*transaction);

    return result;
}

void Converter::printTransactions()
{
    for (const auto& transaction : transactions_)
	    std::cout << transaction->getAmount() << ' ' << transaction->getFromCurrency() << "->" << transaction->getResult() << ' ' <<
		    transaction->getToCurrency() << '\n';
}


void Converter::addTransaction(const Transaction& transaction)
{
    transactions_.push_back(std::make_unique<Transaction>(transaction));
}

void Converter::rollbackLastTransaction()
{
    if (!transactions_.empty())
        transactions_.pop_back();
}

void Converter::clearTransactions()
{
    transactions_.clear();
}

void menu(const Currency& usd, const Currency& eur, const Currency& byn)
{
    int choice = 0;

    do 
    {
        Converter::printTransactions();
        std::cout << "Currency Converter\n"
            << "Enter your choice:\n"
            << "1 - Convert one currency to another one\n"
            << "2 - Rollback last transaction\n"
            << "-1 - Exit\n"
            << "Your choice: ";
        std::cin >> choice;

        switch (choice)
    	{
        case 1: 
        {
            int fromCurrencyChoice, toCurrencyChoice;
            const Currency* currency1;
            const Currency* currency2;
            double amount;
            std::cout << "Enter first currency (0 - USD, 1 - EUR, 2 - BYN): ";
            std::cin >> fromCurrencyChoice;
            std::cout << "Enter second currency (0 - USD, 1 - EUR, 2 - BYN): ";
            std::cin >> toCurrencyChoice;
            std::cout << "Enter amount to convert: ";
            std::cin >> amount;

            std::string fromCurrencyCode, toCurrencyCode;

            switch (fromCurrencyChoice)
            {
            case 0: currency1 = &usd; fromCurrencyCode = usd.getCode(); break;
            case 1: currency1 = &eur; fromCurrencyCode = eur.getCode(); break;
            case 2: currency1 = &byn; fromCurrencyCode = byn.getCode(); break;
            default: std::cout << "Invalid currency choice\n"; continue;
            }

            switch (toCurrencyChoice)
            {
            case 0: currency2 = &usd; toCurrencyCode = usd.getCode(); break;
            case 1: currency2 = &eur; toCurrencyCode = eur.getCode(); break;
            case 2: currency2 = &byn; toCurrencyCode = byn.getCode(); break;
            default: std::cout << "Invalid currency choice\n"; continue;
            }

            const double result = Converter::convert(currency1, currency2, amount);
            std::cout << "Converted " << amount << " " << fromCurrencyCode
                << " to " << result << " " << toCurrencyCode << std::endl;
            break;
        }

        case 2:
            Converter::rollbackLastTransaction();
            std::cout << "Last transaction rolled back\n";
            break;
        case -1:
            return;
        default:
            std::cout << "Invalid choice\n";
        }

        system("pause");
        system("cls");
    } while (choice != -1);
}

int main()
{
	const Currency usd("USD", 1);
	const Currency eur("EUR", 1.086);
	const Currency byn("BYN", 0.3072);

    menu(usd, eur, byn);

    std::cout << "Have a nice day!\n";
    return 0;
}
