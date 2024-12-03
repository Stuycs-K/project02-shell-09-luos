.PHONY: compile clean
compile shell: shell.o command.o directory.o
	@gcc -o shell shell.o command.o directory.o
shell.o: shell.c command.h
	@gcc -c shell.c
command.o: command.c directory.h
	@gcc -c command.c
directory.o: directory.c
	@gcc -c directory.c
clean:
	@rm -rf *.o shell
