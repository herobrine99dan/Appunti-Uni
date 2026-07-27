clear
echo "Testing file" $1
filename=$1
gcc -Wall -Wextra -g -fsanitize=address,undefined -Wshadow  -Wwrite-strings -Wformat=2 -Wpedantic -o output $1 -lm
./output input.bin output.txt
