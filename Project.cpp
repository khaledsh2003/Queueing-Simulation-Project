/*
Purpose and design: The purpose of the program is to simulate a queueing system. So, this simulation will be used to gather some statics. The program reads the number of queue/server pairs, the probability that a customer will arrive in a single tick, the longest time a transaction may take, the duration of the simulation in ticks, and a integer seed value for the random number generator. Then, the program will simulate the queueing system for the specified time and with the specified inputs. Also, during each tick some events occur. Like a customer is dequeued when a teller is free, and a customer is enqueued to the shortest line. Moreover, transaction times are decreased after each simulation tick. Finally, the program reports some statics. Those statics include: the number of customers served, the probability that a customer will arrive in a single tick, the average wait times of customers served, the longest time a customer waited, and the number of customers left in the queues when the simulation stops.
*/
// File: project7.cpp
#include<iostream>
#include "Queue.h"                              // include queue class
#include<cstdlib>
#include<iomanip>
#include<bits/stdc++.h>

using namespace std;
// A function that examines the lengths of the queues and the remaining transactions.
// Precondition: A queue object, the number of the queues or tellers, and the tellers’ array
// Postcondition: correct index is returned to where a customer should enter
int shortest(Queue q1[],int length, int teller1[])
{
    int min=0;
    int size=0;
    for(int x=1;x<length;x++)                                          // loop until end of queues
    {
        if(q1[min].size()>q1[x].size())
            {
                min=x;                                                // compute the minimum queue size
                size=q1[x].size();                                   // save minimum size of the queue
            }                                           
                                                
    }
    for(int x=0;x<length;x++)                                          // loop again until end of queues
    {
        if(teller1[x]==0 && q1[x].size()==0)                           // if teller is free and queue empty then return index
            return x;
        else if(teller1[x]==0 && q1[x].size() == size && size!=0)      // if teller is free, size of a queues is equal to  the shortest size, and the size is not zero then return index
            return x;
    }
    return min;     // if second loop did not return anything then return the shortest queue length

}
// A function that determines which queue is not empty and has a free server
// Precondition: A queue object, an integer number of the queues or tellers inputted, and an integer tellers’ array
// Postcondition: A correct index is returned to where a customer should be served
int tellerfree( int teller2[],Queue q2[],int length)
{
    for(int x=0;x<length;x++)                       // loop until end of queues
    {
        if((teller2[x]==0) && (!q2[x].empty()))     // if teller free and queue is not empty
            return x;                               // return index
    }
    return -10; // if nothing is returned previously then return -10
}
// A function that determines the total length of queues
// Precondition: A queue object and an integer number of the queues or tellers inputted
// Postcondition: A sum of queues total lengths is returned
int sum_length(int length, Queue q4[])
{
    int sum=0;
    for(int x=0;x<length;x++)        // loop until end of queues
    {
        sum+=q4[x].size();           // Accumulate sum
    }
    return sum;
}
int main()
{
    int QueNum=0;
    int Prob=0;
    int Trans_Duration=0;
    int Simulation_Duration=0;
    int seed=0;
    int trans_time=0;
    int count=0;
    int entry_time=0;
    float wait_sum=0.0;
    // get user input for the simulation
    cout<<"Enter these parameters of the simulation:"<<endl;
    cout<<"  The number of queue/server pairs: ";
    cin>>QueNum;
    cout<<"  The probability that a customer arrives in one tick (%): ";
    cin>>Prob;
    cout<<"  The maximum duration of a transaction in ticks: ";
    cin>>Trans_Duration;
    cout<<"  The duration of the simulation in ticks: ";
    cin>>Simulation_Duration;
    cout<<"Enter a random number seed:";
    cin>>seed;
    srand(seed);
  
    Queue q[QueNum];   
    
      count=0;
                 // declare array of queue objects
    int teller[QueNum];             // declare array of tellers
    for(int x=0;x<QueNum;x++)       // initialize tellers to be free
    {
        teller[x]=0;
    }



    int y;                          // hold shortest queue index
    int point=-10;
    int time12[700];                // holds all wait sums

    for(int time=1;time<Simulation_Duration+1;++time)       // simulate until the length of duration
    {
        if(rand()%100 < Prob)                               // if customer arrived
        {
            y=shortest(q,QueNum,teller);                    // find shortest index
            q[y].enqueue(time);                             // add the customer to shortest queue
        }
        for(int x=0;x<QueNum;x++)                           // loop over the number of queues
        {
            point=tellerfree(teller,q,QueNum);              // if teller free and queue not empty point will hold index
            if(point!=-10)                                  // if index returned not -10 then dequeue customer
            {
                entry_time=q[point].dequeue();              // dequeue
                wait_sum+=(time-entry_time);                // accumulate wait sums
                time12[count]=(time-entry_time);            // accumulate wait sums in an array
                ++count;                                    // increment number of customers served
                trans_time=(rand()%Trans_Duration)+1;       // random transaction time for new customer
                trans_time+=1;                              // beacuse the new added teller will be decremented 
                teller[point]=trans_time;
            }
        }
        for(int u=0;u<QueNum;u++)                            // loop over the number of tellers
        {

            if(teller[u]!=0)                                 // if teller is not free
                --teller[u];                                 // decrement transaction time
        }
        // formatting snapshot of simulation
        cout<<time;
        cout<<endl;
        for(int x=0;x<QueNum;x++)
        {
            cout<<setw(9)<<teller[x]<<"  "<<q[x];
            cout<<endl;
        }
        cout<<endl;
      

    }
    //printing out statics
    // number of customers served and wait time average
    float avg=0.0;
    avg=wait_sum/count;

    cout<<count<<" customers waited an average of "<<avg<<" ticks."<<endl;
    // get the longest time a customer waited by getting max number of array of wait sums
    cout<<"The longest time a customer waited was "<<*max_element (time12, time12+count)<<" ticks."<<endl;
    // get the number of customers that are not served yet
    cout<<sum_length(QueNum,q)<<" customers remain in the lines."<<endl;
    return EXIT_SUCCESS;
   
}
