all:
	lex ex1.l
	gcc lex.yy.c -ll -o ex1.bin
	./ex1.bin ex1.txt
	emacs out.txt
