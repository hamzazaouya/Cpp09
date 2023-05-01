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

    if(iss.eof())
        throw BadInputException();
    std::getline(iss, token, ' ');
    return (token);
}

void  BitcoinExchange::_check_mounth(std::string &token1, std::string &token2)
{
    std::istringstream  iss(token1);
    unsigned int        mounth;

    iss >> mounth;
    if(mounth > 12 || mounth < 1)
        throw BadInputException();
    this->_check_day(token2, mounth);
}

void  BitcoinExchange::_check_day(std::string &token, unsigned int &mounth)
{
    std::istringstream iss(token);
    int day;
    int arr[] = {31, 28, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    iss >> day;
    if(day < 0 || day > arr[mounth - 1])
        throw BadInputException();
}

void    BitcoinExchange::_check_year(std::string &token)
{
    int max_y;
    int min_y;
    int year;
    std::string max_year;
    std::string min_year;
    std::istringstream iss_max_year(this->_data.rbegin()->first);
    std::istringstream iss_min_year(this->_data.begin()->first);

    std::getline(iss_max_year, max_year, '-');
    std::getline(iss_min_year, min_year, '-');
    std::istringstream is_max_year(max_year);
    std::istringstream is_min_year(min_year);
    std::istringstream is_year(token);

    is_max_year >> max_y;
    is_min_year >> min_y;
    is_year >> year;

    if(year < min_y || year > max_y)
        throw BadInputException();
}

void BitcoinExchange::check_date()
{
    std::string token_year;
    std::string token_mounth;
    std::string token_day;
    std::istringstream iss(this->_date);

    std::getline(iss, token_year, '-');
    this->_check_year(token_year);
    std::getline(iss, token_mounth, '-');
    std::getline(iss, token_day, '-');
    this->_check_mounth(token_mounth, token_day);
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
            check_date();
            if(this->_token(iss) != "|")
                throw BadInputException();
            std::stringstream is(this->_token(iss));
            if(!iss.eof())
                throw BadInputException();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << this->_date << std::endl;
        }
        
    }
}

void BitcoinExchange::_fillMapData()
{
    std::ifstream data_file;
    std::string line;
    std::string token1;
    std::string token2;
    //size_t      year;
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
