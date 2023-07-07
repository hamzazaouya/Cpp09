#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(std::vector<int> &nums): nums1(nums), nums2(nums.begin(), nums.end())
{
    struct timeval start_t1,start_t2, end_t1, end_t2;

    std::cout << "Before: ";
    for(int i = 0; i < static_cast<int> (nums1.size()); i++)
        std::cout << this->nums1[i] << " ";
    std::cout << std::endl;

    gettimeofday(&start_t1, NULL);
    this->make_pairs_vector();
    gettimeofday(&end_t1, NULL);
    std::cout << "After:  ";
    for(int i = 0 ; i < static_cast<int> (this->nums1.size()); i++)
        std::cout << this->nums1[i] << " ";
    std::cout << std::endl;
    gettimeofday(&start_t2, NULL);
    this->make_pairs_deque();
    gettimeofday(&end_t2, NULL);
    std::cout<<"Time to process a range of " <<" elements with std::deque : "\
        << static_cast<float>(((end_t1.tv_sec - start_t1.tv_sec) / 1000000.0) \
        + end_t1.tv_usec - start_t1.tv_usec) <<" us "<<std::endl;
    std::cout<<"Time to process a range of " <<" elements with std::deque : "\
        << static_cast<float>(((end_t2.tv_sec - start_t2.tv_sec) / 1000000.0) \
        + end_t2.tv_usec - start_t2.tv_usec) <<" us "<<std::endl;
}

void PmergeMe::make_pairs_vector()
{
    std::vector<std::pair<int, int> > pairs;
    int unpair = -1;
    if (this->nums1.size() % 2)
    {
        unpair = *this->nums1.rbegin();
        this->nums1.pop_back();
    }
    for(int i = 0; i < static_cast<int>(this->nums1.size()); i+=2)
    {
        std::pair<int, int> tmp_pair(this->nums1[i], this->nums1[i + 1]);
        if (tmp_pair.first > tmp_pair.second)
            std::swap(tmp_pair.first, tmp_pair.second);
        pairs.push_back(tmp_pair);
    }
    std::sort(pairs.begin(), pairs.end());
    this->nums1.clear();
    for(int i = 0; i < static_cast<int>(pairs.size()); i++)
        this->nums1.push_back(pairs[i].first);
    for(int i = 0; i < static_cast<int>(pairs.size()); i++)
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

void PmergeMe::make_pairs_deque()
{

    std::vector<std::pair<int, int> > pairs;
    int unpair = -1;
    if (this->nums2.size() % 2)
    {
        unpair = *this->nums2.rbegin();
        this->nums2.pop_back();
    }
    for(int i = 0; i < static_cast<int>(this->nums2.size()); i+=2)
    {
        std::pair<int, int> tmp_pair(this->nums2[i], this->nums2[i + 1]);
        if (tmp_pair.first > tmp_pair.second)
            std::swap(tmp_pair.first, tmp_pair.second);
        pairs.push_back(tmp_pair);
    }
    std::sort(pairs.begin(), pairs.end());
    this->nums2.clear();
    for(int i = 0; i < static_cast<int>(pairs.size()); i++)
        this->nums2.push_back(pairs[i].first);
    for(int i = 0; i < static_cast<int>(pairs.size()); i++)
    {
        std::deque<int>::iterator itr = std::upper_bound(this->nums2.begin(), this->nums2.end(), pairs[i].second);
        this->nums2.insert(itr, pairs[i].second);
    }
    if (unpair != -1)
    {
        std::deque<int>::iterator itr = std::upper_bound(this->nums2.begin(), this->nums2.end(), unpair);
        this->nums2.insert(itr, unpair);
    }
}

PmergeMe::~PmergeMe() {}