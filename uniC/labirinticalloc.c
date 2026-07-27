#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void printLabyrinth(int rows, int columns, char *labyrinth)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (labyrinth[i * rows + j] == 'S')
            {
                printf(ANSI_COLOR_GREEN "%c " ANSI_COLOR_RESET, labyrinth[i * rows + j]);
            }
            else if (labyrinth[i * rows + j] == 'X')
            {
                printf(ANSI_COLOR_CYAN "%c " ANSI_COLOR_RESET, labyrinth[i * rows + j]);
            }
            else
            {
                printf("%c ", labyrinth[i * rows + j]);
            }
        }
        printf("\n");
    }
}

void shuffleDirections(int dirs[4][2])
{
    for (int q = 0; q < 4; q++)
    {
        for (int i = 0; i < 4; i++)
        {
            int newIndex = rand() % 4;
            int temp[] = {dirs[i][0], dirs[i][1]};
            dirs[i][0] = dirs[newIndex][0];
            dirs[i][1] = dirs[newIndex][1];
            dirs[newIndex][0] = temp[0];
            dirs[newIndex][1] = temp[1];
        }
    }
}

void generateMaze(int rows, int columns, char *labyrinth, int x, int y)
{
    labyrinth[x * rows + y] = '.';
    int directions[4][2] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}};
    shuffleDirections(directions);
    for (int i = 0; i < 4; i++)
    {
        int newX = x + directions[i][0] * 2;
        int newY = y + directions[i][1] * 2;
        if (newX > 0 && newX < rows && newY > 0 && newY < columns)
        {
            if (labyrinth[newX * rows + newY] == '#')
            {
                labyrinth[(newX - directions[i][0]) * rows + newY - directions[i][1]] = '.';
                generateMaze(rows, columns, labyrinth, newX, newY);
            }
        }
    }
}

void putExit(int rows, int columns, char *labyrinth)
{
    while (1)
    {
        int y = rand() % columns;
        if (labyrinth[y * rows + rows - 2] == '.')
        {
            labyrinth[y * rows + rows - 1] = '.';
            return;
        }
    }
}

void initializeLabyrinth(int rows, int columns, char *labyrinth)
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            labyrinth[y * rows + x] = '#';
        }
    }
}

int mazeTraverse(int rows, int columns, char *labyrinth, int x, int y)
{
    // Safety checks
    if (x < 0 || y < 0)
    {
        return 0;
    }
    if (x > rows - 1 || y > columns - 1)
    {
        return 0;
    }
    char cell = labyrinth[x * rows + y];
    if (cell != 'X' && cell != '#')
    {
        printf("Visiting cell %d,%d \n", x, y);
        labyrinth[x * rows + y] = 'X';
        // Set current cell as visited
        if (y == columns - 1)
        { // We are on the edge, and the cell is a path block, surely it is the exit
            printf("Exit found at: %d, %d \n", x, y);
            labyrinth[x * rows + y] = 'S';
            return 1;
        }

        printf("Updating labyrinth \n");
        printf("---------------------\n");
        printLabyrinth(rows, columns, labyrinth);
        // Visit adjacent cells
        if (mazeTraverse(rows, columns, labyrinth, x, y - 1) || mazeTraverse(rows, columns, labyrinth, x, y + 1) ||
            mazeTraverse(rows, columns, labyrinth, x + 1, y) || mazeTraverse(rows, columns, labyrinth, x - 1, y))
        {
            labyrinth[x * rows + y] = 'S';
            // printf("Cell in the stack: %d, %d \n", x, y);
            return 1;
        }
    }
    return 0;
}

int main()
{
    srand((long)time(NULL));
    int rows, columns;
    printf("Type rows and columns separated by a comma, Ex: 12,8 \n");
    scanf(" %d,%d", &rows, &columns);
    // Sono equivalenti, tranne che calloc inizializza a zero i valori della memoria
    char *labyrinth = (char *)calloc(rows * columns, sizeof(char));
    // char *labyrinth = (char *) malloc(rows * columns * sizeof(char)); //equivalente, però non inizializza
    printf("initializing labyrinth \n");
    perror("Miao");
    initializeLabyrinth(rows, columns, labyrinth);
    printf("generating \n");
    generateMaze(rows, columns, labyrinth, 2, 0);
    putExit(rows, columns, labyrinth);
    mazeTraverse(rows, columns, labyrinth, 2, 0);
    printLabyrinth(rows, columns, labyrinth);
    free(labyrinth);
}
