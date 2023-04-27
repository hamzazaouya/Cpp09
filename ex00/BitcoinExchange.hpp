#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>

class BitcoinExchange
{
    private:

        std::map<std::string, float>    _data;
        std::string                     _date;
        float                           _value;
        char *                          _input_file;

        void _fillMapData();
    public:
        BitcoinExchange();
        BitcoinExchange(char *input_file);

    class FileNotExistException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return ("File Does't Exist");
            }
    };
};

#endif