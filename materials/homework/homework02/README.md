# [CE3002] Operating System -- Homework 02 (Answer + Notes)

> CE3002 Operating System
> 
> - Year: 2024 Spring  
> - Lecturer: 曾黎明
> - Student: 林群賀
> - Dept: ATM
> - Student ID: 109601003

### 1. 是非題 (共 5 題，每題 3 分)

1. **[F]** All of deadlock necessary conditions (i.e. mutual exclusion, hold and wait, no preemptive and circular waiting) exist, the system must be in deadlock.

    > [!NOTE]
    > unsafe 未必 deadlock，但 deadlock 一定 unsafe。

2. **[T]** The resources allocation graph has no cycle, the system must not be in deadlock.


3. **[F]** If Banker's algorithm returns an unsafe, it means the resource request must make the system in deadlock.

    > [!NOTE]
    > unsafe 未必 deadlock，但 deadlock 一定 unsafe。

4. **[T]** Dynamic linking must needs a support from the operating system.

    > [!NOTE]
    > static linking 不需要 OS 支援 (load)，但 dynamic linking 需要 OS 支援 (execution)。

5. **[T]** The copy-on-write technique decrease the time of the process creation.

    > [!NOTE]
    > COW allows more efficient process creation as only modified pages are copied

    
### 2. 單選題 (共 15 題，每題 4 分)
    
6. Which one of the following is a correct statement about disk space allocation methods?
    - [ ] (A) Linked allocation may suffer from the external fragmentation problem
    - [ ] (B) Linked allocation can efficiently support direct accesses into a file.
    - [ ] (C) Contiguous allocation can be enhanced by using "extents" to solve its non-sequential access performance problem.
    - [x] (D) Indexed allocation does not suffer from the external fragmentation problem.
    - [ ] (E) None of the above.

    > [!NOTE]
    > 1. Linked allocation 👉🏻 internal
    > 2. 

7. [?] Consider a tiny paging system that has 16 KB physical memory, and the frame size is $1 KB$. Let the logical address have 16 bits. The page table uses single-level direct index. Which one of the following is not correct?
    - [ ] (A) The frame number has 4 bits
    - [ ] (B) The page number has 6 bits
    - [x] (C) There are 16 entries in the page table.
    - [ ] (D) A page-table entry stores a frame number 
    - [ ] (E) The page table requires 320 bits, including the valid-invalid bits.

    > [!NOTE]
    > 1. 16 KB / 1 KB = 16 frames
    > 2. frame size = 1 KB = $2^{10}$ bytes 👉🏻 10 bits (page offsets)
    > 3. logical address 16 bits = 6 bits (page number) + 10 bits (page offsets)
    > 4. Page table entries = 2^6 = 64 entries
    > 5. each table entry = 4 bits (frame number) + 1 bit (valid-invalid bit) = 5 bits
    > 6. 64 * 5 = 320 bits
    

8. Which of the following statements on the concept of deadlocks is not correct?
    - [x] (A) If we use banker's algorithm to control the resource request and allocation, and when we find the system is unsafe, and still grant the resource request, the system will enter the deadlock state.
    - [ ] (B) If a deadlock situation arises, the four conditions of mutual exclusion, hold and wait, no preemption, and circular wait must hold simultaneously.
    - [ ] (C) If there is a cycle of resource allocation graph for a system with single instance resource, it will be in a deadlock state.
    - [ ] (D) If a system is in the safe state, it will not be in a deadlock state.
    - [ ] (E) If there is a cycle of resource allocation graph for a system with resource of multiple instances, it may not be in a deadlock state.

    > [!NOTE]
    > 1. unsafe 未必 deadlock，但 deadlock 一定 unsafe。
    > 2. 四個同時要有，但都有不一定 deadlock
    > 3. single instance resource 有 cycle 一定 deadlock
    > 4. safe state 一定沒有 Deadlock
    > 5. multiple instance resource 有 cycle 不一定 deadlock

