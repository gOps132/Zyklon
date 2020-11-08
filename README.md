# Zyklon

This project is based on the Hazel Game Engine

right now I am just following the game engine series and trying to wrap my head around it.

Currently trying scaling it into some serious hobby project.


( if the other unfamiliar implemented code is rubbish there is a good chance it's made by 
a 14 year old... )

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

### Initial Setup:

THIS IS NOT TESTED ON WINDOWS

```sh
    $ git clone https://github.com/gOps132/Zyklon
    
    $ cd scripts
    $ bash pull.sh

    AND
    
    $ bash build.sh 
```

### NOTE:

CMake Version <= 3.14

This project is made with the visual studio code IDE.
I made a specific task to run the currently selected executable at the workspace directory using vscode cmake-tools.
As long as you run the executable in the workspace directory, your fine.

I have not used windows in a long time.

Many thanks to Master Cherno, Jason Turner, Craig Scott and etc. for the amazingly useful content.