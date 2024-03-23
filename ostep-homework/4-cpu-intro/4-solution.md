 
# Homework - Chapter 4

## 1. Run process-run.py withthefollowingflags:-l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.
    
100% da X:Y Y=100% flag für cpu nutzung
  ```sh
    bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -l 5:100,5:100 -p -c
    Time        PID: 0        PID: 1           CPU           IOs
      1        RUN:cpu         READY             1          
      2        RUN:cpu         READY             1          
      3        RUN:cpu         READY             1          
      4        RUN:cpu         READY             1          
      5        RUN:cpu         READY             1          
      6           DONE       RUN:cpu             1          
      7           DONE       RUN:cpu             1          
      8           DONE       RUN:cpu             1          
      9           DONE       RUN:cpu             1          
     10           DONE       RUN:cpu             1          
    
    Stats: Total Time 10
    Stats: CPU Busy 10 (100.00%)
    Stats: IO Busy  0 (0.00%)
```
## 2. Now run with these flags: ./process-run.py -l 4:100,1:0. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use -c and -p to find out if you were right.
   
4 ticks 1.process mit 100% cpu nutzung + 7 ticks 2.process 2 io 5 blockende
```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -l 4:100,1:0 -c -p
  Time        PID: 0        PID: 1           CPU           IOs
    1        RUN:cpu         READY             1          
    2        RUN:cpu         READY             1          
    3        RUN:cpu         READY             1          
    4        RUN:cpu         READY             1          
    5           DONE        RUN:io             1          
    6           DONE       BLOCKED                           1
    7           DONE       BLOCKED                           1
    8           DONE       BLOCKED                           1
    9           DONE       BLOCKED                           1
   10           DONE       BLOCKED                           1
   11*          DONE   RUN:io_done             1          
  
  Stats: Total Time 11
  Stats: CPU Busy 6 (54.55%)
  Stats: IO Busy  5 (45.45%)
```
## 3. Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right.
  
io 4xcpu blocked io`
```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -l 1:0,4:100 -c -p
  Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1          
    2        BLOCKED       RUN:cpu             1             1
    3        BLOCKED       RUN:cpu             1             1
    4        BLOCKED       RUN:cpu             1             1
    5        BLOCKED       RUN:cpu             1             1
    6        BLOCKED          DONE                           1
    7*   RUN:io_done          DONE             1          
    
  Stats: Total Time 7
  Stats: CPU Busy 6 (85.71%)
  Stats: IO Busy  5 (71.43%)
```
## 4. We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process is- sues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, in- stead waiting until the process is completely finished. What hap- pens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH ON END), one doing I/O and the other doing CPU work?
 
wieder 11 ticks
```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -l 1:0,4:100 -c -p -S SWITCH_ON_END
  Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1          
    2        BLOCKED         READY                           1
    3        BLOCKED         READY                           1
    4        BLOCKED         READY                           1
    5        BLOCKED         READY                           1
    6        BLOCKED         READY                           1
    7*   RUN:io_done         READY             1          
    8           DONE       RUN:cpu             1          
    9           DONE       RUN:cpu             1          
   10           DONE       RUN:cpu             1          
   11           DONE       RUN:cpu             1          

  Stats: Total Time 11
  Stats: CPU Busy 6 (54.55%)
  Stats: IO Busy  5 (45.45%)
```
## 5. Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCHONIO).Whathappensnow?Use-c and -p to confirm that you are right.
  
wieder 7 ticks
```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -l 1:0,4:100 -c -p -S SWITCH_ON_IO
  Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1          
    2        BLOCKED       RUN:cpu             1             1
    3        BLOCKED       RUN:cpu             1             1
    4        BLOCKED       RUN:cpu             1             1
    5        BLOCKED       RUN:cpu             1             1
    6        BLOCKED          DONE                           1
    7*   RUN:io_done          DONE             1          
  
  Stats: Total Time 7
  Stats: CPU Busy 6 (85.71%)
  Stats: IO Busy  5 (71.43%)
