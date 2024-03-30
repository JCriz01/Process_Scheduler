//
// Created by Jesse Crispin on 3/24/24.
//

#ifndef PROCESS_JOB_SCHEDULER_JOBSCHEDULER_H
#define PROCESS_JOB_SCHEDULER_JOBSCHEDULER_H
#include "Process.h"
#include <deque>
#include <vector>

using namespace std;

class JobScheduler {
    int numberOfProcesses;
    vector<Process> queue;
    int quantumTime;
    double averageWaitTime;
    double averageTurnAroundTime;
    double contextSwitchTime;
public:
    vector<Process> jobList;

    JobScheduler();
    void setJobSize(int size);
    void addProcess(Process process);
    void printJobList();
    void firstComeFirstServe();
    void getAverageWaitTime();
    void getAverageTurnAroundTime();
    void shortestJobNext();
    void shortestRemainingTime();
    void roundRobin();
    void setQuantumTime(int quantumTime);

    void sortJobList(string jobType);
    int searchByJobID(int jobID);
    void sortByJobId(deque<Process> &list);
    JobScheduler& operator=( deque<Process> &jobScheduler);
    void setContextSwitchTime(double contextSwitchTime);
    void getContextSwitchTime();
};


#endif //PROCESS_JOB_SCHEDULER_JOBSCHEDULER_H
