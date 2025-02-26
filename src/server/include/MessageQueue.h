#pragma once 

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class MessageQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_queue.push(std::move(value));
        cv.notify_one();
    }

    
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(m_mtx);
        if (m_queue.empty()) {
            return std::nullopt;
        }
        T value = std::move(m_queue.front());
        m_queue.pop();
        return value;
    }


    T waitAndPop() {
        std::unique_lock<std::mutex> lock(m_mtx);
        cv.wait(lock, [this] { return !m_queue.empty(); });
        T value = std::move(m_queue.front());
        m_queue.pop();
        return value;
    }


    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mtx);
        return m_queue.empty();
    }


    size_t size() const {
        std::lock_guard<std::mutex> lock(m_mtx);
        return m_queue.size();
    }

private:
    mutable std::mutex m_mtx;
    std::queue<T> m_queue;
    std::condition_variable cv;
};
