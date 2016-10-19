# Producer-Consumer-Model-Threads-Race-Condition-

This small project contains 1 main program and you may compile according to the directions below.

---mapqueue---

To compile: make mapqueue
To run: ./mapqueue <number of consumer threads> (this command-line argument is optional)
Description:

The mapqueue program takes an optional command-line argument: <number of consumer threads>. The program implements a simple simulation of producer-consumer model where the producer thread puts a job on the job queue every second and the consumer threads take jobs from the queue and finish them. When each consumer thread is done with the job taken, it tries to take another job from the queue. When no command-line argument is given, the program will simulate this system using one consumer thread.

The program uses mutex to avoid race condition. 
