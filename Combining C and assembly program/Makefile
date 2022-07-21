start:
	gcc -c A.c
	gcc -c C.c
	nasm -f elf64 B.asm
	gcc -no-pie A.o B.o C.o -o out
	./out