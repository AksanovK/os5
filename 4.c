#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char *fPath = "./";
    char *sPath = argv[1];
    char path[512];
    int N = strtol(argv[2], NULL, 10);

    snprintf(path, sizeof path, "%s%s", fPath, sPath);
    file = fopen(path, "r");
    if (file == NULL) {
        printf("Не удалось открыть файл");
        return 1;
    }
   
    char c;
    int count = 0;

    while ( (c = getc(file)) != EOF ) {
        if (N != 0 && count == N) {
            getchar();
            count = 0;
        }
        printf("%c", c); 
        if (c == '\n') {
            count++;
        } 
    }

    if ((fclose(file)) == EOF) {
        printf("Не удалось закрыть файл");
        return 1;
    }
    return 0;
}