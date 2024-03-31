# Homework - Chapter 8 - Scheduling: The Multi-Level Feedback Queue

## 1. Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each jobs and turning of I/Os.

```sh
bsys@30921e249eed:~/bsys/ostep-homework/8-cpu-sched-mlfq$ ./mlfq.py -s 8 -j 2 -n 2 -i 0
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 0
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime  23 - ioFreq   9
  Job  1: startTime   0 - runTime  13 - ioFreq   7

Compute the execution trace for the given workloads.
If you would like, also compute the response and turnaround
times for each of the jobs.

Use the -c flag to get the exact results when you are finished.
```

0-8     j0  q1  allot_rest 1    runtime 9

9-15    j1  q1  allot_rest 3    runtime 7

16      j0  q1  allot_rest 0    runtime 10

17-19   j1  q1  allot_rest 0    runtime 10

20-28   j0  q0  allot_rest 1    runtime 19 nur bis 27??????

29-31   j1  q0  allot_rest 3    runtime 13

32      j1 FINISHED

32-35   j0  q0  allot_rest 7    runtime 23  

36      j0  FINISHED


```sh
bsys@30921e249eed:~/bsys/ostep-homework/8-cpu-sched-mlfq$ ./mlfq.py -s 9 -j 2 -n 2 -i 0 
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 0
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime  46 - ioFreq   4
  Job  1: startTime   0 - runTime  14 - ioFreq   8

Compute the execution trace for the given workloads.
If you would like, also compute the response and turnaround
times for each of the jobs.

Use the -c flag to get the exact results when you are finished.
```

0-3     j0  q1  allot_rest 6    runtime 4

4-11    j1  q1  allot_rest 2    runtime 8

12-15   j0  q1  allot_rest 2    runtime 8

16-17   j1  q1  allot_rest 0    runtime 10

18-19   j0  q1  allot_rest 0    runtime 10

20-23   j1  q0  allot_rest 6    runtime 14

j1 FINISHED

24-25   j0  q0  allot_rest 6    runtime 14

18-19 + 24-25 4ticks I/O

26-29   j0  q1  allot_rest 2    runtime 18

...


```sh
bsys@30921e249eed:~/bsys/ostep-homework/8-cpu-sched-mlfq$ ./mlfq.py -s 13 -j 2 -n 2 -i 0 
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 0
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime  26 - ioFreq   7
  Job  1: startTime   0 - runTime  68 - ioFreq   8

Compute the execution trace for the given workloads.
If you would like, also compute the response and turnaround
times for each of the jobs.

Use the -c flag to get the exact results when you are finished.
```

0-6     j0  q1  allot_rest 3    runtime +7=7

j0 I/O

7-14    j1  q1  allot_rest 2    runtime +8=8

j1 I/O

15-17   j0  q1  allot_rest 0    runtime +3=10

18-19   j1  q1  allot_rest 0    runtime +2=10

20-23   j0  q0  allot_rest 6    runtime +4=14

j0 I/O

24-29   j1  q0  allot_rest 4    runtime +6=16

j1 I/O

30-35   j0  q0  allot_rest 0    runtime +6=20

36-39   j1  q0  allot_rest 0    runtime +4=20

40      j0  q0  allot_rest 9    runtime +1=21

j0 I/O

41-44   j1  q0  allot_rest 6    runtime +4=24

j1 I/O

45-49   j0  q0  allot_rest 5    runtime +5=26

j0 FINISHED

50-55   j1  q0  allot_rest 0    runtime +6=30

56-57   j1  q0  allot_rest 8    runtime +2=32

j1 I/O

58-65   j1  q0  allot_rest 0    runtime +8=40

j1 I/O

66-73   j1  q0  allot_rest 2    runtime +8=48

j1 I/O

74-75   j1  q0  allot_rest 0    runtime +2=50

76-81   j1  q0  allot_rest 4    runtime +6=56

j1 I/O

82-85   j1  q0  allot_rest 0    runtime +4=60

86-89   j1  q0  allot_rest 6    runtime +4=64

j1 I/O

90-93   j1  q0  allot_rest 2    runtime +4=68

j1 FINISHED