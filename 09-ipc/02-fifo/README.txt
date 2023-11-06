This example uses a named pipe (also known as fifo) for inter-process communication (IPC).

Named pipes are pipes that can be reached using a file name. They appear in the file system with file type 'p'. To create a named pipe use the system function mkfifo or the command line utility with the same name. This example expects you to create the named pipe in advance using the mkfifo command.

Just like pipes, although you may create solutions using named pipes in half-duplex mode, it is more common to just treat them as unidirectional and use multiple pipes when bidirectional communication is needed.