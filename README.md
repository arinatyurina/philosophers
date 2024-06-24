# MyPhilosophers Project

## Introduction

The MyPhilosophers project is a unique take on the classic "Dining Philosophers" problem, illustrating synchronization issues and techniques in concurrent programming. This scenario involves a certain number of philosophers sitting at a round table, alternating between thinking and eating. Each philosopher needs two forks (or chopsticks) to eat, but there are only as many forks as there are philosophers, leading to potential conflicts and the need for proper synchronization to avoid deadlocks and ensure that all philosophers can eventually eat.

## Setup

1. Clone the repository:

    ```sh
    git clone https://github.com/arinatyurina/philosophers.git
    ```

2. Compile the program:

    ```sh
    make
    ```

## Usage

To run the simulation, execute the following command:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
+ **number_of_philosophers**: the number of philosophers and also the number of forks.  
+ **time_to_die**: time (in milliseconds) a philosopher can go without eating before dying.  
+ **time_to_eat**: time (in milliseconds) it takes for a philosopher to eat.  
+ **time_to_sleep**: time (in milliseconds) a philosopher spends sleeping.  
+ **number_of_times_each_philosopher_must_eat (optional)**: if all philosophers eat this many times, the simulation ends. If not specified, the simulation runs indefinitely.

## Terminology

### Thread
**Definition**: A thread is a single sequence stream within a process.  
**The differences between process and thread**: Threads are not independent from each other unlike processes. As a result, threads shares with other threads their code section, data section and OS resources like open files and signals. But, like processes, a thread has its own program counter (PC), a register set, and a stack space. 

#### pthread_create: used to create a new thread 
```sh
int pthread_create(pthread_t * thread, 
                   const pthread_attr_t * attr, 
                   void * (*start_routine)(void *), 
                   void *arg);
```
**thread**: pointer to an unsigned integer value that returns the thread id of the thread created.  
**attr**: pointer to a structure that is used to define thread attributes like detached state, scheduling policy, stack address, etc. Set to NULL for default thread attributes.  
**start_routine**: pointer to a subroutine that is executed by the thread. The return type and parameter type of the subroutine must be of type void *. The function has a single attribute but if multiple values need to be passed to the function, a struct must be used.  
**arg**: pointer to void that contains the arguments to the function defined in the earlier argument

#### pthread_exit: used to terminate a thread 
```sh
void pthread_exit(void *retval);
``` 
This method accepts a mandatory parameter retval which is the pointer to an integer that stores the return status of the thread terminated. The scope of this variable must be global so that any thread waiting to join this thread may read the return status.

### Mutex
**Definition**: A Mutex is a lock that we set before using a shared resource and release after using it.  
When the lock is set, no other thread can access the locked region of code.
So we see that even if thread 2 is scheduled while thread 1 was not done accessing the shared resource and the code is locked by thread 1 using mutexes then thread 2 cannot even access that region of code.
So this ensures synchronized access of shared resources in the code.

#### pthread_mutex_init
```sh
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
``` 
**mutex**: Pointer to a pthread_mutex_t structure that is initialized by this function.  
**attr**: Pointer to a pthread_mutexattr_t structure that specifies the mutex's attributes. Set to NULL for default attributes.
#### pthread_mutex_lock
```sh
int pthread_mutex_lock(pthread_mutex_t *mutex);
```
**mutex**: Pointer to a pthread_mutex_t structure that has been initialized using pthread_mutex_init.
#### pthread_mutex_unlock
```sh
int pthread_mutex_unlock(pthread_mutex_t *mutex);
``` 
**mutex**: Pointer to a pthread_mutex_t structure that has been initialized and locked using pthread_mutex_lock.
#### pthread_mutex_destroy
```sh
int pthread_mutex_destroy(pthread_mutex_t *mutex);
``` 
**mutex**: Pointer to a pthread_mutex_t structure that has been initialized using pthread_mutex_init. After calling pthread_mutex_destroy, this mutex cannot be used unless it is reinitialized with pthread_mutex_init
