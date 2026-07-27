clear
gcc -Wall -Wextra -g -fsanitize=address -o soluzione 27-06-2023.c
./soluzione out.bin 4 < input.txt