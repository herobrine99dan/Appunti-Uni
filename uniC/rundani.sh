clear
gcc -Wall -Wextra -g -fsanitize=address,undefined -Wshadow  -Wwrite-strings -Wformat=2 -Wpedantic -Wconversion -o output dani.c -lm
./output parole.txt a.txt
