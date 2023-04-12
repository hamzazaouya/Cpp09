#include "RPN.hpp"

void RPN::calc(char *str)
{
    std::stack<int> nums;
    int n1, n2;

    int i = 0;
    while(str[i])
    {
    
        if(str[i] >= '0' && str[i] <= '9')
            nums.push(str[i] - '0');
        else if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            n1 = nums.top();
            nums.pop();
            n2 = nums.top();
            nums.pop();
            if(str[i] == '+')
                nums.push(n2 + n1);
            else if(str[i] == '-')
                nums.push(n2 - n1);
            else if(str[i] == '*')
                nums.push(n2 * n1);
            else
                nums.push(n2 / n1);
        }
        else if(str[i] != ' ')
        {
            std::cerr << "Invalid caracter" << std::endl;
            exit(0);
        }
        i++;
    }
    std::cout << nums.top() << std::endl;
}