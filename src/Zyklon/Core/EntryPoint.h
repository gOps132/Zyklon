#ifndef __ENTRYPOINT_H__
#define __ENTRYPOINT_H__

#ifdef ZYKLON_EXPORT

int main()
{
	Zyklon::Log::init("APP");

	ZYKLON_CORE_WARN("Initialized Log");
	ZYKLON_CORE_INFO("Welcome To Zyklon Game Engine");

	auto app = Zyklon::Application::createApplication();
	app->run();
	delete app;

	return 1;
}

#endif
#endif // __ENTRYPOINT_H__