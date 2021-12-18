#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main (int argc, char * argv[]) {
FILE *file;
char *firstPartPath = "./";
char *secondPartPath = argv[1];
char path[512];
snprintf(path, sizeof path, "%s%s", firstPartPath, secondPartPath);

char currentSymbol = ' ';
file = fopen(path, "w");

if (file == NULL) {
printf("Не удалось найти файл");
return 0;
}

while (true) {
scanf(" %s", &currentSymbol);

if (strcmp(&currentSymbol, "*") == 0) {
break;
}

if ((fputc((int) currentSymbol, file)) == EOF) {
printf("Не удается записать символ в файл");
return 0;
}
}

if ((fclose(file)) == EOF) {
printf("Не удалось закрыть файл");
return 0;
}
return 0;
}