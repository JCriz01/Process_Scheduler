//
// Created by Jesse Crispin on 3/24/24.
//

#include "JobScheduler.h"
#include <iostream>
using namespace std;

//default constructor
JobScheduler::JobScheduler(){
    numberOfProcesses = 0;
}

//setting the number of processes.
void JobScheduler::setJobSize(int size){
    numberOfProcesses = size;
}

//adding a process to the job list.
void JobScheduler::addProcess(Process process){
    jobList.push_back(process);
}

//searching for a job by job id.
int JobScheduler::searchByJobID(int jobID) {
    for(int i = 0; i < numberOfProcesses; i++){
        if(jobList[i].getJobID() == jobID){
            return i;
        }
    }
    return -1;

}

//overloading the = operator to copy the jobScheduler object.
JobScheduler& JobScheduler::operator=( deque<Process> &jobScheduler) {
    //copying the jobScheduler object to the current object.
    for(int i = 0; i < jobScheduler.size(); i++){
        jobList[i].setCpuCycle(jobScheduler[i].getCpuCycle());
        jobList[i].setFinishTime(jobScheduler[i].getFinishTime());
        jobList[i].setTurnAroundTime(jobScheduler[i].getTurnAroundTime());
        jobList[i].setWaitTime(jobScheduler[i].getWaitTime());
    }
    return *this;
}

