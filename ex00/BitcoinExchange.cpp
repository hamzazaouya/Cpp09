#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs)
{
    this->_data = rhs._data;
    this->_date = rhs._date;
    this->_value = rhs._value;
    this->_input_file = rhs._input_file;
}

void BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    this->_data = rhs._data;
    this->_date = rhs._date;
    this->_value = rhs._value;
    this->_input_file = rhs._input_file;
}



BitcoinExchange::BitcoinExchange(char *file): _input_file(file)
{
    this->_fillMapData();
    this->_executeFile();
}

std::string BitcoinExchange::_token(std::istringstream &iss)
{
    std::string token;

    std::getline(iss, token, ' ');
    return (token);
}

bool BitcoinExchange::check_date() const
{
    size_t      num;
    std::string token;
    std::istringstream iss(this->_date);

    if(this->_date > this->_data.rbegin()->first || this->_date < this->_data.begin()->first)
        throw BadInputException();
    std::getline(iss, token, '-');
    std::getline(iss, token, "-");
    

}

void BitcoinExchange::_executeFile()
{
    std::ifstream       file;
    std::string         line;
    std::string         token;

    file.open(this->_input_file);
    if(!file.is_open())
        throw FileNotExistException();
    std::getline(file, line);
    if(line != "date | value")
        throw FileContentErrorException();
    while(std::getline(file, line))
    {
        std::istringstream  iss(line);

        try 
        {
            this->_date =  this->_token(iss);
            if(!check_date())
                throw BadInputException();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        // if(iss.eof())
        //     std::cout << "end of string" << std::endl;
        // else
        //     std::cout << "Not the end of string" << std::endl;
    }
}

void BitcoinExchange::_fillMapData()
{
    std::ifstream data_file;
    std::string line;
    std::string token1;
    std::string token2;
    size_t      year;
    float f;
    
    data_file.open("data.csv");
    if(!data_file.is_open())
        throw FileNotExistException();
    std::getline(data_file, line);
    while(std::getline(data_file, line))
    {
        std::istringstream iss(line);
        std::getline(iss, token1, ',');
        std::getline(iss, token2);
        std::istringstream is(token2);
        is >> f;
        this->_data.insert(std::make_pair(token1, f));
    }
}
