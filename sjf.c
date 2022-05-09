//if arrival time is all 0, sort by burst time
//if same burst time, first come first serve must be applied

//have two arrays: array of processes and the sorted queue

// queue is sorted by arrival time 
/*
    1. A processes must arrive before being performed
    2. A process must be completed before another process executes
    3. If a process completes its execution, it checks if there are any process that has arrived
        a. Insert to the queue when current time is equal to the arrival time of the process
        b. When a process is completed, identify the shortest burst time in the current queue
        c. 
*/

//compare if arrival time is >= to time completion