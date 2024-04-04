
## Homework - Chapter 13: The Abstraction: Adress Spaces

# 2. Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?

```
bsys@30921e249eed:~/bsys$ free --mega
               total        used        free      shared  buff/cache   available
Mem:           16733        1843        5670           5        9220       14546
Swap:           4294           0        4294
```

nein theoretisch 32gb vorhanden

# 4.

pre
```
               total        used        free      shared  buff/cache   available
Mem:           16733        1222       15025           1         485       15221
Swap:           4294         872        3422
```



```
bsys@30921e249eed:~/bsys/ostep-homework/13-sol/solution_jk$ ./memory-user 1000

               total        used        free      shared  buff/cache   available
Mem:           16733        2220       14028           1         484       14223
Swap:           4294         873        3421
```



```
bsys@30921e249eed:~/bsys/ostep-homework/13-sol/solution_jk$ ./memory-user 8000
               total        used        free      shared  buff/cache   available
Mem:           16733        9230        7018           1         484        7213
Swap:           4294         875        3419
```



```
bsys@30921e249eed:~/bsys/ostep-homework/13-sol/solution_jk$ ./memory-user 16200

               total        used        free      shared  buff/cache   available
Mem:           16733       16198         199           1         335         245
Swap:           4294        2191        2103
```

# 7. Now run pmap on some of these processes. using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?

```
bsys@30921e249eed:~/bsys$ ps auxw
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.0  0.0   7664     0 ?        Ss   19:21   0:00 /bin/bash /entrypoint.sh
root           7  0.0  0.0  36848  6980 ?        S    19:21   0:00 /usr/bin/python3 /usr/bin/supervisord -c /etc/supervisor/conf.d/s
root           8  0.0  0.0  15436     8 ?        S    19:21   0:00 sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups
bsys          79  0.0  0.0   2892     0 ?        S    19:22   0:00 sh /home/bsys/.vscode-server/cli/servers/Stable-863d2581ecda68499
bsys         141  0.3  0.3 959504 50448 ?        Sl   19:22   0:07 /home/bsys/.vscode-server/cli/servers/Stable-863d2581ecda6849923a
root         165  0.0  0.0  16892    28 ?        Ss   19:22   0:00 sshd: bsys [priv]
bsys         176  0.0  0.0  17608  1036 ?        S    19:22   0:02 sshd: bsys@notty
bsys         177  0.0  0.0   7824  1776 ?        Ss   19:22   0:00 bash
bsys         197  0.1  0.0  60412  1832 ?        Sl   19:22   0:03 /home/bsys/.vscode-server/code-863d2581ecda6849923a2118d93a088b07
bsys         235  1.2  0.9 12146356 150072 ?     Sl   19:22   0:27 /home/bsys/.vscode-server/cli/servers/Stable-863d2581ecda6849923a
bsys         246  0.0  0.0 850852 12708 ?        Sl   19:22   0:00 /home/bsys/.vscode-server/cli/servers/Stable-863d2581ecda6849923a
bsys         259  0.2  0.1 762876 24684 ?        Rl   19:22   0:05 /home/bsys/.vscode-server/cli/servers/Stable-863d2581ecda6849923a
bsys         293  0.0  0.0   8088  2748 pts/0    Ss+  19:22   0:00 /bin/bash --init-file /home/bsys/.vscode-server/cli/servers/Stabl
bsys         309  0.7  0.1 177436 31436 ?        Sl   19:22   0:16 /home/bsys/.vscode-server/extensions/ms-vscode.cpptools-1.19.9-li
bsys         366  0.0  0.0 605408  6112 ?        Sl   19:22   0:00 /home/bsys/.vscode-server/cli/servers/Stable-863d2581ecda6849923a
bsys         551  0.0  0.0   8088  2608 pts/1    Ss   19:23   0:00 /bin/bash --init-file /home/bsys/.vscode-server/cli/servers/Stabl
bsys         567  0.0  0.0   8088  2752 pts/2    Ss+  19:23   0:00 /bin/bash --init-file /home/bsys/.vscode-server/cli/servers/Stabl
bsys        8307  0.0  0.1 608804 23760 ?        Sl   19:41   0:00 /home/bsys/.vscode-server/cli/servers/Stable-863d2581ecda6849923a
bsys        8375  0.0  0.0   7956  2756 pts/3    Ss+  19:41   0:00 /bin/bash
bsys       12071  0.0  0.0   6092  1004 ?        S    19:58   0:00 sleep 180
bsys       12124  0.0  0.0  10392  1656 pts/1    R+   19:59   0:00 ps auxw
```



