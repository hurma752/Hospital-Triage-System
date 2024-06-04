#include "surgery_scheduler.h"

using namespace std;

surgery minHeap[MAX_UPCOMING_SURGERIES];
int minHeapSize = 0;


void heapifyUp(int index) {
    while (index > 0 && minHeap[(index - 1) / 2].duration > minHeap[index].duration) {
        swap(minHeap[index], minHeap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeapSize && minHeap[left].duration < minHeap[smallest].duration) {
        smallest = left;
    }
    if (right < minHeapSize && minHeap[right].duration < minHeap[smallest].duration) {
        smallest = right;
    }
    if (smallest != index) {
        swap(minHeap[index], minHeap[smallest]);
        heapifyDown(smallest);
    }
}

void insertMinHeap(surgery s) {
    if (minHeapSize < MAX_UPCOMING_SURGERIES) {
        minHeap[minHeapSize] = s;
        heapifyUp(minHeapSize);
        minHeapSize++;
    }
    else {
        cout << "Min-Heap is full\n";
    }
}

surgery extractMin() {
    if (minHeapSize == 0) {
        cout << "Min-Heap is empty\n";
        return surgery{};
    }
    surgery root = minHeap[0];
    minHeap[0] = minHeap[--minHeapSize];
    heapifyDown(0);
    return root;
}


doctor doctors[] = {
    {11, 0, "Josh", true},
    {12, 0, "Mina", true},
    {13, 0, "Nina", true},
    {14, 0, "Bina", true},
    {15, 0, "Bob", true}
};

staff staffs[] = {
    {21, 0, "Mia", true},
    {22, 0, "Ana", true},
    {23, 0, "Joe", true},
    {24, 0, "Noah", true},
    {25, 0, "Mish", true},
    {26, 0, "Priya", true},
    {27, 0, "pony", true},
    {28, 0, "momo", true},
    {29, 0, "kofe", true}
};

operationroom ots[] = {
    {1, true},
    {2, true},
    {3, true}
};

surgery s[3];
surgery u[10];

void displayoperationroom() {
    for (int i = 0; i < 3; i++) {
        cout << "\nRoom number: " << ots[i].room;
        if (ots[i].isAvailable == false) {
            cout << " room not available right now" << endl;
        }

    }
    cout << endl;
}

void availablestaff() {
    cout << "staff: ";
    for (int i = 0; i < 9; i++) {
        cout << "\nID: " << staffs[i].id << " Name: " << staffs[i].name << ", Surgeries performed: " << staffs[i].surgeriesperformed;
        if (staffs[i].isAvailable == false) {
            cout << " not available right now" << endl;
        }
    }
    cout << endl;
}

void availabledoctors() {
    cout << "doctors: ";
    for (int i = 0; i < 5; i++) {
        cout << "\nID: " << doctors[i].id << " Name: " << doctors[i].name << ", Surgeries performed: " << doctors[i].surgeriesperformed;
        if (doctors[i].isAvailable == false) {
            cout << " not available right now" << endl;
        }
    }
    cout << endl;
}
void schedulesurgery(int c, int& scheduledsurgery, int& upcomingsurgery) {
    string st;
    int room, s1id, s2id, s3id, did, pid, duration;

    cout << "\nEnter patient ID: ";
    cin >> pid;
    cout << "Enter start time: ";
    cin >> st;
    cout << "Enter duration of the surgery (in hours): ";
    cin >> duration;

    displayoperationroom();
    cout << "Select operation room: ";
    cin >> room;

    availabledoctors();
    cout << "Select doctor by ID: ";
    cin >> did;

    availablestaff();
    cout << "Select staff member 1 by ID: ";
    cin >> s1id;
    cout << "Select staff member 2 by ID: ";
    cin >> s2id;
    cout << "Select staff member 3 by ID: ";
    cin >> s3id;

    doctor* selectedDoctor = nullptr;
    for (int i = 0; i < 5; ++i) {
        if (doctors[i].id == did) {
            selectedDoctor = &doctors[i];
            break;
        }
    }

    staff* selectedStaff[3] = { nullptr, nullptr, nullptr };
    for (int i = 0; i < 9; ++i) {
        if (staffs[i].id == s1id) selectedStaff[0] = &staffs[i];
        if (staffs[i].id == s2id) selectedStaff[1] = &staffs[i];
        if (staffs[i].id == s3id) selectedStaff[2] = &staffs[i];
    }

    operationroom* selectedRoom = nullptr;
    for (int i = 0; i < 3; ++i) {
        if (ots[i].room == room) {
            selectedRoom = &ots[i];
            break;
        }
    }

    if (selectedDoctor == nullptr || selectedStaff[0] == nullptr || selectedStaff[1] == nullptr || selectedStaff[2] == nullptr || selectedRoom == nullptr) {
        cout << "Invalid selection. Please try again.\n";
        return;
    }

    if (c == 2) {
        selectedRoom->isAvailable = false;
        selectedDoctor->isAvailable = false;
        for (int i = 0; i < 3; ++i) {
            selectedStaff[i]->isAvailable = false;
        }

        s[scheduledsurgery].doc = *selectedDoctor;
        s[scheduledsurgery].s[0] = *selectedStaff[0];
        s[scheduledsurgery].s[1] = *selectedStaff[1];
        s[scheduledsurgery].s[2] = *selectedStaff[2];
        s[scheduledsurgery].ot = *selectedRoom;
        s[scheduledsurgery].starttime = st;
        s[scheduledsurgery].patientid = pid;
        s[scheduledsurgery].duration = duration;
        s[scheduledsurgery].surgerynumber = scheduledsurgery + 1;

        scheduledsurgery++;
    }
    else if (c == 1) {
        selectedRoom->isAvailable = false;
        selectedDoctor->isAvailable = false;
        for (int i = 0; i < 3; ++i) {
            selectedStaff[i]->isAvailable = false;
        }
        surgery newSurgery;
        newSurgery.doc = *selectedDoctor;
        newSurgery.s[0] = *selectedStaff[0];
        newSurgery.s[1] = *selectedStaff[1];
        newSurgery.s[2] = *selectedStaff[2];
        newSurgery.ot = *selectedRoom;
        newSurgery.starttime = st;
        newSurgery.patientid = pid;
        newSurgery.duration = duration;
        newSurgery.surgerynumber = scheduledsurgery + 1;
        insertMinHeap(newSurgery);
        upcomingsurgery++;
    }

    cout << "Surgery scheduled successfully!\n";
}



void endsurgery(int& scheduledsurgery, int& upcomingsurgery) {
    int y;
    string et;
    cout << "Enter surgery number that's ended: ";
    cin >> y;

    for (int i = 0; i < 3; i++) {
        if (s[i].surgerynumber == y) {

            for (int j = 0; j < 5; j++) {
                if (doctors[j].id == s[i].doc.id) {
                    doctors[j].isAvailable = true;
                    doctors[j].surgeriesperformed++;
                    break;
                }
            }
            for (int k = 0; k < 3; k++) {
                for (int j = 0; j < 9; j++) {
                    if (staffs[j].id == s[i].s[k].id) {
                        staffs[j].isAvailable = true;
                        staffs[j].surgeriesperformed++;
                        break;
                    }
                }
            }

            for (int j = 0; j < 3; j++) {
                if (ots[j].room == s[i].ot.room) {
                    ots[j].isAvailable = true;
                    break;
                }
            }
            cout << "\nEnter end time: ";
            cin >> et;
            s[i].endtime = et;


            ofstream outfile("C:\\Users\\MUHAMMAD ZAFAR\\Desktop\\surgery_details.txt", ios::app);


            if (outfile.is_open()) {
                outfile << "Surgery Number: " << s[i].surgerynumber << "\n";
                outfile << "Doctor: " << s[i].doc.name << " (ID: " << s[i].doc.id << ")\n";
                outfile << "Staff:\n";
                for (int j = 0; j < 3; j++) {
                    outfile << "\t" << s[i].s[j].name << " (ID: " << s[i].s[j].id << ")\n";
                }
                outfile << "Operation Room: " << s[i].ot.room << "\n";
                outfile << "Start Time: " << s[i].starttime << "\n";
                outfile << "End Time: " << s[i].endtime << "\n";
                outfile << "Duration: " << s[i].duration << " hours\n";
                outfile << "Patient ID: " << s[i].patientid << "\n";
                outfile << "--------------------------------------------\n";
                outfile.close();
            }
            else {
                cout << "Unable to open file";
            }
            cout << "Surgery details saved to file." << endl;
            if (upcomingsurgery > 0) {
                s[i] = extractMin();
                for (int j = 0; j < 5; j++) {
                    if (doctors[j].id == s[i].doc.id) {
                        doctors[j].isAvailable = false;
                        break;
                    }
                }
                for (int k = 0; k < 3; k++) {
                    for (int j = 0; j < 9; j++) {
                        if (staffs[j].id == s[i].s[k].id) {
                            staffs[j].isAvailable = false;
                            break;
                        }
                    }
                }
                for (int j = 0; j < 3; j++) {
                    if (ots[j].room == s[i].ot.room) {
                        ots[j].isAvailable = false;
                        break;
                    }
                }
                upcomingsurgery--;
            }
            break;
        }
    }
}

void displayupcomingsurgery() {
    cout << "Upcoming Surgeries:\n";

    if (minHeapSize == 0) {
        cout << "No upcoming surgeries\n";
    }
    else {
        for (int i = 0; i < minHeapSize; i++) {
            cout << "Surgery Number: " << minHeap[i].surgerynumber << "\n";
            cout << "Patient ID: " << minHeap[i].patientid << "\n";
            cout << "Doctor: " << minHeap[i].doc.name << "\n";
            cout << "Staff: ";
            for (int j = 0; j < 3; j++) {
                cout << minHeap[i].s[j].name << " ";
            }
            cout << "\nOperation Room: " << minHeap[i].ot.room << "\n";
            cout << "Duration: " << minHeap[i].duration << "\n";
            cout << "Start Time: " << minHeap[i].starttime << "\n\n";
        }
    }
}


void displaycurrentsurgery() {
    cout << "Current Surgeries:\n";
    for (int i = 0; i < 3; i++) {
        if (s[i].surgerynumber != 0) {
            cout << "Surgery Number: " << s[i].surgerynumber << "\n";
            cout << "Patient ID: " << s[i].patientid << "\n";
            cout << "Doctor: " << s[i].doc.name << "\n";
            cout << "Staff: ";
            for (int j = 0; j < 3; j++) {
                cout << s[i].s[j].name << " ";
            }
            cout << "\nOperation Room: " << s[i].ot.room << "\n";
            cout << "\nDuration: " << s[i].duration << "\n";
            cout << "Start Time: " << s[i].starttime << "\n\n";
        }
    }
}
void displayall() {
    cout << "Previously Performed Surgeries:\n";
    ifstream infile("surgery_details.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    }
    else {
        cout << "No previously performed surgeries recorded or unable to open file.\n";
    }
    cout << "\nCurrent Surgeries\n";
    displaycurrentsurgery();
    cout << "\nUpcoming Surgeries\n";
    displayupcomingsurgery();
}
void cancelsurgery(int t, int& scheduledsurgery, int& upcomingsurgery) {
    int surg, i, w;
    cout << "Enter surgery number you want to cancel: ";
    cin >> surg;

    if (t == 1) {
        for (i = 0; i < 3; i++) {
            if (s[i].surgerynumber == surg) {
                for (w = 0; w < 5; w++) {
                    if (doctors[w].id == s[i].doc.id) {
                        doctors[w].isAvailable = true;
                        break;
                    }
                }
                for (w = 0; w < 9; w++) {
                    for (int j = 0; j < 3; j++) {
                        if (staffs[w].id == s[i].s[j].id) {
                            staffs[w].isAvailable = true;
                        }
                    }
                }
                for (w = 0; w < 3; w++) {
                    if (ots[w].room == s[i].ot.room) {
                        ots[w].isAvailable = true;
                    }
                }
                s[i].starttime = "";
                s[i].duration = 0;
                s[i].endtime = "";
                s[i].patientid = 0;
                s[i].surgerynumber = 0;
                s[i].doc = {};
                for (int j = 0; j < 3; j++) {
                    s[i].s[j] = {};
                }
                s[i].ot = {};

                if (upcomingsurgery > 0) {
                    s[scheduledsurgery] = minHeap[0];
                    for (w = 0; w < 5; w++) {
                        if (doctors[w].id == minHeap[0].doc.id) {
                            doctors[w].isAvailable = false;
                            break;
                        }
                    }
                    for (int j = 0; j < 3; j++) {
                        for (w = 0; w < 9; w++) {
                            if (staffs[w].id == minHeap[0].s[j].id) {
                                staffs[w].isAvailable = false;
                                break;
                            }
                        }
                    }
                    for (w = 0; w < 3; w++) {
                        if (ots[w].room == minHeap[0].ot.room) {
                            ots[w].isAvailable = false;
                            break;
                        }
                    }
                    scheduledsurgery++;
                    swap(minHeap[0], minHeap[minHeapSize - 1]);
                    minHeapSize--;
                    heapifyDown(0);
                }
                break;
            }
        }
    }

    else if (t == 2) {
        for (i = 0; i < minHeapSize; i++) {
            if (minHeap[i].surgerynumber == surg) {
                minHeap[i] = minHeap[minHeapSize - 1];
                minHeapSize--;
                heapifyDown(i);
                break;
            }
        }

    }
}




