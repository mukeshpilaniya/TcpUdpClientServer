---
abstract: |
    Application security relies on the memory isolation and memory
    management unit is responsible for that like kernel address space are
    marked as non-accessible from user space and are protected. In this
    paper, we present Meltdown. Meltdown exploit side effects of
    out-of-order execution to allow a user-level program to read data stored
    inside the kernel memory that are marked as non-accessible from user
    program.\
    Such, access is not allowed by the hardware level protection mechanism
    implemented in CPU, but the vulnerability exists in the design of these
    CPU and mostly Intel CPU are affected by meltdown. Meltdown breaks all
    the security guarantees of a system which is not patched by KASLR.
---

<span style="color:red; font-family:Georgia; text-align:center; font-size:2em;">The </span>

\

![image](iiitb_logo.jpg){width="2in" height="2in"}

**(1,0)<span>300</span>**\
\[2mm\]\
\[1mm\] **(1,0)<span>300</span>**\
\[2mm\] <span style="font-variant:small-caps;">**Mentor**</span>\
<span style="font-variant:small-caps;">**Prof.Thangaraju B**</span>\
<span
style="font-variant:small-caps;">**Professor,IIIT-Bangalore**</span>\
\[4cm\]

<span style="font-variant:small-caps;">Mukesh Kumar Pilaniya</span>\
<span style="font-variant:small-caps;">M.Tech $1^{st}$ Year</span>\
<span style="font-variant:small-caps;">MT2019068</span>

