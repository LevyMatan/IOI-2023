#include <vector>

std::vector<long long> smallest_sums(int N, std::vector<int> A, std::vector<int> B);

/**
 * @brief smallest_sums_efficient - Given two sorted arrays A and B of size N each.
 * return the first smallest N elements for the sum A[i] + B[j].
 * 
 * Time complexity: O(N)
 * Space complexity: O(N)
 * @param N - Length of A and B
 * @param A - Sorted array of integers
 * @param B - Sorted array of integers
 * @return std::vector<int> 
 */
std::vector<long long> smallest_sums_efficient(int N, std::vector<int> A, std::vector<int> B);