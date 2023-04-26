#include "BitcoinExchange.hpp"

class FileNotOpenException: public std::exception
{
    public:
        const char* what() const throw()
        {
            return ("Error: could not open file.");
        }
};

int main(int argc, char **argv)
{
    try
    {
        if(argc > 1)
        {
            (void) argv;
        }
        else
            throw FileNotOpenException();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}