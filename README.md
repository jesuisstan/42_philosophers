# 42_philosophers

## Foreword
This is one of the Ecole 42 common core projects.\
In computer science, the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.\
The project is about handling `dining philosophers problem` with threading a process.\
Written with holly C language and provides good understanding of [Multithreaded programming](https://www.ibm.com/docs/en/aix/7.2?topic=concepts-multithreaded-programming), processes, mutexes and semaphores.

## Description
The project simulates the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) and handles it with:
1. [mutexes](https://www.ibm.com/docs/en/aix/7.2?topic=programming-using-mutexes) (mandatory part in folder `philo`);
2. [semaphores](https://www.ibm.com/docs/en/i/7.1?topic=threads-semaphores) (bonus part in folder `philo_bonus`).

Basic rules:
- One or more philosophers are sitting at a round table doing one of three things:\
eating, thinking, or sleeping.
- While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table.
- It is assumed that a philosopher must eat with two forks, one for each hand.
- Every philosopher needs to eat.
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- Each time a philosopher has finished eating, he will drop his forks and start sleeping.
- When a philosopher is done sleeping, he will start thinking.
- The simulation stops when a philosopher dies.

For the mandatory part:
- To avoid philosophers duplicating forks, the forks state with a mutex for each of them.
- Each philosopher should be a thread.

For the bonus part:
- Forks have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.

Full project description you can find in `subject_philo.pdf`.

## Requirements
- installed `gcc`
- installed `Makefile`

## How to use?
### Mandatory part (`mutexes`):
1. Run `make` to compile the project in `philo` folder.
2. Execute `./philo` with different arguments of your choise to run simulation like this:
```sh
./philo 5 800 200 200
```
(no philosopher should die!)\
#### or
```sh
./philo 5 800 200 200 7
```
(no one should die and the simulation should stop when all the philosopher has eaten atleast 7 times each).\

3. Run `make fclean` to delete all created files.

### Bonus part (`semaphores`):
1. Run `make` to compile the project in `philo_bonus` folder.
2. Execute `./philo_bonus` with different arguments of your choise to run simulation like this:
```sh
./philo_bonus 4 410 200 200
```
(no philosopher should die!)\
#### or
```sh
./philo_bonus 5 800 200 200 7
```
(no one should die and the simulation should stop when all the philosopher has eaten atleast 7 times each).\

3. Run `make fclean` to delete all created files.
