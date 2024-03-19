# CPSC-323-Project-1

Write a lexer from scratch by designing and implementing your FSA that returns the tokens from the simple source code in C/C++/Java/Python in the given file “input_scode.txt”. 
 
• Requirement: You need to design and implement FSA for tokens - identifier and integer, the rest can be written ad-hoc. Otherwise, there will be a deduction of 3 points!

• Requirement: You need to write your REs and draw the FSA for the above required tokens: identifier and integer and put them in a document named as “FSA _mydesign.doc”.

• Requirement: Your executable program, which is supposed to be developed in C/C++/Java/Python, should represent the implementation of your idea. To read and return the subsequent token, use the lexer() method.

• Requirement: Print out the result into two columns, one for tokens and another for lexemes, and save it into a document named as “output” (see an example I/O as below).

• Requirement: You must write a “readme” file to briefly specify documentation & how to setup/run your program if needed.

• Requirement: Your submission must have Five (5) files: the given “input_scode.txt”, your design file, your program file, output file, and a readme file.

 **Note:** Your program should read a file containing the source code of input_scode.txt to generate tokens and write out the results to an output file. Make sure that you print both the tokens, and lexemes.

**Input (source code text):**

                   while (t < upper) s = 22.00;
  
**Output:**
 
                   token                                      lexeme
                   -----------------------------------------------------------
                   keyword                                    while 
                   separator                                      (, )            
                   identifier                                       t, s 
                   operator                                        <, = 
                   integer                                        1 
                   real                                             22.00  
                   punctuation                                   ; 

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

## Team: Rilijin G Carrillo, Francisco Godoy, Anthony Seng

## Instruction to run
Follow the command on the terminal to run:

clang++ lexer.cpp -o lexer

clang++ shell.cpp -o shell

./shell

## lexer.cpp
This file contains the tokens and lexer class, along with some error exception handling. 

## shell.cpp
This is the main file to run. 
Make sure lexer.cpp, shell.cpp, “input_sourcecode.txt” are all in the same folder location otherwise the main file will run an error. 
Running main on shell.cpp will create output.txt with a table of Tokens and corresponding Lexeme in list. May need to install imported modules in shell.cpp before running main.
