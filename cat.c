#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void cat(char fileName[1000]) {
    FILE *fp;
    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("cat: %s: No such file or directory", fileName);
        exit(1);
    } else {
        char c;
        while ((c = fgetc(fp)) != EOF) {
            printf("%c", c);
        }
    }

    fclose(fp);
}


void cat_n(char fileName[1000]) {
    char buffer[2048];
    FILE *fp;
    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("cat: %s: No such file or directory", fileName);
        exit(1);
    } else {
        char c;
        int line = 1;
        while ((c = fgets(buffer, 2048, fp)) != NULL) {
            printf("%d. %s", line, buffer);
            line++;
            
        }
    }
    fclose(fp);
}

void cat_E(char fileName[1000]) {
    FILE *fp;
    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("cat: %s: No such file or directory", fileName);
        exit(1);
    } else {
        char c;
        while ((c = fgetc(fp)) != EOF) {
            if (c == '\n') {
                printf(" $ \n");
            } else {
                printf("%c", c);
            }
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    char command[100];
    char fileName[1000];

    strcpy(command, argv[1]);
    strcpy(fileName, argv[2]);

    if (fileName != NULL) {
        if (strcmp(command, "-n") == 0) {
            cat_n(fileName);
        } else if (strcmp(command, "-E") == 0) {
            cat_E(fileName);
        } else {
            cat(fileName);
        }
    } else {
        printf("cat: missing operand");
        exit(1);
    }
}
