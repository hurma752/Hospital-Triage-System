
#ifndef PATIENT_QUEUE_H
#define PATIENT_QUEUE_H

#include <iostream>
#include <string>

const int MAX_SIZE = 100;

struct Patient {
    std::string name;
    std::string severity;

    Patient(std::string n = "", std::string s = "") : name(n), severity(s) {}
};

void minHeapify(Patient heap[], int n, int i);
void buildMinHeap(Patient heap[], int n);
void insertPatient(Patient heap[], int& size, const std::string& name, const std::string& severity);
Patient getNextPatient(Patient heap[], int& size);
void listPatients(Patient heap[], int size);

#endif // PATIENT_QUEUE_H