```
bsys@30921e249eed:~/bsys$ pmap 177
177:   bash
000055a63940d000    188K r---- bash
000055a63943c000    892K r-x-- bash
000055a63951b000    232K r---- bash
000055a639556000     16K r---- bash
000055a63955a000     36K rw--- bash
000055a639563000     44K rw---   [ anon ]
000055a63a960000    264K rw---   [ anon ]
00007f4276c5a000   3300K r---- locale-archive
00007f4276f93000     12K rw---   [ anon ]
00007f4276f96000    160K r---- libc.so.6
00007f4276fbe000   1620K r-x-- libc.so.6
00007f4277153000    352K r---- libc.so.6
00007f42771ab000      4K ----- libc.so.6
00007f42771ac000     16K r---- libc.so.6
00007f42771b0000      8K rw--- libc.so.6
00007f42771b2000     52K rw---   [ anon ]
00007f42771bf000     56K r---- libtinfo.so.6.3
00007f42771cd000     68K r-x-- libtinfo.so.6.3
00007f42771de000     56K r---- libtinfo.so.6.3
00007f42771ec000     16K r---- libtinfo.so.6.3
00007f42771f0000      4K rw--- libtinfo.so.6.3
00007f42771f2000     28K r--s- gconv-modules.cache
00007f42771f9000      8K rw---   [ anon ]
00007f42771fb000      8K r---- ld-linux-x86-64.so.2
00007f42771fd000    168K r-x-- ld-linux-x86-64.so.2
00007f4277227000     44K r---- ld-linux-x86-64.so.2
00007f4277233000      8K r---- ld-linux-x86-64.so.2
00007f4277235000      8K rw--- ld-linux-x86-64.so.2
00007ffd0dd4a000    132K rw---   [ stack ]
00007ffd0dd7b000     16K r----   [ anon ]
00007ffd0dd7f000      8K r-x--   [ anon ]
 total             7824K
```



```
bsys@30921e249eed:~/bsys$ pmap -x 177
177:   bash
Address           Kbytes     RSS   Dirty Mode  Mapping
000055a63940d000     188       0       0 r---- bash
000055a63943c000     892     612       0 r-x-- bash
000055a63951b000     232     144       0 r---- bash
000055a639556000      16       4       0 r---- bash
000055a63955a000      36      16      12 rw--- bash
000055a639563000      44      16      16 rw---   [ anon ]
000055a63a960000     264     100      72 rw---   [ anon ]
00007f4276c5a000    3300       4       0 r---- locale-archive
00007f4276f93000      12       8       8 rw---   [ anon ]
00007f4276f96000     160       0       0 r---- libc.so.6
00007f4276fbe000    1620     760       0 r-x-- libc.so.6
00007f4277153000     352      64       0 r---- libc.so.6
00007f42771ab000       4       0       0 ----- libc.so.6
00007f42771ac000      16      12       0 r---- libc.so.6
00007f42771b0000       8       8       4 rw--- libc.so.6
00007f42771b2000      52      12       4 rw---   [ anon ]
00007f42771bf000      56       0       0 r---- libtinfo.so.6.3
00007f42771cd000      68       0       0 r-x-- libtinfo.so.6.3
00007f42771de000      56       0       0 r---- libtinfo.so.6.3
00007f42771ec000      16       0       0 r---- libtinfo.so.6.3
00007f42771f0000       4       0       0 rw--- libtinfo.so.6.3
00007f42771f2000      28       0       0 r--s- gconv-modules.cache
00007f42771f9000       8       0       0 rw---   [ anon ]
00007f42771fb000       8       0       0 r---- ld-linux-x86-64.so.2
00007f42771fd000     168       0       0 r-x-- ld-linux-x86-64.so.2
00007f4277227000      44       0       0 r---- ld-linux-x86-64.so.2
00007f4277233000       8       0       0 r---- ld-linux-x86-64.so.2
00007f4277235000       8       0       0 rw--- ld-linux-x86-64.so.2
00007ffd0dd4a000     132      12      12 rw---   [ stack ]
00007ffd0dd7b000      16       0       0 r----   [ anon ]
00007ffd0dd7f000       8       4       0 r-x--   [ anon ]
---------------- ------- ------- ------- 
total kB            7824    1776     128
```



