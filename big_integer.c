/*
 *  CSE202: Big Integer Manipulation Program
 *  Steven Kravitz
 *  swk324@lehigh.edu
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// big_integer structure
struct two_quadwords{
  unsigned long lsq;
  long msq;
};
// big_integer typedef
typedef struct two_quadwords big_integer;

// Union to store big integers as 16 characters or two quadwords
union value{
  big_integer binary;
  char hex[16];
};

// Prototypes of the methods to manipulate big integers


//parses the arguements and decides which functions to execute on the program
int parseArgs(int argc, char* argv[], union value *u1, union value *u2, unsigned *k);

//returns the integer value of hexidecimal characters
int hexToDec(char hex);

// reads a big integer from string input and stores it in the union v
// returns 0 if the hexadecimal number is invalid, 1 otherwise
int read_big_integer(union value *v, char *input);

// writes the value of b to standard output as 32 hex characters
void write_big_integer(union value b);

// performs b1 & b2 and stores the result in b1_and_b2
void and_big_integers(big_integer b1, big_integer b2,
                      big_integer *b1_and_b2);

// performs b1 | b2 and stores the result in b1_or_b2
void or_big_integers(big_integer b1, big_integer b2,
                    big_integer *b1_or_b2);

// performs b1 ^ b2 and stores the result in b1_xor_b2
void xor_big_integers(big_integer b1, big_integer b2,
                      big_integer *b1_xor_b2);

// performs ~b and stores the result in b
void not_big_integer(big_integer *b);

// performs b << k and stores the result in b
void shift_big_integer_left(big_integer *b, unsigned k);

// performs b >> k and stores the result in b
void shift_big_integer_right(big_integer *b, unsigned k);

// performs b1+b2 and stores the result in sum
// returns 1 if overflow occurs, 0 otherwise
int add_big_integers(big_integer b1, big_integer b2, big_integer *sum);

// prints the message and value followed by the program usage message
void print_usage(const char *message, const char* value);

// main method
int main(int argc, char* argv[]){ 
	union value u1; 	//stores the main union
	union value u2; 	//will only be used for and, or, xor, and add
	union value result; //will only be used for and, or, xor, and add
	unsigned k;			//will only be used for shift left and shift right
	int overflow;		//used to store value of whether or not addition overflowed
	int operation = parseArgs(argc, argv, &u1, &u2, &k);
	switch(operation){
		case 1: //not
			fprintf(stdout, "~ ");
			write_big_integer(u1);
			fprintf(stdout, " = ");
			not_big_integer(&u1.binary);
			write_big_integer(u1);
			break;
		case 2: //and
			write_big_integer(u1);
			fprintf(stdout, " &\n");
			write_big_integer(u2);
			fprintf(stdout, " =\n");
			and_big_integers(u1.binary, u2.binary, &result.binary);
			write_big_integer(result);
			break;
		case 3: //or
			write_big_integer(u1);
			fprintf(stdout, " |\n");
			write_big_integer(u2);
			fprintf(stdout, " =\n");
			or_big_integers(u1.binary, u2.binary, &result.binary);
			write_big_integer(result);
			break;
		case 4: //xor
			write_big_integer(u1);
			fprintf(stdout, " ^\n");
			write_big_integer(u2);
			fprintf(stdout, " =\n");
			xor_big_integers(u1.binary, u2.binary, &result.binary);
			write_big_integer(result);
			break;
		case 5: //shift left
			write_big_integer(u1);
			fprintf(stdout, " << %i = ", k);
			shift_big_integer_left(&u1.binary, k);
			write_big_integer(u1);
			break;
		case 6: //shift right
			write_big_integer(u1);
			fprintf(stdout, " >> %i = ", k);
			shift_big_integer_right(&u1.binary, k);
			write_big_integer(u1);
			break;
		case 7: //add
			write_big_integer(u1);
			fprintf(stdout, " +\n");
			write_big_integer(u2);
			fprintf(stdout, " =\n");
			overflow = add_big_integers(u1.binary, u2.binary, &result.binary);
			write_big_integer(result);
			if(overflow){
				fprintf(stdout, " - Overflow");
			}
			break;
	}
	fprintf(stdout, "\n");
	return 0;
}

//checks to make sure that there is the correct number of args and checks to make sure the operation argument is valid
//returns a value representing which function is to be called
//invalid arguements return 0
//not returns 1
//and returns 2
//or returns 3
//xor returns 4
//shift left returns 5
//shift right returns 6
//add returns 7
int parseArgs(int argc, char* argv[], union value *u1, union value *u2, unsigned *k){
	int rc = 1;
	if(argc < 3 || argc > 4){//checks if incorrect num of arguments
    	print_usage("Too many or too few arguments", "");
    	return 0;
	}
	if(argc == 3){ // NOT operation (3 arguments)
		if(strcmp(argv[1], "not") == 0){ // check if operation is 'not'
			rc = 1;
    	}
		else{
			print_usage("Invalid operation:", argv[1]);
			return 0;
		}
	}
	if(argc == 4){ //and, or, xor, sl, sr, add operations (4 arguments)
		if(strcmp(argv[1], "and") == 0){
			rc = 2;
		}
		else if(strcmp(argv[1], "or") == 0){
			rc = 3;
		}
		else if(strcmp(argv[1], "xor") == 0){
			rc = 4;
		}
		else if(strcmp(argv[1], "sl") == 0){
			rc = 5;
		}
		else if(strcmp(argv[1], "sr") == 0){
			rc = 6;
		}
		else if(strcmp(argv[1], "add") == 0){
			rc = 7;
		}
		else{
			print_usage("Invalid operation:", argv[1]);
			return 0;
		}
	}
	switch(rc){
		case 1:	
			if(read_big_integer(u1, argv[2]) == 0){
				print_usage("Invalid input:", argv[2]);
				return 0;
			}
			else{
			}
			break;
		case 2:
		case 3:
		case 4:
		case 7:
			if(read_big_integer(u1, argv[2]) == 0){
				print_usage("Invalid input", argv[2]);
				return 0;
			}
			else if(read_big_integer(u2, argv[3]) == 0){
				print_usage("Invalid input", argv[3]);
				return 0;
			}
			else{
			}
			break;
		case 5:
		case 6:
			if(read_big_integer(u1, argv[3]) == 0){
				print_usage("Invalid input", argv[3]);
				return 0;
			}	
			else{
				*k = (unsigned)atoi(argv[2]);
			}
			break;
	}
	return rc;
}

//returns the integer value of hexidecimal characters
int hexToDec(char hex){
	switch (hex){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': case 'a': return 10;
		case 'B': case 'b': return 11;
		case 'C': case 'c': return 12;
		case 'D': case 'd': return 13;
		case 'E': case 'e': return 14;
		case 'F': case 'f': return 15;
		default: return -1;
	}
}

// reads 32 hex characters
// returns 0 if the hexadecimal number is invalid, 1 otherwise
int read_big_integer(union value *v, char *input){
	int j = 0;
	if(strlen(input) != 32){
		return 0;
	}
	for(int i = 15; i >= 0; i--){ 
		char temp1 = hexToDec(input[j++]);
		char temp2 = hexToDec(input[j++]);
		if((temp1 == -1) || (temp2 == -1)){
			return 0;
		}
		v->hex[i] = temp1 << 4 | temp2;
	}
	return 1;
}

// writes the 32 hex characters b to standard output
void write_big_integer(union value b){	
	for(int i = 15; i >= 0; i--){
		fprintf(stdout, "%02x", (unsigned char)b.hex[i]);
	}
}

// performs b1 & b2 and stores the result in b1_and_b2
void and_big_integers(big_integer b1, big_integer b2,
                      big_integer *b1_and_b2){
	b1_and_b2->lsq = b1.lsq & b2.lsq;
	b1_and_b2->msq = b1.msq & b2.lsq;
}

// performs b1 | b2 and stores the result in b1_or_b2
void or_big_integers(big_integer b1, big_integer b2,
                    big_integer *b1_or_b2){
	b1_or_b2->lsq = b1.lsq | b2.lsq;
	b1_or_b2->msq = b1.msq | b2.msq;
}

// performs b1 ^ b2 and stores the result in b1_xor_b2
void xor_big_integers(big_integer b1, big_integer b2,
                      big_integer *b1_xor_b2){
	b1_xor_b2->lsq = b1.lsq ^ b2.lsq;
	b1_xor_b2->msq = b1.msq ^ b2.msq;
}

// performs ~b and stores the result in b
void not_big_integer(big_integer *b){
	b->lsq = ~b->lsq;
	b->msq = ~b->msq;
}

// performs b << k and stores the result in b
void shift_big_integer_left(big_integer *b, unsigned k){
	if(k > 64){
		b->msq = b->lsq << (k - 64);
		b->lsq = 0;
	}
	else{
		b->msq = (b->msq << k) | (b->lsq >> (64 - k));
		b->lsq = b->lsq << k;
	}
}

// performs b >> k and stores the result in b
void shift_big_integer_right(big_integer *b, unsigned k){
	if(k > 64){
		b->lsq = b->msq >> (k - 64);
		if(b->msq < 0) {	
			b->msq = b->msq >> k;
		}
		else{
			b->msq = 0;
		}
	}
	else{
		b->lsq = (b->lsq >> k) | (b->msq << (64 - k));
		b->msq = b->msq >> k;
	}
}

// performs b1+b2 and stores the result in sum
// returns 1 if overflow occurs, 0 otherwise
int add_big_integers(big_integer b1, big_integer b2, big_integer *sum){
	int rc = 0;
	sum->lsq = b1.lsq + b2.lsq;
	sum->msq = b1.msq + b2.msq;
	if(sum->lsq < b1.lsq || sum->lsq < b2.lsq){//the lsq has carry out since it is less than both of the addends
		sum->msq++;	
	}
	if((b1.msq > 0 && b2.msq > 0 && sum->msq < 0) || (b1.msq < 0 && b2.msq < 0 && sum->msq > 0)){//overflow since the sign of the sum is not equal to the sign of either of the addends
		rc = 1;
	}
	return rc;
	//todo
	//if the sum is less than b1 or less than b2, there has been overflow
}

// prints the message and value followed by the program usage message
void print_usage(const char *message, const char* value){
	if(!strcmp(value, "")){
		fprintf(stdout, "%s", message);
	}
	else{
		fprintf(stdout, "%s '%s'", message, value);
	}
	fprintf(stdout,
		"\nUsage:"
		"\n        ./prog0 op [k] number1 [number2]"
		"\n                op: operation from {not, sl, sr, and, or, xor, add}"
		"\n                k: shift positions for operations 'sl' and 'sr'"
		"\n                number1: operand in hex for unary operations 'not', 'sl', 'sr'"
		"\n                or first operand in hex for binary operations 'and', 'or', 'xor', 'add'"
		"\n                number2: second operand in hex for binary operations");
}
