#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct params {
    char* input_filename;
    char* output_filename;
} params;

void* safeCalloc(int i, int j) {
    void* rb = calloc(i, j);
    if(rb == NULL) {
        perror("Allocazione fallita \n");
        exit(1);
    }
    return rb;
}

params* decodeParameters(int argc, char* argv[]) {
    if(argc != 3) {
        perror("Numero di parametri non valido\n");
        exit(1);
    }
    char* inputCloned = safeCalloc(strlen(argv[1]) + 1, sizeof(char));
    char* outCloned = safeCalloc(strlen(argv[2]) + 1, sizeof(char));
    strcpy(inputCloned, argv[1]);
    strcpy(outCloned, argv[2]);
    char* ext = strrchr(argv[1],'.');
    char* ext1 = strrchr(argv[2],'.');
    if(strcmp(ext, ".txt") != 0 || strcmp(ext1, ".txt") != 0) {
        perror("Illegal file extension\n");
        exit(1);
    }
    params* pam = safeCalloc(1, sizeof(params));
    pam->input_filename = inputCloned;
    pam->output_filename = outCloned;
    return pam;
}

void readHeader(FILE* filePtr, int* n, int* m) {
    char buf[8];
    fgets(buf, sizeof buf, filePtr);
    sscanf(buf, "%d %d ", n, m);
}

double* readFile(FILE* filePtr, int n, int m) {
    double* mat = safeCalloc(n * m, sizeof(double));
    char buf[128];
    int index = 0;
    while (fgets(buf, sizeof buf, filePtr) != NULL) {
        char* token = strtok(buf, " ");
        for(int i = 0; i < n+1; i++) {
            //printf("%s \n", token);
            mat[index++] = atof(token);
            token = strtok(NULL, " ");
        }
    }
    return mat;
}

double getMeanOfRow(double* mat, int n, int m, int row) {
    double sum = 0;
    for(int i = 0; i < m; i++) {
       // printf("Accessing element: %d \n", row * n + i);
        sum += mat[row * m + i];
    }
    return sum / m;
}

double* getArray(double* mat, int n, int m) {
    /*Definisca un array Y di n double e inserisca in Y[i] la media dei valori indicati dai puntatori
nella i-esima riga di X. Ordini, dunque, l’array Y in senso ascendente mediante l’algoritmo
selection sort.*/
    double* arrayY = safeCalloc(n, sizeof(double));
    for(int i = 0; i < n; i++) {
        //printf("Getting mean of row %d\n", i);
        arrayY[i] = getMeanOfRow(mat, n, m, i);
    }
    return arrayY;
}

void selectionSort(double* arrayY, int size) {
//12:49→13:36
    for(int i = 0; i < size; i++) {
        int smallestIndex = i;
        for(int j = i; j < size; j++) {
            if(arrayY[j] < arrayY[smallestIndex]) {
                smallestIndex = j;
            }
        }
        double temp = arrayY[i];
        arrayY[i] = arrayY[smallestIndex];
        arrayY[smallestIndex] = temp;
    }
}

void processX(double* mat, double* arrayY, int n, int m) {
    /*Per ogni riga di X, ponga a NULL tutti puntatori nella riga i-esima che puntino a valori
superiori a Y[i]. Ad esempio, sia X[i][j] il j-esimo elemento della i-esima riga di X. Se
X[i][j]>Y[i], allora X[i][j] dovrà puntare a NULL.*/
    for(int x = 0; x < n; x++) {
        for(int y = 0; y < m; y++) {
            int index = x * m + y;
            if(mat[index] > arrayY[x]) {
                mat[index] = 0;
            }
            //printf(" %f\n", mat[index]);
        }
    }
}

void printMatrix(double* mat, int n, int m, FILE* stream) {
    int index = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[index] == 0.00) {
                fprintf(stream, "%4s ", "*");
            } 
            else {
                fprintf(stream, "%.2f ", mat[index]);
            }
            index++;
        }
        fprintf(stream, "\n");
    }
}

void writeFile(double* mat, int n, int m, char* outputFile) {
    FILE* filePtr = fopen(outputFile, "w");
    if(filePtr == NULL) {
        perror("File non leggibile \n");
        exit(1);
    }
    printMatrix(mat, n, m, filePtr);
    fclose(filePtr);
}

void printArray(double* arrayY, int n) {
    for(int i = 0; i < n; i++) {
        printf("%.2f ", arrayY[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    params* pam = decodeParameters(argc, argv);
    printf("======A Stampa Parametri====== \n");
    printf("input_filename = %s\noutput_filename = %s \n", pam->input_filename, pam->output_filename);
    printf("======B Valori n e m====== \n");
    FILE* filePtr = fopen(pam->input_filename,"r");
    if(filePtr == NULL) {
        perror("File inaccessibile \n");
        exit(1);
    }
    int n,m;
    
    readHeader(filePtr, &n, &m);
    printf("n=%d m=%d\n", n, m);
    printf("======B Matrice X====== \n");
    double* mat = readFile(filePtr, n, m);
    printMatrix(mat, n, m, stdout);
    printf("======C Array Y====== \n"); 
    double* arrayY = getArray(mat, n, m);
    printArray(arrayY, n);
    printf("======C Array Y Ordinato======\n");
    selectionSort(arrayY, n);
    printArray(arrayY,n);
    printf("======D Matrice X modificata====== \n");
    processX(mat, arrayY, n, m);
    printMatrix(mat, n, m, stdout);
    writeFile(mat, n, m, pam->output_filename);

    fclose(filePtr);
    free(arrayY);
    free(mat);
    free(pam->input_filename);
    free(pam->output_filename);
    free(pam);
}