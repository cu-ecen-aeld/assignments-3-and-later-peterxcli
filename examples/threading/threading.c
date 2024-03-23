#include "threading.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg, ...)
// #define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg, ...) printf("threading ERROR: " msg "\n", ##__VA_ARGS__)

void *threadfunc(void *thread_param) {
    struct thread_data *thread_func_args = (struct thread_data *)thread_param;

    // Sleep before obtaining the mutex
    usleep(thread_func_args->wait_to_obtain_ms * 1000); // Convert ms to us

    // Obtain the mutex
    if (pthread_mutex_lock(thread_func_args->mutex) == 0) {
        // Sleep before releasing the mutex
        usleep(thread_func_args->wait_to_release_ms * 1000); // Convert ms to us

        // Release the mutex
        pthread_mutex_unlock(thread_func_args->mutex);
        thread_func_args->thread_complete_success = true;
    } else {
        ERROR_LOG("Failed to lock mutex");
        thread_func_args->thread_complete_success = false;
    }

    return thread_func_args;
}

bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex, int wait_to_obtain_ms, int wait_to_release_ms) {
    struct thread_data *thread_data_ptr = (struct thread_data *)malloc(sizeof(struct thread_data));
    if (!thread_data_ptr) {
        ERROR_LOG("Failed to allocate memory for thread_data");
        return false;
    }

    // Initialize thread_data
    thread_data_ptr->mutex = mutex;
    thread_data_ptr->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_data_ptr->wait_to_release_ms = wait_to_release_ms;
    thread_data_ptr->thread_complete_success = false;

    // Create the thread
    if (pthread_create(thread, NULL, threadfunc, thread_data_ptr) != 0) {
        ERROR_LOG("Failed to create thread");
        free(thread_data_ptr); // Clean up allocated memory on failure
        return false;
    }

    return true; // Thread started successfully
}