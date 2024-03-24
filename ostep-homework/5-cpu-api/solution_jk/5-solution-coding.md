
# Homework - Chapter 5 - Interlude: Process API

## 1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[]) {
    // parent
    int a = 10;
    printf("parent=%d\n", a);

    if (fork_or_die() == 0) {
        // child
        printf("child=%d\n", a);
        a += 10;
        printf("child+10=%d\n", a);
        exit(0);
    }

    // parent
    a += 10;
    printf("parent+10=%d\n", a);
    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution$ ./a1
parent=10
parent+10=20
child=10
child+10=20
```
## 2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[]) {
    // parent
    close(STDOUT_FILENO);
    open("a2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    printf("parent\n");

    if (fork_or_die() == 0) {
        // child
        printf("child\n");
        exit(0);
    }

    return 0;
}


```

```
parent
child
parent

```

Beide können zugreifen. Parent wird jedoch nachdem child fertig ist nochmals geprinted.
## 3. Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

Nicht immer nur wenn print nach Child kommt

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[]) {
    // parent
    close(STDOUT_FILENO);
    open("a3.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if (fork_or_die() == 0) {
        // child
        printf("hello\n");
        exit(0);
    }

    //parent
    printf("goodbye\n");
    return 0;
}


```

```
hello
goodbye

```

## 4. Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?


## 5. Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

void wait_or_die() {
    int rc = wait(NULL);
    assert(rc > 0);
}

int main(int argc, char *argv[]) {
    // parent
    if (fork_or_die() == 0) {
        // child
        int x = wait(NULL);
        printf("PID(CHILD): %d\n",x);
        exit(0);
    }
    int x = wait(NULL);
    printf("PID(PARENT): %d\n",x);

    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution$ ./a5
PID(CHILD): -1
PID(PARENT): 10654
```

wait() returns the process ID or -1 if an error occured.
## 6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?
```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

void wait_or_die() {
    int rc = wait(NULL);
    assert(rc > 0);
}

int main(int argc, char *argv[]) {
    // parent

    // create a child process
    int pid = fork_or_die();
    if (pid == 0) {
        // child
        printf("child\n");
        exit(0);
    }
    printf("parent\n");
    int status;
    waitpid(pid, status, 0);
    printf("status: exit(%d)\n", status);


    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution$ ./a6
parent
child
status: exit(0)
```

waitpid() ist nützlich um auf bestimmten Prozess zu warten. 
## 7. Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?
```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

void wait_or_die() {
    int rc = wait(NULL);
    assert(rc > 0);
}

int main(int argc, char *argv[]) {
    // parent

    // create a child process
    int pid = fork_or_die();
    if (pid == 0) {
        // child
        int status_child;
        pid_t x_child = waitpid(getpid(), &status_child, 0);
        printf("CHILD status: exit(%d)\n", status_child);
        printf("CHILD PID: %d\n", x_child);
        exit(0);
    }
    int status;
    pid_t x = waitpid(pid, &status, 0);
    printf("PARENT status: exit(%d)\n", status);
    printf("PARENT PID: %d\n", x);


    return 0;
}


```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api/solution$ ./a6
CHILD status: exit(-1472891968)
CHILD PID: -1
PARENT status: exit(0)
PARENT PID: 12405
```

## 8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.