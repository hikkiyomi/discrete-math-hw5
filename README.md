# Discrete Math HW5

Firstly, you should download any compiler (e.g. Clang, GCC, ...)  
To compile the code, use "clang++ {$filename}" or "g++ {$filename}" or etc.  
Then run the built .exe file in the console using "./{$filename}"  
**You might want to use CMake to build .exe files from .cpp. In this case check CMakeLists.txt as well.**

> You can also use online compilers to run code, but they might be slow.  
> _Time Limit Exceptions_ might pop up as well.

Solutions are located in "src" folder.
File "full_code.cpp" contains all the solutions that were written.  
To launch solutions in "full_code.cpp", just call functions "TaskX()" in main function where X is the letter of task.

Example:

```cpp
// Launch tasks here:

TaskJ(); // if you run this function, manually change "countries" array with "countries_for_task_j" array
TaskK(); // same case

TaskB(); // ! you do not want to call this function together with TaskJ or TaskK, because they use different "countries" array
         // ! this is shown for example only

// -----------------
```
