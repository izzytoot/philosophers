# 🍝 PHILOSOPHERS

## 1. About the project
This project is based on the famous dining philosophers, used in computer science to illustrate common issues in concurrent programming. It introduces us to the basics of threading processes.

## 2. The problem
- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternate between eating, thinking, or sleeping:
- While they are eating, they are not thinking nor sleeping;
- while thinking, they are not eating nor sleeping;
- While sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- A philosopher must take two forks to eat, one in each hand.
- When finished eating, they put their forks back on the table and start sleeping.
- Once awake, they start thinking again.
- The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.

<div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/philos.png">
</div>

## 3. The rules
- Global variables are forbidden!
- The  program should take the following arguments:
- Global variables are forbidden!
- The program should take the following arguments:
```
./philo <nb_philos> <time_to_die> <time_to_eat> <time_to_sleep> [max_meals]
```
- where:
  - number_of_philosophers (nb_philos): The number of philosophers and of forks.
  - time_to_die (in milliseconds): the time a philosopher has between meals, otherwise philosopher dies.
  - time_to_eat (in milliseconds): the time a philosopher takes to eat. During this time a philo hols 2 forks.
  - time_to_sleep (in milliseconds): the time a philosopher takes to sleep.
- Each philosopher has a number ranging from 1 to nb_philos.
- Philo_1 sits between Philo_2 and Philo_nb_philos (last philo). Philo_2 sits between Philo_1 and Philo_3. And so on...
- Any state change of a philosopher must be formatted as follows:
  - timestamp_in_ms X has taken a fork
  - timestamp_in_ms X is eating
  - timestamp_in_ms X is sleeping
  - timestamp_in_ms X is thinking
  - timestamp_in_ms X died
    - timestamp_in_ms is current time in milliseconds.
    - X is the Philo's number.
- A displayed state message should not be mixed up with another message.
- A message announcing a Philo died should be displayed no more than 10 ms after the actual death.
- The program shouldn't have any data races.
- Philosophers should avoid dying!

### EXAMPLES OF THE PROGRAM RUNNING:
1. Philos survive, full at 2 meals:
  <div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/ex.%201.png">
</div>

2. Philos die due to starvation at 100ms:
<div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/ex.%202.png">
</div>

## 4. Code Workflow

<div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/legenda.png">
</div>

<div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/workflow%201.png">
</div>

<div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/workflow%202.png">
</div>

<div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/workflow%203.png">
</div>

<div aling="left">
     <img src="https://github.com/izzytoot/philosophers/blob/main/images/workflow%204.png">
</div>
