#include <vector>

std::vector<int> smallest_sums(int N, std::vector<int> A, std::vector<int> B);

/**
 * @brief smallest_sums_efficient - Given two sorted arrays A and B of size N each.
 * return the first smallest N elements for the sum A[i] + B[j].
 *
 * Time complexity: O(N)
 * Space complexity: O(N)
 * @param N Length of A and B
 * @param A Sorted array of integers
 * @param B Sorted array of integers
 * @return std::vector<int>
 */
std::vector<int> smallest_sums_efficient(int N, std::vector<int> A, std::vector<int> B);

/**
 * Computes the sum of the smallest i+1 pairs of elements from A and B, for i = 0 to N-1.
 *
 * @param N The length of the input vectors A and B.
 * @param A The first input vector of length N.
 * @param B The second input vector of length N.
 * @return A vector C of length N, where C[i] is the sum of the smallest i+1 pairs of elements from
 * A and B.
 */
std::vector<int> smallest_sums_chathelp(int N, std::vector<int> A, std::vector<int> B);