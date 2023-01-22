# Linux code that gives for students a score for their C program assigment
Linux code that evaluates C codes  using provided inputs and expected outputs, generating a pass/fail report in a CSV file.
For using this project- first save the ex1.c and the ex2.c in your Linux environment, than write a config file which caotains on the first line the path to the directory which contains all the students C program files, on the second line a path to the input file and on the third line a path to a the expected output file.
than compile the ex1.c under the name comp.out and after that compile and run the ex2.c with the config file as an argument.
On the end the code will genrate a CVS file which contains all the stidents score (100 if output=expexcted output and 0 if not).
