# Homework - Chapter 5 - Interlude: Process API

## 1. Run ./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it.

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 10

ARG seed 10
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action: a forks b
Process Tree?
Action: a forks c
Process Tree?
Action: c EXITS
Process Tree?
Action: a forks d
Process Tree?
Action: a forks e
Process Tree?
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 10 -c

ARG seed 10
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 12

ARG seed 12
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action: a forks b
Process Tree?
Action: a forks c
Process Tree?
Action: b forks d
Process Tree?
Action: d forks e
Process Tree?
Action: d forks f
Process Tree?
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 12 -c

ARG seed 12
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: b forks d
                               a
                               ├── b
                               │   └── d
                               └── c
Action: d forks e
                               a
                               ├── b
                               │   └── d
                               │       └── e
                               └── c
Action: d forks f
                               a
                               ├── b
                               │   └── d
                               │       ├── e
                               │       └── f
                               └── c
```
## 2. One control the simulator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percent- age changes? Check your answer with -c.

Bei geringer fork-percentage kurzer Baum, bei hoher Baum mit vielen Ästen/Verzweigungen -> langer Baum.
```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -a 100 -f 0.1 -s 12 -c -F

ARG seed 12
ARG fork_percentage 0.1
ARG actions 100
ARG action_list 
ARG show_tree False
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: b EXITS
Action: a forks c
Action: c forks d
Action: c EXITS
Action: d forks e
Action: e EXITS
Action: d EXITS
Action: a forks f
Action: f EXITS
Action: a forks g
Action: g EXITS
Action: a forks h
Action: h EXITS
Action: a forks i
Action: i forks j
Action: j EXITS
Action: i EXITS
Action: a forks k
Action: k EXITS
Action: a forks l
Action: l EXITS
Action: a forks m
Action: m EXITS
Action: a forks n
Action: a forks o
Action: o EXITS
Action: n EXITS
Action: a forks p
Action: a forks q
Action: a forks r
Action: q EXITS
Action: r EXITS
Action: p EXITS
Action: a forks s
Action: s EXITS
Action: a forks t
Action: t EXITS
Action: a forks u
Action: u forks v
Action: u EXITS
Action: v EXITS
Action: a forks w
Action: w EXITS
Action: a forks x
Action: x EXITS
Action: a forks y
Action: y EXITS
Action: a forks z
Action: z EXITS
Action: a forks A
Action: A EXITS
Action: a forks B
Action: B EXITS
Action: a forks C
Action: C EXITS
Action: a forks D
Action: D EXITS
Action: a forks E
Action: E EXITS
Action: a forks F
Action: F EXITS
Action: a forks G
Action: G EXITS
Action: a forks H
Action: H EXITS
Action: a forks I
Action: I EXITS
Action: a forks J
Action: J EXITS
Action: a forks K
Action: K EXITS
Action: a forks L
Action: L forks M
Action: M EXITS
Action: L EXITS
Action: a forks N
Action: N EXITS
Action: a forks O
Action: a forks P
Action: a forks Q
Action: O EXITS
Action: P EXITS
Action: Q EXITS
Action: a forks R
Action: R EXITS
Action: a forks S
Action: S EXITS
Action: a forks T
Action: a forks U
Action: U EXITS
Action: T EXITS
Action: a forks V
Action: V EXITS
Action: a forks W
Action: W EXITS
Action: a forks X
Action: X EXITS
Action: a forks Y
Action: Y EXITS

                        Final Process Tree:
                               a

bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -a 100 -f 0.9 -s 12 -c -F

