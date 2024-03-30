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

