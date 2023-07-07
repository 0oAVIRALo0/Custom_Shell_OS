#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void _rm(char fileName[1000]) {
    int status = unlink(fileName);
    printf("sts: %d \n", status);
    if (status == -1) {
        printf("rm: cannot remove %s", fileName);
        exit(1);
    }
}

void rm_v(char fileName[1000]) {
    int status = unlink(fileName);
    if (status == -1) {
        printf("rm: cannot remove %s", fileName);
        exit(1);
    } else {
        printf("rm: removed %s", fileName);
    }
}

void rm_i(char fileName[1000]) {
    char c;
    printf("rm: remove %s?(y/n) ", fileName);
    scanf("%c", &c);
    if (c == 'y') {
        int status = unlink(fileName);
        if (status == -1) {
            printf("rm: cannot remove %s", fileName);
            exit(1);
        } else {
            printf("rm: removed %s", fileName);
        }
    } else {
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    char command[100];
    char fileName[1000];

    strcpy(command, argv[1]);
    strcpy(fileName, argv[2]);

    if (fileName != NULL) {
        if (strcmp(command, "-v") == 0) {
            rm_v(fileName);
        } else if (strcmp(command, "-i") == 0) {
            rm_i(fileName);
        } else {
            _rm(fileName);
        }
    } else {
        printf("rm: missing operand");
        exit(1);
    }
}
