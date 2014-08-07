Jake Austin
Comp11 Project 4
ReadMe

The program consists of 4 headers and 4 cpp files

TrigInfoSTR.h    -- header for struct TrigInfo (no cpp file)

TrigVector.h     -- header and cpp for Trigram Vector class
TrigVector.cpp

Language.h       -- header and cpp for Language class
Language.cpp 

Analyzer.h       -- header and cpp for Analyzer class
Analyzer.cpp

proj4main.cpp    -- cpp file for the whole program



It is compiled as:
g++ -g -Wall -Wextra proj4main.cpp TrigVector.cpp Language.cpp Analyzer.cpp


The master file is read in using cin, and has the stamp END after files to read.

Known Bugs: 
in Analyzer.cpp, in function printResults
           -- error for converting double to int (done for percentages)
in Analyzer.cpp, in function readIn (I believe, could be somewhere else)
           -- Cannot read in master file with Unknown as first file listed
in TrigVector.cpp, in function readFile() 
           -- Sometimes misses last word