9. Suppose that there is a machine with 32-bit addresses and a two-level page table. Note that the first 10 bits of an address is an index into the first level page table and the next 10 bits are an index into a second level page table. The page tables are stored in memory and each entry in the page tables is 4 bytes. Suppose the space allocated to a specific process is 64 Mbytes. How many pages are occupied by this process?
    - [ ] (A) $2^{26} pages$
    - [x] (B) $2^{14} pages$
    - [ ] (C) $2^{12} pages$
    - [ ] (D) $2^{10} pages$
    - [ ] (E) None of the above

    > [!NOTE]
    > | 10 | 10 | 12 |
    >
    > 12 is page offset, so page size is $2^{12}$ bytes
    > 
    > 64 Mbytes = $2^{26}$ bytes
    > 
    > $2^{26} / 2^{12} = 2^{14}$ pages


10. (Continued from the previous question.) How much space is occupied in memory by the page tables for the specific process? 
    - [x] (A) $68 kbytes$
    - [ ] (B) $64 kbytes$
    - [ ] (C) $16 kbytes$
    - [ ] (D) $4 kbytes$
    - [ ] (E) None of the above


    > [!NOTE]
    > page offset 做

11. Which of the following statements is incorrect?
    - [ ] (A) A spinlocks is a lock that will cause a requesting process to busy-wait to get it when it is in the locked state.
    - [x] (B) Using spinlocks will not cause deadlock on a multi-processor system.
    - [ ] (C) A spinlock should not be used on a uni-processor system.
    - [ ] [?] (D) Compared with a non-spinlock, a spinlock allows a requesting process to get the lock more quickly because the process need not do a context switch.
    - [ ] (E) For a non-spinlock, its `wait()` and `signal()` operations must be executed atomically.

    > [!NOTE]
    > 1. 如果需要 busy-wait 👉🏻 spinlock
    > 2. spinlock 只用在 multi-processor system


12. The following code fragments describe a solution of the bounded-buffer problem. The three variables S1, S2, and S3 are all semaphores. Suppose that the buffer initially has 10 empty slots. What are the correct initial values of the semaphores?
    
    **Producer processes:**
    
    ```c
    do {
        // produce an item
        wait(S2);       // empty
        wait(S1);       // mutex
        // add the item to the buffer

        signal(S1);     // mutex
        signal(S3);     // full
    } while(true);
    ```
    
    **Consumer processes:**
    
    ```c
    do {
        wait(S3);       // full
        wait(S1);       // mutex
        // remove an item from buffer
        signal(S1);     // mutex
        signal(S2);     // empty
        // consume the removed item
    } while(true);
    ```
    - [ ] (A) $S1=1; S2=1; S3=1$
    - [ ] (B) $S1=1; S2=0; S3=0$
    - [ ] (C) $S1=9; S2=1; S3=1$
    - [x] (D) $S1=1; S2=10; S3=0$
    - [ ] (E) $S1=0; S2=10; S3=10$

    > [!NOTE]
    > 知道 producer 是先 empty；consumer 是先 full 推出 S1, S2, S3 再用 slots 只有 10 個去推

13. Which of the following statements is incorrect?
    - [ ] (A) The "TestAndSet()" instruction used for process synchronization must have hardware support so that the Test and Set operations can be done atomically.
    - [ ] (B) The "TestAndSet()" instruction can be used to implement a lock.
    - [ ] (C) An atomic "Swap()" instruction can be used to replace the "TestAndSet()" instruction.
    - [ ] (D) A mutex lock is a special semaphore whose value ranges only between 0 and 1.
    - [x] [?] (E) A mutex is used to protect a critical section of code. It cannot protect a shared variable.

    > [!NOTE]
    > 1. `TestAndSet()`, `ComparedAndSwap()` 都是 Hardware level 的 atomic operation，可以用來實作 lock。
    > 2. `TestAndSet()` 可用來實作 lock
    > 3. `Swap()` 可以取代 `TestAndSet()`
    > 4. mutex 是 semaphore 的一種，只有 0 和 1
    > 5. Mutexes and other synchronization mechanisms are useful when one or more threads modify the variable. [Do I have to use a mutex to protect shared variables that I use for read-only purposes without in-place modification in C++ multithreading?]

    [Do I have to use a mutex to protect shared variables that I use for read-only purposes without in-place modification in C++ multithreading?]: https://www.quora.com/Do-I-have-to-use-a-mutex-to-protect-shared-variables-that-I-use-for-read-only-purposes-without-in-place-modification-in-C++-multithreading


