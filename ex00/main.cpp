#include "BitcoinExchange.hpp"

class FileNotOpenException: public std::exception
{
    public:
        const char* what() const throw()
        {
            return ("Error: You have to provide Two Or more files");
        }
};

int main(int argc, char **argv)
{
    try
    {
        if(argc > 2)
        {
            for(int i = 2; i < argc; i++)
                BitcoinExchange btc(argv[i], argv[1]);
        }
        else
            throw FileNotOpenException();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}