```
## 6. One other important behavior is what to do when an I/O completes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -c -p -I IO RUN LATER) Are system resources being effectively utilized?

Prozess wird erst wieder aufgerufen wenn alle nachfolgenden fertig. Nicht effizient da während weiterer IO blocks cpu anderer Prozesse laufen könnte
```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_LATER
  Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
    1         RUN:io         READY         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY         READY             1             1
    3        BLOCKED       RUN:cpu         READY         READY             1             1
    4        BLOCKED       RUN:cpu         READY         READY             1             1
    5        BLOCKED       RUN:cpu         READY         READY             1             1
    6        BLOCKED       RUN:cpu         READY         READY             1             1
    7*         READY          DONE       RUN:cpu         READY             1          
    8          READY          DONE       RUN:cpu         READY             1          
    9          READY          DONE       RUN:cpu         READY             1          
   10          READY          DONE       RUN:cpu         READY             1          
   11          READY          DONE       RUN:cpu         READY             1          
   12          READY          DONE          DONE       RUN:cpu             1          
   13          READY          DONE          DONE       RUN:cpu             1          
   14          READY          DONE          DONE       RUN:cpu             1          
   15          READY          DONE          DONE       RUN:cpu             1          
   16          READY          DONE          DONE       RUN:cpu             1          
   17    RUN:io_done          DONE          DONE          DONE             1          
   18         RUN:io          DONE          DONE          DONE             1          
   19        BLOCKED          DONE          DONE          DONE                           1
   20        BLOCKED          DONE          DONE          DONE                           1
   21        BLOCKED          DONE          DONE          DONE                           1
   22        BLOCKED          DONE          DONE          DONE                           1
   23        BLOCKED          DONE          DONE          DONE                           1
   24*   RUN:io_done          DONE          DONE          DONE             1          
   25         RUN:io          DONE          DONE          DONE             1          
   26        BLOCKED          DONE          DONE          DONE                           1
   27        BLOCKED          DONE          DONE          DONE                           1
   28        BLOCKED          DONE          DONE          DONE                           1
   29        BLOCKED          DONE          DONE          DONE                           1
   30        BLOCKED          DONE          DONE          DONE                           1
   31*   RUN:io_done          DONE          DONE          DONE             1          
  
  Stats: Total Time 31
  Stats: CPU Busy 21 (67.74%)
  Stats: IO Busy  15 (48.39%)
```
## 7. Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just com- pleted an I/O again be a good idea?
  
wenn 1. prozess noch mehr io blocks hat kann das parallel zu cpu von anderen prozess laufen. sinnvoll das io ergebnis direkt zu verwerten?
```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_IMMEDIATE
  Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
    1         RUN:io         READY         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY         READY             1             1
    3        BLOCKED       RUN:cpu         READY         READY             1             1
    4        BLOCKED       RUN:cpu         READY         READY             1             1
    5        BLOCKED       RUN:cpu         READY         READY             1             1
    6        BLOCKED       RUN:cpu         READY         READY             1             1
    7*   RUN:io_done          DONE         READY         READY             1          
    8         RUN:io          DONE         READY         READY             1          
    9        BLOCKED          DONE       RUN:cpu         READY             1             1
   10        BLOCKED          DONE       RUN:cpu         READY             1             1
   11        BLOCKED          DONE       RUN:cpu         READY             1             1
   12        BLOCKED          DONE       RUN:cpu         READY             1             1
   13        BLOCKED          DONE       RUN:cpu         READY             1             1
   14*   RUN:io_done          DONE          DONE         READY             1          
   15         RUN:io          DONE          DONE         READY             1          
   16        BLOCKED          DONE          DONE       RUN:cpu             1             1
   17        BLOCKED          DONE          DONE       RUN:cpu             1             1
   18        BLOCKED          DONE          DONE       RUN:cpu             1             1
   19        BLOCKED          DONE          DONE       RUN:cpu             1             1
   20        BLOCKED          DONE          DONE       RUN:cpu             1             1
   21*   RUN:io_done          DONE          DONE          DONE             1          
  
  Stats: Total Time 21
  Stats: CPU Busy 21 (100.00%)
  Stats: IO Busy  15 (71.43%)
