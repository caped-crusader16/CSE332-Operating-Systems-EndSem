/*Krina Khakhariya 
AU1940208*/

/*Question 1. Print the following Pattern
A 1 a B 2 b C 3 c ... Y 25 y Z 26 z
Using any one of the following concepts
a. Multiprocesses (Hint: using 3 child processes)
b. Multithreads (Hint: using 3 Threads)
(PS: Process Synchronization or Thread Synchronization is key thing for
pattern printing)*/
#include <iostream>
#include <thread>
#include<mutex>
#include<semaphore.h>
#include <unistd.h>
#define THREAD_NUM 3
using namespace std;

sem_t Small_Letter;
sem_t Capital_Letter;
sem_t num;
//Function for Small Letters
void func_small(){      
    for(int i = 1;i<27;i++){
      sem_wait(&num);   
        std::cout<<" "<<i<<" ";
    sem_post(&Small_Letter);
    }
}
//Function for Captial Letters
void func_caps(){    
char ch;
    
    for (ch = 'A'; ch <= 'Z'; ++ch){
     sem_wait(&Capital_Letter);
        std::cout<<ch<<"";
    sem_post(&num);
    }
}
//Function for Numbers
void func_num(){
    char ch;
    for (ch = 'a'; ch <= 'z'; ++ch){
    sem_wait(&Small_Letter);
        std::cout<<ch<<" ";
    sem_post(&Capital_Letter);
    }
}
int main(){
sem_init(&Small_Letter, 0, 0);
sem_init(&Capital_Letter, 0, 1);
sem_init(&num, 0, 0);
  std::thread small_thread,capital_thread,numeric_thread;

  small_thread =  std::thread(func_small);
  capital_thread = std::thread(func_caps);
  numeric_thread = std::thread(func_num);
  
    capital_thread.join();
    numeric_thread.join();
    small_thread.join();
}