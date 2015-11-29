# Assembler + Absolute Loader
5th semester Mini Project

Members : 2

Ashutosh Verma, CS 5A, 2007440

Shubham Gupta, CS 5C, 2007548


Description : 
  This project contains a c language code(addressing.c) which work in a similar manner to the 1-pass & 2-pass 
of a typical SIC machine. We have included features like indexed addressing, program addressing in hexadecimal format, 
line numbers, symtab, optab, opcodes, text record and an absolute loader. Optab(mnemonics and their opcodes) is our own.

  The program takes input in the form of a SIC code. It addresses the SIC program, creates symtab.txt, uses 2D character array 
to store symtab and optab. It further generates intermediate.txt and using this file text record(object_file.txt) is generated.

  Now, an absolute loader plays its role. It shows how the text record will look if the file is loaded into main memory.
  
  
How to compile  : 
  Copy the code from the file addressing.c, paste it into an editor and save with .c extension. Now, copy the SIC program from
new_input.txt, paste this into notepad and save it as new_input.txt

  Now, sit back and watch.  
  
The following files will be generated : 
addressed_file.txt, symtab.txt, intermediate.txt, object_file.txt and loader.txt

Note  : The c code addressing.c & input file new_input.txt should be in the same folder.


Thank you ^_^
