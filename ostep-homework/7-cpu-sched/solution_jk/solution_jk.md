# Homework - Chapter 7 - Scheduling: Introduction

## 1. Compute the response time and turnaround time when running three jobs of lenght 200 with the SJF and FIFO schedulers

```sh
bsys@30921e249eed:~/bsys/ostep-homework/7-cpu-sched$ ./scheduler.py -p FIFO -l 200,200,200
ARG policy FIFO
ARG jlist 200,200,200

Here is the job list, with the run time of each job: 
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


Compute the turnaround time, response time, and wait time for each job.
When you are done, run this program again, with the same arguments,
but with -c, which will thus provide you with the answers. You can use
-s <somenumber> or your own job list (-l 10,15,20 for example)
to generate different problems for yourself.
```
FIFO: 

Turnaround Time
0: 200
1: 400
2: 600

Response Time
0: 000
1: 200
2: 400

Wait Time
0: 000
1: 200
2: 400

SJF: 

FIFO: 
Turnaround Time
0: 200
1: 400
2: 600

Response Time
0: 000
1: 200
2: 400

Wait Time
0: 000
1: 200
2: 400


## Now do the same but with jobs of different lengths: 100, 200 and 300.

```sh
bsys@30921e249eed:~/bsys/ostep-homework/7-cpu-sched$ ./scheduler.py -p FIFO -l 100,200,300 
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job: 
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


Compute the turnaround time, response time, and wait time for each job.
When you are done, run this program again, with the same arguments,
but with -c, which will thus provide you with the answers. You can use
-s <somenumber> or your own job list (-l 10,15,20 for example)
to generate different problems for yourself.
```

Beide gleich da jobs in SJF Reihenfolge reinkommen.

FIFO: 

Turnaround Time
0: 100
1: 300
2: 600

Response Time
0: 000
1: 100
2: 300

Wait Time
0: 000
1: 100
2: 300

SJF: 

Turnaround Time
0: 100
1: 300
2: 600

Response Time
0: 000
1: 100
2: 300

Wait Time
0: 000
1: 100
2: 300

## 3. Now do the same but also with the RR scheduler and a time-slice of 1.

```sh
bsys@30921e249eed:~/bsys/ostep-homework/7-cpu-sched$ ./scheduler.py -p FIFO -l 100,200,300 -q 1
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job: 
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


Compute the turnaround time, response time, and wait time for each job.
When you are done, run this program again, with the same arguments,
but with -c, which will thus provide you with the answers. You can use
-s <somenumber> or your own job list (-l 10,15,20 for example)
to generate different problems for yourself.
```

FIFO und SJF gleich.

FIFO: 

Turnaround Time
0: 100
1: 300
2: 600

Response Time
0: 000
1: 100
2: 300

Wait Time
0: 000
1: 100
2: 300

SJF: 

Turnaround Time
0: 100
1: 300
2: 600

Response Time
0: 000
1: 100
2: 300

Wait Time
0: 000
1: 100
2: 300

RR: 

Turnaround Time
0: 098
1: 499
2: 600

Response Time
0: 000
1: 001
2: 002

Wait Time
0: 198
1: 299
2: 300

## 4. For what types of workloads does SJF deliver the same turnaround times as FIFO?

Wenn Jobs gleich lang sind und wenn Jobs in Reihenfolge kommen. Sprich erst der kürzeste und dann aufsteigend.

## 5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

Wenn Jobdauer aller Jobs gleich der Quantum länge ist. Wenn Jobs in Reihenfolge von kurz nach lange kommen und dabei nie länger gehen wie ein Quamtum Slice.

## 6. What happens to response time with SJF as jobs lengths increase? Can you simulate to demonstrate the trend?

Die Response Time wird drastisch steigen da wenn z.B. der kürzeste Jobs 5000 sec braucht der 2. Job schon eine Response time von 5000 hat und der dritte dann min. 10000.

```sh
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 5000.00  Wait 0.00
  Job   1 -- Response: 5000.00  Turnaround 10000.00  Wait 5000.00
  Job   2 -- Response: 10000.00  Turnaround 20000.00  Wait 10000.00
  Job   3 -- Response: 20000.00  Turnaround 43000.00  Wait 20000.00

  Average -- Response: 8750.00  Turnaround 19500.00  Wait 8750.00
```

Round Robin mit Quantum Slice 10 sec hingegen:
```sh
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 19970.00  Wait 14970.00
  Job   1 -- Response: 10.00  Turnaround 19980.00  Wait 14980.00
  Job   2 -- Response: 20.00  Turnaround 29990.00  Wait 19990.00
  Job   3 -- Response: 30.00  Turnaround 43000.00  Wait 20000.00

  Average -- Response: 15.00  Turnaround 28235.00  Wait 17485.00
```

## 7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives worst-casse response time, given N jobs?

Response Time erhöht sich proportional.

response(n) = n-1 * (quantum length + context switch time) + quatum length

Passiert nur wenn Jobs auch lännger gehen als quantum length. 