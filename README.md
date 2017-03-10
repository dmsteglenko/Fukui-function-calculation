This repository contains source code and binaries for Fukui function calculation program. Fukui functions are reactivity descriptors defined in the framework of Density Functional Theory (DFT). Software implementation corresponds to the way described in the article :     Renato R. Contreras, Patricio Fuentealba, Marcelo Galván, Patricia Pérez.                                            
"A direct evaluation of regional Fukui functions in molecules". Chemical Physics Letters, V. 304, (1999), p. 405-413.

Normally you need to download corresponding binary file (/bin/Win/fukui.exe - for Windows or /bin/Linux/fukui - for Linux).
How to use:
type in command prompt > ./fukui coh2.out     (program works with *.out and *.log files of Gaussian 03 and Gaussian 09)

After program will stop continuing,  current directory should contain coh2.fuk file. This is simple text file and it may be viewed by any text editor.

Note, calculation of Fukui function requires N*(N-1) multiplications and if input file contain large number of basis function it takes a lot of time. The largest file, which had been tested is about 579 Mb and  contain 2471 basis function. This job takes about 16 min of time on core i3 CPU @ 2.4GHz on Windows. Linux version  in few times (7-8 times) faster.  



License: GPL 3.0 
