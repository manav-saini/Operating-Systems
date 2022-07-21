How to run?
    run the make command in the directory containing all these programs
    ./part_1
    ./part_2
    ./part_3
    ctrl + c to stop 

In these programs we are declaring fork and bowls as semaphores so that we can maintain synchronzation while accessing them and to prevent deadlocks. We access them using the sem_wait function and we leave their access using the sem_post function. Philosophers are declared as threads. 

part_1.c
    The philosophers choose a chopstick on their left, then another on their right, and eventually begin eating. To prevent a deadlock, the philosopher returns the first chopstick if he is unable to obtain it and attempts to eat later. 
        This avoids deadlock and allows everyone to finish eating.
part_2.c
    In part_2 there will be no deadlock condition because only one fork and one of the four bowls is required so no condition will occur when a philosopher will remain hungry for ever. Bowls are not assignesd to particular philosophers and philosopher eating doesn't depends on other philosopher resources so there won't be any deadlock.
part_3.c
    The philosophers choose a chopstick on their left, then another on their right, then a bowl, and eventually begin eating. To prevent a deadlock, the philosopher returns the first chopstick if he is unable to obtain it and attempts to eat later. Similarly, if he or she fails to pick up the bowl, they return both chopsticks that they had previously taken up.
        This avoids deadlock and allows everyone to finish eating.
