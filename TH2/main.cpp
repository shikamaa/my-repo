#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class parallel_scheduler {
public:
    parallel_scheduler(size_t capacity) : capacity(capacity), stop(false) {
        for (size_t i = 0; i < capacity; ++i) {
            threads.push_back(std::thread(&parallel_scheduler::worker, this));
        }
    }

    ~parallel_scheduler() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }
    }

    void run(std::function<void()> func) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(func);
        }
        cv.notify_one();
    }

private:
    void worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) return;
                task = tasks.front();
                tasks.pop();
            }
            task();
        }
    }

    size_t capacity;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;
};

void task(int i) {
    std::cout << "Task " << i << " executed\n";
}

int main() {
    parallel_scheduler pool(3);
    for (int i = 0; i < 10; ++i) {
        pool.run([i]() { task(i); });
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
