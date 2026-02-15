#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

namespace SimpleNet {

class ThreadPool {
public:
	explicit ThreadPool(size_t threads);
	void enqueue(std::function<void()> task);
	~ThreadPool();

private:
	std::vector<std::thread> workers_;
	std::queue<std::function<void()>> tasks_;

	std::mutex mutex_;
	std::condition_variable cv_;
	std::atomic<bool> stop_{false};

	

};

}


