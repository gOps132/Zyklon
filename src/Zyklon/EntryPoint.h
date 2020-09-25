#ifndef __ENTRYPOINT_H__
#define __ENTRYPOINT_H__

/*
 * The entrypoint will change overtime
 * Only for use for zyklon client applications 
 */

#ifdef ZYKLON_EXPORT

extern Zyklon::Application *CreateApplication();

int main(int argc, char **argv)
{
    Zyklon::Log::init();
    ZYKLON_CORE_WARN("Initialized Log");
    ZYKLON_CORE_INFO("Welcome To Zyklon Game Engine");

    auto app = Zyklon::CreateApplication();
    app->Run();
    delete app;

    return 1;
}

#endif
#endif // __ENTRYPOINT_H__