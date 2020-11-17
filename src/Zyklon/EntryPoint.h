#ifndef __ENTRYPOINT_H__
#define __ENTRYPOINT_H__

#ifdef ZYKLON_EXPORT

int main(int argc, char **argv)
{
    Zyklon::Log::init("APP");

    ZYKLON_CORE_WARN("Initialized Log");
    ZYKLON_CORE_INFO("Welcome To Zyklon Game Engine");

    auto app = Zyklon::Application::create_application();
    app->run();
    delete app;

    return 1;
}

#endif
#endif // __ENTRYPOINT_H__