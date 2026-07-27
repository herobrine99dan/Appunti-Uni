#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record {
    char *input_filename;
    char *output_filename;
};

struct coda {
    char *stringa;
    struct coda *nextPtr;
};

struct record decodeParameters(int argc, char *argv[]);
void readFileToQueue(const char *fileName);

int main(int argc, char *argv[]) {
    struct record fileNames = decodeParameters(argc, argv);

    puts("======A Stampa Parametri======");
    // printf("input_filename = %s\noutput_filename = %s", fileNames.input_filename, fileNames.output_filename);
    readFileToQueue(fileNames.input_filename);

    return 0;
}

struct record decodeParameters(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Numero di parametri non valido.");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 1; i < argc; i++) {
        if(!strstr(argv[i], ".txt")) {
            fprintf(stderr, "Estensione dei file di testo non valida.");
            exit(EXIT_FAILURE);
        }

        if(strlen(argv[i]) > 100) {
            fprintf(stderr, "Lunghezza di una delle stringhe non valide.");
            exit(EXIT_FAILURE);
        }
    }

    return (struct record){argv[1], argv[2]};
}

/* /funzione che legge il contenuto del file di input e costruisce la coda Q come
definito nel punto B del testo. */
void readFileToQueue(const char *fileName) {
    FILE *fPtr = fopen(fileName, "r");

    if(fPtr == NULL) {
        fprintf(stderr, "Non e' stato possibile caricare il file.");
        exit(EXIT_FAILURE);
    }

    char buf[51];
    while(fgets(buf, sizeof buf, fPtr) != NULL)
        printf("\"%s\"\n", buf);
 
    if(feof(fPtr))
       puts("End of file reached");

    fclose(fPtr);
}