Introduction {#secintro}
============

A operating system provide security to each application using memory
isolation technique. Operating system provide guarantee that one
application or program can not access other application data without
permission of operating system(kernel).Kernel level permission bit is
set by hardware level mechanism known as supervisor bit. Supervisor bit
provide isolation between kernel address space and user address space.
So, the idea is that this bit can only set when entering into kernel
code and it’s cleared when switching to user process(mode). This
hardware feature allows operating system to map kernel address space to
address space of each process and it’ is efficient address transitions
mechanism.\
In this paper, we present meltdown, the attack itself is quite
sophisticated, so we break it down into serval small steps and each step
is easy to understand.\
Meltdown does not exploit any kind of software vulnerability it works on
all the major intel system. The root cause of meltdown attack is
**out-of-order execution**.\
Out-of-order execution provide strength to CPU to execute instruction
faster and increase efficiency of CPU, in a latter part we have describe
it in brief. Through out-of-order execution we exploit cache side
channel to retrieve data store in L3 cache. However, out-of-order
influence cache side channel and as a result, an attacker can dump
entire kernel memory by reading cache memory in an out-of-order
execution stream.\
\[1cm\] **Outline**

-   In this section we will describe about

    -   Cache Side channel and attacks

    -   Out-Of-Order Execution

    -   Address Spaces Randomization

-   Meltdown and Its Components

-   Evluation

-   Conclusion

Background {#bkg}
==========

In this section we describe cache side channel, out-of-order execution
and address spaces translation.

Cache Side Channel and Attacks {#cs}
------------------------------

Cache based attack on CPU’s have been around for a number of years,
meltdown and spectre are known issue of Cache side channel. Cache side
channel attack enabled by the micro architecture design of the CPU. Side
channel attacks are part of hardware design so they are difficult to
defeat.\
In order to speed up memory access and address translation CPU contains
the small memory known as cache memory that store frequently used data.
Every instruction and every piece of data that require main memory. The
CPU retrieves the instruction and data from main memory execute that
instruction and store result back in main memory. So, to improve
performance of accessing main memory a hardware level access is made to
various level of cache memory. If the require instruction or data
already in cache memory CPU retrieved that data from cache execute it
and save back to cache, with the help of various write back policy cache
data is written back to main memory eg: - write back and write through.\
Here, the main point is cache memory is used for storing frequently
access data.\
The attacker can not directly read data stored in cache memory but this
does not mean that there is not information leakage, the cache is much
smaller than main memory and nearest to the CPU, so data retrieving from
cache memory is much faster than accessing data from main memory. Cache
side channel exploit this timing difference for retrieving data.
Different cache technique has been proposed in the past including
Evict+Time, Prime+Probe and Flush+Reload.\

![Cache Architecture](cache-architecture.png){height="3in"}

The next piece of background information required to understand the CPU
cache topology of modern processors. Figure \[1\] shows a generic
topology that is common to most of modern CPU’s. Modern CPU’s generally
contain multiple levels of cache memory. In this figure we assume that
CPU is dual core and each core contains its own L1 and L2 cache memory
and L3 cache is shared in between core0 and core1. We exploiting cache
side channel attack in L3 cache only because that is practical to
exploit and for side channel attack, we are using Flush+Reload technique
because it’s works on a single cache line granularity.\
All the technique works this way: manipulate cache to known state, wait
for victim activity and examine what has changed. Program virtual
address map to physical address with the help of page table. L1 cache is
nearest to the CPU and split between a data and an instruction cache. If
the data not found in L1 cache than load instruction passed to the next
Cache hierarchy. This is the point where the page table come into play.
Page table are used to translate virtual address into a physical
address, once’s we have physical address CPU can query into L2 cache and
if data is not found in L2 cache then Load instruction is passed to L3
cache. L3 is inclusive shared cache between core0 and core1.\

### FLUSH+RELOAD attack

Using Flush+Reload an attacker can exploit last-level shared inclusive
cache, an attacker frequently flush a targeted memory location using the
clflush instruction and by measuring the time it takes to reload the
data, the attacker can determine whether data was loaded into the cache
memory by the another application or process in the meantime.\

Out-Of-Order Execution
----------------------

A processor that executes the instructions one after the other, may use
the resources not to its full extent that leads to poor efficiency of
the processor.To improve the efficiency of the processor, there are two
methods,either by executing different sub-steps of sequential
instructions at the same time or maybe executing the instructions
entirely at the same time depending on the availability of resources.
Further improvement within the processor can achieved through
**Out-of-Order Execution**. Out-of-order execution are often achieved by
executing the instruction in an different form.\
Out-of-order execution is an approach that’s utilized in high
performance microprocessors.Out-Of-Order efficiently uses instruction
cycles (Instruction Cycles is a process by which a computer retrieves
program instruction from its memory which can invoke pre-fetching,
determines what action the instruction requires and carries out those
actions.) and reduces costly delay. A processor will execute the
instruction in an order of availability of knowledge or operands rather
than original order of the instructions in the program.By doing so,the
processor will avoid being idle while data is retrieved for the next
instruction in a program.\
Out-of-Order Execution can be regarded as **A Room guarded by a Security
Officer**.The attacker wants to enter the room to get some secret value
but the Security Guard have 2 options either it can allow the attacker
to access the data depending on the permissions or it can deny the
attacker to access the room’s data.\

![Out-Of-Order Execution](out-of-order.png){height="3in"}

In figure 2 the line 3 causes an interrupt because user(attacker) wants
to access the kernel data, this line leads CPU to do two things\
1)The CPU raises an exception since user level program want to access
kernel level data, this causes program or application to either crash if
the program doesn’t have exception handling mechanism.\
2)Mean-while when CPU is busy in permission check the CPU doesn’t want
the other computational parts to be idle since this may degrade the
performance or efficiency so the CPU execute the adjacent instructions
depending on the availability of data operands.\
Now the user is either allowed or denied to access the data, but in both
cases due to **Out-of-Order Execution** the adjacent instructions are
executed. If the permission is granted then the adjacent instructions
are successfully executed but if the permission is denied the program or
application may abruptly end(or may show appropriate message depending
on the Exception Handling Mechanism) but in both cases the value from
the kernel is fetched by the CPU and stored in a temporary register in
**Cache Memory**. The Cache Memory is not flushed in either case of
access permission check, that means the data is still available
somewhere in the Cache. So from outside or user point of view the
attacker has not accessed the data but from inside it can still access
the data through Cache Memory via Timing Difference.\
We will show in the Evaluation(Section 5) the proof of Out-of-Order
Execution that how the attacker can access the secret data.\
\[0.5cm\]

Address Space Randomization
---------------------------

CPU’s support two kind of address spaces so that processes are isolated
from each other.\
**Virtual Address Spaces** where all the virtual addresses are
translated to physical addresses via page translation tables. A virtual
address space is split into a group of pages which will be mapped to the
respective physical memory through a multi-level page translation table.
These page translation tables define the particular virtual to physical
mapping and also protection(like dirty bit etc) properties that are wont
to enforce privilege checks, like readable, writable, executable and
user-accessible. The currently used translation table is held during a
special CPU register. On each context switch(change of process states),
the OS updates this register with subsequent process translation table
address in order to implement per-process virtual address spaces.Because
of that, each process can only refer data that belongs to its virtual
address space. Every virtual address space itself is split into a
**User** and a **Kernel** part i.e each process gets a user address
space and kernel address space. While the user address space are often
accessed by the current or ongoing application, the kernel address space
can only be accessed if the CPU is running in privileged mode(mode bit
set to 1). This is enforced by the operating system which disable the
user-accessible property of the corresponding translation tables. The
kernel address space doesn’t only have memory mapped for the kernel’s
own usage, but it also must perform operations on user pages.
Consequently, the entire physical memory is usually mapped within the
kernel.\
The exploitation of memory corruption attacks majorly requires knowledge
of addresses of particular data. In order to carry out such attacks,
**Address Space Layout Randomization (ASLR)** has been introduced. To
protect kernel, KASLR randomizes the offsets i.e the starting address
from where the system is loaded is changed every time the system is
booted, making attacks harder as they now require to guess the situation
of kernel data structures. However, side channel, the attacker has to
precisely determine the kernel address . A combination of a software bug
and therefore the knowledge of these addresses can lead to privileged
code execution.\
\[1cm\]

Meltdown and its Components
===========================

Meltdown Attack uses flaw in most of the modern processors.These flaws
exists in the CPU’s itself i.e it can be regarded as a Hardware Defect
rather than a software bug, it allows a user-level program to read data
stored inside the kernel memory. We cannot access kernel space due to
the hardware protection mechanism, but a defect exists in the design of
these CPU’s which allows to defeat the hardware protection and thus
carry out these types of attacks. Because the defect exists within the
hardware,it is very difficult to fundamentally fix the problem, unless
we change the CPU’s in our computers.\

Transient Instruction
---------------------

Before doing an in-depth analysis of how meltdown takes place, first we
need to understand what is Transient Instruction.\
Any Instruction that executes Out-of-order in the program and has
measurable side effects is known as Transient Instruction.\
Transient instructions occur all the time, because the CPU runs ahead of
the current instruction all the time to minimize the experienced latency
and, thereby, to maximize the performance or efficiency.These
instructions introduce an exploitable side channel if their operation
depend on a secret value. We specialise in addresses that are mapped
within the attacker’s process, i.e., the user-accessible user space
addresses as well as the user-inaccessible which may kernel space
addresses or other user’s address space.The attacks targeting code that
is executed within the context (i.e., address space) of other user
processes are also possible, but out of context in this work, because
the physical memory (including the memory of other user processes) they
are read through the kernel space.\

Attack Description
------------------

Meltdown attack basically consists of 3 steps:\
**1.To know Secret Kernel Address Space** The content of an
attacker-chosen memory location(kernel space address), which can not be
accessed by the attacker, is loaded into a register.\
**2.Out-of-Order Instruction Execution** A transient
instruction(out-of-order execution) accesses a cache line supported by
the register.\
**3.Using Cache as Side Channel to read the secret data** The attacker
uses Flush+Reload (Timing Difference Attack) to work out the cache line
accessed in the previous step and hence the secret stored at the
specified memory location.\
Since these is for single memory location if the attacker uses these
technique for other locations then it can get the secret from other
locations in kernel space as well which may lead to unavoidable
consequences.\
\[1cm\]

Evaluation
==========

In this section we describe each step that need to done for performing
meltdown attack.\

Environment Setting
-------------------

For setting up our lab environment we are using 32-bit ubuntu 16.04 LTS
in oracle virtual box 6.0, setting related to hardware device is
specified in given image.\

![Environment Setting](environ.PNG){height="3in"}

Code Compilation
----------------

While compiling source code we have to add march=native flag. march
native flag tells the compiler to enable all the instruction subset
supported by the local machine.\
\[0.3cm\]

*gcc-march=native -o myprogram myprogram.c*\

Reading from Cache versus Main Memory
-------------------------------------

cache memory is nearest to CPU so, first CPU check data in cache, if
data is present in cache than it will fetch directly from it and if data
is not present than it will fetch from main memory. Fetching data from
cache is much faster than fetching data from main memory.\
\[0.3cm\]

*gcc -march=native -o CacheTime CacheTime.c*\

![Program Illustrating the Timing Difference of Probing
Array](CacheProgram.PNG){width="7in" height="7in"}

![Access Timing of Probing Array](cachetime.PNG){width="7in"
height="3in"}

Using Cache as Side-Channel
---------------------------

The objective of this section is extracting a secret value used by the
victim function. We are assuming that victim function uses a secret
value as index to load some values from an array and the secret value
can not be accessed from the outside. Our objective is to use side
channel to get this secret value. The technique that we are using for
retrieving secret value is Flush+Reload.\
\[1cm\] First Flush the entire array from the cache memory to make sure
that array is not cached. After that we invoke the victim function,
which access of the array element based on the value of secret, that
array index value is cached by the cache memory. And the final step is
reloading the entire array and measure the time it takes to reload each
element. So, if the array index is previously cached than it requires
less CPU cycle.\
The output of the program shown in fig 6 below:\
\[0.2cm\]

**Output: -**\
array \[126\*4096 + 1024\] is in cache.\
The Secret = 126.\
gcc -march=native -o FlushReload FlushReload.c\

![Program showing Cache is used as a Side
Channel](Flush+Reload1.png){width="7in" height="7in"}

 Preparation for Meltdown Attack
--------------------------------

For preparing meltdown attack we have to placed secret data in kernel
space and we show that user-level program can access that data without
going into kernel space. The implementation of the kernel module is
provided in MeltdownKernel.c.\
*make*\
*sudo insmod MeltdownKernel.ko*\
*dmesg*\

![Meltdown Attack](meltdownModule.PNG){height="0.5in"}

Exception Handling
------------------

When user program tries to access kernel memory than memory access
violation is triggered and segmentation fault is generated.\

![Exception Handling](exception.PNG){width="5in" height="4in"}

Out-of-Order Execution
----------------------

Meltdown is a race condition vulnerability, which involves racing
between out-of-order execution and access block so, for exploiting
meltdown successfully we must have to win race condition. To win race
condition we have to keep CPU execution busy somehow and for that we are
using assembly code form.\

![Out-of-Order Execution](out-of-order1.PNG){width="5in" height="2in"}

Meltdown Attack
---------------

To make attack more practical and improve efficiency of attack we create
a score array of size 256, one element for each possible secret value
then we run attack multiple times.\

*gcc -march=native -o MeltdownAttack MeltdownAttack.c*

![Reading Secret Value from Kernel](result.PNG){height="0.5in"}

The code in MeltdownAttack can only steals a one byte secret from the
kernel.\

Conclusion
==========

In this paper we presented Meltdown, a vulnerability or attack to the
software system which can read kernel data or secret data from an
underprivileged user-level program, since it does not depend on any
software vulnerability as well as it is independent of the type of
Operating System.\
To prevent Meltdown KAISER can be used more accurately we can say that
it is a counter-measure to Meltdown Attack, it is a kernel modification
to not have the kernel mapped in the user space.This modification to
protect side channel attacks breaking KASLR(Kernel Address Space Layout
Randomization) but it also prevents Meltdown.\

Bibliography
============

-   Moritz Lipp,Michael Schwarz,Daniel Gruss\
    January 3,2018 - [*Metldown
    paper*](https://arxiv.org/pdf/1801.01207.pdf)\

-   Jacek Galowicz\
    January 3,2018 - [*Meltdown
    Blogpost*](https://blog.cyberus-technology.de/posts/2018-01-03-meltdown.html)\

-   Jann Horn, Project Zero\
    January 3,2018 - [*Reading privileged memory with a
    side-channel*](https://googleprojectzero.blogspot.com/2018/01/reading-privileged-memory-with-side.html)\

-   Jake Edge\
    October 9, 2013 - [*Kernel Address Space
    Layout Randomization(KASLR)*](https://lwn.net/Articles/569635/)\

-   Daniel Gruss,Clementine Maurice, Klaus Wagner, and Stefan Mangard\
    [*Flush+Flush:A Fast and Stealthy Cache
    Attack*](https://gruss.cc/files/flushflush.pdf)\
