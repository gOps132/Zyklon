# Zyklon

right now I am just following the game engine series and trying to wrap my head around it.

I dunno, maybe I'll scale it into some serious hobby project :).

## citations
https://github.com/TheCherno/Hazel

watch the Hazel Game Engine Series!!
https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT

## Libraries used
* spdlog
* glad
* glfw
* glm
* imgui
* stb_image
* Debugbreak

## Other Used
* cmake modules from Jason Turners cpp_starter_project
    * https://github.com/lefticus/cpp_starter_project


### TODO:
[ ] Fix concurrency problem with spdlog logging

[ ] Add Rendering API

[ ] Add clang-format config

### Initial Setup:

<!-- TODO: Configure setup on specific platform -->

* Linux
```sh
    $ git clone https://github.com/gOps132/game-engine-demo
    
    $ mugit select main
    $ mugit pull
    $ cd Zyklon
    $ mugit select zyklon
    $ mugit pull

    AND
    
    $ bash build.sh 
```

* MacOS
* Windows

### Note

* Run the bash files to load the cmake cache into vscode's cmake tool extension
and then run it in there. Also works with CLion and etc. You can also use the 
compile_command.json with however you please.

* This cmakelists.txt file will definitely not compile and link correctly in windows  

* prefer to to build with cmake build option -DSPDLOG_ENABLE_PCH=ON

* .vscode cmake args used:
    *   "cmake.configureArgs": [
        "-DSPDLOG_ENABLE_PCH=ON",
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    ]