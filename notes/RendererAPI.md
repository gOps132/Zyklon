09/30/2020
Started adding developement notes to Zyklon

21:08
Watching the Chernos video on abstracting the graphics API the part of the whole Context of this is
to abstract the implementations on rendering with a specific graphics API, yeah this is kind of trivial
but reading the API documentation works, the trivial part of the Abstraction is to have it implement on 
runtime or implement a specific graphics API on compile time. 

PROS
|Compilation|Runtime|
|---|---|
|oppurtunity for optimizaition|Actual support for multiple APIs in one executable|
||Easier debugging opportunities like profiling and testing the performance on each graphics implementation|

CONS
|Compilation|Runtime|
|---|---|
|only supports one specific API In that binary|Miss out on compile time optimization|

10/01/2020

Renderer API design

10/02/2020

The renderer API is gonna be a very large part of the codebase
there are tons of things to decide a rendering API mostly where
the processing should be done in, the CPU or the GPU.