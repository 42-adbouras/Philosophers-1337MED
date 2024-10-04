## ToC
- [Introduction to threads](#introduction-to-threads)
	* [What is a thread](#what-is-a-thread)
	* [Working with threads](#working-with-threads)
	* [Race conditions](#race-conditions)






## Introduction to threads

### What is a thread
A thread is a lightweight process that can run simultaneously with other threads in the same application. They help in performing multiple tasks simultaneously, improving the efficiency of applications, especially in multicore processors.\
Here is some thread's characteristics:\
Threads require less overhead to create and manage compared to processes. This means creating and managing threads involves fewer system resources and less time than doing the same for processes. Threads share the same memory space and resources within a process, so they can be created, destroyed, and switched between more quickly. In contrast, processes are more isolated and require more overhead due to their separate memory allocations and additional management by the operating system.\
Threads within the same process share the same memory space, allowing for easy communication but also increasing the risk of race conditions.\
Threads enable concurrent execution, meaning multiple threads can run simultaneously, especially on multi-core processors. Additionally, a process can have multiple threads, but a thread can't have its own process or threads.

### Working with threads

The subject requires us to utilize the POSIX thread (pthread) library. It is commonly used for thread management. Here’s a step by step guide to create and using threads:\

* Include the Library:
```c
#include <pthread.h>
```
* Define a Thread Function:\
This function will executed by the thread. It must return a void* type.
```c
void	*thread_routine(void* arg)
{
    // Perform tasks here
    return (NULL);
}
```
* Create a Thread:\
Use `pthread_create` to create a new thread. It takes four arguments:\
A pointer to `pthread_t` variable (to hold the thread ID).\
Thread attributes (usually NULL for default).\
The function to execute.\
An argument to pass to the thread function (can be NULL).
```c
pthread_t thread;

pthread_create(&thread, NULL, threadFunction, NULL);
```

* Wait for a Thread to Finish:\
Use `pthread_join` to wait for a specific thread to complete.
This prevents the main thread from exiting before the created thread finishes.

* Key Functions:\
	* `pthread_create` Creates a new thread of execution.
	```c
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
	```
	`thread`: This is a pointer to a `pthread_t` variable that `pthread_create` will fill with an identifier for the new thread. You can use this identifier in other thread related functions.\
	`attr`: This is a pointer to a `pthread_attr_t` structure that specifies thread attributes. If this parameter is `NULL`, then the thread is created with default attributes.\
	`start_routine`: This is a pointer to the function that the new thread will start executing. The function must have the following signature: `void *function_name(void *arg)`. This function takes a single argument and returns a pointer to void.\
	`arg`: This is a pointer that will be passed as the argument to the `start_routine` function. If your function takes more than one argument, then you can pass a pointer to a structure containing the arguments.
	* `pthread_join`: Causes the calling thread to wait for the termination of the specified thread.
	```c
	int pthread_join(pthread_t thread, void **value_ptr)
	```
	`thread`: This is the identifier of the thread to wait for. This identifier is the one that was filled by `pthread_create` when the thread was created.
	`value_ptr`: This is a pointer to a void* variable that will be filled with the return value of the thread. When the thread we're waiting for finishes execution, whatever it returns is passed back via this `value_ptr`. If this argument is `NULL`, then the return value of the thread is ignored.\
	* `pthread_detach`: Marks a thread for deletion.
	```c
	int pthread_detach(pthread_t thread)
	```
	`thread`: This is the identifier of the thread to be detached. This identifier is the one that was filled by `pthread_create` when the thread was created.

### Race conditions
Race conditions in C occur when multiple threads access shared resources concurrently, leading to unpredictable outcomes. If two or more threads modify a variable without proper synchronization, the final value can depend on the timing of thread execution, resulting in inconsistent or erroneous behavior.\
For example, consider two threads trying to increment a shared counter. If both threads read the counter simultaneously, they may both see the same initial value, increment it, and then write back the same result, effectively losing one increment.\
Here where it comes to MUTEXes, you can use mutexes to control access to shared resources, ensuring that only one thread can modify the resource at a time. This way, you can maintain data integrity and consistency in a multithreaded environment.\
* Key Functions:\
	* `pthread_mutex_init`: Initialize a mutex with specified attributes.
	```c
	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
	```
	`mutex`: This is a pointer to a `pthread_mutex_t` variable that `pthread_mutex_init` will initialize. This mutex can then be used in other mutex related functions.\
	`attr`: This is a pointer to a `pthread_mutexattr_t` structure that specifies mutex attributes. If this parameter is `NULL`, then the mutex is created with default attributes.
	* `pthread_mutex_lock`: Lock a mutex and block until it becomes available (unlocked).
	```c
	int pthread_mutex_lock(pthread_mutex_t *mutex)
	```
	`mutex`: This is a pointer to an initialized `pthread_mutex_t` variable that `pthread_mutex_lock` will try to lock. This mutex should have been previously initialized using `pthread_mutex_init`.\
	* `pthread_mutex_unlock`: Unlock a mutex.
	```c
	int pthread_mutex_unlock(pthread_mutex_t *mutex)
	```
	`mutex`: This is a pointer to an initialized `pthread_mutex_t` variable that `pthread_mutex_unlock` will unlock. This mutex should have been previously locked by the same thread using `pthread_mutex_lock`.
	* `pthread_mutex_destroy`: Destroy a mutex.
	```c
	int pthread_mutex_destroy(pthread_mutex_t *mutex)
	```








