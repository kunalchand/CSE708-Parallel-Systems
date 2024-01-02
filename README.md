# CSE708-Parallel-Systems
Subset Sum Count using OpenMP in C

* Code runs on a single processor with multiple cores, having one thread per core.
* It supports multiple columns per core (hardware) or threads (software), where all cores/threads share a global memory.
* The number of columns per thread will be dynamically adjusted by the code as per need.

### Project Description:

For my semester-long parallel computing project, I implemented a solution to the subset sum count problem using OpenMP in C. My goal was to determine the number of subsets within an array that sum to a target value. My approach divided the dynamic programming table into column groups, with each core/thread responsible for computations on one group. Through open multi-processing, all the cores share intermediate results in a golobal memory to collectively calculate the final subset count. By testing on large inputs and varying core counts, I quantified speedup versus sequential execution and studied scaling behavior. This project allowed me to apply course concepts like thread creation, load balancing, data sharing and synchronization. Over the course of the project, I gained hands-on experience with parallel algorithm design, OpenMP programming, and performance analysis. Completing it demonstrated my skills in practical parallel computing.

### Key Features:

* Implemented parallel algorithm in C/C++ to count the number of subset sums equaling a target value, leveraging parallel processing with shared memory for performance gains over sequential code execution.
* Incorporated a feature to dynamically divide workload between OpenMP threads by adjusting column-wise decomposition of dynamic programming table at runtime to ensure optimal load balancing.
* Quantified speedup versus sequential execution and studied scaling behavior by testing for different large inputs.
* Streamlined testing by auto Slurm script submission for each test case via Shell script, reducing manual efforts.

Reference:
https://www.geeksforgeeks.org/count-of-subsets-with-sum-equal-to-x/
