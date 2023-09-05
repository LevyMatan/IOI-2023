#include "a_plus_b/aplusb.h"

#include <algorithm>

/**
 * @brief smallest_sums - Given two sorted arrays A and B of size N each.
 * return the first smallest N elements for the sum A[i] + B[j].
 * Naive algorithm:
 * We can compute all N^2 sums and sort them in increasing order.
 * Then return the first N elements.
 * Time complexity analysis:
 * Computing all N^2 sums takes O(N^2) time.
 * Sorting N^2 elements takes O(N^2 log(N^2)) = O(N^2 log(N)) time.
 * Returning the first N elements takes O(N) time.
 * Overall time complexity: O(N^2 log(N))
 * Space complexity: O(N^2)
 * @param N - Length of A and B
 * @param A - Sorted array of integers
 * @param B - Sorted array of integers
 * @return std::vector<int>
 * @example N = 3, A = [0, 2, 2], B = [3, 5, 6]
 * The first 3 smallest sums are 0 + 3 = 3, 0 + 5 = 5, 0 + 5 = 5.
 */
std::vector<long long> smallest_sums(int N, std::vector<int> A, std::vector<int> B) {
  std::vector<long long> C_long(N * N);
  std::vector<long long> C(N);

  if (1 == N) {
    C[0] = A[0] + B[0];
    return C;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      C_long[i * N + j] = A[i] + B[j];
    }
  }

  std::sort(C_long.begin(), C_long.end());
  for (int j = 0; j < N; j++) {
    C[j] = C_long[j];
  }
  return C;
}

/**
 * @brief A Plus B
 * Borcsa has two arrays, each of them containing N non-negative integers.
 * The numbers in the first array are A[0],A[1],…,A[N − 1] and the numbers in the second array
 * are B[0],B[1],…,B[N − 1]. The numbers in both arrays are in increasing order, that is,
 * A[0] ≤ A[1] ≤ … ≤ A[N − 1], and
 * B[0] ≤ B[1] ≤ … ≤ B[N − 1].
 * Borcsa really likes arithmetical addition, so for each i from 0 to N − 1 and for each j from 0 to
 * N − 1, inclusive, she computed the sum A[i] + B[j].
 * Let array C contain all N sums computed by Borcsa, sorted in increasing order. Your task is to
 * find the first N values in C.
 *
 * Solving idea:
 * We can use a similar approach as in the previous problem, but we can do it more efficiently.
 * That is, instead of computing all N^2 sums, we can compute only the first N sums.
 * Lets look at the entire C array as a matrix.
 * CC =
 * [A[0]   + B[0], A[0]   + B[1], A[0]   + B[2],..., A[0] + B[N-1]]
 * [A[1]   + B[0], A[1]   + B[1], A[1]   + B[2],..., A[1] + B[N-1]]
 * [A[2]   + B[0], A[2]   + B[1], A[2]   + B[2],..., A[2] + B[N-1]]
 * ...
 * [A[N-1] + B[0], A[N-1] + B[1], A[N-1] + B[2],..., A[N-1] + B[N-1]]
 *
 * The C matrix is sorted in increasing order in both rows and columns.
 * Now we can do a virtual merge of the rows using merge algorithm.
 * Lets assume the last elemnt C[k] = A[i] + B[j].
 * We need to find C[k+1].
 * We know that all element in CC with row <= i and col <= j are already in C.
 * The possible candidates are A[i+1] + B[possible_j] where possible_j < j
 * and A[possible_i] + B[j+1] where possible_i < i.
 * e.g.:
 * A = [0, 2, 2]
 * B = [3, 5, 6]
 * CC = [
 * [3, 5, 6],
 * [5, 7, 8],
 * [5, 7, 8]
 * ]
 * Time complexity: O(N^2)
 * Space complexity: O(N)
 *
 * @param N - Length of A and B
 * @param A - Sorted array of integers
 * @param B - Sorted array of integers
 * @return std::vector<int> - First N values in C
 */
std::vector<long long> smallest_sums_efficient(int N, std::vector<int> A, std::vector<int> B) {
  std::vector<long long> C(N);
  std::vector<int> CC_index(N, 0);
  C[0] = A[0] + B[0];
  CC_index[0]++;
  int k = 1;
  while (k < N) {
    std::vector<int> temp_vector;
    for (int l = 0; l < N; l++) {
      temp_vector.push_back(A[l] + B[CC_index[l]]);
    }
    auto min_it = std::min_element(temp_vector.begin(), temp_vector.end());
    int min_val = *min_it;
    int min_idx = std::distance(temp_vector.begin(), min_it);
    C[k] = min_val;
    k++;
    CC_index[min_idx]++;
  }

  return C;
}