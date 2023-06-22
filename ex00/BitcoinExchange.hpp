#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cctype>
#include <string>

class BitcoinExchange
{
    private:
        std::map<std::string, float>    _data;
        std::string                     _date;
        float                           _value;
        char *                          _input_file;
    public:
        BitcoinExchange();
        BitcoinExchange(char *input_file);
        BitcoinExchange(const BitcoinExchange &);
        void operator=(const BitcoinExchange &);
        ~BitcoinExchange();

        void        _fillMapData();
        void        _executeFile();
        void        _check_year(std::string );
        void        _check_mounth(std::string , std::string );
        void        _check_day(std::string token, unsigned int mounth);
        void        check_date() ;
        void        caluclate();
        void        check_date_token();
        std::string is_str_all_digit(std::string token);
        std::string _token(std::istringstream &);
        void        check_value_token(std::string token);

    class FileNotExistException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return ("File Does't Exist");
            }
    };

    class FileContentErrorException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return ("Error in File Content");
            }
    };

    class BadInputException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return ("Error: bad input => ");
            }
    };

    class NotPositiveNumberException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return ("Error: not a positive number.");
            }
    };

    class LargeNumberException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return ("Error: too large a number.");
            }
    };
};

#endif