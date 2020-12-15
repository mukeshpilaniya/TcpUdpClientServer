

International Institute of Information

Technology(I I IT), Bangalore

Meltdown Attack

Mentor

Prof.Thangaraju B

Professor,IIIT-Bangalore

Mukesh Kumar Pilaniya

st

Shreyansh Jain

st

M.Tech 1 Year

MT2019068

M.Tech 1 Year

MT2019106





Contents

[1](#br4)[ ](#br4)[Introduction](#br4)

1

[2](#br5)[ ](#br5)[Background](#br5)

2

2

3

3

5

[2.1](#br5)[ ](#br5)[Cache](#br5)[ ](#br5)[Side](#br5)[ ](#br5)[Channel](#br5)[ ](#br5)[and](#br5)[ ](#br5)[Attacks](#br5)[ ](#br5). . . . . . . . . . . . . . . . . . . . . . . .

[2.1.1](#br6)[ ](#br6)[FLUSH+RELOAD](#br6)[ ](#br6)[attack](#br6)[ ](#br6). . . . . . . . . . . . . . . . . . . . . . . .

[2.2](#br6)[ ](#br6)[Out-Of-Order](#br6)[ ](#br6)[Execution](#br6)[ ](#br6). . . . . . . . . . . . . . . . . . . . . . . . . . . . .

[2.3](#br8)[ ](#br8)[Address](#br8)[ ](#br8)[Space](#br8)[ ](#br8)[Randomization](#br8)[ ](#br8). . . . . . . . . . . . . . . . . . . . . . . . . .

[3](#br8)[ ](#br8)[Meltdown](#br8)[ ](#br8)[and](#br8)[ ](#br8)[its](#br8)[ ](#br8)[Components](#br8)

[3.1](#br9)[ ](#br9)[Transient](#br9)[ ](#br9)[Instruction](#br9)[ ](#br9). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

[3.2](#br9)[ ](#br9)[Attack](#br9)[ ](#br9)[Description](#br9)[ ](#br9). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

5

6

6

[4](#br10)[ ](#br10)[Evaluation](#br10)

7

7

7

7

9

[4.1](#br10)[ ](#br10)[Environment](#br10)[ ](#br10)[Setting](#br10)[ ](#br10). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

[4.2](#br10)[ ](#br10)[Code](#br10)[ ](#br10)[Compilation](#br10)[ ](#br10). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

[4.3](#br10)[ ](#br10)[Reading](#br10)[ ](#br10)[from](#br10)[ ](#br10)[Cache](#br10)[ ](#br10)[versus](#br10)[ ](#br10)[Main](#br10)[ ](#br10)[Memory](#br10)[ ](#br10). . . . . . . . . . . . . . . . . . .

[4.4](#br12)[ ](#br12)[Using](#br12)[ ](#br12)[Cache](#br12)[ ](#br12)[as](#br12)[ ](#br12)[Side-Channel](#br12)[ ](#br12). . . . . . . . . . . . . . . . . . . . . . . . . .

[4.5](#br14)[ ](#br14)[Prepration](#br14)[ ](#br14)[for](#br14)[ ](#br14)[Meltdown](#br14)[ ](#br14)[Attack](#br14)[ ](#br14). . . . . . . . . . . . . . . . . . . . . . . . . 11

[4.6](#br16)[ ](#br16)[Exception](#br16)[ ](#br16)[Handling](#br16)[ ](#br16). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 13

[4.7](#br17)[ ](#br17)[Out-of-Order](#br17)[ ](#br17)[Execution](#br17)[ ](#br17). . . . . . . . . . . . . . . . . . . . . . . . . . . . . 14

[4.8](#br17)[ ](#br17)[Meltdown](#br17)[ ](#br17)[Attack](#br17)[ ](#br17). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 14

[5](#br18)[ ](#br18)[Prevention](#br18)[ ](#br18)[of](#br18)[ ](#br18)[Meltdown](#br18)[ ](#br18)[Attack](#br18)[ ](#br18)[-](#br18)[ ](#br18)[KAISER](#br18)[ ](#br18)[Patch](#br18)

[6](#br19)[ ](#br19)[Conclusion](#br19)

15

16





List of Figures

[1](#br6)

[2](#br7)

[3](#br10)

[4](#br11)

[5](#br12)

[6](#br13)

[7](#br14)

[8](#br15)

[9](#br16)

[Cache](#br6)[ ](#br6)[Architecture](#br6)[ ](#br6). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

3

4

7

8

9

[Out-Of-Order](#br7)[ ](#br7)[Execution](#br7)[ ](#br7). . . . . . . . . . . . . . . . . . . . . . . . . . . . .

[Environment](#br10)[ ](#br10)[Setting](#br10)[ ](#br10). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

[Program](#br11)[ ](#br11)[Illustrating](#br11)[ ](#br11)[the](#br11)[ ](#br11)[Timing](#br11)[ ](#br11)[Diﬀerence](#br11)[ ](#br11)[of](#br11)[ ](#br11)[Probing](#br11)[ ](#br11)[Array](#br11)[ ](#br11). . . . . . . . .

[Access](#br12)[ ](#br12)[Timing](#br12)[ ](#br12)[of](#br12)[ ](#br12)[Probing](#br12)[ ](#br12)[Array](#br12)[ ](#br12). . . . . . . . . . . . . . . . . . . . . . . . .

[Program](#br13)[ ](#br13)[showing](#br13)[ ](#br13)[Cache](#br13)[ ](#br13)[is](#br13)[ ](#br13)[used](#br13)[ ](#br13)[as](#br13)[ ](#br13)[a](#br13)[ ](#br13)[Side](#br13)[ ](#br13)[Channel](#br13)[ ](#br13). . . . . . . . . . . . . . . 10

[Reading](#br14)[ ](#br14)[of](#br14)[ ](#br14)[Secret](#br14)[ ](#br14)[Value](#br14)[ ](#br14)[from](#br14)[ ](#br14)[Cache](#br14)[ ](#br14). . . . . . . . . . . . . . . . . . . . . . . 11

[Program](#br15)[ ](#br15)[illustrating](#br15)[ ](#br15)[Meltdown](#br15)[ ](#br15)[Attack](#br15)[ ](#br15). . . . . . . . . . . . . . . . . . . . . 12

[dmesg](#br16)[ ](#br16)[command](#br16)[ ](#br16). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 13

[10](#br16)[ ](#br16)[Exception](#br16)[ ](#br16)[Handling](#br16)[ ](#br16). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 13

[11](#br17)[ ](#br17)[Output](#br17)[ ](#br17)[of](#br17)[ ](#br17)[Exception](#br17)[ ](#br17)[Handling](#br17)[ ](#br17)[Program](#br17)[ ](#br17). . . . . . . . . . . . . . . . . . . . 14

[12](#br17)[ ](#br17)[Out-of-Order](#br17)[ ](#br17)[Execution](#br17)[ ](#br17). . . . . . . . . . . . . . . . . . . . . . . . . . . . . 14

[13](#br18)[ ](#br18)[Reading](#br18)[ ](#br18)[Secret](#br18)[ ](#br18)[Value](#br18)[ ](#br18)[from](#br18)[ ](#br18)[Kernel](#br18)[ ](#br18). . . . . . . . . . . . . . . . . . . . . . . . 15

[14](#br18)[ ](#br18)[Output-](#br18)[ ](#br18)[Program](#br18)[ ](#br18)[Reading](#br18)[ ](#br18)[Secret](#br18)[ ](#br18)[Value](#br18)[ ](#br18)[from](#br18)[ ](#br18)[Kernel](#br18)[ ](#br18). . . . . . . . . . . . . . 15

[15](#br19)[ ](#br19)[KAISER](#br19)[ ](#br19)[PATCH](#br19)[ ](#br19). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 16





Abstract

Application security relies on the memory mapping in the system as well as isolation

if memory unit and memory management unit is responsible for that like kernel address

system space that are marked as not accessible from user space and are marked as

priviliged. In this paper, we present Meltdown, Meltdown exploit vulnerabilities of

out-of-order execution which allows a user program to read data stored inside the

kernel-level memory that are marked as not accessible from user-level program.

Such, accessing of data is not allowed by the hardware level protection mechanism

implemented in Central Processing Unit(CPU), but the vulnerability exists in the

design of these CPU and mostly intel CPU are aﬀected by meltdown. Meltdown

breaks all the security guarantees of a system which is not patched by KASLR.

1 Introduction

A operating system provide security to each application using memory isolation technique.

Operating system provide guarantee that one application or program can not access other

application data without permission of operating system(kernel).Kernel level permission bit

is set by hardware level mechanism known as supervisor bit. Supervisor bit provide isolation

between kernel address space and user address space. So, the aim is that this bit could only

be set when entering into kernel space and it’s cleared when switching to user process(mode)

space. This hardware feature allows OS to map kernel address space to address space of

other user process and it is an very eﬃcient address transitions [scehme.(1)(9)](#br19)

In this paper, we present Meltdown, the attack itself is quite complex, therefore we break it

down into quite small steps so that each step is easy to [understand.(1)(9)](#br19)

Meltdown does not exploit any kind of software vulnerability i.e it does not use or break

internal software system but it is a hardware attack and it works on all the major intel

system. The major cause of meltdown attack is out-of-order execution[.(1)(9)](#br19)

Out-of-order execution increases CPU eﬃciency and allows CPU to execute instruction faster

and, in a second half of the paper we have describe it in short. Through Out-of-Order

execution we exploit cache side channel to catch data store in L3 cache. However, out-of-

order attacks cache side channel and the result allows an attacker to dump whole kernel

memory by reading cache memory in an out-of-order execution [manner.(1)(9)](#br19)

Outline

• In this section we will describe about

– Cache Side channel and attacks

– Out-Of-Order Execution

– Address Spaces Randomization

• Meltdown and Its Components

1





• Evluation

• Conclusion

2 Background

In this section we describe cache side channel, out-of-order execution and address space

randomization.

2.1 Cache Side Channel and Attacks

Cache based attack on the processor were happening for a number of years, meltdown and

spectre are famous known attacks of Cache side channel. Cache side channel attacks are

enabled using the micro architecture design of the processor. They are part of hardware

design and thus they are very diﬃcult to [defeat.(9)(10)](#br20)

In order to speed up memory access and address translation CPU contains the small memory

known as cache memory that store frequently used data. Every instruction and every piece

of data that require main memory. The CPU retrieves the instruction and data from main

memory execute that instruction and store result back in main memory. So, to improve per-

formance of accessing main memory a hardware level access is made to various level of cache

memory. If the require instruction or data already in cache memory CPU retrieved that

data from cache execute it and save back to cache, with the help of various write back policy

cache data is written back to main memory eg: - write back and write [through.(1)(4)(9)](#br19)

Here, the main point is cache memory is used for storing frequently access data.

The attacker can not directly read data stored in cache memory but this does not mean that

there is not information leakage, the cache is much smaller than main memory and nearest

to the CPU, so data retrieving from cache memory is much faster than accessing data from

main memory. Cache side channel exploit this timing diﬀerence for retrieving data. Diﬀer-

ent cache technique has been proposed in the past including Evict+Time, Prime+Probe and

[Flush+Reload.(2)](#br19)

The next piece of background information required to understand the CPU cache topology

of modern processors. Figure [1] shows a generic topology that is common to most of modern

CPU’s. Modern CPU’s generally contain multiple levels of cache memory. In this ﬁgure we

assume that CPU is dual core and each core contains its own L1 and L2 cache memory and

L3 cache is shared in between core0 and core1. We exploiting cache side channel attack in

L3 cache only because that is practical to exploit and for side channel attack, we are using

Flush+Reload technique because it’s works on a single cache line granularity[.(1)(4)(9)](#br19)

All the technique works this way: manipulate cache to known state, wait for victim activity

and examine what has changed. Program virtual address map to physical address with the

help of page table. L1 cache is nearest to the CPU and split between a data and an instruc-

tion cache. If the data not found in L1 cache than load instruction passed to the next Cache

hierarchy. This is the point where the page table come into play. Page table are used to

2





Figure 1: Cache Architecture

translate virtual address into a physical address, once’s we have physical address CPU can

query into L2 cache and if data is not found in L2 cache then Load instruction is passed to

L3 cache. L3 is inclusive shared cache between core0 and [core1.(3)(9)](#br19)

2.1.1 FLUSH+RELOAD attack

Using Flush+Reload an attacker can exploit last-level shared inclusive cache i.e Level3 cache,

an attacker frequently ﬂush a targeted memory location using the clﬂush instruction and

thereby measuring the time it takes to reload the data, now the attacker can know whether

data was loaded into the cache memory by another application or any current process in the

mean[time.(1)(9](#br19)[)](#br20)

2.2 Out-Of-Order Execution

Out-Of-Order execution allows processor to execute the instructions one after the other,

the processor uses the resources not to its full extent which makes CPU performance ineﬃ-

cient.Thus, to improve the eﬃciency of CPU, there are two methods,ﬁrst by executing various

sub-steps of sequential instructions at the same time(simultaneously) or secondly maybe by

executing instructions simultaneously depending on the resources availability. Further im-

provement within the CPU can be achieved by Out-of-Order Execution. Out-of-order

instruction execution are usually achieved by executing the instruction in an various diﬀerent

[form.(4)(9)](#br19)

Out-of-order execution is a method or approach that is utilized in high performance micro-

3





processors. Out-Of-Order eﬃciently uses instruction cycles (Instruction Cycles is a process

by which a computer system pulls program instruction from the memory which can invoke

pre-fetching or pre-processing, also determines what action the instruction requires or what

resources it needs and carries out those actions.) and reduces costly delay due to resource

unavailability. A processor will execute the instruction order of availability of knowledge or

operands or resources rather than original order of the instructions in the program. Through

this, the CPU will avoid being idle or free while data is retrieved for the next instruction in

advance for a p[rogram.(4)(9)](#br19)

Out-of-Order Execution can be regarded as A Room guarded by a Security Oﬃcer.The

attacker wants to enter the room to get some secret value but the Security Guard have 2

options either it can allow the attacker to access the data depending on the permissions or

it can deny the attacker to access the room’s [data.(4)(9)](#br19)

Figure 2: Out-Of-Order Execution

In ﬁgure 2 the line 3 causes an interrupt because user(attacker) wants to access the kernel

data, this line leads CPU to do two things

1)The CPU raises an exception since user level program want to access kernel level data,

this causes program or application to either crash if the program doesn’t have exception

handling mechanism.

2)Mean-while when CPU is busy in permission check the CPU doesn’t want the other com-

putational parts to be idle since this may degrade the performance or eﬃciency so the CPU

execute the adjacent instructions depending on the availability of data operands.

Now the user is either allowed or denied to access the data, but in both cases due to Out-

of-Order Execution the adjacent instructions are executed. If the permission is granted

then the adjacent instructions are successfully executed but if the permission is denied the

4





program or application may abruptly end(or may show appropriate message depending on

the Exception Handling Mechanism) but in both cases the value from the kernel is fetched

by the CPU and stored in a temporary register in Cache Memory. The Cache Memory is

not ﬂushed in either case of access permission check, that means the data is still available

somewhere in the Cache. So from outside or user point of view the attacker has not accessed

the data but from inside it can still access the data through Cache Memory via Timing

[Diﬀerence.(1)(4)(9)](#br19)

We will show in the Evaluation(Section 5) the proof of Out-of-Order Execution that how the

attacker can access the secret data.

2.3 Address Space Randomization

CPU’s support two kind of address spaces so that processes are isolated from each other.

Virtual Address Spaces can be deﬁned as virtual addresses that are translated to phys-

ical(logical) addresses through page translation tables. Virtual address space is divided

into a group of pages that will be mapped to the corresponding logical or physical memory

through a multi-level page translation table. The page translation tables are used to deﬁne

the speciﬁc mapping virtual to physical address and also protection bit(like dirty bit etc)

properties that are used to force privilege checks, like read access, write access, executable

or not and user-accessible or not. The currently used translation table is stored in a special

CPU register. On each context switch(change of process states), the OS updates this register

with corresponding process translation table address so as to implement per-process virtual

address spaces.Thus, each process can only refer to data that belongs to its own virtual

address space. Every virtual address space is divided into two categories which are User

and Kernel parts so that each process gets a user and kernel address space. The currently

running application uses the user address space, while the kernel address space would only

be accessed if CPU is running(active) and also in privileged mode(mode bit set to 1). This

is done by the operating system which disable the user-accessible property of the current or

speciﬁc translation tables. The kernel address space does not only have memory mapped for

the kernel’s own use, but it must also perform operations on the user pages. As a result of

this, the whole physical memory is mapped with the k[ernel.(1)(4)(9)](#br19)

3 Meltdown and its Components

Meltdown Attack uses ﬂaw in most of the modern processors.These ﬂaws exists in the CPU’s

itself i.e it can be regrded as a Hardware Defect rather than a software bug, it allows a user-

level program to read data stored inside the kernel memory. We cannot access kernel space

5





due to the hardware protection mechanism, but a defect exists in the design of these CPU’s

which allows to defeat the hardware protection and thus carry out these types of attacks.

Because the defect exists within the hardware,it is very diﬃcult to fundamentally ﬁx the

problem, unless we change the CPU’s in our [computers.(1)(4)(9)](#br19)

3.1 Transient Instruction

Before doing an in-depth analysis of how meltdown takes place, ﬁrst we need to understand

what is Transient Instruction.

Any Instruction that executes Out-of-order in the program and has measurable side eﬀects

is known as Transient Instruction.

Transient instructions occur all the time, because the CPU runs ahead of the current in-

struction all the time to minimize the experienced latency and, thereby, to maximize the

performance or eﬃciency.These instructions introduce an exploitable side channel if their

operation depend on a secret value. We specialise in addresses that are mapped within the

attacker’s process, i.e., the user-accessible user space addresses as well as the user-inaccessible

which may kernel space addresses or other user’s address space.The attacks targeting code

that is executed within the context (i.e., address space) of other user processess are also pos-

sible, but out of context in this work, because the physical memory (including the memory

of other user processes) they are read through the kernel [space.(1)(4)(9)](#br19)

3.2 Attack Description

Meltdown attack can be divided into 3 steps:

1.To know Secret Kernel Address Space The content of an attacker chosen memory

location which is stored in kernel space address and which can not be accessed by the at-

tacker, is loaded into a register.

2.Out-of-Order Instruction Execution A transient instruction which is an out-of-order

instruction accesses the cache line supported by the register.

3.Using Cache as Side Channel to read the secret data The attacker uses Flush+Reload

technique (Timing Diﬀerence Attack) to work out the cache line accessed in the previous

step and thus the secret stored at the speciﬁed memory location.

Since these is only applicable for single memory location if the attacker uses these technique

for other locations then it can get the secret from other locations in kernel space as well

which may lead to unavoidable conse[quences.(1)(2)(4)(9)](#br19)

6





4 Evaluation

In this section we describe each step that need to done for performing meltdown attack.

4.1 Environment Setting

For setting up our lab environment we are using 64-bit ubuntu 16.04 LTS in oracle virtual

box 6.0, setting related to hardware device is speciﬁed in given [3.](#br10)

Figure 3: Environment Setting

4.2 Code Compilation

While compiling source code we have to add -march=native ﬂag. while compiling the pro-

gram -march=native ﬂag tells the compiler to produce speciﬁc code for the local machine.

For, example to compile a myprogram.c we are using the following command :

gcc-march=native -o myprogram myprogram.c

4.3 Reading from Cache versus Main Memory

Cache memory is nearest to CPU so, ﬁrst CPU check data in cache, if data is present in

cache than it will fetch directly from it and if data is not present than it will fetch from main

memory. Fetching data from cache is much faster than fetching data from main memory.

7





gcc -march=native -o CacheTime CacheTime.c

In the Figure [4](#br11)[ ](#br11)at line number 19, ﬁrst we have initialized an array of size 10\*PAZESIZE.

For ﬁnding PAGESIZE run the following command in terminal “getconf PAGESIZE” and

put your own PAGESIZE in line 8. After that we ﬂush the array address to make sure that

array indexes are not cached and in the next phase, we are accessing index 4 and 7 as shown

in line number 25 and 26 so that index 4 and 7 is cached by cache. From line number 29 to

35 we are accessing the array index and measuring the timing using rdtscp time stamp.

Figure 4: Program Illustrating the Timing Diﬀerence of Probing Array

8





Figure [5](#br12)[ ](#br12)illustrate the timing diﬀerence where accessing the array index 3 and 7 is much

faster than others.

Figure 5: Access Timing of Probing Array

4.4 Using Cache as Side-Channel

The objective of this section is extracting a secret value used by the victim function. We

are assuming that victim(); function at line 53 uses a secret value deﬁne in line 14, as index

to load values from an array and the secret value cannot be accessed from the outside. Our

objective is to use side channel to get this secret value. The technique that we are using for

retrieving secret value is Flush(line 16)+Reload(line27) Functions.

As Shown in Figure [6](#br13)[ ](#br13)at line 14, ﬁrst we set one-byte secretValue variable equal to 105.Since

for a one-byte secret value there are 256 possibilities so in line 12 we declare array of size

256\*PAGESIZE. We multiply by PAGESIZE because caching is done at a block level, not

at a byte level so, if one byte is cached by cpu than adjacent byte will also cached. Since

the ﬁrst array[0\*PAGESIZE] may also cached by some cache block as a default behavior

of cache. Therefore, to make sure array[0\*PAGESIZE] will not cached we are accessing ar-

ray[i\*PAGESIZE+DELTA], where DELTA is a constant deﬁne in line number 10.

9





Figure 6: Program showing Cache is used as a Side Channel

First Flush the entire array using ﬂushSideChannel(); from the cache memory to make

sure that array is not cached. After that we invoke the victim(); function, which access of

the array element based on the value of secret, that array index value is cached by the cache

memory. And the ﬁnal step is calling the reloadSideChannel(); function which reload the

10





entire array and measure the time it takes to reload each element. So, if the array index is

previously cached than it requires less CPU cycle. The output of the program illustrates in

Figure [7.](#br14)

The output of the program shown in ﬁg [6](#br13)[ ](#br13)below:

Figure 7: Reading of Secret Value from Cache

4.5 Prepration for Meltdown Attack

For preparing meltdown attack we have to placed secret value in kernel space and we show

that how a user-level program can access that data without going into kernel space. To store

the Secret value in kernel space we are using kernel Module approach and the code is listed

in [8.](#br15)

11





Figure 8: Program illustrating Meltdown Attack

For executing the meltdown attack ﬁrst, we need to know address of secret value so, the

kernel module saves the address of secret value in kernel buﬀer at line 41. which we will get it

using ‘dmseg‘ command as shown in Figure [9.](#br16)[ ](#br16)The next thing is this secret value need to be

cached so to achieve this we are creating a ﬁle /proc/secret data at line number 46. Which

provide a link to communicate a user level program to kernel module. Therefore, when a

user-level program read /proc/secret data ﬁle then it will invoke read proc() function at line

\23. The read proc() function will load the secret value (line 25) which is cached by CPU.

read proc() function will not return secret value so it does not leak secret value.

• Compile the kernel module

make

• Install the kernel module

sudo insmod MeltdownKernel.ko

• Print secret value address

dmesg

12





Figure 9: dmesg command

4.6 Exception Handling

When user program tries to access kernel memory in Figure [10](#br16)[ ](#br16)at line 23 than memory access

violation is triggered and segmentation fault is generated. To avoid segmentation fault, we

are using SIGSEGV signal because c does not provide try/catch techniques like java. So to

implement try/catch in c we are using sigsetjmp() at line 21 and siglongjmp at line 10.

Figure 10: Exception Handling

The execution of this program is quite complex but let’s understand it line by line. First,

we register a SIGSEGV signal handler in line 19 which will invoke catch segv function (line

7). once’s the signal handler complete processing it let the program to continue its execution

so for that we have to deﬁne a checkpoint that we are achieve by sigsetjmp(buﬀer,1) at line

\21. sigsetjmp save the stack context in buﬀer that it latter used by siglongjmp (line 10).

siglongjmp rollback the stack context in buﬀer and return the second argument which is 1

so the program execution is start form else part (line 29), output is illustrate in [11.](#br17)

13





Figure 11: Output of Exception Handling Program

4.7 Out-of-Order Execution

Meltdown is a race condition vulnerability, which involves racing between out-of-order exe-

cution and access block so, for exploiting meltdown successfully we must have to win race

condition. To win race condition we have to keep CPU execution busy somehow and for

that we are using assembly level code.

Figure 12: Out-of-Order Execution

The code in Figure [12](#br17)[ ](#br17)is simply a loop over 400 times (line 63). In the next line it adds a

number 0X141 (321 in decimal) to the eax register to keep rax register busy so that we can

win race condition.

4.8 Meltdown Attack

To make attack more practical and improve eﬃciency of attack we create a score array of size

\256. The reason of creating an array of size 256 is that for one byte there is 256 possibilities.

Therefore, one element for each possible secret value and we run attack multiple times as

shown in Figure 13 at line 92. This step is combination of all step that are describe above,

after running multiple times the highest value of score array is our answer. The output of

this step is illustrated in Figure 14.

14





Figure 13: Reading Secret Value from Kernel

Figure 14: Output- Program Reading Secret Value from Kernel

The code in MeltdownAttack can only steals a one byte secret from the kernel.

5 Prevention of Meltdown Attack - KAISER Patch

The exploitation in the memory attacks usually requires correct knowledge of addresses of

speciﬁc data. So in order to carry out these attacks, Address Space Layout Random-

ization (ASLR) has been introduced. To protect kernel, KASLR randomizes the oﬀsets

which means the starting address from where the system is loaded and is changed every time

15





the system is booted , making attacks harder as the attacker now require to guess the situa-

tion of kernel data [structures.(1)(4)(9)](#br19)[ ](#br19)But, with side channel, the attacker has to precisely

determine the kernel address . A combination of a software bug and the knowledge of the

physical addresses can lead to privileged code [execution.(1)(4)(9)](#br19)

To Prevent Meltdown KAISER technique can be used more accurately or we can say that it

is a counter measure to Meltdown Attack. KAISER hide the kernel space from user space

using randomization technique. KAISER allow the kernel to randomize the kernel location

at boot time. The Output of same program after applying KAISER patch is illustrated in

Figure 15.

Figure 15: KAISER PATCH

6 Conclusion

In this paper we presented Meltdown, a vulnerability or attack to the software system which

can read kernel data or secret data from an underprivileged user-level program, since it does

not depend on any software vulnerability as well as it is independent of the type of Operating

System.

To prevent Meltdown KAISER can be used more accurately we can say that it is a counter-

measure to Meltdown Attack, it is a kernel modiﬁcation to not have the kernel mapped in

the user space.This modiﬁcation to protect side channel attacks breaking KASLR(Kernel

Address Space Layout Randomization) but it also prevents Meltdown.

References

[1] Zheng Zmy(2019) Meltdown: Reading Kernel Memory from User Space

<https://blog.csdn.net/zheng_zmy/article/details/103479066>

[2] Wenliang Du, Syracuse University(2018) Meltdown Attack Lab

[http://www.cis.syr.edu/](http://www.cis.syr.edu/~wedu/seed/Labs_16.04/System/Meltdown_Attack/Meltdown_Attack.pdf)[ ](http://www.cis.syr.edu/~wedu/seed/Labs_16.04/System/Meltdown_Attack/Meltdown_Attack.pdf)[wedu/seed/Labs_16.04/System/Meltdown_Attack/](http://www.cis.syr.edu/~wedu/seed/Labs_16.04/System/Meltdown_Attack/Meltdown_Attack.pdf)

[~](http://www.cis.syr.edu/~wedu/seed/Labs_16.04/System/Meltdown_Attack/Meltdown_Attack.pdf)

[Meltdown_Attack.pdf](http://www.cis.syr.edu/~wedu/seed/Labs_16.04/System/Meltdown_Attack/Meltdown_Attack.pdf)

[3] Areej(2020) - Diﬀerence between l1 l2 and l3 cache memory

[4] Moritz Lipp,Michael Schwarz,Daniel Gruss - Metldown paper -

<https://arxiv.org/pdf/1801.01207.pdf>

16





[5] Jacek Galowicz - Metldown paper -

<https://blog.cyberus-technology.de/posts/2018-01-03-meltdown.html>

[6] Jann Horn, Project Zero

\-

side-channel [https://googleprojectzero.blogspot.com/2018/01/](https://googleprojectzero.blogspot.com/2018/01/reading-privileged-memory-with-side.html)

Reading privileged memory with

a

\-

[reading-privileged-memory-with-side.html](https://googleprojectzero.blogspot.com/2018/01/reading-privileged-memory-with-side.html)

[7] Jake Edge - Kernel Address Space Layout Randomization(KASLR) -

<https://lwn.net/Articles/569635/>

[8] Daniel Gruss,Clementine Maurice, Klaus Wagner, and Stefan Mangard-

Flush+Flush:A Fast and Stealthy Cache Attack -

<https://gruss.cc/files/flushflush.pdf>

[9] Jann Horn, Project Zero - Reading privileged memory with a side-channel

<https://cryptome.org/2018/01/spectre-meltdown.pdf>

[10] Yinqian Zhang - Cache Side Channels: State of the Art and Research Oppor-

tunities

[http://web.cse.ohio-state.edu/](http://web.cse.ohio-state.edu/~zhang.834/slides/tutorial17.pdf)[ ](http://web.cse.ohio-state.edu/~zhang.834/slides/tutorial17.pdf)[zhang.834/slides/tutorial17.pdf](http://web.cse.ohio-state.edu/~zhang.834/slides/tutorial17.pdf)

[~](http://web.cse.ohio-state.edu/~zhang.834/slides/tutorial17.pdf)

17