```
bsys@30921e249eed:~/bsys$ pmap -XX  177
177:   bash
     Address Perm   Offset Device  Inode Size KernelPageSize MMUPageSize  Rss Pss Shared_Clean Shared_Dirty Private_Clean Private_Dirty Referenced Anonymous LazyFree AnonHugePages ShmemPmdMapped FilePmdMapped Shared_Hugetlb Private_Hugetlb Swap SwapPss Locked THPeligible              VmFlags Mapping
55a63940d000 r--p 00000000  08:30 166361  188              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me bash
55a63943c000 r-xp 0002f000  08:30 166361  892              4           4  612 117          612            0             0             0        612         0        0             0              0             0              0               0    0       0      0           0       rd ex mr mw me bash
55a63951b000 r--p 0010e000  08:30 166361  232              4           4  144  36          140            0             4             0        144         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me bash
55a639556000 r--p 00148000  08:30 166361   16              4           4    4   4            0            0             4             0          4         4        0             0              0             0              0               0   12      12      0           0       rd mr mw me ac bash
55a63955a000 rw-p 0014c000  08:30 166361   36              4           4   16  16            0            0             4            12         12        16        0             0              0             0              0               0   20      20      0           0    rd wr mr mw me ac bash
55a639563000 rw-p 00000000  00:00      0   44              4           4   16  16            0            0             0            16          8        16        0             0              0             0              0               0    0       0      0           0    rd wr mr mw me ac 
55a63a960000 rw-p 00000000  00:00      0  264              4           4  100 100            0            0            28            72         64       100        0             0              0             0              0               0   92      92      0           0    rd wr mr mw me ac [heap]
7f4276c5a000 r--p 00000000  08:30 176186 3300              4           4    4   0            4            0             0             0          4         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me locale-archive
7f4276f93000 rw-p 00000000  00:00      0   12              4           4    8   8            0            0             0             8          4         8        0             0              0             0              0               0    0       0      0           0    rd wr mr mw me ac 
7f4276f96000 r--p 00000000  08:30 166553  160              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me libc.so.6
7f4276fbe000 r-xp 00028000  08:30 166553 1620              4           4  760  79          760            0             0             0        760         0        0             0              0             0              0               0    0       0      0           0       rd ex mr mw me libc.so.6
7f4277153000 r--p 001bd000  08:30 166553  352              4           4   64   4           64            0             0             0         64         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me libc.so.6
7f42771ab000 ---p 00215000  08:30 166553    4              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0             mr mw me libc.so.6
7f42771ac000 r--p 00215000  08:30 166553   16              4           4   12  12            0            0            12             0         12        12        0             0              0             0              0               0    4       4      0           0       rd mr mw me ac libc.so.6
7f42771b0000 rw-p 00219000  08:30 166553    8              4           4    8   8            0            0             4             4          8         8        0             0              0             0              0               0    0       0      0           0    rd wr mr mw me ac libc.so.6
7f42771b2000 rw-p 00000000  00:00      0   52              4           4   12  12            0            0             8             4         12        12        0             0              0             0              0               0    8       8      0           0    rd wr mr mw me ac 
7f42771bf000 r--p 00000000  08:30  54537   56              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me libtinfo.so.6.3
7f42771cd000 r-xp 0000e000  08:30  54537   68              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0       rd ex mr mw me libtinfo.so.6.3
7f42771de000 r--p 0001f000  08:30  54537   56              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me libtinfo.so.6.3
7f42771ec000 r--p 0002c000  08:30  54537   16              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0   16      16      0           0       rd mr mw me ac libtinfo.so.6.3
7f42771f0000 rw-p 00030000  08:30  54537    4              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    4       4      0           0    rd wr mr mw me ac libtinfo.so.6.3
7f42771f2000 r--s 00000000  08:30 168235   28              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0          rd mr me ms gconv-modules.cache
7f42771f9000 rw-p 00000000  00:00      0    8              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    8       8      0           0    rd wr mr mw me ac 
7f42771fb000 r--p 00000000  08:30 166503    8              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me ld-linux-x86-64.so.2
7f42771fd000 r-xp 00002000  08:30 166503  168              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0       rd ex mr mw me ld-linux-x86-64.so.2
7f4277227000 r--p 0002c000  08:30 166503   44              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0          rd mr mw me ld-linux-x86-64.so.2
7f4277233000 r--p 00037000  08:30 166503    8              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    8       8      0           0       rd mr mw me ac ld-linux-x86-64.so.2
7f4277235000 rw-p 00039000  08:30 166503    8              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    8       8      0           0    rd wr mr mw me ac ld-linux-x86-64.so.2
7ffd0dd4a000 rw-p 00000000  00:00      0  132              4           4   12  12            0            0             0            12          4        12        0             0              0             0              0               0    4       4      0           0 rd wr mr mw me gd ac [stack]
7ffd0dd7b000 r--p 00000000  00:00      0   16              4           4    0   0            0            0             0             0          0         0        0             0              0             0              0               0    0       0      0           0    rd mr pf io de dd [vvar]
7ffd0dd7f000 r-xp 00000000  00:00      0    8              4           4    4   0            4            0             0             0          4         0        0             0              0             0              0               0    0       0      0           0    rd ex mr mw me de [vdso]
                                         ==== ============== =========== ==== === ============ ============ ============= ============= ========== ========= ======== ============= ============== ============= ============== =============== ==== ======= ====== =========== 
                                         7824            124         124 1776 424         1584            0            64           128       1716       188        0             0              0             0              0               0  184     184      0           0 KB 
```



