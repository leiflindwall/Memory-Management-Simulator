# 351-Project-2
Memory Management Simulator

Group Members:

Michael Lindwall michaellindwall@csu.fullerton.edu

Alexander Lavrov alavrov@csu.fullerton.edu

Marc Liander Reyes mlcr@csu.fullerton.edu

Trung Ngo ndtrung95@csu.fullerton.edu

Instructions:

This project was written in C++ and is meant to be run in a UNIX-style command line terminal that supports GCC, Makefiles.

Type "make" in a terminal window in the folder that contains the code to compile the programs.

The Makefile will automatically run the executable, immediately prompting the user to enter the memory size.
Then the user will enter the page size as 1 digit, and will be asked for a workload file.  For testing, this was
"in1.txt".  The output of the simulation will be printed to the terminal.

To break out of the program in the terminal, press "CTRL-C".

To remove compiled object files, type "make clean" in the directory containing the files.

Team Collaboration: 

We first began by thinking of how we should approach designing the simulator. Alexander and Michael met before class one day and drew up the design document.  Then Michael wrote the basic structures and logic for the simulator to get the project started.  Through Github, Marc and Trung fixed issues with the code that were causing off-by-one errors and incorrect output.
Once the major issues were worked out, it was just a matter of fixing small issues with the output and testing the different input cases.

Extra Credit: N/A

Special Notes: N/A