14. Which of the following statements about memory management is correct?
    - [ ] (A) To allocate contiguous memory from free holes, the best-fit algorithm is the optimum solution in memory utilization.
    - [ ] [?] (B) Pure segmentation suffers from internal fragmentation.
    - [ ] (C) A system can detect thrashing by using a figure, in which CPU utilization is plotted against the execution time.
    - [ ] (D) For first-in-first-out page replacement, the page-fault rate will definitely not increase as the number of frames increases.
    - [x] (E) None of the above is correct.


    > [!NOTE]
    > 1. contiguous memory allocation 用 first fit
    > 2. pure segmentation 不會有 internal fragmentation，但 pure paging 會有 external fragmentation
    > 3. page fault 可能會隨著 frames 變多而增加

    > [!TIP]
    > Page fault rate too high 👉🏻 OS need more page 👉🏻 replace existing frame but quickly need replaced frame back
    > 
    > 👉🏻 CPU utilization decrease instantly, also OS thinks it needs to increase the degree of multiprogramming 👉🏻 another process added to system

15. You have a $7200-rpm$ disk with a track-to-track seek time of 1 ms. The disk has 400 sectors on each track. Each sector has 1KB. What is the maximum date transfer rate in $MB/sec$?
    - [ ] (A) 32
    - [x] (B) 48
    - [ ] (C) 56
    - [ ] (D) 64
    - [ ] (E) None of the above.

    > [!NOTE]
    > 7200 rpm = 120 rps
    >
    > 120 * 400 = 48000 KB/s = 48 MB/s

16. Which of the requirements for a solution to the critical-section problem are not satisfied for the following program?
    
    ```c
    //lock is a shared data and initialized to 0
    while(1){
        key=1;
        while(key){
            atomic_swap(lock, key);
            <Critical Section>
            Lock=0;
            <Remainder Section>
        }
    }
    ```
    
    - [ ] (A) Mutual Exclusion
    - [ ] (B) Progress
    - [ ] (C) No preemption
    - [x] (D) Bounded Waiting

    > [!NOTE]
    > `atomic_swap()` -> 滿足 No preemption (不可被打斷)、Mutual Exclusion
    >
    > 但主要是因為此程式沒有設定等待 critical-section 的時間的界值 (A bound must exist on the number of times) [Introduction of Process Synchronization]

    [Introduction of Process Synchronization]: https://www.geeksforgeeks.org/introduction-of-process-synchronization/




17. Which of the following descriptions regarding the multithread models are correct?
    1. In ~~One-to-One~~ model, only one thread can access the kernel at a time on multiprocessors.
    2. In Many-to-One model, the entire process will block if a thread makes a blocking system call.
    3. In Many-to-Many model, the number of kernel threads can be specific to either a particular application or a particular machine.
    4. In ~~One-to-One~~ model, developers can create as many user threads as necessary.
    5. The two-level model is a variation of the Many-to-Many model.
    
    - [ ] (A) II and III	
    - [ ] (B) II, III, and IV
    - [ ] (C) I, II, IV, and V
    - [x] (D) II, III, and V
    - [ ] (E) I, III, and V

    > [!NOTE]
    > 1. Many-to-One model, only one thread can access the kernel at a time on multiprocessors.
    > 2. Many-to-Many model, developers can create as many user threads as necessary.
    > 3. In One-to-One model, creating user thread requires the corresponding Kernel thread.


18. Which of the following statements is false?
    - [ ] [?] (A) Working set theory can be used to control the level of multiprogramming.
    - [x] [?] (B) System calls are only executed with privileged instructions which are not supposed to be used by user programs.
    - [ ] (C) The memory hierarchy does not always guarantee efficiency in information retrieval.
    - [ ] (D) In practice, the SJF scheduling algorithm may not be optimal in average waiting time.
    - [ ] [?] (E) The technology of virtual memory system may fail for some specific CPU instruction sets.

    > [!NOTE]
    > 


19. The banker’s algorithm is used for deadlock-avoidance. For a system with n processes and m types of resources, what is the order of complexity of this algorithm?
    - [ ] (A) $m$ 
    - [ ] (B) $n$
    - [ ] (C) $m \times n$
    - [ ] (D) $m^{2} \times n$
    - [x] (E) $m \times n^{2}$


