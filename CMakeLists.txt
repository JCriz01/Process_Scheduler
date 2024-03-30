cmake_minimum_required(VERSION 3.26.4)
project(Process_Job_Scheduler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Process_Job_Scheduler main.cpp
        Process.cpp
        Process.h
        JobScheduler.cpp
        JobScheduler.h)
