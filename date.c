#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void date() {
    char weekdayName[10];
    char monthName[10];
    time_t t = time(NULL);
    if (t == -1) {
        perror("Error: ");
        exit(1);
    } else {
        struct tm *tm = localtime(&t);
        if (tm == NULL) {
            perror("Error: ");
            exit(1);
        } else {
            strftime(weekdayName, 10, "%a", tm);
            strftime(monthName, 10, "%b", tm);
            printf("%s %s %d %d:%d:%d PDT %d", weekdayName, monthName, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_year + 1900);
        }    
    }
}

void date_u() {
    char weekdayName[10];
    char monthName[10];
    time_t t = time(NULL);
    if (t == -1) {
        perror("Error: ");
        exit(1);
    } else {
        struct tm *tm = gmtime(&t);
        if (tm == NULL) {
            perror("Error: ");
            exit(1);
        } else {
            strftime(weekdayName, 10, "%a", tm);
            strftime(monthName, 10, "%b", tm);
            printf("%s %s %d %d:%d:%d UTC %d", weekdayName, monthName, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_year + 1900);
        }    
    }
}

void date_R() {
    char weekdayName[10];
    char monthName[10];
    char timeZone[10];
    time_t t = time(NULL);
    if (t == -1) {
        perror("Error: ");
        exit(1);
    } else {
        struct tm *tm = localtime(&t);
        if (tm == NULL) {
            perror("Error: ");
            exit(1);
        } else {
            strftime(weekdayName, 10, "%a", tm);
            strftime(monthName, 10, "%b", tm);
            printf("%s, %d %s %d:%d:%d %d -0600", weekdayName, tm->tm_mday, monthName,  tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
        }    
    }
}

int main(int argc, char *argv[]) {
    char command[10];

    char *token = strtok(argv[1], " ");
    strcpy(command, token);

    if (strcmp(command, "-u") == 0) {
        date_u();
    } else if (strcmp(command, "-R") == 0) {
        date_R();
    } else {
        date();
    }
}
