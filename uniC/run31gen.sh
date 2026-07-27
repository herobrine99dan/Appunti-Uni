clear
gcc -Wall -Wextra -g -fsanitize=address,undefined 31gen2024.c -o soluzione
./soluzione input.txt output.txt