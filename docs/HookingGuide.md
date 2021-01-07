# Hooking Guide
In order to hook a game's function, its address and prototype need to be known. This will allow us to replace the original function with our own function and we can then call the original function again, after we've run our code before it (or after, it doesn't really matter).

## How it works
Before hooking, a new set of memory needs to be allocated since we're going to add new instructions to the game. The free memory will be used to store our hook function.  
Then, we need to replace the original function address with a jump to our own function, so that we can execute our code. Our function should also include a jump back to the original function.

## How to do it
The code for the whole hoook can be written manually, but this requires low level and C++ knoweledge, although it can be replicated from existing hacking guides.  
Alternatively, a library like **Microsoft's Detours** can be used, which will allocate the necessary memory and hook the function all on its own, just by suppling the original function address and the new function's address.

## Can hooking be done with C# or other high level languages?
Hooking can be done with a library such as **MemorySharp** but its usage will depend on what function needs to be hooked. Since Etaine hooks functions which have `char*` buffers as a parameter, the buffer processing needs to be done fast since when another packet arrives, the buffer will change. We can't know for certain if C# hooks will be fast enough to read the buffer before its value changes, since it's relatively a lot slower than C++ code. For this reason, it's better to avoid C# but as mentioned earlier, it will depend on the usage context.