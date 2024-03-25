
# Homework - Chapter 5 - Interlude: Process API

## 1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // parent
    int rc = fork();
    int a = 10;

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        printf("child=%d\n", a);
        a += 10;
        printf("child+10=%d\n", a);
        exit(0);
    } else {
        // parent
        a += 10;
        printf("parent+10=%d\n", a);
    }

    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution_jk$ ./a1
parent+10=20
child=10
child+10=20
```
## 2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // parent
    close(STDOUT_FILENO);
    open("a2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        printf("child\n");
        exit(0);
    } else {
        // parent
        printf("parent\n");
    }

    return 0;
}


```

```
parent
child

```

Beide können zugreifen. Parent wird jedoch nachdem child fertig ist nochmals geprinted.
## 3. Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

Nicht immer nur wenn print nach Child kommt

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

volatile int child_finished = 0;

void sigchild_handler(int sig) {
    child_finished = 1;
}

int main(int argc, char *argv[]) {
    // parent
    close(STDOUT_FILENO);
    open("a3.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    signal(SIGCHLD, sigchild_handler);

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        printf("hello\n");
        exit(0);
    } else {
        // parent
        while (!child_finished) {
            // wait for child to finish
        }
        printf("goodbye\n");

    }

    return 0;
}


```

```
hello
goodbye

```
## 4. Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    // Using execl()
    pid = fork();
    if (pid == 0) {
        printf("Using execl()\n\n");
        execl("/bin/ls", "ls", NULL);
        // If execl() fails
        perror("execl");
        exit(EXIT_FAILURE);
    }
    wait(NULL); // Wait for the child process to finish
    
    // Using execle()
    pid = fork();
    if (pid == 0) {
        printf("using execle()\n\n");
        char *envp[] = { "PATH=/bin", NULL }; // Example environment variable
        execle("/bin/ls", "ls", NULL, envp);
        // If execle() fails
        perror("execle");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execlp()
    pid = fork();
    if (pid == 0) {
        printf("using execlp()\n\n");
        execlp("ls", "ls", NULL);
        // If execlp() fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execv()
    pid = fork();
    if (pid == 0) {
        printf("using execv()\n\n");
        char *args[] = { "/bin/ls", NULL };
        execv("/bin/ls", args);
        // If execv() fails
        perror("execv");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execvp()
    pid = fork();
    if (pid == 0) {
        printf("using execvp()\n\n");
        char *args[] = { "ls", NULL };
        execvp("ls", args);
        // If execvp() fails
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execvpe()
    pid = fork();
    if (pid == 0) {
        printf("using execvpe()\n\n");
        char *args[] = { "ls", NULL };
        char *envp[] = { "PATH=/bin", NULL }; // Example environment variable
        #include <unistd.h> // Include the necessary header file

        execvpe("ls", args, envp);
        // If execvpe() fails
        perror("execvpe");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution_jk$ ./a4
Using execl()

5-solution-coding.md  5-solution.md  a1  a1.c  a2  a2.c  a2.output  a3  a3.c  a3.output  a4  a4.c  a5  a5.c  a6  a6.c  a7  a7.c  a8.c
using execle()

5-solution-coding.md  5-solution.md  a1  a1.c  a2  a2.c  a2.output  a3  a3.c  a3.output  a4  a4.c  a5  a5.c  a6  a6.c  a7  a7.c  a8.c
using execlp()

5-solution-coding.md  5-solution.md  a1  a1.c  a2  a2.c  a2.output  a3  a3.c  a3.output  a4  a4.c  a5  a5.c  a6  a6.c  a7  a7.c  a8.c
using execv()

5-solution-coding.md  5-solution.md  a1  a1.c  a2  a2.c  a2.output  a3  a3.c  a3.output  a4  a4.c  a5  a5.c  a6  a6.c  a7  a7.c  a8.c
using execvp()

5-solution-coding.md  5-solution.md  a1  a1.c  a2  a2.c  a2.output  a3  a3.c  a3.output  a4  a4.c  a5  a5.c  a6  a6.c  a7  a7.c  a8.c
using execvpe()

5-solution-coding.md  5-solution.md  a1  a1.c  a2  a2.c  a2.output  a3  a3.c  a3.output  a4  a4.c  a5  a5.c  a6  a6.c  a7  a7.c  a8.c
```

