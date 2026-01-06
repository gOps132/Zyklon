#ifndef __TASK_H__
#define __TASK_H__

#include "ThreadManager.h"

#include <future>
#include <functional>
#include <string>

namespace Zyklon {

template <typename T> class Task {
public:
	Task(const std::string &name, std::function<T()> work)
		: m_name(name), m_work(std::move(work))
	{
	}

	std::future<T> execute(ThreadType thread_type)
	{
		ZYKLON_CORE_INFO("Tasks '{0}' queued {1} thread", m_name,
						 threadTypeToString(thread_type));

		auto promise = std::make_shared<std::promise<T>>();
		auto future = promise->get_future();

		ThreadManager::getInstance().submitTask(thread_type, [this, promise]() {
			try {
				ZYKLON_CORE_INFO("Task '{0}' started", m_name);
				auto result = m_work();
				promise->set_value(result);
				ZYKLON_CORE_INFO("Task '{0} completed successfully", m_name);
			}
			catch (const std::exception &e) {
				ZYKLON_CORE_ERROR("Task '{0}' failed: {1}", m_name, e.what());
				promise->set_exception(std::current_exception());
			}
		});

		return future;
	}

private:
	std::string m_name;
	std::function<T()> m_work;
};

} // namespace Zyklon

#endif // __TASK_H__