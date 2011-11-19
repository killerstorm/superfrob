nasm -f elf64 primitives.asm

gcc -o callasm callasm.c primitives.o -lpthread

g++ -O2 -o superfrob superfrob.cpp -lpthread
