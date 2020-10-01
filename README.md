# Zyklon

right now I am just following the game engine series and trying to wrap my head

pardon my poor cmake skills and everything else...

The sandbox project uses Zyklon as a dll

## game engine resources
https://github.com/TheCherno/Hazel

watch the game engine series
https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT

## Libraries used
* spdlog
* glad
* glfw
* glm
* imgui
* stb_image
* Debugbreak

### TODO:
[ ] Fix concurrency problem with spdlog logging

[ ] Add Rendering API

[ ] Add clang-format config

Extras for the game engine series

### Initial Setup:

<!-- TODO: 
    Configure setup on specific platform 
 -->

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