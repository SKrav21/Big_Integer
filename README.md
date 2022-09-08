# CSE202-Big-Integer-SP2022
Big-Integer: A programming exercise to create a new type for big integers (128 bits), store, access and manipulate big integers using bit-level and arithmetic operations

# Learning Objectives
1) Create a programmer-defined data type for big integers represented on 128 bits using C structures

2) Define a function to read a string from the standard input and store it in memory as two quadruple words (128 bits) using C unions for the little endian order

3) Define six functions for bitwise operations to manipulate big integers as two quadruple words (not, and, or, xor, shift left, and shift right)

4) Define a function to add two big integers on 128 bits using the integer addition on 64 bits

5) Define a function to output the binary representation of a big integer from memory to the standard output using unions


# Instructions
Write a C program named big_integer.c to accept two or three command-line arguments as listed below:
1. An operation from the set {"not", "and", "or", "xor", "sl", "sr", "add"}
2. 32 hex characters (most significant on the left) for the first operand of the operation, or
3. An unsigned integer for the number of positions for the shift operations only
4. Another 32 hex characters for the second operand of the binary operations only
The 32 hex characters (one or two depending on the operation) should be stored in 16 adjacent bytes in memory that represent the big integer type (128 bits) using a union.

Here are examples of the program runs:

1. "not" operation
$> ./prog0 not ffffffffffffffffffffffffffffffff  

~ ffffffffffffffffffffffffffffffff = 00000000000000000000000000000000


2. shift left operation
$> ./prog0 sl 25 ffffffffffffffffffffffffffffffff  

ffffffffffffffffffffffffffffffff << 25 = fffffffffffffffffffffffff2000000

3. shift right operation
$> ./prog0 sr 12 ffffffffffffffffffffffffffff000  

fffffffffffffffffffffffffffff000 >> 12 = ffffffffffffffffffffffffffffffff

4. and operation
$> ./prog0 and ffffffffffffffffffffffffffffffff  0000ffffffffffffffffffff00000000

ffffffffffffffffffffffffffffffff &
0000ffffffffffffffffffff00000000 =
0000ffffffffffffffffffff00000000

5. or operation
$> ./prog0 or ffffffffffffffffffffffffffffffff  0000ffffffffffffffffffff00000000

ffffffffffffffffffffffffffffffff |
0000ffffffffffffffffffff00000000 =
ffffffffffffffffffffffffffffffff

6. xor operation
$> ./prog0 xor ffffffffffffffffffffffffffffffff  0000ffffffffffffffffffff00000000

ffffffffffffffffffffffffffffffff ^
0000ffffffffffffffffffff00000000 =
ffff00000000000000000000ffffffff

7. add operation
$> ./prog0 add ffffffffffffffffffffffffffffffff  0000ffffffffffffffffffff00000000

ffffffffffffffffffffffffffffffff +
0000ffffffffffffffffffff00000000 =
0000fffffffffffffffffffeffffffff

8. Input error (invalid operand, not hexadecimal)
$> ./prog0 not ffff111122223333444455556666777g

Invalid input
Usage:
        ./prog0 op [k] number1 [number2]
        op: operation from {not, sl, sr, and, or, xor, add}
        k: shift positions for operations 'sl' and 'sr'
        number1: operand in hex for unary operations 'not', 'sl', 'sr'
                or first operand in hex for binary operations 'and', 'or', 'xor', 'add', 'sub'
        number2: second operand in hex for binary operations only

9. Input error (invalid operation)
$> ./prog0 sub ffffffffffffffffffffffffffffffff  0000ffffffffffffffffffff00000000

Invalid operation 'sub'
Usage:
        ./prog0 op [k] number1 [number2]
        op: operation from {not, sl, sr, and, or, xor, add}
        k: shift positions for operations 'sl' and 'sr'
        number1: operand in hex for unary operations 'not', 'sl', 'sr'
         or first operand in hex for binary operations 'and', 'or', 'xor', 'add', 'sub'
        number2: second operand in hex for binary operations only

# Approach
1) After verifying the input is valid, read the input 32 hex characters into the union's 16 character array. Do not forget to consider "Little Endian" for the system you are compiling and running on. You want to be able to access those same 16 bytes of the character array as a big integer (two quadwords).

2) After storing the hex digits, you will perform the operation and store the result in a big integer type variable.

3) Print the operation, its operands, and the result as shown in the examples above.


# Important Notes
1) The case of the input hex characters can be uppercase, lowercase, or mixed case.

2) You can place as many or as few whitespace characters between your output fields as whitespace will be ignored when comparing your program's output with the reference output.

3) You can use any case for any letters in your output as the case of the letters are ignored when comparing your program's output with the reference output.

4) You MUST use the structure and the union typedef provided in the big_integer.c starter file.

5) You are NOT allowed to use any library functions or other programs to directly perform operations on big integers. Use the operations &, |, ^, <<, >>, or + on the type long.

6) Remember that the right shift operation extends the sign bit for signed operands

7) The add operation of the two most significant quadwords should consider the carry out from adding the two least significant quadwords and displays a message when an overflow occurs

8) Do NOT modify the makefile, tests.in, tests.cases, or runTests.sh files... only modify the big_integer.c file.

9) Refer to the Programming Assignment Grading Rubric on Coursesite to maximize your score.

10) To submit your code for grading, simply perform a "git push"; which will upload your changes to GitHub Classroom and run the auto-grader. You may continue to push changes until you are informed "All tests passed" or the deadline published on Coursesite.

11) Post any questions on Piazza.
