## Philosophers

### <a name="top"> Content list:</a>

+ [Project description](#Description)

+ [Basic rules](#Basic)

+ [Specific rules](#Specific)

+ [Test cases](#Cases)

### <p><a name="Description">Project description</a></p>
The dining philosophers problem ([wiki](https://en.wikipedia.org/wiki/Dining_philosophers_problem#:~:text=In%20computer%20science%2C%20the%20dining,and%20techniques%20for%20resolving%20them.)) in a new interpretation 

(In this project, i learned the basics of threading a process, how to make threads, discover the mutex and semaphores)

This project include 3 different programs with basic rules, and some specific rules for each individual.

To test programs you need:

1. Download files.
2. Use "make" command in corresponding folder (example:"./philo_one/").
3. Run compiled file with parameters described in [basic rules](#Params) (example:"./philo_one 4 410 200 200").

![GitHub Logo](/dining_philosophers.png)

### <p><a name="Basic"> Basic rules, same for all programs:</a></p>

• A number of philosophers are sitting at a round table doing one of three things: eating, thinking or sleeping.

• While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.

• The philosophers sit at a circular table with a large bowl of spaghetti in the center.

• There are some forks on the table.

• As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.

• The philosophers must never be starving.

• Every philosopher needs to eat.

• Philosophers don’t speak with each other.

• Philosophers don’t know when another philosopher is about to die.

• Each time a philosopher has finished eating, he will drop his forks and start sleeping.

• When a philosopher is done sleeping, he will start thinking.

• The simulation stops when a philosopher dies.

• <a name="Params">Each program have the same options:</a>

	1. number_of_philosophers: is the number of philosophers and also the number
	of forks
	
	2. time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
	milliseconds after starting his last meal or the beginning of the simulation, it
	dies
	
	3. time_to_eat: is in milliseconds and is the time it takes for a philosopher to
	eat. During that time he will need to keep the two forks.
	
	4. time_to_sleep: is in milliseconds and is the time the philosopher will spend
	sleeping.
	
	5. number_of_times_each_philosopher_must_eat: argument is optional, if all
	philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
	simulation will stop. If not specified, the simulation will stop only at the death
	of a philosopher.
	
• Each philosopher should be given a number from 1 to ’number_of_philosophers’.

• Philosopher number 1 is next to philosopher number ’number_of_philosophers’. Any other philosopher with number N is seated between philosopher N - 1 and philosopher N + 1

• Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)

	◦ timestamp_in_ms X has taken a fork

	◦ timestamp_in_ms X is eating

	◦ timestamp_in_ms X is sleeping

	◦ timestamp_in_ms X is thinking

	◦ timestamp_in_ms X died

• Time between the death of a philosopher and when it will print its death not more more than 10 ms.

### <p><a name="Specific"> **Specific rules and description**  </a></p>

#### 1.	philo_one (philosopher with threads and mutex)

In this version the non common rules:

 • One fork between each philosopher, therefore there will be a fork at the right and at the left of each philosopher.

 • To avoid philosophers duplicating forks, forks protected with a mutex for each of them.

 • Each philosopher a thread.
 
***

#### 2.	philo_two (philosopher with threads and semaphore)

  In this version the non common rules:

  • All the forks are in the middle of the table.

  • They have no states in memory but the number of available forks is represented by a semaphore.

  • Each philosopher a thread.

***

#### 3.	philo_three (philosopher with processes and semaphore)

 In this version the non common rules:

 • All the forks are in the middle of the table.

 • They have no states in memory but the number of available forks is represented by a semaphore.

 • Each philosopher a process.
 
### <p><a name="Cases"> **Example of test cases**  </a></p>

 1. Test with 5 800 200 200, no one should die!

 2. Test with 5 800 200 200 7, no one should die and the simulation should stop when all the philosopher has eaten at least 7 times each!

 3. Test with 4 410 200 200, no one should die!

 4. Test with 4 310 200 100, a philosopher should die!

 
<p><a href="#top">Go to the content list</a></p>
