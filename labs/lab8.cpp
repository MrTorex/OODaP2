
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>

class custom_exception final : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "CustomException occurred";
    }
};

class product
{
private:
    std::string name_;
    double price_;

public:
    product(const std::string& name, const double price)
    {
        if (price < 0)
            throw std::invalid_argument("Price cannot be negative");

        this->name_ = name;
        this->price_ = price;
    }

    std::string get_name() { return name_; }
    double get_price() const { return price_; }
};

class order
{
private:
    std::vector<product*> products_;

public:
    void add_product(product* product)
    {
        if (product == nullptr)
            throw std::invalid_argument("Product cannot be null");

        products_.push_back(product);
    }

    double get_total() const
    {
        if (products_.empty())
            throw std::runtime_error("Order is empty");

        double total = 0;

        for (const product* product : products_)
            total += product->get_price();

        return total;
    }
};

class shop
{
private:
    std::vector<order*> orders_;

public:
    void add_order(order* order)
    {
        if (order == nullptr)
            throw custom_exception();

        orders_.push_back(order);
    }
};

void custom_terminate()
{
    std::cerr << "Terminating due to an unhandled exception\n";
    abort();
}

int main()
{
    std::set_terminate(custom_terminate);

    bool exit_requested = false;

    while (!exit_requested) 
    {
        std::cout << "Choose an option:\n";
        std::cout << "1. Generate invalid price exception\n";
        std::cout << "2. Generate null product exception\n";
        std::cout << "3. Generate empty order exception\n";
        std::cout << "4. Generate custom exception\n";
        std::cout << "5. Generate unknown exception\n";
        std::cout << "6. Custom terminate\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        try 
        {
            const auto order = new ::order();
            const auto shop = new ::shop();
            switch (choice) {
            case 1:
                shop->add_order(order);
                order->add_product(new product("Plate", -100));
                break;
            case 2:
                shop->add_order(order);
                order->add_product(nullptr);
                break;
            case 3:
                shop->add_order(order);
                order->get_total();
                break;
            case 4:
                throw custom_exception();
            case 5:
                throw std::runtime_error("Unknown exception");
            case 6:
                terminate();
            case 7:
                exit_requested = true;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
            }

            std::cout << "Total order cost: " << order->get_total() << '\n';
        }
        catch (std::exception& e) 
        {
            std::cerr << "Exception: " << e.what() << '\n';
        }
        catch (...) 
        {
            std::cerr << "Unknown exception occurred" << '\n';
        }
    }

    std::cout << "Have a nice day!";

    return 0;
}
