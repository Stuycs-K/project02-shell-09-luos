.PHONY: compile clean
compile shell: shell.o commands.o files.o
	@gcc -o shell shell.o commands.o files.o
shell.o: shell.c commands.h
	@gcc -c shell.c
commands.o: commands.c files.h
	@gcc -c commands.c
files.o: files.c
	@gcc -c files.c
clean:
	@rm -rf *.o shell test.txt
