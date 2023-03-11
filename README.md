# Core_Interpreter

Jiyong Kwag

Submitting files:

1. core.h: containing the core keyword, symbols and others of the language
2. executor.c: contains the executable C file that execute the parseTree into executable program.
3. executor.h: cotains the header files for executro.c
4. main.c: run the whole program
5. memory.c: cotains the data structure of the program. It handles the variable names and their values into array of integer variables and record array.
6. memory.h: header file for memory.c
7. parser.c: Recieving the file name from the main and processing the parsing with scanner
8. parser.h: header file for parser.c
9. scanner.c: Recieving the file name from the main and processing the tokenizing the program
10. scanner.h: header file for parser.c
11. tree.h: testing the parser
12. Readme.Md

Any Special Feature:

In the project, I created functions that can check the stored integer values and records values with their name. If it is not initialized array, then function does not print anything. This feature enables me to check the values easily without go deeper into debug.

Description:

In this project, we are asked build the executable program that run the parTree based on the given regular grammar. Overall, like parse.c, it recursivley went down into the tree to retrieve all the declared variables and stores into memory.c Then, using these variales initialize the value and process the mathemtical functions. Furthermore, in the project, we designed some error features, like uninialized error or array index out of range. Especially, in the memory.c I used the similar data structure that professor gave up. I used the two dimensional arrays to keep track of the integer variable and record varaibles. Then, I used anther single array to keep track of values of integer variables. Then, for the record varaible I used another two dimensional arrays that stores that array of each record varaibles. 

Testing:

At first, I created simple test cases using the each of non-terminals in the given regular grammar, for exmaple 1-1-1-1 and out(3) to test small cases. In this project, I have not see any known bugs.