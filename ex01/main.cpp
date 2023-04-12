#include "RPN.hpp"

int main(int argc, char **argv)
{
    RPN rpn;

    if(argc == 2)
    {
        rpn.calc(argv[1]);
    }
    else
        std::cout << "Error: Bad Argument" << std::endl;
}