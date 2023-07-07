#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
#include<limits.h>
#include<pthread.h>
#include<assert.h>


void cd_L(char dir[1000]) {
    int status = chdir(dir);
    if (status == -1) {
        printf("cd: %s: No such file or directory", dir);
        exit(1);
    } else {
        printf("Current directory: %s", getcwd(dir, 1000));
    }
}

void cd_P(char dir[1000]) {
    char *path = realpath(dir, NULL);
    int status = chdir(path);
    if (status == -1) {
        printf("cd: %s: No such file or directory", dir);
        exit(1);
    } else {
        printf("Current directory: %s", getcwd(dir, 1000));
    }
}

void cd() {
    int status = chdir("..");
    if (status == -1) {
        printf("No such file or directory");
        exit(1);
    } else {
        printf("Current directory: %s", getcwd(NULL, 0));
    }
}

void cd_main(char dir[1000]) {
    char command[1000];
    char a[100];
    char fileName[1000];

    char *token = strtok(dir, " ");
    if (token != NULL) {
        strcpy(command, token);
        token = strtok(NULL, " ");
    }
    
    if (token != NULL) {
        strcpy(a, token);
        token = strtok(NULL, " ");
    }

    while (token != NULL) {
        strcpy(fileName, token);
        token = strtok(NULL, " ");
    }
    if (strcmp(command, "cd") == 0) {
        if (strcmp(a, "-L") == 0) {
            cd_L(fileName);
        } else if (strcmp(a, "-P") == 0) {
            cd_P(fileName);
        } else {
            cd();
        }
    } else {
        printf("Invalid command");
        exit(1);
    }
}

void echo_n(char str[1000]) {
    printf("str: %s \n", str);
    int i = 0;
    while (str[i] != '\0') {
        printf("%c", str[i]);
        i++;
    }
}

void echo_help(char str[1000]) {
    printf("echo - write arguments to the standard output. \n");
    printf("Usage: echo [OPTION]... [STRING]... \n");
}

void echo(char str[1000]) {
    char command[10];
    char a[10];
    char input[1000];
    char *token = strtok(str, " ");
    if (token != NULL) {
        strcpy(command, token);
        token = strtok(NULL, " ");
    }

    if (token != NULL) {
        strcpy(a, token);
        token = strtok(NULL, "");
    }

    while (token != NULL) {
        strcpy(input, token);
        token = strtok(NULL, "");
    }
    if (strcmp(command, "echo") == 0) {
        if (strcmp(a, "-n") == 0) {
            echo_n(input);
        } else if (strcmp(a, "-help") == 0) {
            echo_help(input);
        }
    } else {
        printf("echo: invalid option");
        exit(1);
    }
}


void pwd_L() {
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s", cwd);
    } else {
        printf("getcwd() error");
        exit(1);
    }
}

void pwd_P() {
    char cwd[1000];
    char buffer[PATH_MAX];
    char *ptr = realpath(cwd, buffer);
    if (ptr != NULL) {
        printf("Current working directory: %s", ptr);
    } else {
        perror("Error: ");
    }
}


void pwd(char str[1000]) {
    char command[10];
    char a[10];
    char buf[10];
    char *token = strtok(str, " ");
    strcpy(command, token);
    token = strtok(NULL, " ");

    if (token != NULL) {
        strcpy(a, token);
        token = strtok(NULL, "");
    }

    if (strcmp(command, "pwd") == 0) {
        if (strcmp(a, "-L") == 0) {
            pwd_L();
        } else if (strcmp(a, "-P") == 0) {
            pwd_P();
        } else {
            pwd_L();
        }
    } else {
        printf("Invalid command");
        exit(1);
    }
}

char shellCommands[10][10] = {"echo", "pwd", "cd", "cat", "ls", "rm", "mkdir", "date"};

void *mythread(void *args) {
    char *m =  (char *) args;
    system(m);
    return (void *)m;
}

