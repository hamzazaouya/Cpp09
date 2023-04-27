#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(char *file): _input_file(file)
{
    this->_fillMapData();
}

void BitcoinExchange::_fillMapData()
{
    std::ifstream data_file;
    std::string line;

    data_file.open("data.csv");
    if(!data_file.is_open())
        throw FileNotExistException();

    while(std::getline(data_file, line) && !data_file.eof())
    {
        if(line.size())
        {
            
        }
    }
    
}       