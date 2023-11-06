This example uses a shared memory object for inter-process communication (IPC).

Shared memory objects are kernel objects representing a block of memory that can be mapped by several processes. These objects are represented as files (usually under /dev/shm), even if they represent a block of memory.

After running the example, delete the shared memory object using rm.

Note that accessing shared memory areas in different processes involves multiple threads, hence requiring synchronization, which is lacking in this example. In real usage, you would need additional kernel objects, like a pthread mutex or a semaphore, to synchronize accesses to shared data.