
#include <iostream>
#include <string>
#include <vector>

class codec
{
public:
    virtual ~codec() = default;

    template <typename T>
    T encode(const std::string&);

    template <typename T>
	std::string decode(const T&);
};

class json_codec : public virtual codec
{
public:
    std::string encode(const std::string&);
	std::string decode(const std::string&);
};

std::string json_codec::encode(const std::string& data)
{
	std::string result = "{ \"data\": [";

    const int size = static_cast<int>(data.size());

    for (int i = 0; i < size; ++i) 
    {
        result += "\"";
        result += data[i];
        result += "\"";
        if (i < size - 1) {
            result += ", ";
        }
    }
    result += "] }";

	return result;
}

std::string json_codec::decode(const std::string& data)
{
    std::string result;

    bool is_reading_char = false;

    auto it = data.cbegin() + 11;

    for (it; it != data.cend(); ++it) 
    {
	    const char ch = *it;
        if (ch == '\"' && !is_reading_char)
            is_reading_char = true;

        else if (ch == '\"' && is_reading_char)
            is_reading_char = false;

        else if (is_reading_char)
            result += ch;
    }

    return result;
}

class xml_codec : public virtual codec
{
public:
    std::string encode(const std::string&);
    std::string decode(const std::string&);
};

std::string xml_codec::encode(const std::string& data)
{
    std::string result = "<data>\n";

    for (const char ch : data) 
    {
        result += "\t<char>";
        result += ch;
        result += "</char>\n";
    }
    result += "</data>";

    return result;
}

std::string xml_codec::decode(const std::string& data)
{
    std::string result;
    std::string::size_type start;
    std::string::size_type end = 0;

    while ((start = data.find("<char>", end)) != std::string::npos) {
        start += 6;
        end = data.find("</char>", start);
        if (end == std::string::npos) {
            break;
        }
        result += data.substr(start, end - start);
    }

    return result;
}

class protobuf_codec : public virtual codec
{
public:
	std::vector<uint8_t> encode(const std::string&);
    std::string decode(const std::vector<uint8_t>&);
};

std::vector<uint8_t> protobuf_codec::encode(const std::string& data)
{
    std::vector<uint8_t> result;

    const size_t data_size = data.size();
    result.push_back(static_cast<uint8_t>(data_size));

    for (const char ch : data)
        result.push_back(static_cast<uint8_t>(ch));

    return result;
}

std::string protobuf_codec::decode(const std::vector<uint8_t>& data)
{
    if (data.empty()) return "";

    const size_t data_size = data[0];
    std::string result;

    for (size_t i = 1; i <= data_size; ++i) {
        result += static_cast<char>(data[i]);
    }

    return result;
}

class codecs final : public json_codec, public xml_codec, public protobuf_codec
{

};

int main()
{
    int choice = 0;

    codecs codec;
    do
    {
        choice = 0;

        std::cout << "Enter your choice:\n1 - continue\nany else - exit: ";
        std::cin >> choice;

        if (choice == 1)
        {
            system("cls");

            std::string line;

            std::cout << "Enter line to encode: ";
            std::cin.ignore();
            std::getline(std::cin, line);

            std::string buffer = codec.json_codec::encode(line);

            std::cout << "Line in JSON:\n";
            std::cout << buffer << '\n';

            std::cout << "Encoded from JSON:\n";
            std::cout << codec.json_codec::decode(buffer) << '\n';

            buffer = codec.xml_codec::encode(line);

            std::cout << "Line in XML:\n";
            std::cout << buffer << '\n';

            std::cout << "Encoded from XML:\n";
        	std::cout << codec.xml_codec::decode(buffer) << '\n';

            std::vector<uint8_t> buffer_vector = codec.protobuf_codec::encode(line);

            std::cout << "Line in Protobuf:\n";
            for (const unsigned char ch : buffer_vector)
                std::cout << +ch << ' ';

            std::cout << "\nEncoded from Protobuf:\n";
            std::cout << codec.protobuf_codec::decode(buffer_vector) << '\n';

            buffer_vector.clear();

            system("pause");
            system("cls");
        }
    } while (choice == 1 );

    std::cout << "Have a nice day!\n";
	return 0;
}