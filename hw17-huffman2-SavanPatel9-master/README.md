[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/RZ54HnKR)
* Compress Data using Huffman Compression

Learning Goals
==============

* Understand bitwise operations

* Compress data using Huffman codes

Compress Data
=============

Continue from HW16, after you build the compression tree, you have
the codes of the characters. The following is an example


```
A 65 00
m 109 010
# 35 0110
G 71 0111
c 99 10
s 115 11
```

Next, consider the end of an article with the following characters:

`Acss#Gcsm...`

The codes will be (spaces are added between bytes for clarity)

`00101111 01100111 1011010 ...`

The first 8 bits will be the first byte. The next 8 bits will be
another byte.

Please use `xxd -b` to inspect the bits in a binary file.


This assignment gives you the end of an article using the
characters in the compression tree.  This assignment uses only the
end of an article, not the entire article, so that the input is
shorter and debugging may be easier.  You can assume that the article
is actually longer than the given test input.  Your program needs to
compress the characters using bits. If some bits in the last byte are
unused, make the unused bits zero.

Example
=======

This goes through an example completely so that you understand how to solve the problem.

Consider running your program with

* `argv[1]` is HW16's input1

* `argv[2]` is HW17's test1

* `argv[3]` is the name of the output (binary) file

From `argv[1]`, the code book is

```
#:0110
A:00
G:0111
c:10
m:010
s:11
```

The second input file has `#AcGms#Ac`.  From the code book, this is the codes for the data:


Character | #    | A  | c  | G    | m   | s  | #    | A  | c  
----------|------|----|----|------|-----|----|------|----|----
Code      | 0110 | 00 | 10 | 0111 | 010 | 11 | 0110 | 00 | 10

Next, we put 8 bits together into one byte:


`01100010 01110101 10110001 00000000`

That is the output of this program. If you use `xxd -b`, it shows

`00000000: 01100010 01110101 10110001 00000000`



Your Program's Inputs
=====================

Your program will take three files as the input:

* `argv[1]` is the compression tree (same as the input for HW16)

* `argv[2]` is the end of an article in HW17's inputs directory

* `argv[3]` is the name of the output (binary) file

You can assume that the compression tree in `argv[1]` is valid and all
characters in `argv[2]` appear in the compression tree.

Submission
==========

Modify main.c and tree.c

Push the code to repo

Note: You will have to copy inputs from hw16 to pass it as `argv[1]` to your program.  
The Makefile should run program with command `./hw17 input1 test1 output1`  
where `input1` is from hw16's inputs, `test1` is from hw17's inputs.

Note: You have to write your own Makefile to test the program
