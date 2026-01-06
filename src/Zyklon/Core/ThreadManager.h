#ifndef __THREADMANAGER_H__
#define __THREADMANAGER_H__

#include <future>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <vector>
#include <functional>

namespace Zyklon {

enum class ThreadType { Main, Asset, Audio, Physics, Network };

inline const char *threadTypeToString(ThreadType type)
{
	switch (type) {
	case ThreadType::Main:
		return "Main";
	case ThreadType::Asset:
		return "Asset";
	case ThreadType::Audio:
		return "Audio";
	case ThreadType::Physics:
		return "Physics";
	case ThreadType::Network:
		return "Network";
	default:
		return "Unknown";
	}
}

class ThreadManager {
public:
	static ThreadManager &getInstance();

	// Submit task to specific thread pool
	template <typename F>
	auto submitTask(ThreadType type, F &&task) -> std::future<decltype(task())>
	{
		using ReturnType = decltype(task());
		auto promise = std::make_shared<std::promise<ReturnType>>();
		auto future = promise->get_future();

		if (type == ThreadType::Main) {
			std::lock_guard<std::mutex> lock(m_main_thread_mutex);
			m_main_thread_tasks.push([task = std::forward<F>(task), promise]() {
				try {
					if constexpr (std::is_void_v<ReturnType>) {
						task();
						promise->set_value();
					} else {
						promise->set_value(task());
					}
				} catch (...) {
					promise->set_exception(std::current_exception());
				}
			});
		} else {
			auto &pool = getOrCreateThreadPool(type);
			std::lock_guard<std::mutex> lock(pool.mutex);
			pool.tasks.push([task = std::forward<F>(task), promise]() {
				try {
					if constexpr (std::is_void_v<ReturnType>) {
						task();
						promise->set_value();
					} else {
						promise->set_value(task());
					}
				} catch (...) {
					promise->set_exception(std::current_exception());
				}
			});
			pool.condition.notify_one();
		}

		return future;
	}

	// Main thread task execution (called from Application::run())
	void processMainThreadTasks();

	void shutdown();

private:
	ThreadManager();
	~ThreadManager();

	struct ThreadPool {
		std::vector<std::thread> workers;
		std::queue<std::function<void()>> tasks;
		std::mutex mutex;
		std::condition_variable condition;
		bool stop = false;
	};

	ThreadPool &getOrCreateThreadPool(ThreadType type);
	void initializeThreadPool(ThreadType type, size_t thread_count = 2);

	std::unordered_map<ThreadType, ThreadPool> m_thread_pools;
	std::queue<std::function<void()>> m_main_thread_tasks;
	std::mutex m_main_thread_mutex;
	bool m_shutdown = false;
};

} // namespace Zyklon

#endif // __THREADMANAGER_H__