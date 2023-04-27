#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, float>    _data;
        std::string                     _date;
        float                           _value;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &);
        void operator=(const BitcoinExchange &);
        ~BitcoinExchange();
};

#endif