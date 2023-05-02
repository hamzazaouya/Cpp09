#include "PmergeMe.hpp"


int main(int argc, char **argv)
{
    int              num;
    std::vector<int> nums;

    for(int i = 1; i < argc; i++)
    {
        {
            std::string token(argv[i]);
            std::istringstream iss(token);
            iss >> num;
            nums.push_back(num);
        }
    }
    PmergeMe pmg(nums);
}