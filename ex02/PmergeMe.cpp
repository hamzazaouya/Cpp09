#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

void PmergeMe::make_pairs()
{
    std::vector<std::pair<int, int>> pairs;
    int unpair = -1;
    if (this->nums1.size() % 2)
    {
        unpair = *this->nums1.rbegin();
        this->nums1.pop_back();
    }
    for(int i = 0; i < (int)this->nums1.size(); i+=2)
    {
        std::pair<int, int> tpair = {this->nums1[i], this->nums1[i + 1]};
        if (tpair.first > tpair.second)
            std::swap(tpair.first, tpair.second);
        pairs.push_back(tpair);
    }
    std::sort(pairs.begin(), pairs.end());
    this->nums1.clear();
    for(int i = 0; i < (int) pairs.size(); i++)
        this->nums1.push_back(pairs[i].first);
    for(int i = 0; i < (int) pairs.size(); i++)
    {
        std::vector<int>::iterator itr = std::upper_bound(this->nums1.begin(), this->nums1.end(), pairs[i].second);
        this->nums1.insert(itr, pairs[i].second);
    }
    if (unpair != -1)
    {
        std::vector<int>::iterator itr = std::upper_bound(this->nums1.begin(), this->nums1.end(), unpair);
        this->nums1.insert(itr, unpair);
    }
}

PmergeMe::~PmergeMe()
{

}