```
## 8. Now run with some randomly generated processes using flags -s 1 -l 3:50,3:50 or -s 2 -l 3:50,3:50 or -s 3 -l 3:50, 3:50. See if you can predict how the trace will turn out. What hap- pens when you use the flag -I IO RUN IMMEDIATE versus that flag -I IO RUN LATER? What happens when you use the flag -S SWITCH ON IO versus -S SWITCH ON END?

SEED=1

SWITCH_ON_END schlechter. Sonst alles gleich.
```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 1 -l 3:50,3:50,3:50 -c -p
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED       RUN:cpu         READY             1             1
    4        BLOCKED       RUN:cpu         READY             1             1
    5        BLOCKED       RUN:cpu         READY             1             1
    6        BLOCKED          DONE        RUN:io             1             1
    7        BLOCKED          DONE       BLOCKED                           2
    8*   RUN:io_done          DONE       BLOCKED             1             1
    9         RUN:io          DONE       BLOCKED             1             1
   10        BLOCKED          DONE       BLOCKED                           2
   11        BLOCKED          DONE       BLOCKED                           2
   12*       BLOCKED          DONE   RUN:io_done             1             1
   13        BLOCKED          DONE        RUN:io             1             1
   14        BLOCKED          DONE       BLOCKED                           2
   15*   RUN:io_done          DONE       BLOCKED             1             1
   16           DONE          DONE       BLOCKED                           1
   17           DONE          DONE       BLOCKED                           1
   18           DONE          DONE       BLOCKED                           1
   19*          DONE          DONE   RUN:io_done             1          
   20           DONE          DONE       RUN:cpu             1          
  
  Stats: Total Time 20
  Stats: CPU Busy 13 (65.00%)
  Stats: IO Busy  16 (80.00%)

bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 1 -l 3:50,3:50,3:50 -c -p -I IO_RUN_IMMEDIATE
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED       RUN:cpu         READY             1             1
    4        BLOCKED       RUN:cpu         READY             1             1
    5        BLOCKED       RUN:cpu         READY             1             1
    6        BLOCKED          DONE        RUN:io             1             1
    7        BLOCKED          DONE       BLOCKED                           2
    8*   RUN:io_done          DONE       BLOCKED             1             1
    9         RUN:io          DONE       BLOCKED             1             1
   10        BLOCKED          DONE       BLOCKED                           2
   11        BLOCKED          DONE       BLOCKED                           2
   12*       BLOCKED          DONE   RUN:io_done             1             1
   13        BLOCKED          DONE        RUN:io             1             1
   14        BLOCKED          DONE       BLOCKED                           2
   15*   RUN:io_done          DONE       BLOCKED             1             1
   16           DONE          DONE       BLOCKED                           1
   17           DONE          DONE       BLOCKED                           1
   18           DONE          DONE       BLOCKED                           1
   19*          DONE          DONE   RUN:io_done             1          
   20           DONE          DONE       RUN:cpu             1          

  Stats: Total Time 20
  Stats: CPU Busy 13 (65.00%)
  Stats: IO Busy  16 (80.00%)

  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 1 -l 3:50,3:50,3:50 -c -p -I IO_RUN_LATER
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED       RUN:cpu         READY             1             1
    4        BLOCKED       RUN:cpu         READY             1             1
    5        BLOCKED       RUN:cpu         READY             1             1
    6        BLOCKED          DONE        RUN:io             1             1
    7        BLOCKED          DONE       BLOCKED                           2
    8*   RUN:io_done          DONE       BLOCKED             1             1
    9         RUN:io          DONE       BLOCKED             1             1
   10        BLOCKED          DONE       BLOCKED                           2
   11        BLOCKED          DONE       BLOCKED                           2
   12*       BLOCKED          DONE   RUN:io_done             1             1
   13        BLOCKED          DONE        RUN:io             1             1
   14        BLOCKED          DONE       BLOCKED                           2
   15*   RUN:io_done          DONE       BLOCKED             1             1
   16           DONE          DONE       BLOCKED                           1
   17           DONE          DONE       BLOCKED                           1
   18           DONE          DONE       BLOCKED                           1
   19*          DONE          DONE   RUN:io_done             1          
   20           DONE          DONE       RUN:cpu             1          

  Stats: Total Time 20
  Stats: CPU Busy 13 (65.00%)
  Stats: IO Busy  16 (80.00%)

bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 1 -l 3:50,3:50,3:50 -c -p -S SWITCH_ON_IO
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED       RUN:cpu         READY             1             1
    4        BLOCKED       RUN:cpu         READY             1             1
    5        BLOCKED       RUN:cpu         READY             1             1
    6        BLOCKED          DONE        RUN:io             1             1
    7        BLOCKED          DONE       BLOCKED                           2
    8*   RUN:io_done          DONE       BLOCKED             1             1
    9         RUN:io          DONE       BLOCKED             1             1
   10        BLOCKED          DONE       BLOCKED                           2
   11        BLOCKED          DONE       BLOCKED                           2
   12*       BLOCKED          DONE   RUN:io_done             1             1
   13        BLOCKED          DONE        RUN:io             1             1
   14        BLOCKED          DONE       BLOCKED                           2
   15*   RUN:io_done          DONE       BLOCKED             1             1
   16           DONE          DONE       BLOCKED                           1
   17           DONE          DONE       BLOCKED                           1
   18           DONE          DONE       BLOCKED                           1
   19*          DONE          DONE   RUN:io_done             1          
   20           DONE          DONE       RUN:cpu             1          

  Stats: Total Time 20
  Stats: CPU Busy 13 (65.00%)
  Stats: IO Busy  16 (80.00%)

  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 1 -l 3:50,3:50,3:50 -c -p -S SWITCH_ON_END
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED         READY         READY                           1
    4        BLOCKED         READY         READY                           1
    5        BLOCKED         READY         READY                           1
    6        BLOCKED         READY         READY                           1
    7        BLOCKED         READY         READY                           1
    8*   RUN:io_done         READY         READY             1          
    9         RUN:io         READY         READY             1          
   10        BLOCKED         READY         READY                           1
   11        BLOCKED         READY         READY                           1
   12        BLOCKED         READY         READY                           1
   13        BLOCKED         READY         READY                           1
   14        BLOCKED         READY         READY                           1
   15*   RUN:io_done         READY         READY             1          
   16           DONE       RUN:cpu         READY             1          
   17           DONE       RUN:cpu         READY             1          
   18           DONE       RUN:cpu         READY             1          
   19           DONE          DONE        RUN:io             1          
   20           DONE          DONE       BLOCKED                           1
   21           DONE          DONE       BLOCKED                           1
   22           DONE          DONE       BLOCKED                           1
   23           DONE          DONE       BLOCKED                           1
   24           DONE          DONE       BLOCKED                           1
   25*          DONE          DONE   RUN:io_done             1          
   26           DONE          DONE        RUN:io             1          
   27           DONE          DONE       BLOCKED                           1
   28           DONE          DONE       BLOCKED                           1
   29           DONE          DONE       BLOCKED                           1
   30           DONE          DONE       BLOCKED                           1
   31           DONE          DONE       BLOCKED                           1
   32*          DONE          DONE   RUN:io_done             1          
   33           DONE          DONE       RUN:cpu             1          

  Stats: Total Time 33
  Stats: CPU Busy 13 (39.39%)
  Stats: IO Busy  20 (60.61%)
