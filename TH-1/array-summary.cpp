#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <sstream>

struct ThreadData {
    const std::vector<int>* array;
    size_t start;
    size_t end;
    long long sum;
};

void* thread_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->sum = 0;
    for (size_t i = data->start; i < data->end; ++i) {
        data->sum += (*data->array)[i];
    }
    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <count_of_elements> <count_of_threads>\n";
        return 1;
    }

    size_t N, M;
    std::stringstream ss1(argv[1]);
    std::stringstream ss2(argv[2]);
    if (!(ss1 >> N) || !(ss2 >> M)) {
        std::cerr << "Invalid input\n<count_of_elements> and <count_of_threads> must be numbers.\n";
        return 1;
    }

    if (N < 1000000) {
        std::cerr << "N must be greater than 1,000,000\n";
        return 1;
    }

    std::vector<int> array(N);
    srand(time(nullptr));
    for (size_t i = 0; i < N; ++i) {
        array[i] = rand();
    }

    clock_t start_single = clock();
    long long total_sum = 0;
    for (size_t i = 0; i < N; ++i) {
        total_sum += array[i];
    }
    clock_t end_single = clock();
    double duration_single = double(end_single - start_single) / CLOCKS_PER_SEC;

    std::vector<pthread_t> threads(M);
    std::vector<ThreadData> thread_data(M);
    size_t chunk_size = N / M;

    clock_t start_multi = clock();
    for (size_t i = 0; i < M; ++i) {
        thread_data[i].array = &array;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == M - 1) ? N : (i + 1) * chunk_size;
        pthread_create(&threads[i], nullptr, thread_sum, &thread_data[i]);
    }

    long long total_sum_threads = 0;
    for (size_t i = 0; i < M; ++i) {
        pthread_join(threads[i], nullptr);
        total_sum_threads += thread_data[i].sum;
    }
    clock_t end_multi = clock();
    double duration_multi = double(end_multi - start_multi) / CLOCKS_PER_SEC;

    std::cout << "Single-thread sum: " << total_sum 
              << "\nTime: " << duration_single << " seconds\n";
    std::cout << "Multi-thread sum: " << total_sum_threads 
              << "\nTime: " << duration_multi << " seconds\n";

    return 0;
}
