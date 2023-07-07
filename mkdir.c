#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

void _mkdir(char dirName[1000]) {
    int status = mkdir(dirName, 0777);
    if (status == -1) {
        printf("mkdir: cannot create directory %s", dirName);
        exit(1);
    }
}

void mkdir_v(char dirName[1000]) {
    int status = mkdir(dirName, 0777);
    if (status == -1) {
        printf("mkdir: cannot create directory %s", dirName);
        exit(1);
    } else {
        printf("mkdir: created directory %s", dirName);
    }
}

void mkdir_m(char dirName[1000], int mode) {
    int status = mkdir(dirName, mode);
    if (status == -1) {
        printf("mkdir: cannot create directory %s \n", dirName);
        exit(1);
    } else {
        printf("mkdir: created directory %s \n", dirName);
    }
}

int main(int argc, char *argv[]) {
    char command[10];
    char dirName[1000];

    strcpy(command, argv[1]);
    strcpy(dirName, argv[2]);

    if (dirName != NULL) {
        if (strcmp(command, "-v") == 0) {
            _mkdir(dirName);
        } else if (strcmp(command, "-m") == 0) {
            int mode = atoi(argv[3]);
            mkdir_m(dirName, mode);
        } else {
            _mkdir(dirName);
        }
    } else {
        printf("mkdir: missing operand");
        exit(1);
    }
}