```

SEED=2

SWITCH_ON_END schlechter. Sonst alles gleich.

```sh
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 2 -l 3:50,3:50,3:50 -c -p
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1         RUN:io         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY             1             1
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED        RUN:io             1             2
    5        BLOCKED       BLOCKED       BLOCKED                           3
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7*   RUN:io_done       BLOCKED       BLOCKED             1             2
    8         RUN:io       BLOCKED       BLOCKED             1             2
    9*       BLOCKED   RUN:io_done       BLOCKED             1             2
   10*       BLOCKED        RUN:io         READY             1             1
   11        BLOCKED       BLOCKED   RUN:io_done             1             2
   12        BLOCKED       BLOCKED       RUN:cpu             1             2
   13        BLOCKED       BLOCKED        RUN:io             1             2
   14*   RUN:io_done       BLOCKED       BLOCKED             1             2
   15        RUN:cpu       BLOCKED       BLOCKED             1             2
   16*          DONE   RUN:io_done       BLOCKED             1             1
   17           DONE          DONE       BLOCKED                           1
   18           DONE          DONE       BLOCKED                           1
   19*          DONE          DONE   RUN:io_done             1          

  Stats: Total Time 19
  Stats: CPU Busy 15 (78.95%)
  Stats: IO Busy  17 (89.47%)
 
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 2 -l 3:50,3:50,3:50 -c -p -I IO_RUN_IMMEDIATE
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1         RUN:io         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY             1             1
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED        RUN:io             1             2
    5        BLOCKED       BLOCKED       BLOCKED                           3
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7*   RUN:io_done       BLOCKED       BLOCKED             1             2
    8         RUN:io       BLOCKED       BLOCKED             1             2
    9*       BLOCKED   RUN:io_done       BLOCKED             1             2
   10*       BLOCKED         READY   RUN:io_done             1             1
   11        BLOCKED         READY       RUN:cpu             1             1
   12        BLOCKED         READY        RUN:io             1             1
   13        BLOCKED        RUN:io       BLOCKED             1             2
   14*   RUN:io_done       BLOCKED       BLOCKED             1             2
   15        RUN:cpu       BLOCKED       BLOCKED             1             2
   16           DONE       BLOCKED       BLOCKED                           2
   17           DONE       BLOCKED       BLOCKED                           2
   18*          DONE       BLOCKED   RUN:io_done             1             1
   19*          DONE   RUN:io_done          DONE             1          
  
  Stats: Total Time 19
  Stats: CPU Busy 15 (78.95%)
  Stats: IO Busy  17 (89.47%)
  
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 2 -l 3:50,3:50,3:50 -c -p -I IO_RUN_LATER
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1         RUN:io         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY             1             1
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED        RUN:io             1             2
    5        BLOCKED       BLOCKED       BLOCKED                           3
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7*   RUN:io_done       BLOCKED       BLOCKED             1             2
    8         RUN:io       BLOCKED       BLOCKED             1             2
    9*       BLOCKED   RUN:io_done       BLOCKED             1             2
   10*       BLOCKED        RUN:io         READY             1             1
   11        BLOCKED       BLOCKED   RUN:io_done             1             2
   12        BLOCKED       BLOCKED       RUN:cpu             1             2
   13        BLOCKED       BLOCKED        RUN:io             1             2
   14*   RUN:io_done       BLOCKED       BLOCKED             1             2
   15        RUN:cpu       BLOCKED       BLOCKED             1             2
   16*          DONE   RUN:io_done       BLOCKED             1             1
   17           DONE          DONE       BLOCKED                           1
   18           DONE          DONE       BLOCKED                           1
   19*          DONE          DONE   RUN:io_done             1          
  
  Stats: Total Time 19
  Stats: CPU Busy 15 (78.95%)
  Stats: IO Busy  17 (89.47%)

  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 2 -l 3:50,3:50,3:50 -c -p -S SWITCH_ON_IO
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1         RUN:io         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY             1             1
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED        RUN:io             1             2
    5        BLOCKED       BLOCKED       BLOCKED                           3
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7*   RUN:io_done       BLOCKED       BLOCKED             1             2
    8         RUN:io       BLOCKED       BLOCKED             1             2
    9*       BLOCKED   RUN:io_done       BLOCKED             1             2
   10*       BLOCKED        RUN:io         READY             1             1
   11        BLOCKED       BLOCKED   RUN:io_done             1             2
   12        BLOCKED       BLOCKED       RUN:cpu             1             2
   13        BLOCKED       BLOCKED        RUN:io             1             2
   14*   RUN:io_done       BLOCKED       BLOCKED             1             2
   15        RUN:cpu       BLOCKED       BLOCKED             1             2
   16*          DONE   RUN:io_done       BLOCKED             1             1
   17           DONE          DONE       BLOCKED                           1
   18           DONE          DONE       BLOCKED                           1
   19*          DONE          DONE   RUN:io_done             1          

  Stats: Total Time 19
  Stats: CPU Busy 15 (78.95%)
  Stats: IO Busy  17 (89.47%)

  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 2 -l 3:50,3:50,3:50 -c -p -S SWITCH_ON_END
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1         RUN:io         READY         READY             1          
    2        BLOCKED         READY         READY                           1
    3        BLOCKED         READY         READY                           1
    4        BLOCKED         READY         READY                           1
    5        BLOCKED         READY         READY                           1
    6        BLOCKED         READY         READY                           1
    7*   RUN:io_done         READY         READY             1          
    8         RUN:io         READY         READY             1          
    9        BLOCKED         READY         READY                           1
   10        BLOCKED         READY         READY                           1
   11        BLOCKED         READY         READY                           1
   12        BLOCKED         READY         READY                           1
   13        BLOCKED         READY         READY                           1
   14*   RUN:io_done         READY         READY             1          
   15        RUN:cpu         READY         READY             1          
   16           DONE       RUN:cpu         READY             1          
   17           DONE        RUN:io         READY             1          
   18           DONE       BLOCKED         READY                           1
   19           DONE       BLOCKED         READY                           1
   20           DONE       BLOCKED         READY                           1
   21           DONE       BLOCKED         READY                           1
   22           DONE       BLOCKED         READY                           1
   23*          DONE   RUN:io_done         READY             1          
   24           DONE        RUN:io         READY             1          
   25           DONE       BLOCKED         READY                           1
   26           DONE       BLOCKED         READY                           1
   27           DONE       BLOCKED         READY                           1
   28           DONE       BLOCKED         READY                           1
   29           DONE       BLOCKED         READY                           1
   30*          DONE   RUN:io_done         READY             1          
   31           DONE          DONE        RUN:io             1          
   32           DONE          DONE       BLOCKED                           1
   33           DONE          DONE       BLOCKED                           1
   34           DONE          DONE       BLOCKED                           1
   35           DONE          DONE       BLOCKED                           1
   36           DONE          DONE       BLOCKED                           1
   37*          DONE          DONE   RUN:io_done             1          
   38           DONE          DONE       RUN:cpu             1          
   39           DONE          DONE        RUN:io             1          
   40           DONE          DONE       BLOCKED                           1
   41           DONE          DONE       BLOCKED                           1
   42           DONE          DONE       BLOCKED                           1
   43           DONE          DONE       BLOCKED                           1
   44           DONE          DONE       BLOCKED                           1
   45*          DONE          DONE   RUN:io_done             1          

  Stats: Total Time 45
  Stats: CPU Busy 15 (33.33%)
  Stats: IO Busy  30 (66.67%)
