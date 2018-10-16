myshell:myshell.c
	gcc -g -o myshell myshell.c
.PHONY:clean
clean:
	rm -f myshell 
