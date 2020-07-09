# PHILOSOPHERS
Recoding of a classic problem in multithread management. This proyect is solved using mutex locks and semaphores.

## The problem
The Dining Philosopher Problem states that K philosophers seated around a circular table with one chopstick between each pair of philosophers. There is one chopstick between each philosopher. A philosopher may eat if he can pickup the two chopsticks adjacent to him. If each philosopher does not eat in a specefic time he may die. The goal of this problem is to correctly manage all resources so no philosopher dies.


### Mutex locks 
This is part of the proyect is solved using a waiter as arbitrator. The waiter will be responsible fo each philosopher picking just two or none chopsticks in case a chopstick is already taken. Prior to give permission, waiter must make sure that the philosopher haven't eatean yet in the current round and it's his turn.

### Semaphores
