//
// Created by Jesse Crispin on 3/21/24.
//

#ifndef PROCESS_JOB_SCHEDULER_PROCESS_H
#define PROCESS_JOB_SCHEDULER_PROCESS_H


class Process {
    private:
        //private variables
        int jobID;
        int arrivalTime;
        int cpuCycle;

        int finishTime=0;
        int turnAroundTime=0;
        int waitTime=0;

    public:
    Process(int jobID, int arrivalTime, int cpuCycle);
    Process();
    int getJobID();
    int getArrivalTime();
    int getCpuCycle();
    int getFinishTime();
    int getTurnAroundTime();
    int getWaitTime();
    void setFinishTime(int finishTime);
    void setTurnAroundTime(int turnAroundTime);
    void setWaitTime(int waitTime);
    void setCpuCycle(int cpuCycle);
    void printProcess();

    //overloading the = operator to copy the process object.
    Process& operator=(const Process &process);
};

#endif //PROCESS_JOB_SCHEDULER_PROCESS_H
