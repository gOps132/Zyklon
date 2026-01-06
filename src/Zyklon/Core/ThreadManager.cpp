#include "ThreadManager.h"
#include "Log.h"

namespace Zyklon {

ThreadManager &ThreadManager::getInstance()
{
	static ThreadManager instance;
	return instance;
}

ThreadManager::ThreadManager()
{
	initializeThreadPool(ThreadType::Asset, 2);
	initializeThreadPool(ThreadType::Audio, 1);
	initializeThreadPool(ThreadType::Physics, 1);
	initializeThreadPool(ThreadType::Network, 2);
}

ThreadManager::~ThreadManager()
{
	shutdown();
}

void ThreadManager::processMainThreadTasks()
{
	std::lock_guard<std::mutex> lock(m_main_thread_mutex);
	while (!m_main_thread_tasks.empty()) {
		m_main_thread_tasks.front()();
		m_main_thread_tasks.pop();
	}
}

void ThreadManager::shutdown()
{
	if (m_shutdown)
		return;

	m_shutdown = true;

	for (auto &[type, pool] : m_thread_pools) {
		{
			std::lock_guard<std::mutex> lock(pool.mutex);
			pool.stop = true;
		}
		pool.condition.notify_all();

		for (auto &worker : pool.workers) {
			if (worker.joinable()) {
				worker.join();
			}
		}
	}

	ZYKLON_CORE_INFO("ThreadManager shutdown complete");
}

ThreadManager::ThreadPool &ThreadManager::getOrCreateThreadPool(ThreadType type)
{
	auto it = m_thread_pools.find(type);
	if (it == m_thread_pools.end()) {
		initializeThreadPool(type, 2);
		it = m_thread_pools.find(type);
	}
	return it->second;
}

void ThreadManager::initializeThreadPool(ThreadType type, size_t thread_count)
{
	auto &pool = m_thread_pools[type];
	pool.workers.reserve(thread_count);

	for (size_t i = 0; i < thread_count; ++i) {
		pool.workers.emplace_back([&pool, type, i]() {
			ZYKLON_CORE_INFO("Started {} thread worker {}", threadTypeToString(type), i);

			while (true) {
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock(pool.mutex);
					pool.condition.wait(lock, [&pool] { return pool.stop || !pool.tasks.empty(); });

					if (pool.stop && pool.tasks.empty())
						break;

					task = std::move(pool.tasks.front());
					pool.tasks.pop();
				}

				task();
			}

			ZYKLON_CORE_INFO("Stopped {} thread worker {}", threadTypeToString(type), i);
		});
	}

	ZYKLON_CORE_INFO("Initialized {} thread pool with {} workers", threadTypeToString(type), thread_count);
}

}