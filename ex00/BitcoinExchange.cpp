#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs)
{
    this->_data = rhs._data;
    this->_date = rhs._date;
    this->_value = this->_value;
}

void BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    this->_data = rhs._data;
    this->_date = rhs._date;
    this->_value = this->_value;
}

BitcoinExchange::~BitcoinExchange()
{
    
}