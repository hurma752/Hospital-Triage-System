#include "patient_queue.h"
#include <iostream>
using namespace std;

int severityToPriority(const string& severity) {
    if (severity == "critical") return 1;
    if (severity == "serious") return 2;
    if (severity == "normal") return 3;
    return 4; 
}

void minHeapify(Patient heap[], int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && severityToPriority(heap[l].severity) < severityToPriority(heap[smallest].severity))
        smallest = l;

    if (r < n && severityToPriority(heap[r].severity) < severityToPriority(heap[smallest].severity))
        smallest = r;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

void buildMinHeap(Patient heap[], int n) {
    for (int i = (n - 1) / 2; i >= 0; i--)
        minHeapify(heap, n, i);
}

void insertPatient(Patient heap[], int& size, const string& name, const string& severity) {
    if (size == MAX_SIZE) {
        cout << "Error: Patient queue is full. Cannot add more patients." << endl;
        return;
    }
    if (severity != "critical" && severity != "serious" && severity != "normal") {
        cout << "Error: Invalid severity level. Only 'critical', 'serious', or 'normal' are accepted." << endl;
        return;
    }
    heap[size++] = Patient(name, severity);
    buildMinHeap(heap, size);
    cout << "Patient '" << name << "' with severity '" << severity << "' added successfully." << endl;
}

Patient getNextPatient(Patient heap[], int& size) {
    if (size == 0) {
        cout << "Error: No patients in the queue." << endl;
        return Patient("", "");
    }
    Patient nextPatient = heap[0];
    heap[0] = heap[size - 1];
    size--;
    minHeapify(heap, size, 0);
    cout << "Next patient: " << nextPatient.name << ", Severity: " << nextPatient.severity << endl;
    return nextPatient;
}

void listPatients(Patient heap[], int size) {
    cout << "Listing all patients in the queue by priority:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Patient: " << heap[i].name << ", Severity: " << heap[i].severity << endl;
    }
}

