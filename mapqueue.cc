#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <queue>

#include <mutex>

using namespace std;

void takeJobs(int threadNum, queue<int>* jobQueue, mutex* jobLock)
{
   /*
   lock jobLock outside of the if statement to avoid the situation where the threads identify the queue to be non-empty and try 
   to pop an item concurrently; unlock jobLock when an item is popped and the statement is printed, so other threads wouldn’t 
   have to wait for the sleeping time. In addition, an else statement is added to unlock jobLock, which deals with the situation 
   where the queue is indeed empty and the unlock part inside the if statement is skipped. 
   */
	
   while (1)
   {  
      jobLock->lock(); 
      if (!jobQueue->empty())
      {  
	 int jobLength = jobQueue->front();
	 jobQueue->pop();  
	 printf("%i took a job of length %i. Number of jobs left: %i\n", threadNum, jobLength, (int)jobQueue->size());
         jobLock->unlock();
	 this_thread::sleep_for(std::chrono::seconds(jobLength));
	 printf("%i finished its job.\n", threadNum);
      }
      else
      {
        jobLock->unlock(); 
      }
   }
   
}

void makeJobs(int threadNum, queue<int>* jobQueue, mutex* jobLock)
{
   /*
   lock jobLock when it pushes a new job to the queue and prints the statement, so no consumer thread would do anything until 
   the producer thread unlocks jobLock. 
   */
	
   while (1)
   {  
      int jobLength = rand()%5 + 1;
      jobLock->lock(); 
      jobQueue->push(jobLength);
      printf("%i created a job of length %i. Number of jobs left: %i\n", threadNum, jobLength, (int)jobQueue->size());
      jobLock->unlock(); 
	 this_thread::sleep_for(std::chrono::seconds(1));
   }
}

int main(int argc, char** argv)
{
   int numConsumers = 1;
   if(argc > 1)
   {
      numConsumers = atoi(argv[1]);
   }
   queue<int> jobQueue;

   mutex jobLock;

   thread producer = thread(makeJobs, 0, &jobQueue, &jobLock);

   thread* consumers = new thread[numConsumers];
   for(int i = 0; i < numConsumers; i++)
   {
      consumers[i] = thread(takeJobs, i + 1, &jobQueue, &jobLock);
   }

   producer.join();
   for(int i = 0; i < numConsumers; i++)
   {
      consumers[i].join();
   }
}
