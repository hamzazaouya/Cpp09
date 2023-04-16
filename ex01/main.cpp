#include "RPN.hpp"

int main(int argc, char **argv)
{
    RPN rpn;

    if(argc == 2)
    {
        try
        {
            rpn.calc(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else
        std::cout << "Error: Bad Argument" << std::endl;
}