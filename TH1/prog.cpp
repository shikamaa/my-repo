#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>

long long sum_array(const std::vector<int>& array, size_t start, size_t count) {
    long long sum = 0;
    for (size_t i = start; i < start + count; ++i) {
        sum += array[i];
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <N> <M>\n";
        return 1;
    }

    size_t N = std::stoul(argv[1]);
    size_t M = std::stoul(argv[2]);

    std::vector<int> array(N);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (size_t i = 0; i < N; ++i) {
        array[i] = std::rand() % 100 + 1;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    long long single_sum = sum_array(array, 0, N);
    auto single_duration = std::chrono::high_resolution_clock::now() - start_time;

    std::cout << "Time spent without threads: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(single_duration).count() << " ms\n";

    size_t chunk_size = N / M;
    std::vector<std::thread> threads(M);
    std::vector<long long> results(M, 0);

    start_time = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < M; ++i) {
        size_t start = i * chunk_size;
        size_t count = (i == M - 1) ? (N - start) : chunk_size;
        threads[i] = std::thread([&results, &array, i, start, count]() {
            results[i] = sum_array(array, start, count);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    long long parallel_sum = 0;
    for (long long result : results) {
        parallel_sum += result;
    }

    auto multi_duration = std::chrono::high_resolution_clock::now() - start_time;

    std::cout << "Time spent with " << M << " threads: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(multi_duration).count() << " ms\n";

    return 0;
}
