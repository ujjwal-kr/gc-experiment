# gc-experiment

Ok and?

https://www.cs.odu.edu/~zeil/cs330/f13/Public/garbageCollection/garbageCollection-htmlsu5.html

## This is not cool

Collecting garbage was never the point. The algorithm is pretty simple, it marks and sweeps the objects added after marking. The main aim is to know when to run the GC, what to mark, and how to allocate memory or free it. How to scan the stack to find pointers to the heap? How to effectively use the freed space in the next malloc? A lot of questions to be answered. I never read the glibc malloc or free implementation, and I am not gonna read it.
