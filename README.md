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
[/] Make custom debugging library

[ ] Add Rendering API

[ ] Add clang-tidy config
    - cpp version

Extras for the game engine series

### Initial Setup:

```sh
    # $ git clone https://github.com/gOps132/game-engine-demo game-engine-demo --recursive
    
    # $ mugit select zyklon
    # $ mugit pull
```
    AND
    
```sh
    $ bash build.sh 
```
### Note

* Run the bash files to load the cmake cache into vscode's cmake tool extension
and then run it in there. Also works with CLion and etc. You can also use the 
compile_command.json with however you please.

* Run the bash file everytime you change it.

* Right now the only graphics API that I use is openGL, eventually when I have time,
I will add other Graphics API support that is fit on multiple platforms. Right now
Imgui does not need abstracting since it's platform independent, which means it supports
multiple graphics API's as well.

* This cmakelists.txt file will definitely not compile and link correctly in windows  

* Planning to switch to mugit. More information -- https://www.youtube.com/watch?v=UulEctX0z4I