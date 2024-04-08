## Homework - Chapter 14 - Interlude: Memory API

# 1. null pointer derefence

Segmentation faulkt

# 2. gdb

```
Starting program: /home/bsys/bsys/14-sol/solution_jk/null 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555168 in main (argc=1, argv=0x7fffffffe118) at null.c:8
8           printf("Value of pointer: %d\n", *pointer);
```

# 3. valgrind

```
bsys@30921e249eed:~/bsys/14-sol/solution_jk$ valgrind --leak-check=yes ./null
==1470== Memcheck, a memory error detector
==1470== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1470== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1470== Command: ./null
==1470== 
==1470== Invalid read of size 4
==1470==    at 0x109168: main (null.c:8)
==1470==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==1470== 
==1470== 
==1470== Process terminating with default action of signal 11 (SIGSEGV)
==1470==  Access not within mapped region at address 0x0
==1470==    at 0x109168: main (null.c:8)
==1470==  If you believe this happened as a result of a stack
==1470==  overflow in your program's main thread (unlikely but
==1470==  possible), you can try to increase the size of the
==1470==  main thread stack using the --main-stacksize= flag.
==1470==  The main thread stack size used in this run was 8388608.
==1470== 
==1470== HEAP SUMMARY:
==1470==     in use at exit: 0 bytes in 0 blocks
==1470==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1470== 
==1470== All heap blocks were freed -- no leaks are possible
==1470== 
==1470== For lists of detected and suppressed errors, rerun with: -s
==1470== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault
```

unallowed access of memory at adress 0x109168, not within mapped region -> segfault

# 4. Unfreed malloc - valgrind

```
bsys@30921e249eed:~/bsys/14-sol/solution_jk$ valgrind ./nofree
==1842== Memcheck, a memory error detector
==1842== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1842== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1842== Command: ./nofree
==1842== 
==1842== 
==1842== HEAP SUMMARY:
==1842==     in use at exit: 4 bytes in 1 blocks
==1842==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==1842== 
==1842== LEAK SUMMARY:
==1842==    definitely lost: 4 bytes in 1 blocks
==1842==    indirectly lost: 0 bytes in 0 blocks
==1842==      possibly lost: 0 bytes in 0 blocks
==1842==    still reachable: 0 bytes in 0 blocks
==1842==         suppressed: 0 bytes in 0 blocks
==1842== Rerun with --leak-check=full to see details of leaked memory
==1842== 
==1842== For lists of detected and suppressed errors, rerun with: -s
==1842== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


```
bsys@30921e249eed:~/bsys/14-sol/solution_jk$ valgrind --leak-check=yes ./nofree
==1912== Memcheck, a memory error detector
==1912== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1912== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1912== Command: ./nofree
==1912== 
==1912== 
==1912== HEAP SUMMARY:
==1912==     in use at exit: 4 bytes in 1 blocks
==1912==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==1912== 
    ==1912== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==1912==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==1912==    by 0x109165: main (in /home/bsys/bsys/14-sol/solution_jk/nofree)
==1912== 
==1912== LEAK SUMMARY:
==1912==    definitely lost: 4 bytes in 1 blocks
==1912==    indirectly lost: 0 bytes in 0 blocks
==1912==      possibly lost: 0 bytes in 0 blocks
==1912==    still reachable: 0 bytes in 0 blocks
==1912==         suppressed: 0 bytes in 0 blocks
==1912== 
==1912== For lists of detected and suppressed errors, rerun with: -s
==1912== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

4 bytes are lost and will be cleaned up by the os after process terminates\

# 5. ivalid wrtie

program runs normal