20. Which of the following is not a necessary condition for the happening of a deadlock?
    - [ ] (A) Mutual exclusion to resources
    - [x] (B) Resources not released by a terminated process
    - [ ] (C) Resource hold and wait by processes
    - [ ] (D) Resource allocation without preemption
    - [ ] (E) Circular waiting in the resource allocation graph

    > [!NOTE]
    > 
    > Deadlock 的 circle: hold and wait, no preemption, mutual exculsion, cicurlar waiting


### 3. 多選題 (共 5 題，每題 5 分)

21. Which of the following statements are correct about the virtual memory technique.
    - [x] (A) Increase the memory utilization.
    - [ ] (B) Decrease the I/O frequency.
    - [x] (C) Increase the Multiprogramming degree.
    - [ ] (D) Decrease the CPU utilization.
    - [ ] (E) None of the above.
 
22. Consider a system with five processes P0~P4 and three resource type A, B, C. Suppose at time T0, the resource allocation state is:

    |       | Allocation | Max    | Need   | Available |
    |-------|------------|--------|--------|-----------|
    |       | A B C      | A B C  | A B C  | A B C     |
    | P0    | 2 1 1      | 3 1 3  | 1 0 2  | 2 1 2     |
    | P1    | 0 1 1      | 3 2 1  | 3 1 0  |           |
    | P2    | 1 0 0      | 1 0 4  | 0 0 4  |           |
    | P3    | 0 1 2      | 2 1 2  | 2 0 0  |           |
    | P4    | 1 0 0      | 1 1 0  | 0 1 0  |           |

    Which of the following statements are correct?

    - [x] (A) `<P4,P3,P2,P0,P1>` is a safe sequence.
    - [x] (B) `<P3,P0,P1,P4,P2>` is a safe sequence.
    - [x] (C) `<P0,P1,P2,P3,P4>` is a safe sequence.
    - [ ] (D) `<P0,P2,P3,P4,P1>` is a safe sequence.
    - [ ] (E) There is no safe sequence.

    > [!TIP]
    > 拿 P0 的 Availabe 去比對 Need，如果 Need <= Available，就可以執行，把 Allocation 加回 Available

23. Consider the page replacement algorithms FIFO (first-in first-out), LRU (least-recently used), and OPT (optimal). Which of the following cases are possible?
    - [x] (A) FIFO outperforms LRU
    - [x] (B) LRU outperforms FIFO
    - [x] (C) FIFO, LRU and OPT have the same number of page faults
    - [ ] (D) LRU causes more page faults with a larger number of here frames
    - [ ] (E) Implementing OPT in real operating systems

    > [!NOTE]
    > OPT 不會運用在 real-os 因為無法預知未來的 page request
    
24. Which of the following statements are correct?
    - [ ] (A) Spinlocks are appropriate for uni-processor systems.
    - [x] (B) The critical-section problem could be solved by disabling interrupts while accessing a shared variable in a uni-processor environment.
    - [ ] (C) Priority inheritance protocols can resolve race conditions in real time systems.
    - [x] (D) A non-preemptive kernel is free from race conditions on kernel data structures.
    - [ ] (E) The current Linux kernel is a non-preemptive kernel and a process running in a kernel mode could not be preempted.

    > [!NOTE]
    > 1. Linux could be preempted in kernel mode, it depends on "Release spinlock."
    > 2. priority ceiling protocol is a synchronization protocol for shared resources to avoid unbounded priority inversion and mutual deadlock due to wrong nesting of critical sections. (Priority inheritance protocols can resolve Priority Inversion) [Priority ceiling protocol]
    > 3. In uni-processor, we can disable interrupt to solve critical-section problem
    > 4. Spinlocks are appropriate for multi-processor systems

    [Priority ceiling protocol]: https://en.wikipedia.org/wiki/Priority_ceiling_protocol


25. Which of the following statements are correct? The less page size is,
    - [x] (A) the more page fault ratio is.
    - [ ] (B) The less page table size is
    - [x] (C) The more I/O frequency is.
    - [x] (D) The less internal fragmentation there is.
    - [ ] (E) None of the above.

    > [!NOTE]
    > Page Size 尺寸小了，page fault ratio 會增加，因為 page size 小，page table size 會增加，I/O frequency 會增加，internal fragmentation 會減少
