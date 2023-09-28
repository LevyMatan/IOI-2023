#include <a_plus_b/aplusb.h>
#include <doctest/doctest.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <map>
#include <random>

/**
 * @brief A function pointer type for the A Plus B function
 *
 */
using APlusBFunction = std::vector<int> (*)(int, std::vector<int>, std::vector<int>);

/**
 * @brief The time_analysis function measures the average running time of a given APlusBFunction
 * function for different input sizes. It returns a std::map that maps input sizes to average
 * running times.
 *
 * @param function: A function pointer to the APlusBFunction function that takes an integer N and
 * two vectors A and B of size N, and returns a vector of int integers.
 * @param MAX_N: The maximum input size to test. The function will test input sizes from 1 to MAX_N
 * in logarithmic steps.
 * @param num_of_iterations: The number of iterations to run for each input size. The function will
 * take the average of the running times over these iterations.
 * @param logarithmic_base: The logarithmic base to use for the input sizes. The function will test
 * input sizes from 1 to MAX_N in logarithmic steps with the given logarithmic base.
 * @return std::map<int, std::chrono::duration<double>>: The function returns a std::map that maps
 * input sizes to average running times. The keys of the map are integers representing the input
 * sizes, and the values are doubles representing the average running times in seconds.
 */
std::map<int, double> time_analysis(APlusBFunction function, int MAX_N, int num_of_iterations,
                                    int logarithmic_base = 10) {
  std::map<int, double> avg_time;
  for (int N = 1; N <= MAX_N; N *= logarithmic_base) {
    std::vector<std::chrono::duration<double>> iteration_duration(num_of_iterations);
    for (int iteration = 0; iteration < num_of_iterations; iteration++) {
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
      std::vector<int> expected = function(N, A, B);
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = end - start;
      iteration_duration[iteration] = diff;
    }
    double sum = 0;
    for (auto duration : iteration_duration) {
      sum += duration.count();
    }
    double average = sum / iteration_duration.size();
    avg_time[N] = average;
  }
  return avg_time;
}

/**
 * @brief Complexity factor computation
 *
 */
using ComplexityFactor = double (*)(int);

double NlogN(int N) {
  if (N < 2) {
    return 1;
  }
  return N * log(N);
}

double N2(int N) {
  if (N < 2) {
    return 1;
  }
  return N * N;
}

double N2logN(int N) {
  if (N < 2) {
    return 1;
  }
  return N * N * log(N);
}
/**
 * @brief The print_complexity_table function prints the results of the time_analysis function in a
 * nice table format and adds the theoretical time complexity.
 *
 * @param avg_time: The results of the time_analysis function.
 * @param complexity_factor: A function pointer to the ComplexityFactor function that takes an
 * integer N and returns the theoretical time complexity of the APlusBFunction function.
 */
void print_complexity_table(std::map<int, double> avg_time, ComplexityFactor complexity_factor) {
  // Print the results in a nice table format and add the theoretical time complexity
  std::cout << "N\t"
            << "avg_time\t"
            << "Measured Complexity Factor"
            << "Theoretical Complexity Factor" << std::endl;
  int last_N = 0;
  double last_time = 1;
  for (auto const& [N, time] : avg_time) {
    std::cout << N << "\t" << time << "\t" << time / last_time << "\t"
              << complexity_factor(N) / complexity_factor(last_N) << std::endl;
    last_N = N;
    last_time = time;
  }
}

TEST_CASE("A Plus B: toy example correctness") {
  int n = 3;
  std::vector<int> A({0, 2, 2});
  std::vector<int> B({3, 5, 6});
  std::vector<int> expected({3, 5, 5});
  std::vector<int> res = smallest_sums(n, A, B);

  for (int i = 0; i < n; ++i) {
    if (i > 0) printf(" ");
    printf("%d", res[i]);
  }
  printf("\n");

  // Test that two vectors are equal
  for (int i = 0; i < n; ++i) {
    CHECK(expected[i] == res[i]);
  }

  // Test that two vectors are equal
  std::vector<int> res_effi = smallest_sums_efficient(n, A, B);
  for (int i = 0; i < n; ++i) {
    CHECK(expected[i] == res_effi[i]);
  }

  // Test that two vectors are equal
  std::vector<int> res_chathelp = smallest_sums_chathelp(n, A, B);
  for (int i = 0; i < n; ++i) {
    CHECK(expected[i] == res_chathelp[i]);
  }
}

TEST_CASE("A Plus B: long test case - Correctness against naive algorithm") {
  // Generate a random number N between 1 and 1000000
  int N = 1 + (rand() % 100);

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
  std::vector<int> expected = smallest_sums(N, A, B);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "smallest_sums took " << diff.count() << " seconds" << std::endl;

  // Compute the result using the efficient algorithm
  start = std::chrono::high_resolution_clock::now();
  std::vector<int> res = smallest_sums_efficient(N, A, B);
  end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  std::cout << "smallest_sums_efficient took " << diff.count() << " seconds" << std::endl;

  // Compute the result using the efficient algorithm
  start = std::chrono::high_resolution_clock::now();
  std::vector<int> res_chathelp = smallest_sums_chathelp(N, A, B);
  end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  std::cout << "smallest_sums_chathelp took " << diff.count() << " seconds" << std::endl;

  // Check that the two results are the same
  for (int i = 0; i < N; ++i) {
    CHECK(expected[i] == res_chathelp[i]);
  }
}

#ifdef TIME_ANALYSIS_TESTS

TEST_CASE("A Plus B: Naive Algorithm, Time Analysis") {
  // Print test name
  std::cout << "A Plus B: Naive Algorithm, Time Analysis" << std::endl;

  // Run the time analysis
  std::map<int, double> avg_time = time_analysis(smallest_sums, 100, 10, 2);

  // Print the results in a nice table format and add the theoretical time complexity
  print_complexity_table(avg_time, N2logN);
}

TEST_CASE("A Plus B: Efficient Algorithm, Time Analysis") {
  // Print test name
  std::cout << "A Plus B: Efficient Algorithm, Time Analysis" << std::endl;

  // Run the time analysis
  std::map<int, double> avg_time = time_analysis(smallest_sums_efficient, 100, 100, 2);

  // Print the results in a nice table format and add the theoretical time complexity
  print_complexity_table(avg_time, N2);
}

TEST_CASE("A Plus B: ChatHelp Algorithm, Time Analysis") {
  // Print test name
  std::cout << "A Plus B: ChatHelp Algorithm, Time Analysis" << std::endl;

  // Run the time analysis
  std::map<int, double> avg_time = time_analysis(smallest_sums_chathelp, 100000, 100, 10);

  // Print the results in a nice table format and add the theoretical time complexity
  print_complexity_table(avg_time, NlogN);
}

#endif  // TIME_ANALYSIS_TESTS