# Zyklon

right now I am just following the game engine series and trying to wrap my head around it.

Currently scaling it into some serious hobby project.

Some of the other code is implemented by a 14 year old (me).

## Citations
https://github.com/TheCherno/Hazel

Watch the Hazel Game Engine Series!!
https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT

## Libraries used
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

### Initial Setup:

Not tested on windows

```sh
    $ git clone https://github.com/gOps132/Zyklon
    
    $ cd scripts
    $ bash pull.sh

    AND
    
    $ bash build.sh 
```

### NOTE:

This project is made with teh visual studio code IDE.

It's hard to find a way for vscode extension: cmake-tools to run the output executable in the workspace directory where the about to be parsed files are needed, so I made a specific task to run the selected executable at the workspace directory. You need to have the extension cmake-tools installed in vscode tho.

In CLion, you simply have to change the working-directory to the current workspace.

I believe most of the IDE implementations I made is portable, not sure about
windows tho :|

Many thanks to Master Cherno, Jason Turner, Craig Scott and etc. for the amazingly useful content.