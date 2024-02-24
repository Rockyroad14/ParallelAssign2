# Parallel Assignment 2
__Author: Jared Reich__
## Part 1:
### How to Run:
To run the second program associated with the second Prompt. First run the command `g++ main.cpp` and then run `./a.exe` or `./a.out` depending on the compiler and environemnt. __Note the difference between the cpp files__
### Approach:
The approach to solving this problem is having one of the members be the counter and the other people eating the cupcake. The counter person counts the times the cupcake appears and eats it. The regular people place the cupcake once and only once. If a person has placed a cupcake before they must leave laybrith without eating it. Once the counter counts all the times the cupcake has been placed then he announces that everyone has visited.
### Correctness and Efficiency of Design:
As for the implementation of the design, a `mutex` and `conditon_variable` has to be used to make sure that only one thread has access to the cupcake at a time and does not create a deadlock if the `condition_variable` was not in the function. 
### Runtime:
The runtime of the algorithim is hard to predict as it depends on when the counter gets to count when a cupcake has been eaten. It could hypothetically take infinite time in a worst case scenario based on the randomness aspect. In best case all of the people who have not eaten the cupcake get picked first next after the cupcake was counted and would run in `O(n)` time.
## Part 2: 
### How to Run:
To run the second program associated with the second Prompt. First run the command `g++ main2.cpp` and then run `./a.exe` or `./a.out` depending on the compiler and environemnt. __Make sure to put in a positive value for N.__
### Approach:
The approach taken on the showroom with the vase is the 1st strategy of any guest could check whether the showroom is open. Each guest is represented by one running thread and also simulates whether the person wants to go into the or not. At the start of the program the user is asked how many people (threads) are wanted.
### Correctness and Efficiency of Design:
The program uses a `mutex`, `conditon_variable`, and `unique_lock` paired with the mutex to execute the strategy. Every thread calls the `enterShowroom()` function. First each thread will decide whether it wants to enter the showroom once. If not then the thread ends. The Person/thread that decided to enter aquires the lock on the mutex and the other threads and guests can wander around/sleep until the thread that is in the showroom notifies the conditonal variable to notify all threads/people that the lock has been released and a random person gets into the showroom. It is not the most efficient design of the three methods.
### Advantages:
1. No Coordination Required
2. Flexibility of allowing guests to check whenever they want.
3. Low Overhead: Only door status needs to be checked and no other mechanisms.
### Disadvantages:
1. Potential Crowding around door.
2. Uncertain when guest might get in.
3. Lack of fairness: First come first served
4. Multithreaded environment guests could lead to race conditions without proper locking and synchronization mechanism.

### Runtime:
A Psedorandom generator has been implemented in the `enterShowroom()` function which can vary the runtime of the program. At most the runtime is dependent on N with every guest entering the showroom making the Person thread sleep for a maximum of 2 seconds. At mos the program will take 2(N) seconds if all threads decide to enter the showroom. 