#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

void ls(char dirName[1000]) {
    DIR *d;
    struct dirent *dir;
    d = opendir(dirName);

    if (d == NULL) {
        printf("ls: cannot access %s: No such file or directory", dirName);
        exit(1);
    } else {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_name[0] == '.') {
                continue;
            } else {
                printf("%s \n", dir->d_name);
            }
        }
    }
}

void ls_a(char dirName[1000]) {
    DIR *d;
    struct dirent *dir;
    d = opendir(dirName);

    if (d == NULL) {
        printf("ls: cannot access %s: No such file or directory", dirName);
        exit(1);
    } else {
        while ((dir = readdir(d)) != NULL) {
            printf("%s \n", dir->d_name);
        }
    }
}

void ls_A(char dirName[1000]) {
    DIR *d;
    struct dirent *dir;
    d = opendir(dirName);

    if (d == NULL) {
        printf("ls: cannot access %s: No such file or directory", dirName);
        exit(1);
    } else {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_name[0] == '.') {
                continue;
            } else if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                continue;
            } else {
                printf("%s \n", dir->d_name);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char command[10];
    char dirName[1000];

    strcpy(command, argv[1]);
    strcpy(dirName, argv[2]);

    if (dirName != NULL) {
        if (strcmp(command, "-a") == 0) {
            ls_a(dirName);
        } else if (strcmp(command, "-A") == 0) {
            ls_A(dirName);
        } else {
            ls(dirName);
        }
    } else {
        printf("ls: missing operand");
        exit(1);
    }
}
