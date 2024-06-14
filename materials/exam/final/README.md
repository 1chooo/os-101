# Final

## Noun

1. translation look-aside buffer (TLB)
2. address-space identifiers (ASIDs)
3. page-table base register (PTBR)
4. page-table length register (PTLR)
5. local descriptor table (LDT)
6. global descriptor table (GDT)
7. Least Recently Used (LRU) Algorithm
8. Lease Frequently Used (LFU) Algorithm
9. Most Frequently Used (MFU) Algorithm
10. Non-Uniform Memory Access (NUMA)

One soft real-time system has five periodic tasks, with periods of 50, 100, 150, 200 and 300 ms each. Assume these tasks require 10, 25, 15, 40 and C ms of CPU time, respectively.What is the largest value of C for the system to be schedulable?

10/50+25/100+15/150+40/200+c/300<=1
(225+c)/300<=1
c<=75

> [!NOTE]
> Spinlocks are not appropriate for multi-core single-processor systems.
> 
> Because the condition that would break a process out of the spinlock can be obtained only by executing a different process.


> [!NOTE]
>
> Only one process can be active within a monitor.

> [!NOTE]
>
> Critical sections can be preserved by disabling kernel preemption.

> [!NOTE]
>
> Wait and signal of a counting semaphore can be implemented with multiple binary semaphores. [Binary Semaphores]

[Binary Semaphores]: https://www.cs.umd.edu/~shankar/412-Notes/10-BinarySemaphores.html

> [!NOTE]
>
> 如果 multiprocessor system採用 interrupt disabling，則需要將所有的CPU核心關掉，而這相當的耗時，但只關掉一顆CPU核心依然會產生錯誤，因此 interrupt disabling 不適合用在 multiprocessor system，只適合用在單核心上，而多核心則使用 spin locks 較為合適。

> [!NOTE]
>
> System calls are not only executed with privileged instructions which are not supposed to be used by user programs.

> [!TIP]
>
> 誰 request，Availability 就要先扣掉，另外 Need 要先扣掉 Request 的再去比對各個的 Need。


> [!NOTE]
>
> if in circle, resource type only one instance -> deadlock [第十四天 Deadlocks(死結)--上]

[第十四天 Deadlocks(死結)--上]: https://ithelp.ithome.com.tw/articles/10206155


Assume that the memory access time is 200 ns, the average page-fault service time including page-fault time and twice memory access time is 10 ms, and the page fault ratio is 15%.
(多選題)
A.If we want the effective memory time is less than 50 μs, the page fault ratio must be less than 0.60%.
B.None of the above.
C.The effective access time is 1500170 ns.
D.The effective access time is 1500180 ns.
E.If we want the effective memory time is less than 100 μs, the page fault ratio must be less than 0.15%.