int main() {
    pthread_t p;
    char hostName[100];
    char password[100];
    printf("Enter host name: ");
    scanf("%[^\n]%*c", hostName);
    printf("\n");
    printf("******************************************************* Welcome to the shell ******************************************************* \n \n");
    printf("%s@:~$ ", hostName);

    while (1) {
        char inputCommand[100];
        char command[100];
        char option[100];
        char fileName[1000];
        char threadCheck[100];
        char buffer1[100];
        char buffer2[100];
        char buffer3[10];
        char bufferInput[100];
        scanf("%[^\n]s ", inputCommand);
        strcpy(bufferInput, inputCommand);
        char *token = strtok(inputCommand, " ");

        if (token != NULL) {
            strcpy(command, token);
            token = strtok(NULL, " ");
        }
        
        if (token != NULL) {
            strcpy(buffer1, token);
            if (strcmp(buffer1, "&t") == 0) {
                strcpy(threadCheck, token);
                token = strtok(NULL, " ");
                if (token != NULL) {
                    strcpy(option, token);
                    token = strtok(NULL, " ");
                }
            } else {
                strcpy(option, token);
                token = strtok(NULL, " ");
            }
        }
        if (token != NULL){
            while (token != NULL) {
                strcpy(fileName, token);
                token = strtok(NULL, "");
            }
        }

        if (strcmp(command, "cd") == 0) {
            cd_main(bufferInput);
            break;
        } else if (strcmp(command, "echo") == 0) {
            echo(bufferInput);
            break;
        } else if (strcmp(command, "pwd") == 0){
            pwd(inputCommand);
            break;
        } else if (strcmp(command, "cat") == 0) {
            if (strcmp(threadCheck, "&t") == 0) {
                if (strcmp(option, "-n") == 0) {
                    char sysCall[100] = "./cat ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);
                    
                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else if (strcmp(option, "-E") == 0) {
                    char sysCall[100] = "./cat ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else {
                    char sysCall[100] = "./cat ";
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                }
            } else {
                if (strcmp(option, "-n") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./cat", "-n", fileName, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else if (strcmp(option, "-E") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./cat", "-E", fileName, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./cat", ".", option, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                }
            }
            break;
        } else if (strcmp(command, "ls") == 0) {
            if (strcmp(threadCheck, "&t") == 0) {
                if (strcmp(option, "-a") == 0) {
                    char sysCall[100] = "./ls ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);
                    
                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else if (strcmp(option, "-A") == 0) {
                    char sysCall[100] = "./ls ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else {
                    char sysCall[100] = "./ls ";
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                }
            } else {
                if (strcmp(option, "-a") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./ls", "-a", fileName, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else if (strcmp(option, "-A") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./ls", "-A", fileName, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./ls", "", ".", NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                }
            }
            break;
        } else if (strcmp(command, "rm") == 0) {
            if (strcmp(threadCheck, "&t") == 0) {
                if (strcmp(option, "-v") == 0) {
                    char sysCall[100] = "./rm ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);
                    
                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else if (strcmp(option, "-i") == 0) {
                    char sysCall[100] = "./rm ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else {
                    char sysCall[100] = "./rm ";
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                }
            } else {
                if (strcmp(option, "-v") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./rm", "-v", fileName, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else if (strcmp(option, "-i") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./rm", "-i", fileName, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./rm", ".", option, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                }
            }
            break;
        } else if (strcmp(command, "mkdir") == 0) {
            if (strcmp(threadCheck, "&t") == 0) {
                if (strcmp(option, "-v") == 0) {
                    char sysCall[100] = "./mkdir ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);
                    
                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else if (strcmp(option, "-m") == 0) {
                    char sysCall[100] = "./mkdir ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else {
                    char sysCall[100] = "./mkdir ";
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                }
            } else {
                if (strcmp(option, "-m") == 0) {
                    char mode[100];
                    printf("Enter mode: ");
                    scanf("%[^\n]%*c", mode);
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./mkdir", "-m", fileName, mode, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], argv[3], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else if (strcmp(option, "-v") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./mkdir", "-v", fileName, NULL};
                        execl(argv[0], argv[0], argv[1], argv[2], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                }
            }
            break;
        } else if (strcmp(command, "date") == 0) {
            if (strcmp(threadCheck, "&t") == 0) {
                if (strcmp(option, "-u") == 0) {
                    char sysCall[100] = "./date ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);
                    
                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else if (strcmp(option, "-R") == 0) {
                    char sysCall[100] = "./date ";
                    strcat(sysCall, option);
                    strcat(sysCall, " ");
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                } else {
                    char sysCall[100] = "./date ";
                    strcat(sysCall, fileName);

                    pthread_create(&p, NULL, mythread, sysCall);
                    pthread_join(p, NULL);
                }
            } else {
                if (strcmp(option, "-u") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./date", "-u", NULL};
                        execl(argv[0], argv[0], argv[1], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else if (strcmp(option, "-R") == 0) {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./date", "-R", NULL};
                        execl(argv[0], argv[0], argv[1], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                } else {
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[] = {"./date", ".", NULL};
                        execl(argv[0], argv[0], argv[1], NULL);
                    } else {
                        pid_t t;
                        t = wait(&status);
                    }
                }
            }
            break;
        } else if (strcmp(command, "exit") == 0) {
            exit(0);
        } else {
            printf("Command not found");
            break;
        }
    }   
}
