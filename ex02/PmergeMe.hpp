#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>

class PmergeMe
{
    std::vector<int> nums1;
    std::vector<std::pair<int, int>> pairs;
    int unpair;

    public:
    PmergeMe();
    void make_pairs();
    ~PmergeMe();
};

#endif