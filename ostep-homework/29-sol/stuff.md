# los soltuiones de la homework 29

**gettimeofday resolution**: 1 microsecond  
**available cpus**: 8


## outputs #2:

```
Program ran for 1608.00 milliseconds with 8 threads, incrementing 10000000 times per thread
Stats for threads:
Avg: 1577.12 milliseconds
Min: 1492.00 milliseconds
Max: 1608.00 milliseconds
Std: 37.84 milliseconds
Counter: 80000000
```

```
Program ran for 1991.00 milliseconds with 80 threads, incrementing 1000000 times per thread
Stats for threads:
Avg: 1645.90 milliseconds
Min: 829.00 milliseconds
Max: 1991.00 milliseconds
Std: 406.04 milliseconds
Counter: 80000000
```

```
Program ran for 2439.00 milliseconds with 800 threads, incrementing 100000 times per thread
Stats for threads:
Avg: 2027.83 milliseconds
Min: 302.00 milliseconds
Max: 2439.00 milliseconds
Std: 517.59 milliseconds
Counter: 80000000
```

```
Program ran for 1750.00 milliseconds with 8000 threads, incrementing 10000 times per thread
Stats for threads:
Avg: 457.33 milliseconds
Min: 0.00 milliseconds
Max: 1750.00 milliseconds
Std: 420.08 milliseconds
Counter: 80000000
```

```
80000 threads with 1000 increments: death
```

**result**: more threads doesn't mean faster execution, it can even make it slower. it's also important to consider the workload per thread and the overhead of creating locks and threads. but there appears to be a sweetspot where multithreading makes sense.


## outputs #3:

```
Program ran for 181.00 milliseconds with 8 threads, incrementing 10000000 times per thread, with a threshold of 100
Stats for threads:
Avg: 173.75 milliseconds
Min: 169.00 milliseconds
Max: 181.00 milliseconds
Std: 5.14 milliseconds
Counter: 80000000
```

```
Program ran for 27.00 milliseconds with 8 threads, incrementing 10000000 times per thread, with a threshold of 10000
Stats for threads:
Avg: 25.00 milliseconds
Min: 23.00 milliseconds
Max: 27.00 milliseconds
Std: 1.22 milliseconds
Counter: 80000000
```

```
Program ran for 114.00 milliseconds with 8000 threads, incrementing 10000 times per thread, with a threshold of 100
Stats for threads:
Avg: 14.56 milliseconds
Min: 0.00 milliseconds
Max: 114.00 milliseconds
Std: 25.90 milliseconds
Counter: 80000000
```

```
Program ran for 0.00 milliseconds with 8000 threads, incrementing 1000 times per thread, with a threshold of 10000
Stats for threads:
Avg: 0.00 milliseconds
Min: 0.00 milliseconds
Max: 0.00 milliseconds
Std: 0.00 milliseconds
Counter: 8000000
```
=> too fast to measure  

**result**: the threshold is important to consider, as it can make a big difference in the performance of the program. if the threshold is too low, the overhead of creating threads and locks can make the program slower than a single-threaded version. if the threshold is too high, the program can be too slow. there's a sweetspot again depending on the workload.
