10/01/2020

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

10/03/2020

There is some issues with concerning the gl hheader and the glsl version
support https://stackoverflow.com/questions/11962665/glcreateshader-was-not-declared-in-this-scope

10/09/2020

I am an idiot, the reason my spdlog piece produced a segmentation fault of concurrency error 
(call stack on std::atomic) is because I been accessing the wrong shared_ptr. It took two months
for me to find this :| .

I want the Client project to control the client name of the project. It kinda makes sense right? 

10/11/2020

I shall implement in parsing the shader in the program. Maybe I should implement a C
data structure this time, I could unit test this part.

spdlog include errors, it must have undergon some updates. the cmake file looks more simpler.
Should I tie to the last revision or use the new one?

I deleted
// #include <spdlog/sinks/stdout_color_sinks.h>
// #include <spdlog/sinks/stdout_sinks.h>

I decided to stick to the new revision of spdlog