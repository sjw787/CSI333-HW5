# CSI333-HW5
For this project students were asked to write a program the compresses and decompresses an input file by reading the input file
one character at a time. When the program encounters runs of characters such as the 'll' in hello during compress mode, it will print the
ascii character that represents the number of repeated characters encountered after the two initial characters. For example, when the
program encounters "hello" the program will print "hell\000o" since '\000' is the ascii character with a value of 0.
When the user uses decompress mode the program will undo the compression that was done to the input file.
1) The usage for this program to compress is './a.out z in.txt out.txt' 
2) The usage for this program to decompress is './a.out d out.txt out2.txt'
After running these two commands in this order out.txt will contain the compressed version of the in.txt file and out2.txt will be
identical to the in.txt file. You can see for yourself by running 'diff in.txt out.txt' to see if there are any differences in the two
files. 
All test files (in.txt, out.txt and out2.txt) are provided
