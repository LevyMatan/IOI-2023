#include <doctest/doctest.h>
#include <a_plus_b/aplusb.h>
#include <cassert>
#include <cstdio>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

TEST_CASE("A Plus B") {

	int N = 3;
	std::vector<int> A({0, 2, 2});
	std::vector<int> B({3, 5, 6});
	std::vector<int> expected({3, 5, 5});
	std::vector<long long> res = smallest_sums(N, A, B);

	int n = res.size();
	for (int i = 0; i < n; ++i) {
		if (i > 0)
			printf(" ");
		printf("%lld", res[i]);
	}
	printf("\n");
	
	for(int i = 0; i < n; ++i) {
  		CHECK(expected[i] == res[i]);
	}

    // Test that two vectors are equal	
	std::vector<long long> res_effi = smallest_sums_efficient(N, A, B);
	for(int i = 0; i < n; ++i) {
  		CHECK(expected[i] == res_effi[i]);
	}
}

TEST_CASE("A Plus B: long test case") {

	// Generate a random number N between 1 and 1000000
	int N = 1 + (rand() % 10000);

	// Generate two arrays A and B of size N
	std::vector<int> A(N);
	std::vector<int> B(N);

	// Fill A and B with random numbers between 0 and 1000000000
	for (int i = 0; i < N; ++i) {
		A[i] = rand() % 1000000;
		B[i] = rand() % 1000000;
	}

	// Sort A and B
	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());

	// Compute the expected result using the naive algorithm
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<long long> expected = smallest_sums(N, A, B);
	auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "smallest_sums took " << diff.count() << " seconds" << std::endl;

	// Compute the result using the efficient algorithm
	start = std::chrono::high_resolution_clock::now();
	std::vector<long long> res = smallest_sums_efficient(N, A, B);
	end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "smallest_sums_efficient took " << diff.count() << " seconds" << std::endl;

	// Check that the two results are the same
	int n = res.size();
	for(int i = 0; i < n; ++i) {
  		CHECK(expected[i] == res[i]);
	}
}
