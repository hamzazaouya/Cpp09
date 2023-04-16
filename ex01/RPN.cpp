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
            if(nums.size() <= 1)
                throw ErrorException();
            n1 = nums.top();
            nums.pop();
            n2 = nums.top();
            nums.pop();
            switch (str[i])
            {
                case '+':
                    nums.push(n2 + n1);
                    break;
                case '-':
                    nums.push(n2 - n1);
                    break;
                case '*':
                    nums.push(n2 * n1);
                    break;
                case '/':
                    nums.push(n2 / n1);
                    break;
            }
        }
        else if(str[i] != ' ')
           throw ErrorException();
        i++;
    }
    if(nums.size() > 1)
        throw  ErrorException();
    std::cout << nums.top() << std::endl;
}