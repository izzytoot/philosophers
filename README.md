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

## 2. The rules
