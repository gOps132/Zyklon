# Zyklon

This project is based on the Hazel Game Engine

right now I am just following the game engine series and trying to wrap my head around it.

Currently trying scaling it into some serious hobby project.

## Citations

### Mostly implemented

https://github.com/TheCherno/Hazel

Watch the Hazel Game Engine Series
https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT

Watch the OpenGL Series
https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2


### Libraries used
* spdlog
* glad
* glfw
* glm
* imgui
* stb_image
* Debugbreak

### Other Used
* cmake modules from Jason Turners cpp_starter_project
    * https://github.com/lefticus/cpp_starter_project

### Initial Setup (Terminal):

NOT TESTED ON WINDOWS

```sh
    $ git clone https://github.com/gOps132/Zyklon
    
    $ cd scripts
    $ bash pull.sh

    AND
    
    $ bash build.sh 
```

### Initial Setup (VSCode):

```sh
    $ git clone https://github.com/gOps132/Zyklon
    
    $ cd Zyklon
    $ code .
    
    // Build root CMakefile
    shortcut: cmd + shift + b
    // click on "Build_And_Run_Selected_CMake_Target"
```

### NOTE:

CMake Version <= 3.14

This project is made with the visual studio code IDE in a Unix machine.

I made a specific task to run the currently selected executable at the workspace directory using vscode cmake-tools.

Make sure to run the executable at the workspace directory.

Not guranteed to work on windows, I don't even know what batch files are.

Many thanks to Master Cherno, Jason Turner, Craig Scott and etc. for the amazingly useful content.