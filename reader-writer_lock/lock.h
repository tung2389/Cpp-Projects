#ifndef LOCK_H
#define LOCK_H

#include <mutex>
#include <condition_variable>

class RWLock {
    public:
        virtual void RLock() = 0;
        virtual void RUnlock() = 0; 
        virtual void WLock() = 0;
        virtual void WUnlock() = 0;
};

class RPreferLock : public RWLock {
    using mutex_t = std::mutex;

    public:
        void RLock() {
            std::lock_guard<mutex_t> lock(read_lock);
            cnt_readers += 1;
            if (cnt_readers == 1) {
                write_lock.lock();
            }
        }

        void RUnlock() {
            std::lock_guard<mutex_t> lock(read_lock);
            cnt_readers -= 1;
            if (cnt_readers == 0) {
                write_lock.unlock();
            }
        }

        void WLock() {
            write_lock.lock();
        }

        void WUnlock() {
            write_lock.unlock();
        }

    private:
        int cnt_readers = 0;
        mutex_t read_lock;
        mutex_t write_lock;
};

class WPreferLock : public RWLock {
    using mutex_t = std::mutex;

    public:
        void RLock() {
            std::lock_guard<mutex_t> g1(only_one_reader_try_lock);
            {
                std::lock_guard<mutex_t> g2(read_lock);
                {
                    std::lock_guard<mutex_t> g3(cnt_readers_lock);
                    cnt_readers += 1;
                    if (cnt_readers == 1) {
                        write_lock.lock();
                    }
                }
            }
        }

        void RUnlock() {
            std::lock_guard<mutex_t> g1(cnt_readers_lock);
            cnt_readers -= 1;
            if (cnt_readers == 0) {
                write_lock.unlock();
            }
        }

        void WLock() {
            {
                std::lock_guard<mutex_t> g1(cnt_writers_lock);
                cnt_writers += 1;
                if (cnt_writers == 1) {
                    read_lock.lock();
                }
            }
            write_lock.lock();
        }

        void WUnlock() {
            write_lock.unlock();
            std::lock_guard<mutex_t> g1(cnt_writers_lock);
            cnt_writers -= 1;
            if (cnt_writers == 0) {
                read_lock.unlock();
            }
        }

    private:
        int cnt_readers = 0;
        int cnt_writers = 0;
        mutex_t only_one_reader_try_lock;
        mutex_t read_lock;
        mutex_t cnt_readers_lock;
        mutex_t cnt_writers_lock;
        mutex_t write_lock;
};


class RPreferCondLock : public RWLock {
    using mutex_t = std::mutex;
    using cond_t = std::condition_variable_any;

    public:
        void RLock() {
            std::lock_guard<mutex_t> lock(mutex);
            cnt_readers += 1;
        }

        void RUnlock() {
            std::lock_guard<mutex_t> lock(mutex);
            cnt_readers -= 1;
            if (cnt_readers == 0) {
                writer_wait.notify_one();
            }
        }

        void WLock() {
            mutex.lock();
            while (cnt_readers > 0) {
                writer_wait.wait(mutex);
            }
        }

        void WUnlock() {
            /*
            This line is critical to avoid deadlock. 
            Suppose that more than one writers are waiting for some readers, so all of them wait.
            Once one of writer are wake up, complete its work and call unlock. Now if there's no more reader,
            and we don't notify other writer, other writers will wait forever. 
            */
            writer_wait.notify_one();
            mutex.unlock();
        }

    private:
        int cnt_readers = 0;
        mutex_t mutex;
        cond_t writer_wait;
};

class WPreferCondLock : public RWLock {
    using mutex_t = std::mutex;
    using cond_t = std::condition_variable_any;

    public:
        void RLock() {
            mutex.lock();
            while (waiting_writers > 0 || writer_active) {
                reader_wait.wait(mutex);
            }
            /* This line is critical to prioritize writers first */
            active_readers += 1;
            mutex.unlock();
        }

        void RUnlock() {
            mutex.lock();
            active_readers -= 1;
            if (active_readers == 0) {
                writer_wait.notify_one();
            }
            mutex.unlock();
        }

        void WLock() {
            mutex.lock();
            waiting_writers += 1;
            while (writer_active || active_readers > 0) {
                writer_wait.wait(mutex);
            }
            writer_active = true;
            waiting_writers -= 1;
            mutex.unlock();
        }

        void WUnlock() {
            mutex.lock();
            if (waiting_writers == 0) {
                reader_wait.notify_all();
            }
            else {
                writer_wait.notify_one();
            }
            writer_active = false;
            mutex.unlock();
        }

    private:
        int active_readers = 0;
        int waiting_writers = 0;
        bool writer_active = false;
        mutex_t mutex;
        cond_t writer_wait;
        cond_t reader_wait;
};

#endif