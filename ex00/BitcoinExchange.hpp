#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
    private:
        std::map<std::string, float>    _data;
        std::string                     _date;
        float                           _value;
        char *                          _input_file;
        size_t                          _min_year;
        size_t                          _max_year;
    public:
        BitcoinExchange();
        BitcoinExchange(char *input_file);
        BitcoinExchange(const BitcoinExchange &);
        void operator=(const BitcoinExchange &);
        ~BitcoinExchange();

        void _fillMapData();
        void _executeFile();
        bool check_date() const;
        std::string _token(std::istringstream &);

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
};

#endif