```
bsys@30921e249eed:~/bsys/14-sol/solution_jk$ valgrind ./invalidwrite
==2499== Memcheck, a memory error detector
==2499== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2499== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==2499== Command: ./invalidwrite
==2499== 
==2499== Invalid write of size 4
==2499==    at 0x1091A2: main (in /home/bsys/bsys/14-sol/solution_jk/invalidwrite)
==2499==  Address 0x4a8f1d0 is 0 bytes after a block of size 400 alloc'd
==2499==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==2499==    by 0x109185: main (in /home/bsys/bsys/14-sol/solution_jk/invalidwrite)
==2499== 
==2499== 
==2499== HEAP SUMMARY:
==2499==     in use at exit: 0 bytes in 0 blocks
==2499==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==2499== 
==2499== All heap blocks were freed -- no leaks are possible
==2499== 
==2499== For lists of detected and suppressed errors, rerun with: -s
==2499== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

# 6. read after free

program runs normal

```
bsys@30921e249eed:~/bsys/14-sol/solution_jk$ valgrind ./readafterfree
==2707== Memcheck, a memory error detector
==2707== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2707== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==2707== Command: ./readafterfree
==2707== 
==2707== Invalid read of size 4
==2707==    at 0x1091CE: main (in /home/bsys/bsys/14-sol/solution_jk/readafterfree)
==2707==  Address 0x4a8f108 is 200 bytes inside a block of size 400 free'd
==2707==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==2707==    by 0x1091C3: main (in /home/bsys/bsys/14-sol/solution_jk/readafterfree)
==2707==  Block was alloc'd at
==2707==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==2707==    by 0x1091A5: main (in /home/bsys/bsys/14-sol/solution_jk/readafterfree)
==2707== 
Value of data[50]: 0
==2707== 
==2707== HEAP SUMMARY:
==2707==     in use at exit: 0 bytes in 0 blocks
==2707==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==2707== 
==2707== All heap blocks were freed -- no leaks are possible
==2707== 
==2707== For lists of detected and suppressed errors, rerun with: -s
==2707== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

# 7. free random shit

```
bsys@30921e249eed:~/bsys/14-sol/solution_jk$ valgrind --leak-check=full --track-origins=yes ./randomfree
==3305== Memcheck, a memory error detector
==3305== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3305== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==3305== Command: ./randomfree
==3305== 
==3305== Invalid free() / delete / delete[] / realloc()
==3305==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==3305==    by 0x1091A9: main (in /home/bsys/bsys/14-sol/solution_jk/randomfree)
==3305==  Address 0x4a8f360 is 336 bytes inside an unallocated block of size 4,193,744 in arena "client"
==3305== 
==3305== 
==3305== HEAP SUMMARY:
==3305==     in use at exit: 400 bytes in 1 blocks
==3305==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==3305== 
==3305== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==3305==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==3305==    by 0x109185: main (in /home/bsys/bsys/14-sol/solution_jk/randomfree)
==3305== 
==3305== LEAK SUMMARY:
==3305==    definitely lost: 400 bytes in 1 blocks
==3305==    indirectly lost: 0 bytes in 0 blocks
==3305==      possibly lost: 0 bytes in 0 blocks
==3305==    still reachable: 0 bytes in 0 blocks
==3305==         suppressed: 0 bytes in 0 blocks
==3305== 
==3305== For lists of detected and suppressed errors, rerun with: -s
==3305== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

# 8. Vector vs Linked List

```
bsys@30921e249eed:~/bsys/ostep-homework/14-sol/solution_jk$ time ./linkedlist 100000000

real    0m4,304s
user    0m3,200s
sys     0m1,104s
bsys@30921e249eed:~/bsys/ostep-homework/14-sol/solution_jk$ time ./vector 100000000

real    0m1,000s
user    0m0,920s
sys     0m0,081s



bsys@30921e249eed:~/bsys/ostep-homework/14-sol/solution_jk$ valgrind ./linkedlist 100000000
==57305== Memcheck, a memory error detector
==57305== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==57305== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==57305== Command: ./linkedlist 100000000
==57305== 
==57305== 
==57305== HEAP SUMMARY:
==57305==     in use at exit: 0 bytes in 0 blocks
==57305==   total heap usage: 100,000,001 allocs, 100,000,001 frees, 1,600,000,016 bytes allocated
==57305== 
==57305== All heap blocks were freed -- no leaks are possible
==57305== 
==57305== For lists of detected and suppressed errors, rerun with: -s
==57305== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
bsys@30921e249eed:~/bsys/ostep-homework/14-sol/solution_jk$ valgrind ./vector 100000000
==57696== Memcheck, a memory error detector
==57696== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==57696== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==57696== Command: ./vector 100000000
==57696== 
==57696== Warning: set address range perms: large range [0x14e95028, 0x24e95058) (noaccess)
==57696== Warning: set address range perms: large range [0x24e96028, 0x44e96058) (noaccess)
==57696== 
==57696== HEAP SUMMARY:
==57696==     in use at exit: 0 bytes in 0 blocks
==57696==   total heap usage: 29 allocs, 29 frees, 1,073,741,836 bytes allocated
==57696== 
==57696== All heap blocks were freed -- no leaks are possible
==57696== 
==57696== For lists of detected and suppressed errors, rerun with: -s
==57696== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```