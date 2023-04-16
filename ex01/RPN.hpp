#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
    public:
        RPN(){}
        void calc(char *);
        ~RPN(){}
    class ErrorException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return ("Error");
            }
    };
};

#endif