```

SEED=3

SWITCH_ON_END schlechter. RUN_IO_IMMEDIATE bisschen besser. Rest gleich.


```sh

  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 3 -l 3:50,3:50,3:50 -c -p
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED       RUN:cpu             1             2
    5        BLOCKED       BLOCKED        RUN:io             1             2
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7        BLOCKED       BLOCKED       BLOCKED                           3
    8*   RUN:io_done       BLOCKED       BLOCKED             1             2
    9*       RUN:cpu         READY       BLOCKED             1             1
   10           DONE   RUN:io_done       BLOCKED             1             1
   11*          DONE        RUN:io         READY             1          
   12           DONE       BLOCKED   RUN:io_done             1             1
   13           DONE       BLOCKED       RUN:cpu             1             1
   14           DONE       BLOCKED          DONE                           1
   15           DONE       BLOCKED          DONE                           1
   16           DONE       BLOCKED          DONE                           1
   17*          DONE   RUN:io_done          DONE             1          
   18           DONE       RUN:cpu          DONE             1          

  Stats: Total Time 18
  Stats: CPU Busy 13 (72.22%)
  Stats: IO Busy  13 (72.22%)
  
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 3 -l 3:50,3:50,3:50 -c -p -I IO_RUN_IMMEDIATE
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED       RUN:cpu             1             2
    5        BLOCKED       BLOCKED        RUN:io             1             2
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7        BLOCKED       BLOCKED       BLOCKED                           3
    8*   RUN:io_done       BLOCKED       BLOCKED             1             2
    9*         READY   RUN:io_done       BLOCKED             1             1
   10          READY        RUN:io       BLOCKED             1             1
   11*         READY       BLOCKED   RUN:io_done             1             1
   12          READY       BLOCKED       RUN:cpu             1             1
   13        RUN:cpu       BLOCKED          DONE             1             1
   14           DONE       BLOCKED          DONE                           1
   15           DONE       BLOCKED          DONE                           1
   16*          DONE   RUN:io_done          DONE             1          
   17           DONE       RUN:cpu          DONE             1          
  
  Stats: Total Time 17
  Stats: CPU Busy 13 (76.47%)
  Stats: IO Busy  13 (76.47%)
  
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 3 -l 3:50,3:50,3:50 -c -p -I IO_RUN_LATER
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED       RUN:cpu             1             2
    5        BLOCKED       BLOCKED        RUN:io             1             2
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7        BLOCKED       BLOCKED       BLOCKED                           3
    8*   RUN:io_done       BLOCKED       BLOCKED             1             2
    9*       RUN:cpu         READY       BLOCKED             1             1
   10           DONE   RUN:io_done       BLOCKED             1             1
   11*          DONE        RUN:io         READY             1          
   12           DONE       BLOCKED   RUN:io_done             1             1
   13           DONE       BLOCKED       RUN:cpu             1             1
   14           DONE       BLOCKED          DONE                           1
   15           DONE       BLOCKED          DONE                           1
   16           DONE       BLOCKED          DONE                           1
   17*          DONE   RUN:io_done          DONE             1          
   18           DONE       RUN:cpu          DONE             1          
  
  Stats: Total Time 18
  Stats: CPU Busy 13 (72.22%)
  Stats: IO Busy  13 (72.22%)
  
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 3 -l 3:50,3:50,3:50 -c -p -S SWITCH_ON_IO
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED        RUN:io         READY             1             1
    4        BLOCKED       BLOCKED       RUN:cpu             1             2
    5        BLOCKED       BLOCKED        RUN:io             1             2
    6        BLOCKED       BLOCKED       BLOCKED                           3
    7        BLOCKED       BLOCKED       BLOCKED                           3
    8*   RUN:io_done       BLOCKED       BLOCKED             1             2
    9*       RUN:cpu         READY       BLOCKED             1             1
   10           DONE   RUN:io_done       BLOCKED             1             1
   11*          DONE        RUN:io         READY             1          
   12           DONE       BLOCKED   RUN:io_done             1             1
   13           DONE       BLOCKED       RUN:cpu             1             1
   14           DONE       BLOCKED          DONE                           1
   15           DONE       BLOCKED          DONE                           1
   16           DONE       BLOCKED          DONE                           1
   17*          DONE   RUN:io_done          DONE             1          
   18           DONE       RUN:cpu          DONE             1          
  
  Stats: Total Time 18
  Stats: CPU Busy 13 (72.22%)
  Stats: IO Busy  13 (72.22%)
  
  bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/4-cpu-intro$ ./process-run.py -s 3 -l 3:50,3:50,3:50 -c -p -S SWITCH_ON_END
  Time        PID: 0        PID: 1        PID: 2           CPU           IOs
    1        RUN:cpu         READY         READY             1          
    2         RUN:io         READY         READY             1          
    3        BLOCKED         READY         READY                           1
    4        BLOCKED         READY         READY                           1
    5        BLOCKED         READY         READY                           1
    6        BLOCKED         READY         READY                           1
    7        BLOCKED         READY         READY                           1
    8*   RUN:io_done         READY         READY             1          
    9        RUN:cpu         READY         READY             1          
   10           DONE        RUN:io         READY             1          
   11           DONE       BLOCKED         READY                           1
   12           DONE       BLOCKED         READY                           1
   13           DONE       BLOCKED         READY                           1
   14           DONE       BLOCKED         READY                           1
   15           DONE       BLOCKED         READY                           1
   16*          DONE   RUN:io_done         READY             1          
   17           DONE        RUN:io         READY             1          
   18           DONE       BLOCKED         READY                           1
   19           DONE       BLOCKED         READY                           1
   20           DONE       BLOCKED         READY                           1
   21           DONE       BLOCKED         READY                           1
   22           DONE       BLOCKED         READY                           1
   23*          DONE   RUN:io_done         READY             1          
   24           DONE       RUN:cpu         READY             1          
   25           DONE          DONE       RUN:cpu             1          
   26           DONE          DONE        RUN:io             1          
   27           DONE          DONE       BLOCKED                           1
   28           DONE          DONE       BLOCKED                           1
   29           DONE          DONE       BLOCKED                           1
   30           DONE          DONE       BLOCKED                           1
   31           DONE          DONE       BLOCKED                           1
   32*          DONE          DONE   RUN:io_done             1          
   33           DONE          DONE       RUN:cpu             1          
  
  Stats: Total Time 33
  Stats: CPU Busy 13 (39.39%)
  Stats: IO Busy  20 (60.61%)
```