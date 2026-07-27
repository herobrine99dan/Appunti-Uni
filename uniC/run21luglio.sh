clear
gcc -Wall -Wextra -g -Werror -fsanitize=address,undefined 21luglio2025.c -o soluzione
./soluzione parole.txt risultato.txt