**The Dining Philosopher Problem** is a classic synchronization and concurrency problem that deals with resource sharing, deadlock, and starvation in systems where multiple processes require limited resources.

In this project, I learned to use `mutex` to ensure that threads take turns accessing shared resources safely and efficiently.

## Running the Program
1. `cd philo`
2. run `make`
3. run program `philo` with these arguments `num_of_philos time_to_die time_to_eat time_to_sleep
 [num_of_times_each_philo_must_eat]`

   Example:
   ```
   ./philo 4 410 200 200
   ```
