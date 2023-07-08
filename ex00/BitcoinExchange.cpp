#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs)
{
    this->_data = rhs._data;
    this->_date = rhs._date;
    this->_value = rhs._value;
    this->_input_file = rhs._input_file;
    this->_csv_file = rhs._csv_file;
}

void BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    this->_data = rhs._data;
    this->_date = rhs._date;
    this->_value = rhs._value;
    this->_input_file = rhs._input_file;
    this->_csv_file = rhs._csv_file;
}

BitcoinExchange::BitcoinExchange(char *file, char *csv_file): _input_file(file), _csv_file(csv_file)
{
    try
    {
        this->_fillMapData();
        this->_executeFile();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string BitcoinExchange::_token(std::istringstream &iss)
{
    std::string token;

    if(iss.eof())
        throw BadInputException();
    iss >> std::ws;
    if(!std::getline(iss, token, ' '))
        throw BadInputException();
    return (token);
}

std::string BitcoinExchange::is_str_all_digit(std::string token)
{
    for(int i = 0; i < static_cast<int> (token.length()); i++)
    {
        if(!isdigit(token[i]))
            throw BadInputException();
    }
    return (token);
}

void  BitcoinExchange::_check_mounth(std::string token1, std::string token2)
{
    std::istringstream  iss(token1);
    unsigned int        mounth;

    iss >> mounth;
    if(mounth > 12 || mounth < 1)
        throw BadInputException();
    this->_check_day(token2, mounth);
}

void  BitcoinExchange::_check_day(std::string token, unsigned int mounth)
{
    std::istringstream iss(token);
    int day;
    int arr[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    iss >> day;
    if(day < 1 || day > arr[mounth - 1])
        throw BadInputException();
}

void    BitcoinExchange::_check_year(std::string token)
{
    int min_y;
    int year;

    std::string min_year;
    std::istringstream iss_min_year(this->_data.begin()->first);
    std::getline(iss_min_year, min_year, '-');
    std::istringstream is_min_year(min_year);
    std::istringstream is_year(token);

    is_min_year >> min_y;
    is_year >> year;

    if(this->_data.begin()->first > this->_date)
        throw BadInputException();
}

void BitcoinExchange::check_date()
{
    if(this->_date.length() != 10)
        throw BadInputException();
    for(int i = 0; i < static_cast<int> (this->_date.length()); i++)
    {
        if(!std::isdigit(this->_date[i]) && this->_date[i] != '-')
            throw BadInputException();
    }
    if(this->_date[4] != '-' || this->_date[7] != '-')
        throw BadInputException();
    this->_check_year(this->_date.substr(0, 4));
    this->_check_mounth(this->_date.substr(5, 2), this->_date.substr(8, 2));
}

void BitcoinExchange::check_value_token(std::string token)
{
    int dots = 0;
    int i = 0;
    if(token[0] == '-')
        i = 1;
    for(; i < static_cast<int>(token.length()); i++)
    {
        if(!isdigit(token[i]) && token[i] != '.')
            throw BadInputException();
        else if(token[i] == '.')
        {
            dots++;
            if(dots > 1)
                throw BadInputException();
        }
    }
    std::stringstream is(token);
    is >> this->_value;
    if(this->_value < 0)
        throw NotPositiveNumberException();
    else if(this->_value > 1000)
        throw LargeNumberException();
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
        iss >> std::ws;
        if(iss.eof())
            continue ;
        try 
        {
            this->_date =  this->_token(iss);
            check_date();
            if(this->_token(iss) != "|")
                throw BadInputException();
            check_value_token(this->_token(iss));
            if(!iss.eof())
                throw BadInputException();
            this->caluclate();
        }
        catch(const std::exception& e)
        {
            if (const NotPositiveNumberException* npnException = dynamic_cast<const NotPositiveNumberException*>(&e))
                std::cout << e.what() << std::endl;
            else if(const LargeNumberException* npnException = dynamic_cast<const LargeNumberException*>(&e))
                std::cout << e.what() << std::endl;
            else
                std::cout << e.what() << this->_date << std::endl;
        }
    }
}

void    BitcoinExchange::caluclate()
{
    std::map<std::string, float>::iterator iter;
    iter = this->_data.find(this->_date);

    if(iter != this->_data.end())
        std::cout << this->_date << " => " << this->_value << " = " << this->_value * iter->second <<  std::endl;
    else
    {
        iter = this->_data.upper_bound(this->_date);
        if(iter != this->_data.begin())
            iter--;
        std::cout << this->_date << " => " << this->_value << " = " << this->_value * iter->second <<  std::endl;
    }
}

void BitcoinExchange::_fillMapData()
{
    std::ifstream data_file;
    std::string line;
    std::string token1;
    std::string token2;
    float f;
    
    data_file.open(this->_csv_file);
    if(!data_file.is_open())
        throw FileNotExistException();
    std::getline(data_file, line);
    if(line.compare("date,exchange_rate"))
       throw FileContentErrorException();
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