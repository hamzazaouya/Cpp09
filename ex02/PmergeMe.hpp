#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class PmergeMe
{
    std::vector<int> nums1;

    public:
    PmergeMe();
    void make_pairs();
    ~PmergeMe();
};

#endif