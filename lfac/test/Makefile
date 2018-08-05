all:
	lex test.l
	gcc lex.yy.c -ll -o test.bin
	./test.bin test.txt
	emacs out.txt
