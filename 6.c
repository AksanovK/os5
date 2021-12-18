#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
    DIR *dir1;
    DIR *dir2;
    char *currentPath = ".";
    char *givenPath = argv[1];
    dir1 = opendir(currentPath);

    if (dir1 == NULL) {
        printf("Ошибка открытия %s", currentPath);
        return 1;
    }

    struct dirent *d;
    while (d = readdir(dir1)) {
        printf("%s\n", d->d_name);
    }

    if (errno == -1) {
        printf("Ошибка чтения %s", currentPath);
        return 1;
    }

    if (closedir(dir1) != 0) {
        printf("Ошибка закрытия %s", currentPath);
        return 1;
    }

    dir2 = opendir(givenPath);
    
    if (dir2 == NULL) {
        printf("Ошибка открытия %s", givenPath);
        return 1;
    }

    struct dirent *d2;
    while (d2 = readdir(dir2)) {
        printf("%s\n", d2->d_name);
    }

    if (errno == -1) {
        printf("Ошибка чтения %s", givenPath);
        return 1;
    } 

    if (closedir(dir2) != 0) {
        printf("Ошибка закрытия %s", givenPath);
        return 1;
    }
    return 0;
}