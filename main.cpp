//Jesse Crispin
#include <iostream>
#include <fstream>
#include "JobScheduler.h"
#include "Process.h"
#include <vector>
using namespace std;

void PrintJobs(vector<Process> jobList){
    string output="------------------------------------\n";
    output += "| Job ID | Arrival Time | CPU Cycle |\n";
    output += "-----------------------------------------\n";
    for(int i = 0; i < jobList.size(); i++){
        output+="| ";
        output+=to_string(jobList[i].getJobID());
        output+=" \t| \t";
        output+=to_string(jobList[i].getArrivalTime());
        output+=" \t\t|\t ";
        output+=to_string(jobList[i].getCpuCycle());
        output+=" \t\t|\t ";
        output+="\n-----------------------------------------\n";

    }
    cout << output;
}

void ParseSource( JobScheduler &JobSchedulerList, vector<string> source ){
    //parsing the source vector and creating the process objects.
    int jobId, arrivalTime, cpuCycle;
    for(int index = 0; index < source.size(); index++ ){
        string currLine = source[index];

        //parsing the current line.
        string token;
        vector<string> tokens;
        for (int i = 0; i < currLine.length(); i++) {
            if(currLine[i] == ' '){
                tokens.push_back(token);
                token="";
            }
            else{
                token += currLine[i];
            }
        }
        tokens.push_back(token);

        //creating the process object.
        jobId = stoi(tokens[0]);
        arrivalTime = stoi(tokens[1]);
        cpuCycle = stoi(tokens[2]);

        Process process(jobId, arrivalTime, cpuCycle);
        JobSchedulerList.addProcess(process);

    }
}

void printUi(){
    cout<<"=========================" << endl;
    cout << "Process Job Scheduler UI" << endl;
    cout << "=========================" << endl;
    cout << "1. First Come First Serve" << endl;
    cout << "2. Shortest Job Next" << endl;
    cout << "3. Shortest Remaining Time" << endl;
    cout << "4. Round Robin(Quantum Time=4)" << endl;
    cout << "5. Print Job List" << endl;
    cout << "6. Exit" << endl;
    cout << "=========================" << endl;
}

int main() {

    JobScheduler JobSchedulerList;

    //cout << "\nEnter the input file name|>:";
    //cin >> inputLocation;
    string inputLocation = "../input.txt";

    fstream inputFile(inputLocation);
    string sourceLine;
    vector<string> source;
    if(!inputFile){
        cout<<"\nError: Unable to open file.";
    }

    while(getline(inputFile, sourceLine)){

        source.push_back(sourceLine);

    }
    //****Assuming that the input file is in the correct format as specified in the assignment.


    //assuming that the first line is the number of processes.
    int numberOfProcesses = stoi(source[0]);

    JobSchedulerList.setJobSize(numberOfProcesses);
    //removing the first line from the source vector.
    source.erase(source.begin());
    //parsing the rest of the data from source vector.
    ParseSource( JobSchedulerList, source);

    //printing the job list.
    PrintJobs(JobSchedulerList.jobList);

    int choice;
    bool isFinished = false;
    char cont;

    while(!isFinished){

        //printing the job scheduler UI.
        printUi();

        //error handling the user input.
        do{
            cout << "\t>: Enter your choice: ";
            cin >> choice;

            if((choice < 1 || choice > 6) || cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "<Invalid choice. Please enter a valid choice>:\n";
            }
            else{
                break;
            }
        }while(choice < 1 || choice > 6 || cin.fail());


        if(choice == 1){
            JobSchedulerList.firstComeFirstServe();
            JobSchedulerList.printJobList();
            JobSchedulerList.getAverageWaitTime();
            JobSchedulerList.getAverageTurnAroundTime();
        }
        if(choice == 2){
            JobSchedulerList.shortestJobNext();
            JobSchedulerList.printJobList();
            JobSchedulerList.getAverageWaitTime();
            JobSchedulerList.getAverageTurnAroundTime();
        }
        if(choice == 3){
            cout<<"Account for context switching? (y/n): ";
            cin >> cont;
            JobSchedulerList.shortestRemainingTime();
            JobSchedulerList.printJobList();
            JobSchedulerList.getAverageWaitTime();
            JobSchedulerList.getAverageTurnAroundTime();
        }
        if(choice == 4){
            cout<<"Account for context switching? (y/n): ";
            cin >> cont;

            int quantumTime;
            cout << "\tEnter the quantum time: ";
            cin >> quantumTime;
            JobSchedulerList.setQuantumTime(quantumTime);
            JobSchedulerList.roundRobin();
            JobSchedulerList.printJobList();
            JobSchedulerList.getAverageWaitTime();
            JobSchedulerList.getAverageTurnAroundTime();
            JobSchedulerList.getContextSwitchTime();
        }
        if(choice == 5){
            PrintJobs(JobSchedulerList.jobList);
        }
        if(choice == 6){
            isFinished = true;
        }
        cout<< "Do you want to continue? (y/n):";
        cin >> cont;
        if(cont == 'n'){
            isFinished = true;
        }
        cout<<endl;

    }
    cout<< "Exiting the program." << endl;


    return 0;
}
