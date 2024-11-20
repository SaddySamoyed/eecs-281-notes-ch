I ran each input file with stack mode, sending the output to a file.
I used the time command and the results are shown below.

NOTE that different machines and compile flags can have significantly
different times!  Don't time code by hand inside of Visual Studio or
Xcode, as these IDEs usually use a debug build rather than one
optimized for speed.

User times:
Big, L input, M output: 0.908s
Big, M input, M output: 0.187s
Big, L input, L output: 0.802s
Big, M input, L output: 0.082s

Small, L input, M output: 0.006s
Small, M input, M output: 0.003s
Small, L input, L output: 0.006s
Small, M input, L output: 0.002s

I also produced the queue mode output files, but didn't time them.
