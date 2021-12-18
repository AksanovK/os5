#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

struct file_sub {
    char path[512];
    char name[50];
    long  size;
};


struct file_sub* sortWith1Type(struct file_sub *file_list)
{
    for(int i = 0 ; i < sizeof(file_list) - 1; i++) { 
       for(int j = 0 ; j < sizeof(file_list) - i - 1 ; j++) {  
           if(file_list[j].size > file_list[j+1].size) {           
              long tmp = file_list[j].size;
              file_list[j].size = file_list[j+1].size ;
              file_list[j+1].size = tmp; 
           }
        }
    }
    return file_list;
}


struct file_sub* sortWith2Type(struct file_sub *file_list)
{
    for(int i = 0 ; i < sizeof(file_list) - 1; i++) { 
       for(int j = 0 ; j < sizeof(file_list) - i - 1 ; j++) {  
           if (strcmp(file_list[j].name, file_list[j+1].name) > 0) {           
              char tmp = file_list[j].name;
              strcpy(file_list[j].name, file_list[j+1].name);
              strcpy(file_list[j+1].name, tmp);
           }
        }
    }
    return file_list;
}


struct file_sub *recursiveReadingDir(char currentDirectory[], char resultDirPath[], int N, struct file_sub *file_list1, int countOfFiles1)
{
    DIR *dir;
    DIR *sDir;
    FILE *file;
    FILE *resultFile;
    int countOfFiles = 0;
    struct file_sub *file_list[1];
    struct file_sub *resultList;
    
    dir = opendir(currentDirectory);
    if (dir != NULL ) {
        struct dirent *d;
        while ( (d = readdir(dir)) != NULL ) {

            if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
                continue;
            }
            
            char newDirPath[512];
            
            snprintf(newDirPath, sizeof newDirPath, "%s%s%s", currentDirectory, "/", d->d_name);
            
            // проверка на каталог
            sDir = opendir(newDirPath);
            if (sDir != NULL ) {
                file_list1 = recursiveReadingDir(newDirPath, resultDirPath, N, file_list1, countOfFiles1);
            }
            if (errno == -1) {
            printf("Ошибка чтения %s", newDirPath);
            return 1;
            }
            if (closedir(dir) != 0) {
            printf("Ошибка закрытия %s", newDirPath);
            return 1;
            }
            
            
            //countOfFiles = countOfFiles + 1;
            countOfFiles = sizeof(file_list1) + 1;
            struct file_sub *new_file_list[countOfFiles];

            for (int i = 0; i < countOfFiles - 1; i++) {
                new_file_list[i] = &file_list1[i];
            }
            
        
            
            // проверка на файл
            file = fopen(newDirPath, "r");
            if (file != NULL) {
                countOfFiles1 = countOfFiles1 + 1;
                // сохранить, вытащив размер и название
                struct stat st;
                stat(newDirPath, &st);
                struct file_sub fSub;
                strcpy(fSub.path, newDirPath);
                strcpy(fSub.name, d->d_name);
                fSub.size = st.st_size;
                new_file_list[countOfFiles] = &fSub;
            }
            if ((fclose(file)) == EOF) {
                printf("Не удалось закрыть файл");
            }
            resultList = new_file_list;
        }
        if (N == 1) {
            resultList = sortWith1Type(resultList);
        } else {
            resultList = sortWith2Type(resultList);
        }
        return resultList;
    }
}


void fileRecording(char filePath, char dirPath, char name) {
    DIR *dir;
    FILE *file1;
    FILE *file2;
    char secondPath[512];
    snprintf(secondPath, sizeof secondPath, "%s%s", dirPath, name);
    file1 = fopen(filePath, "r");
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

int main(int argc, char* argv[])
{
    struct file_sub *listOfFiles;
    DIR *dir1;
    DIR *dir2;
    char *givenDirPath = argv[1];
    int N = strtol(argv[2], NULL, 10);
    char *newDirPath = argv[3];
    struct file_sub *file_list;
    int countOfFiles = 0;
    file_list = recursiveReadingDir(givenDirPath, newDirPath, N, file_list, countOfFiles);
    
    char s;
        int i = 0;
        while (i < sizeof(file_list)) {
            s = strcat(file_list[i].path, " ");
            s = strcat(s, file_list[i].name);
            s = strcat(s, " ");
            printf("%c", s);
            printf("%lld\n", file_list[i].size);
            fileRecording(file_list[i].path, newDirPath, countOfFiles + "");
        }
     // 1 или 2 
    // надо считать все файлы из каталога и из его подкаталогов и сохранить
    // отсортировать все файлы
    // создавать новые файлы в нужном каталоге и записывать туда все из нужного файла
    // вывести полный путь, имя, размер в консоль
    return 0;
}