ARG seed 12
ARG fork_percentage 0.9
ARG actions 100
ARG action_list 
ARG show_tree False
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: a forks c
Action: b forks d
Action: d forks e
Action: d forks f
Action: d forks g
Action: d forks h
Action: h forks i
Action: h forks j
Action: g forks k
Action: e forks l
Action: a forks m
Action: l forks n
Action: b forks o
Action: o EXITS
Action: f forks p
Action: e forks q
Action: c forks r
Action: a forks s
Action: p forks t
Action: h forks u
Action: j forks v
Action: a forks w
Action: w forks x
Action: q EXITS
Action: h forks y
Action: r forks z
Action: f forks A
Action: m forks B
Action: n forks C
Action: y forks D
Action: p forks E
Action: m forks F
Action: z forks G
Action: t forks H
Action: y forks I
Action: j forks J
Action: x forks K
Action: s forks L
Action: k forks M
Action: L forks N
Action: M forks O
Action: M forks P
Action: h forks Q
Action: N forks R
Action: l forks S
Action: p forks T
Action: a forks U
Action: D forks V
Action: V EXITS
Action: b forks W
Action: M forks X
Action: G forks Y
Action: B forks Z
Action: G forks aa
Action: Y forks ab
Action: i forks ac
Action: W forks ad
Action: ab forks ae
Action: N forks af
Action: l forks ag
Action: p forks ah
Action: P forks ai
Action: ac forks aj
Action: p forks ak
Action: aj forks al
Action: O forks am
Action: ak EXITS
Action: B forks an
Action: ag forks ao
Action: M forks ap
Action: z forks aq
Action: M forks ar
Action: X forks as
Action: ae EXITS
Action: an forks at
Action: ad forks au
Action: g forks av
Action: x forks aw
Action: Z EXITS
Action: S forks ax
Action: N forks ay
Action: D forks az
Action: F forks aA
Action: ac forks aB
Action: g forks aC
Action: af forks aD
Action: ac forks aE
Action: E EXITS
Action: O forks aF
Action: n forks aG
Action: C forks aH
Action: B forks aI
Action: y forks aJ
Action: M forks aK
Action: aE forks aL
Action: am forks aM
Action: Q forks aN
Action: aA forks aO
Action: Q forks aP

                        Final Process Tree:
                               a
                               ├── b
                               │   ├── d
                               │   │   ├── e
                               │   │   │   └── l
                               │   │   │       ├── n
                               │   │   │       │   ├── C
                               │   │   │       │   │   └── aH
                               │   │   │       │   └── aG
                               │   │   │       ├── S
                               │   │   │       │   └── ax
                               │   │   │       └── ag
                               │   │   │           └── ao
                               │   │   ├── f
                               │   │   │   ├── p
                               │   │   │   │   ├── t
                               │   │   │   │   │   └── H
                               │   │   │   │   ├── T
                               │   │   │   │   └── ah
                               │   │   │   └── A
                               │   │   ├── g
                               │   │   │   ├── k
                               │   │   │   │   └── M
                               │   │   │   │       ├── O
                               │   │   │   │       │   ├── am
                               │   │   │   │       │   │   └── aM
                               │   │   │   │       │   └── aF
                               │   │   │   │       ├── P
                               │   │   │   │       │   └── ai
                               │   │   │   │       ├── X
                               │   │   │   │       │   └── as
                               │   │   │   │       ├── ap
                               │   │   │   │       ├── ar
                               │   │   │   │       └── aK
                               │   │   │   ├── av
                               │   │   │   └── aC
                               │   │   └── h
                               │   │       ├── i
                               │   │       │   └── ac
                               │   │       │       ├── aj
                               │   │       │       │   └── al
                               │   │       │       ├── aB
                               │   │       │       └── aE
                               │   │       │           └── aL
                               │   │       ├── j
                               │   │       │   ├── v
                               │   │       │   └── J
                               │   │       ├── u
                               │   │       ├── y
                               │   │       │   ├── D
                               │   │       │   │   └── az
                               │   │       │   ├── I
                               │   │       │   └── aJ
                               │   │       └── Q
                               │   │           ├── aN
                               │   │           └── aP
                               │   └── W
                               │       └── ad
                               │           └── au
                               ├── c
                               │   └── r
                               │       └── z
                               │           ├── G
                               │           │   ├── Y
                               │           │   │   └── ab
                               │           │   └── aa
                               │           └── aq
                               ├── m
                               │   ├── B
                               │   │   ├── an
                               │   │   │   └── at
                               │   │   └── aI
                               │   └── F
                               │       └── aA
                               │           └── aO
                               ├── s
                               │   └── L
                               │       └── N
                               │           ├── R
                               │           ├── af
                               │           │   └── aD
                               │           └── ay
                               ├── w
                               │   └── x
                               │       ├── K
                               │       └── aw
                               └── U

```
## 3. Now, switch the output by using the -t flag (e.g., run ./fork.py -t). Given a set of process trees, can you tell which actions were taken?

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -t -s 20

ARG seed 20
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree True
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action?
                               a
                               └── b
Action?
                               a
Action?
                               a
                               └── c
Action?
                               a
                               └── c
                                   └── d
Action?
                               a
                               ├── c
                               │   └── d
                               └── e
```
a+b,b-,a+c,c+d,a+e
```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 20

ARG seed 20
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action: a forks b
Process Tree?
Action: b EXITS
Process Tree?
Action: a forks c
Process Tree?
Action: c forks d
Process Tree?
Action: a forks e
Process Tree?
```
## 4. One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example:./fork.py -A a+b,b+c,c+d,c+e,c-. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.

FALSCH - Child Prozesse von C werden Child Prozesse des Parents von C sprich childs von B.

Child Prozesse von C werden Child Prozesse von A sprich dem Hauptprozess
```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -A a+b,b+c,c+d,c+e,c- -c

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```
RICHTIG bei -R flag - Child Prozesse von C werden Child Prozesse des Parents von C sprich childs von B.
```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -A a+b,b+c,c+d,c+e,c- -R -c

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent True
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```
## 5. One last flag to explore is the -F flag, which skips intermediate steps and only asks to fill in the final process tree. Run ./fork.py -F and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.
a---b
|   |--e
|
|---c
|   |---d
|
|---f
```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 50 -F

ARG seed 50
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree False
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action: a forks b
Action: a forks c
Action: c forks d
Action: b forks e
Action: a forks f

                        Final Process Tree?

bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 50 -F -c

ARG seed 50
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree False
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: a forks c
Action: c forks d
Action: b forks e
Action: a forks f

                        Final Process Tree:
                               a
                               ├── b
                               │   └── e
                               ├── c
                               │   └── d
                               └── f

```
## 6. Finally, use both -t and -F together. This shows the final process tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 34 -t -F

ARG seed 34
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree True
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action?
Action?
Action?
Action?
Action?

                        Final Process Tree:
                               a
                               ├── c
                               │   └── e
                               └── d
```

a forks b
b exits
a forks c
a forks d
c forks e

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 34 -t -F -c

ARG seed 34
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree True
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: b EXITS
Action: a forks c
Action: a forks d
Action: c forks e

                        Final Process Tree:
                               a
                               ├── c
                               │   └── e
                               └── d

```

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 22 -t -F

ARG seed 22
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree True
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action?
Action?
Action?
Action?
Action?

                        Final Process Tree:
                               a
                               ├── c
                               └── d
                                   └── e

```

a forks b
b exits
a forks c
a forks d
d forks e

```sh
bsys@09e654bfdad0:~/workspace/bsys/ostep-homework/5-cpu-api$ ./fork.py -s 22 -t -F -c

ARG seed 22
ARG fork_percentage 0.7
ARG actions 5
ARG action_list 
ARG show_tree True
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: a forks c
Action: b forks d
Action: b EXITS
Action: d forks e

                        Final Process Tree:
                               a
                               ├── c
                               └── d
                                   └── e

´´´