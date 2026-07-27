clear
gcc -Wall -Wextra -g -fsanitize=address,undefined 24sept2024.c -o soluzione
./soluzione input.text output.output