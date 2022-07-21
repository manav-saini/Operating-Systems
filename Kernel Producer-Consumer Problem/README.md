How to run?
    Navigate to the directory using cd command
    run "make" command
    ./p
    ./c

Changes made in sys.c file
    Mutex lock and and a queue using a 2D character array was defined in the sys.c file first. Then insert and delete functions were made in the same file.In insert function if the cpacity variable is not equal to the rear pointer then first the mutex is locked and queue is enqueued, the rear pointer is incremented and then mutex is unlocked. In delete function if the front pointer and the rear pointer are not equal then mutex is locked and then the first element in the queue is taken out.
    Other than this two system calls reader and writer are defined. 
        In writer system call we take the pointer of char in which data is taken from the /dev/urandom file then to get the value from user space to kernel space we call the copy_from_user function and then call the insert function with the data as the parameter. 
        In reader system call we call the delete function with a pointer to char as a parameter to store the dequeued value. Then to tranfer the value from kernel space to user space we call the copy_to_user function.
Changes made in syscal_64.tbl
    337 common  writer          sys_writer
    338 common  reader          sys_reader
P.c
    In P.c we first open the /dev/urandom file using the open system call and then with the help of the read syatem call we read the first 8 bytes and store it in the data char array and then we call the writer system call to enqueue it in the queue maintained in the kernel.This all hapens in an infinite while loop
C.c
    In C.c we first declare a character array of size 8 then we call the reader system call which dequeue the element from the queue maintained in kernel and transfer it to user space. Then we print the data that we got from kenel space.
    

    
