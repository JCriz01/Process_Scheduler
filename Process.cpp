//
// Created by Jesse Crispin on 3/21/24.
//

#include "Process.h"

Process::Process(int jobID, int arrivalTime, int cpuCycle){
    this->jobID = jobID;
    this->arrivalTime = arrivalTime;
    this->cpuCycle = cpuCycle;
}

Process::Process(){
    jobID = 0;
    arrivalTime = 0;
    cpuCycle = 0;
}

int Process::getJobID(){
    return jobID;
}

int Process::getArrivalTime(){
    return arrivalTime;
}

int Process::getCpuCycle(){
    return cpuCycle;
}

int Process::getFinishTime(){
    return finishTime;
}

int Process::getTurnAroundTime(){
    return turnAroundTime;
}

int Process::getWaitTime(){
    return waitTime;
}

void Process::setFinishTime(int finishTime){
    this->finishTime = finishTime;
}

void Process::setTurnAroundTime(int turnAroundTime){
    this->turnAroundTime = turnAroundTime;
}

void Process::setWaitTime(int waitTime){
    this->waitTime = waitTime;
}

void Process::setCpuCycle(int cpuCycle){
    this->cpuCycle = cpuCycle;
}

void Process::printProcess(){

}

Process& Process::operator=(const Process &process){
    this->jobID = process.jobID;
    this->arrivalTime = process.arrivalTime;
    if(process.cpuCycle != 0)
        this->cpuCycle = process.cpuCycle;
    this->finishTime = process.finishTime;
    this->turnAroundTime = process.turnAroundTime;
    this->waitTime = process.waitTime;
    return *this;
}
