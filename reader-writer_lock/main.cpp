#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <chrono>
#include <cassert>
#include "lock.h"
using namespace std::chrono;

class Benchmark {
    using thread_t = std::thread;
    using mutex_t = std::mutex;

    public:
        Benchmark(RWLock& rwlock, int cnt_readers, int cnt_writers) 
            : cnt_readers(cnt_readers), cnt_writers(cnt_writers) {
                this->rwlock = &rwlock;
                nums = std::vector<int>(1000, 0);
                for (int i = 0; i < nums.size(); i++) {
                    nums[i] = i;
                }
            }

        int run(std::string lock_filename) 
        {
            std::ofstream lock_file;
            lock_file.open(lock_filename, std::ios::out);
            std::cout.rdbuf(lock_file.rdbuf());
            std::cout << "read,write" << '\n';

            {
                std::unique_lock<mutex_t> race_lock_guard(race_lock);

                for (int i = 0; i < cnt_readers; i++) {
                    threads.push_back(thread_t([&, i] {this->read(i);}));
                }
                for (int i = 0; i < cnt_writers; i++) {
                    threads.push_back(thread_t([&, i] {this->write(i, i);}));
                }
                all_threads_ready.wait(race_lock_guard);
            }

            auto start = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
            // Start the race 
            race.notify_all();
            for (thread_t &thread : threads) {
                thread.join();
            }
            auto end = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();

            lock_file.close();
            return end - start;
        }
    
    private:
        RWLock* rwlock;
        int cnt_readers;
        int cnt_writers;
        
        std::vector<int> nums;
        std::vector<thread_t> threads;
        mutex_t cout_lock;
        mutex_t race_lock;
        std::condition_variable_any race;
        std::condition_variable all_threads_ready;
        int cnt_threads = 0;

        int read_requests = 0;
        int write_requests = 0;

        void prep_race() {
            std::unique_lock<mutex_t> race_lock_guard(race_lock);
            cnt_threads += 1;
            if (cnt_threads == cnt_readers + cnt_writers) {
                // Notify the benchmark thread that all threads has ready to race.
                all_threads_ready.notify_one();
            }
            else {
                race.wait(race_lock_guard);
            }
        }

        void read(int id)
        {
            prep_race();

            for (int i = 0; i < 100; i++) {
                // auto start = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
                rwlock->RLock();
                // auto end = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
                // auto delay = end - start;
                {
                    std::lock_guard<mutex_t> cout_guard(cout_lock);
                    read_requests += 1;
                    std::cout << read_requests << "," << write_requests << '\n';

                    // std::cout << "Read " << id << " arrive: " << start << '\n';
                    // std::cout << "Read " << id << " start: " << end << '\n';
                    // std::cout << "Read " << id << " delay: " << delay << '\n';
                }

                // Test if the condition nums[idx] + 1 == nums[idx + 1] should always be true
                for (int idx = 0; idx < nums.size() - 1; idx++) {
                    assert(nums[idx] + 1 == nums[idx + 1]);
                }
                rwlock->RUnlock();
            }
        }

        void write(int id, int inc) 
        {
            prep_race();

            for (int i = 0; i < 100; i++) {
                // auto start = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
                rwlock->WLock();
                // auto end = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
                // auto delay = end - start;
                {
                    std::lock_guard<mutex_t> cout_guard(cout_lock);
                    write_requests += 1;
                    std::cout << read_requests << "," << write_requests << '\n';

                    // std::cout << "Write " << id << " arrive: " << start << '\n';
                    // std::cout << "Write " << id << " start: " << end << '\n';
                    // std::cout << "Write " << id << " delay: " << delay << '\n';
                }

                for (int idx = 0; idx < nums.size(); idx++) {
                    nums[idx] = nums[idx] + inc;
                }
                rwlock->WUnlock();
            }
        }
};

int main() 
{
    std::cout.setf(std::ios::unitbuf);

    RPreferLock rprefer_lock;
    WPreferLock wprefer_lock;
    RPreferCondLock rprefer_cond_lock;
    WPreferCondLock wprefer_cond_lock;

    long long rprefer_time = 0, wprefer_time = 0, rprefer_cond_time = 0, wprefer_cond_time = 0;

    std::ofstream runtime_file;
    runtime_file.open("runtime.csv", std::ios::out);
    std::cout.rdbuf(runtime_file.rdbuf());
    std::cout << "rprefer,rprefer_cond,wprefer,wprefer_cond" << '\n';

    for (int i = 0; i < 100; i++) {
        Benchmark rprefer_benchmark(rprefer_lock, 10, 10);
        rprefer_time += rprefer_benchmark.run("rprefer_lock.csv");

        Benchmark wprefer_benchmark(wprefer_lock, 10, 10);
        wprefer_time += wprefer_benchmark.run("wprefer_lock.csv");

        Benchmark rprefer_cond_benchmark(rprefer_cond_lock, 10, 10);
        rprefer_cond_time += rprefer_cond_benchmark.run("rprefer_cond_lock.csv");

        Benchmark wprefer_cond_benchmark(wprefer_cond_lock, 10, 10);
        wprefer_cond_time += wprefer_cond_benchmark.run("wprefer_cond_lock.csv");

        std::cout.rdbuf(runtime_file.rdbuf());
        std::cout << rprefer_time << "," << rprefer_cond_time << "," << wprefer_time << "," << wprefer_cond_time << '\n';
    }
    runtime_file.close();
}