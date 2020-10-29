## 10/01/2020

Im thinking about reworking the "solution"
it's too messy to have 2 project working at once
for me I just want one Zyklon directory with an examples directory
for the sandbox

20:32

I am also having doubts on the mugit tool that I am using, it seems
that it's just some extra overhead, most modules that I am using seems to
be on branch master, and everytime that I mugit pull the module does not 
checkout on the specified branch which seems like a joke, because that's the
purpose of the tool in the first place.

## 10/03/2020

There is some issues with concerning the gl hheader and the glsl version
support https://stackoverflow.com/questions/11962665/glcreateshader-was-not-declared-in-this-scope

## 10/09/2020

I am an idiot, the reason my spdlog piece produced a segmentation fault of concurrency error 
(call stack on std::atomic) is because I been accessing the wrong shared_ptr. It took two months
for me to find this :| .

I want the Client project to control the client name of the project. It kinda makes sense right? 

## 10/11/2020

I shall implement in parsing the shader in the program. Maybe I should implement a C
data structure this time, I could unit test this part.

spdlog include errors, it must have undergon some updates. the cmake file looks more simpler.
Should I tie to the last revision or use the new one?

I deleted
// #include <spdlog/sinks/stdout_color_sinks.h>
// #include <spdlog/sinks/stdout_sinks.h>

I decided to stick to the new revision of spdlog

## 10/13/2020

I am thinking on moving the entrypoint for the client to handle, since I really want the client to
be more explictt, altough the entrypoint is a part of the game engine, maybe I could have some wrappers
like

Zyklon::Start(callback fn for d)

since I am talking about explicit code, I also want every copy constructor to explicit, since 
I don't want any accidental copying and that sucks for performance.

## 10/15/2020

The only issue regarding clang format is changing the order of the macros, or more specificcally, include
macros.

I think I had made a mistake in using mugit instead of git, it requires the client who is using the engine to install a python cli called mugit and it's quite a hastle, I think it's much better, if you have the normal git repository and a bash file to checkout to a specific repository. I believe that is
more portable because this zyklon project that I have is sort of a static library.

It seems that I have to redo the renderer soon, the structure of the renderer is good enough

I abstracted away the graphics context

I am having some thoughts about reshaping the engine API with callbacks, this method seems more verbose and has
more oppurtunity for optimizations. :|

## 10/23/2020 

Added the same stdlib shader parser code from the opengl series.

trying to abstract the vertex buffer layout myself, most of ht ecode is already implememnted in the
opengl series, the problem is how to abstract the properly. MAybe I'll overlook this when I get started
with vulkan.

I do not think that the vertex array interface is going to be graphics API agnostic

## 10/26/2020

I should remember that I need to think about the target_include_directories visibility.

why can't we just make the application::create_application function static? I'm sure master Cherno 
has some good reason.

I am planning to switch the naming conventions into c style naming conventions so it's much more consistent.

## 10/27/2020

Continued with the buffer layouts. I really need to think on tricks on saving memory and less allocations.
Like using more efficient data, structures, compile time computations, pmr.

I have to make more snse of this gaen engine first before I advance to that.

I am noticing so many problems in terms of memory in this code.

Take in mind, most of these code are implemented by Master Cherno. I am still analyzing and understanding some parts (especially the bloody event system). I get imposter syndrom even though I thouroughly understand the code, because I keep 
reminding myself that I didn't write it. Even the blocks that I wrote seems to be copied in my eyes. Is this
normal? 
I'm sad now...

I'm planning to add some unit testing. note for this later.

## 10/28/2020

Great, I fixed the relative directory problem in vscode, which is finding files from the project root
directory. I solved this using a simple tasks.json running sandbox in the root directory, puttin
binaries in the bin directory is not a bad decision after all. This means, I don't have to use the 
vscode debugger along with the cmake tools to change the binary executable at the workspaceFolder, 
this oonly works at debugging mode.

run custom tasks with
    ctrl + shift + b

However there are some setbacks. I can't use ctrl + f7 to run using the vscode cmake tools normally
anymore. Instead I need to build first then use ctrl + shift + b to run a custom task. It's not that a big deal tho, it's just a
bit annoying.

## 10/29/2020

Added more cleaner task on running a cmake target on the workspaceFolder

My naming convention is really confusing.

I felt like I disliked the current code. I felt like that there are so many things that
are factored out in terms of performance and the naming conventions, the bloody naming
conventions it's just not consistent.

I might need to rework the whole code base.

I won't worry, things will get better soon.

Finally, found out how to not sort the macros when formatting code with clang-format.
There is literally an option called SortIncludes, I just set it to false.

There are a lot of problems with commit lately mostly because the commits are really vague, so
drafted a simple solution. Every small change I make a small frequent commit, with the "fc" or the 
"frequent_commit" prefix.