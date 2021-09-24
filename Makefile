services:
	gcc -Wall -Wextra -pedantic *.c -o services

services_E:
	gcc *.c -o services

gdb_services:
	gcc -g -Wall -Werror -Wextra -pedantic -std=c90 *.c -o services
run:
	./monty
clear_:
	rm -r services
