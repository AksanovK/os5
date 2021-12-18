#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
    FILE *file1;
	FILE *file2;
    char *fPath = "./";
    char *sPath = argv[1];
    char *tPath = argv[2];
    char firstPath[512];
    char secondPath[512];

    snprintf(firstPath, sizeof firstPath, "%s%s", fPath, sPath);
    snprintf(secondPath, sizeof secondPath, "%s%s", fPath, tPath);
    file1 = fopen(firstPath, "r");
    file2 = fopen(secondPath, "w");
    
    if (file1 == NULL) {
        printf("Ошибка открытия первого файла");
        return 1;
    }
    
    if (file2 == NULL) {
        printf("Ошибка открытия второго файла");
        return 1;
    }

    char s;
    while ((s = fgetc(file1)) != EOF) {
        if ((fputc((int) s, file2)) == EOF) {
            printf("Ошибка записи во второй файл");
            return 1;
        }
    }

    if ((fclose(file1)) == EOF) {
        printf("Ошибка закрытия первого файла");
        return 1;
    }
    
    if ((fclose(file2)) == EOF) {
        printf("Ошибка закрытия второго файла");
        return 1;
    }
}