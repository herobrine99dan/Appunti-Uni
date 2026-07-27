clear
echo "Testing file" $1
filename=$1
gcc -Wall -Wextra -g -fsanitize=address,undefined -Wshadow  -Wwrite-strings -Wformat=2 -Wpedantic -Wconversion -o output $1 -lm
./output input.txt output.txt