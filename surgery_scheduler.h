#ifndef SURGERY_SCHEDULER_H
#define SURGERY_SCHEDULER_H

#include <iostream>
#include <string>
#include <fstream>

struct doctor {
    int id;
    int surgeriesperformed;
    std::string name;
    bool isAvailable;
};

struct staff {
    int id;
    int surgeriesperformed;
    std::string name;
    bool isAvailable;
};

struct operationroom {
    int room;
    bool isAvailable;
};

struct surgery {
    doctor doc;
    staff s[3];
    operationroom ot;
    std::string starttime;
    int patientid;
    int duration;
    std::string endtime;
    int surgerynumber;
};

const int MAX_UPCOMING_SURGERIES = 10;
extern surgery minHeap[MAX_UPCOMING_SURGERIES];
extern int minHeapSize;

void schedulesurgery(int c, int& scheduledsurgery, int& upcomingsurgery);
void endsurgery(int& scheduledsurgery, int& upcomingsurgery);
void cancelsurgery(int t, int& scheduledsurgery, int& upcomingsurgery);
void displayupcomingsurgery();
void displaycurrentsurgery();
void displayall();

#endif /* SURGERY_SCHEDULER_H */