```
bsys@30921e249eed:~/bsys$ pmap -p 177
177:   bash
000055a63940d000    188K r---- /usr/bin/bash
000055a63943c000    892K r-x-- /usr/bin/bash
000055a63951b000    232K r---- /usr/bin/bash
000055a639556000     16K r---- /usr/bin/bash
000055a63955a000     36K rw--- /usr/bin/bash
000055a639563000     44K rw---   [ anon ]
000055a63a960000    264K rw---   [ anon ]
00007f4276c5a000   3300K r---- /usr/lib/locale/locale-archive
00007f4276f93000     12K rw---   [ anon ]
00007f4276f96000    160K r---- /usr/lib/x86_64-linux-gnu/libc.so.6
00007f4276fbe000   1620K r-x-- /usr/lib/x86_64-linux-gnu/libc.so.6
00007f4277153000    352K r---- /usr/lib/x86_64-linux-gnu/libc.so.6
00007f42771ab000      4K ----- /usr/lib/x86_64-linux-gnu/libc.so.6
00007f42771ac000     16K r---- /usr/lib/x86_64-linux-gnu/libc.so.6
00007f42771b0000      8K rw--- /usr/lib/x86_64-linux-gnu/libc.so.6
00007f42771b2000     52K rw---   [ anon ]
00007f42771bf000     56K r---- /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
00007f42771cd000     68K r-x-- /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
00007f42771de000     56K r---- /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
00007f42771ec000     16K r---- /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
00007f42771f0000      4K rw--- /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
00007f42771f2000     28K r--s- /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
00007f42771f9000      8K rw---   [ anon ]
00007f42771fb000      8K r---- /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
00007f42771fd000    168K r-x-- /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
00007f4277227000     44K r---- /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
00007f4277233000      8K r---- /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
00007f4277235000      8K rw--- /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
00007ffd0dd4a000    132K rw---   [ stack ]
00007ffd0dd7b000     16K r----   [ anon ]
00007ffd0dd7f000      8K r-x--   [ anon ]
 total             7824K


code, anonymous memory -> swap, libraries, heap


```

# 8. Finally, let's run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?

```
bsys@30921e249eed:~/bsys$ pmap 11465
11465:   ./memory-user 16200
00005564d8584000      4K r---- memory-user
00005564d8585000      4K r-x-- memory-user
00005564d8586000      4K r---- memory-user
00005564d8587000      4K r---- memory-user
00005564d8588000      4K rw--- memory-user
00005564d9a6b000    132K rw---   [ anon ]
00007f2ef7fe7000 15820328K rw---   [ anon ]
00007f32bd971000    160K r---- libc.so.6
00007f32bd999000   1620K r-x-- libc.so.6
00007f32bdb2e000    352K r---- libc.so.6
00007f32bdb86000      4K ----- libc.so.6
00007f32bdb87000     16K r---- libc.so.6
00007f32bdb8b000      8K rw--- libc.so.6
00007f32bdb8d000     52K rw---   [ anon ]
00007f32bdba2000      8K rw---   [ anon ]
00007f32bdba4000      8K r---- ld-linux-x86-64.so.2
00007f32bdba6000    168K r-x-- ld-linux-x86-64.so.2
00007f32bdbd0000     44K r---- ld-linux-x86-64.so.2
00007f32bdbdc000      8K r---- ld-linux-x86-64.so.2
00007f32bdbde000      8K rw--- ld-linux-x86-64.so.2
00007ffee619f000    132K rw---   [ stack ]
00007ffee61c9000     16K r----   [ anon ]
00007ffee61cd000      8K r-x--   [ anon ]
 total         15823092K
```


