#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <deque>
#include <sys/time.h>

class PmergeMe
{
    std::vector<int> nums1;
    std::deque<int> nums2;
    

    public:
    PmergeMe();
    PmergeMe(std::vector<int> &nums);
    void make_pairs_vector();
    void make_pairs_deque();
    ~PmergeMe();
};

#endif