void JobScheduler::sortByJobId( deque<Process> &list) {
    //sorting the job list based on job id.
    //ascending order.
    for(int i = 0; i < list.size(); i++){
        for(int j = i+1; j < list.size(); j++){
            if(list[i].getJobID() > list[j].getJobID()){
                Process temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void JobScheduler::firstComeFirstServe() {
    bool isFinished = false;
    int jobIndex = 0;

    while ( jobIndex < numberOfProcesses){
        if(jobIndex == 0){

            int finshTime = jobList[jobIndex].getArrivalTime() + jobList[jobIndex].getCpuCycle();
            jobList[jobIndex].setFinishTime( finshTime );

            int turnAroundTime = jobList[jobIndex].getFinishTime() - jobList[jobIndex].getArrivalTime();
            jobList[jobIndex].setTurnAroundTime( turnAroundTime );

            jobList[jobIndex].setWaitTime(0);

            cout<<"Job ID: "<<jobList[jobIndex].getJobID()<<" Arrival Time: "<<jobList[jobIndex].getArrivalTime()
            <<" CPU Cycle: "<<jobList[jobIndex].getCpuCycle()<<" Finish Time: "<<jobList[jobIndex].getFinishTime()
            <<" Turn Around Time: "<<jobList[jobIndex].getTurnAroundTime()<<" Wait Time: "<<jobList[jobIndex].getWaitTime()
            <<endl;

        }
        else{
            //getting previous job's finish time.
            int prevFinishTime = jobList[jobIndex-1].getFinishTime();

            //setting current job's finish time.
            int finshTime = prevFinishTime + jobList[jobIndex].getCpuCycle();
            jobList[jobIndex].setFinishTime( finshTime);

            //setting current job's turn around time.
            int turnAroundTime = jobList[jobIndex].getFinishTime() - jobList[jobIndex].getArrivalTime();
            jobList[jobIndex].setTurnAroundTime( turnAroundTime );

            //setting current job's wait time.
            int waitTime = jobList[jobIndex - 1].getFinishTime() - jobList[jobIndex].getArrivalTime();
            jobList[jobIndex].setWaitTime( waitTime );

            cout<<"Job ID: "<<jobList[jobIndex].getJobID()<<" Arrival Time: "<<jobList[jobIndex].getArrivalTime()
                <<" CPU Cycle: "<<jobList[jobIndex].getCpuCycle()<<" Finish Time: "<<jobList[jobIndex].getFinishTime()
                <<" Turn Around Time: "<<jobList[jobIndex].getTurnAroundTime()<<" Wait Time: "<<jobList[jobIndex].getWaitTime()
                <<endl;
        }
        jobIndex +=1;
    }
}

void JobScheduler::getAverageWaitTime() {
    double totalWaitTime = 0;
    for(int i = 0; i < numberOfProcesses; i++){
        totalWaitTime += jobList[i].getWaitTime();
    }
    averageWaitTime = totalWaitTime / numberOfProcesses;
    cout << "Average Wait Time: " << averageWaitTime << endl;
}

void JobScheduler::getAverageTurnAroundTime() {
    double totalTurnAroundTime = 0;
    for(int i = 0; i < numberOfProcesses; i++){
        totalTurnAroundTime += jobList[i].getTurnAroundTime();
    }
    averageTurnAroundTime = totalTurnAroundTime / numberOfProcesses;
    cout << "Average Turn Around Time: " << averageTurnAroundTime << endl;
}

void JobScheduler::sortJobList(std::string jobType) {
    if(jobType == "SJN"){
        //sorting the job list based on the smallest cpu cycle first.
        //Basically sorting in descending order based on cpu cycle.
        for(int i = 1; i < numberOfProcesses; i++){
            for(int j = i+1; j < numberOfProcesses; j++){
                if(jobList[i].getCpuCycle() > jobList[j].getCpuCycle()){
                    Process temp = jobList[i];
                    jobList[i] = jobList[j];
                    jobList[j] = temp;
                }
            }
        }
    }
    if(jobType =="RR"){
        //sorting the job list based on the smallest cpu cycle first.
        //Basically sorting in descending order based on cpu cycle.
        for(int i = 0; i < numberOfProcesses; i++){
            for(int j = i+1; j < numberOfProcesses; j++){
                if(jobList[i].getArrivalTime() > jobList[j].getArrivalTime()){
                    Process temp = jobList[i];
                    jobList[i] = jobList[j];
                    jobList[j] = temp;
                }
            }
        }

    }
    if(jobType == "SRT"){
        //sorting by arrival time.
        for(int i = 0; i < numberOfProcesses; i++) {
            for (int j = i + 1; j < numberOfProcesses; j++) {
                if (jobList[i].getArrivalTime() > jobList[j].getArrivalTime()) {
                    Process temp = jobList[i];
                    jobList[i] = jobList[j];
                    jobList[j] = temp;
                }
            }
        }
    }
}

void JobScheduler::setContextSwitchTime(double time) {
    this->contextSwitchTime = time;
}

void JobScheduler::getContextSwitchTime() {
    cout << "Context Switch Time: " << contextSwitchTime << endl;
}

void JobScheduler::shortestJobNext() {
    sortJobList("SJN");
    //Same as first come first serve after sorting based on cpu cycle.
    firstComeFirstServe();
}

void JobScheduler::setQuantumTime(int quantumTime) {
    this->quantumTime = quantumTime;
}

void JobScheduler::roundRobin() {

    //creating double ended queue to store the processes.
    deque<Process> readyQueue;
    deque<Process> runningQueue;
    deque<Process> waitingQueue;
    deque<Process> finishedQueue;
    Process currJob;
    //sorting the job list based on arrival time.
    sortJobList("RR");

    bool isFinished = false;
    double contextSwitchCounter = 0;
    int timeLeft=0;
    int currTime = jobList[0].getArrivalTime();
    int switchTime=quantumTime;
    int startingTime = currTime;
    //adding jobs to ready queue
    for(int i = 0; i < numberOfProcesses; i++){
        readyQueue.push_back(jobList[i]);
    }

    //getting jobs that have arrived at 0.
    //for(int i = 0; i < numberOfProcesses; i++){
    //    if(readyQueue[i].getArrivalTime() == 0){
    //        waitingQueue.push_back(readyQueue[i]);
    //    }
    //}

    while(finishedQueue.size() != jobList.size() ){

        //executing first job in the waiting queue.

        //checking if any job(s) has arrived at the current time.
        while (readyQueue.front().getArrivalTime() == currTime){
            waitingQueue.push_back(readyQueue.front());
            readyQueue.pop_front();
        }
        switchTime = currTime - quantumTime;

        //checking if cpu cycle is less than quantum time.
        if(waitingQueue.size() != 0){

            currJob = waitingQueue.front();


            for(int i=startingTime; i <= currTime; i= i+quantumTime){
                if(i == currTime){
                    //startingTime = currTime;
                    if(!isFinished){
                        waitingQueue.push_back(currJob);
                        waitingQueue.pop_front();

                        if(jobList[currJob.getJobID() -1].getCpuCycle() - currJob.getCpuCycle() > 0 && waitingQueue.size() != 1)
                            contextSwitchCounter += 1;
                    }

                    //adding the current job to the back of the waiting queue.
                    //removing the current job from the front of the waiting queue.
                    //making currJob the newest job in the waiting queue.
                    currJob = waitingQueue.front();
                    //contextSwitchCounter += 1;
                    //cout << currJob.getJobID() << currJob.getArrivalTime() << currJob.getCpuCycle() << endl;
                }
            }

            if(isFinished){

                isFinished = false;
            }            //currJob = waitingQueue.front();
            //calculating how much time is left
            timeLeft = currJob.getCpuCycle() - 1;
            currJob.setCpuCycle(timeLeft);
            waitingQueue.front().setCpuCycle(timeLeft);
            //setting finish time since the job is done.
            if(timeLeft == 0){
                currTime += 1;

                int currJobCpu = jobList[searchByJobID(currJob.getJobID())].getCpuCycle();

                currJob.setFinishTime(currTime);
                currJob.setTurnAroundTime(currJob.getFinishTime() - currJob.getArrivalTime());
                currJob.setWaitTime(currJob.getTurnAroundTime() - currJobCpu);



                //currTime += 1;
                waitingQueue.pop_front();
                finishedQueue.push_back(currJob);

                isFinished = true;
                startingTime = currTime;
            }
            //else, the job is not done at all.
            else{
                currTime += 1;
                //adding the job back to the waiting queue.
                //waitingQueue.push_back(currJob);
            }

        }
        else{
            currTime += 1;
        }
    }

    sortByJobId(finishedQueue);
    //copying the finished queue to the job list.
    for(int i = 0; i < finishedQueue.size(); i++){
        jobList[i] = finishedQueue[i];
    }
    setContextSwitchTime(contextSwitchCounter * 0.1 );

}

//done, need context swithcing implemented
void JobScheduler::shortestRemainingTime() {
    //sorting the job list based on the cpu cycle, in descending order.
    sortJobList("SRT");

    //creating a ready queue
    deque<Process> readyQueue;
    //creating a waitingQueue;
    deque<Process> waitingQueue;
    //creating a finished queue.
    deque<Process> finishedQueue;

    Process currJob = jobList[0];
    int switchTime = 0;
    int processFlag = currJob.getJobID();
    int currTime = jobList[0].getArrivalTime();
    Process waitingQueueTracker=currJob;
    //adding jobs to ready queue
    for(int i = 0; i < numberOfProcesses; i++){
        readyQueue.push_back(jobList[i]);
    }

    //sorting readyQueue based on arrival time.
    for(int i = 0; i < readyQueue.size(); i++){
        for(int j = i+1; j < readyQueue.size(); j++){
            if(readyQueue[i].getArrivalTime() > readyQueue[j].getArrivalTime()){
                Process temp = readyQueue[i];
                readyQueue[i] = readyQueue[j];
                readyQueue[j] = temp;
            }
        }
    }

    //iterate the currTime incrementally until all jobs are done.
    //every time the while loop will run, we will check the processes in the waiting queue,
    //if there is a process that is waiting and its cpu cycle is less than the current running process,
    //we will switch the processes. (SRT)

    while(finishedQueue.size() != jobList.size()){
        //checking if any job(s) has arrived at the current time.

        while (readyQueue.front().getArrivalTime() == currTime){
            waitingQueue.push_back(readyQueue.front());
            readyQueue.pop_front();

        }

        //finding the current smallest cpu cycle job in the waiting queue.
        int smallestCpuCycle = waitingQueue[0].getCpuCycle();
        currJob = waitingQueue[0];
        waitingQueueTracker = waitingQueue[0];
        processFlag = currJob.getJobID();
        for(int i = 1; i < waitingQueue.size(); i++){
            if(waitingQueue[i].getCpuCycle() < smallestCpuCycle){
                smallestCpuCycle = waitingQueue[i].getCpuCycle();
                currJob = waitingQueue[i];
                waitingQueueTracker = waitingQueue[i];
                processFlag = currJob.getJobID();
            }
        }

        //checking if cpu cycle is less than quantum time.
        if(waitingQueue.size() != 0){
            //currJob = waitingQueue
            int timeLeft = currJob.getCpuCycle() - 1;
            currJob.setCpuCycle(timeLeft);
            waitingQueueTracker.setCpuCycle(timeLeft);
            //setting finish time since the job is done.

            //find the currJob in waiting queue and updating it to the current currJob info.
            for(int i = 0; i < waitingQueue.size(); i++){
                if(waitingQueue[i].getJobID() == processFlag){
                    waitingQueue[i] = currJob;
                }
            }


            //waitingQueue[processFlag - 1] = currJob;
            if(timeLeft == 0){
                currTime += 1;
                currJob.setFinishTime(currTime);
                currJob.setTurnAroundTime(currJob.getFinishTime() - currJob.getArrivalTime());
                currJob.setWaitTime(currJob.getTurnAroundTime() - jobList[processFlag - 1].getCpuCycle());

                //find the job in the queue to be removed in the waiting queue.
                for(int i = 0; i < waitingQueue.size(); i++){
                    if(waitingQueue[i].getJobID() == processFlag){
                        waitingQueue.erase(waitingQueue.begin() + i);
                    }
                }

                finishedQueue.push_back(currJob);
            }
            //else, the job is not done at all.
            else{
                currTime += 1;
            }
        }
        else{
            currTime += 1;
        }
    }
    sortByJobId(finishedQueue);
    //copying the finished queue to the job list.
    for(int i = 0; i < finishedQueue.size(); i++){
        jobList[i] = finishedQueue[i];
    }
}


void JobScheduler::printJobList() {
string output = "----------------------------\n";
    for(int i = 0; i < jobList.size(); i++){
        output+="| ";
        output+=to_string(jobList[i].getJobID());
        output+=" \t| \t";
        output+=to_string(jobList[i].getArrivalTime());
        output+=" \t\t|\t ";
        output+=to_string(jobList[i].getCpuCycle());
        output+=" \t\t|\t ";
        output+=to_string(jobList[i].getFinishTime());
        output+=" \t\t|\t ";
        output+=to_string(jobList[i].getTurnAroundTime());
        output+=" \t\t|\t ";
        output+=to_string(jobList[i].getWaitTime());
        output+=" \t\t|\t ";
        output+="\n-----------------\n";

    }
    cout << output;
}