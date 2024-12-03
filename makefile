.PHONY: compile clean
compile shell: shell.o command.o
	@gcc -o shell shell.o command.o
shell.o: shell.c command.h
	@gcc -c shell.c
command.o: command.c
	@gcc -c command.c
clean:
	@rm -rf *.o shell