execl(), execle(), execlp(): These functions take the program name and its arguments as separate parameters. execle() also allows passing environment variables.

execv(), execvp(), execvpe(): These functions take the program name and its arguments as an array of strings (argv). execvp() also searches for the program in the directories listed in the PATH environment variable. execvpe() additionally allows passing environment variables.

`execl("PATH", ARG0, ARG1, ARGn, NULL)` Pfad zum Programm + Argumentliste mit `NULL` terminiert.

`execle("PATH", ARG0, ARG1, ARGn, ENV[])` Pfad zum Programm + Argumentliste + Array mit Environment-Variablen mit `NULL` terminiert.

`execlp(FILE_NAME, ARG0, ARG1, ARGn, NULL)` Programmname, wenn nicht `/FILENAME` wird in `PATH_ENVIRONMENT` gesucht + Argumentliste mit `NULL` terminiert.

`execv("PATH", ARGS[])` Pfad zum Programm + Array mit Argumenten mit `NULL` terminiert.

`exevp(FILE_NAME, ARGS[])` Programmname, wenn nicht `/FILENAME` wird in `PATH_ENVIRONMENT` gesucht + Array mit Argumenten mit `NULL` terminiert.

`execvpe("PATH", ARGS[], ENV[])` Pfad zum Programm + Array mit Argumenten mit `NULL` terminiert + Array mit Environment-Variablen mit `NULL` terminiert.

`ARG[0]` normalerweise Programmname!

## 5. Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // parent
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        int x = wait(NULL);
        printf("PID(CHILD): %d\n",x);
        exit(0);
    } else {
        // parent
        int x = wait(NULL);
        printf("PID(PARENT): %d\n",x);
    }

    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution_jk$ ./a5
PID(CHILD): -1
PID(PARENT): 25378
```

wait() returns the process ID or -1 if an error occured.
## 6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // parent
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        int status_child;
        pid_t x_child = waitpid(getpid(), &status_child, 0);
        printf("CHILD status: exit(%d)\n", status_child);
        printf("CHILD PID: %d\n", x_child);
        exit(0);
    } else {
        // parent
        int status;
        pid_t x = waitpid(rc, &status, 0);
        printf("PARENT status: exit(%d)\n", status);
        printf("PARENT PID: %d\n", x);
    }
    
    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution_jk$ ./a6
CHILD status: exit(-1108905024)
CHILD PID: -1
PARENT status: exit(0)
PARENT PID: 25400
```

waitpid() ist nützlich um auf bestimmten Prozess zu warten. 
## 7. Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // parent
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        close(STDOUT_FILENO);
        printf("child\n");
        exit(0);
    } else {
        // parent
        printf("parent\n");
    }
    
    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution_jk$ ./a7
parent
```

Child printet nichts. Parent printet.
## 8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // parent
    int pipefd[2]; // File descriptors for the pipe
    pid_t child_1 = fork(); // Child 1
    int MAX_MSG = 256;
    char inbuf[MAX_MSG]; // Buffer for reading from the pipe
    char *msg = "Hello, World!";

    if  (child_1 < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    // Create the pipe
    pipe(pipefd);
    
    if  (child_1 == 0) {

        // Create Child 2
        int child_2 = fork();
        if (child_2 < 0) {
            // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }

        if (child_2 == 0) {
        close(pipefd[1]); // Close the write end of the pipe
        read(pipefd[0], inbuf, MAX_MSG);
        printf("%s\n", inbuf);
        close(pipefd[0]); // Close the read end of the pipe
        exit(0);
        }

        // Child 1
        close(pipefd[0]); // Close the read end of the pipe
        write(pipefd[1], msg, MAX_MSG);
        close(pipefd[1]); // Close the write end of the pipe
        exit(0);
    }


    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution_jk$ ./a8
Hello, World!
```