prog0: big_integer.c
	gcc -g -Wall -Wextra -Wwrite-strings -oprog0 big_integer.c

clean:
	rm -f prog0
	rm -f tests.out
