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

I made a specific task to run the currently selected executable at the workspace directory using vscode cmake-tools.

VScode tasks are made to facilitate running the project in the workspace directory

Many thanks to Master Cherno, Jason Turner, Craig Scott and etc. for the amazingly useful content.``

### Naming Convention

- classes, structs and enums: PascalCase

- methods and functions: camelCase

- properties and variables: snake_case

### TODOS:

[ ] Add an object system with default primitivess
[ ] Add a physics system
[ ] Code base for platform and graphics API'S is getting kinda big so refractor those into its
	own directory
[ ] Add uniform optimizations to openGL API