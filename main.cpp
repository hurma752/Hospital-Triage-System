#include <iostream>
#include "appointment_system.h"
#include "patient_queue.h"
#include "surgery_scheduler.h"

using namespace std;

Patient patientQueue[MAX_SIZE];
int queuesize = 0;
int scheduledSurgery = 0;
int upcomingSurgery = 0;

void managePatients() {
    char choice;
    do {
        string name;
        string severity;
        cout << "Enter patient name: ";
        cin >> name;
        cout << "Enter severity level (critical, serious, normal): ";
        cin >> severity;
        insertPatient(patientQueue, queuesize, name, severity);

        cout << "Do you want to add another patient? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "--------------------------------------------" << endl;
    listPatients(patientQueue, queuesize);

    cout << "--------------------------------------------" << endl;
    Patient nextPatient = getNextPatient(patientQueue, queuesize);
    if (nextPatient.name != "")
        cout << "Next patient to be treated: " << nextPatient.name << ", Severity: " << nextPatient.severity << endl;

    cout << "--------------------------------------------" << endl;
    listPatients(patientQueue, queuesize);
}

void manageSurgery() {
    char choice;
    bool exitSurgeryMenu = false;
    do {
        cout << "\n1. Schedule Surgery\n";
        cout << "2. End Surgery\n";
        cout << "3. Cancel Surgery\n";
        cout << "4. Display Current Surgeries\n";
        cout << "5. Schedule Upcoming Surgery\n";
        cout << "6. Clear Screen\n";
        cout << "7. See Upcoming Surgeries\n";
        cout << "8. See Surgery History\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            if (scheduledSurgery == 3) {
                cout << "Three surgeries are already underway. Schedule for the future.\n";
            }
            else {
                schedulesurgery(2, scheduledSurgery, upcomingSurgery);
            }
            break;
        case '2':
            if (scheduledSurgery == 0) {
                cout << "No surgeries are in progress right now.\n";
            }
            else {
                endsurgery(scheduledSurgery, upcomingSurgery);
                scheduledSurgery--;
            }
            break;
        case '3':
            if (scheduledSurgery == 0 && upcomingSurgery == 0) {
                cout << "No surgeries are under process or scheduled.\n";
            }
            else {
                int t;
                cout << "Enter 1 to cancel the current surgery \nEnter 2 to cancel upcoming scheduled surgeries\n";
                cin >> t;
                cancelsurgery(t, upcomingSurgery, scheduledSurgery);
                if (t == 1) {
                    scheduledSurgery--;
                }
                else {
                    upcomingSurgery--;
                }
            }
            break;
        case '4':
            if (scheduledSurgery == 0) {
                cout << "No surgeries have been scheduled.\n";
            }
            else {
                displaycurrentsurgery();
            }
            break;
        case '5':
            if (scheduledSurgery == 3) {
                schedulesurgery(1, scheduledSurgery, upcomingSurgery);
            }
            else {
                cout << "There's a slot free for surgery currently; hence, can't schedule for the future.\n";
            }
            break;
        case '6':
            system("cls");
            break;

            break;
        case '7':
            displayupcomingsurgery();
            break;
        case '8':
            displayall();
            break;
        case '0':
            exitSurgeryMenu = true;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (!exitSurgeryMenu);
}

int main() {
    initializeDoctors();

    char choice;
    do {
        cout << "\n1. Book Appointment\n";
        cout << "2. Complete Appointment\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. Display Appointments\n";
        cout << "5. Manage Patient Queue\n";
        cout << "6. Manage Surgery\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            bookAppointment();
            break;
        case '2':
            completeAppointment();
            break;
        case '3':
            cancelAppointment();
            break;
        case '4':
            displayAppointments();
            break;
        case '5':
            managePatients();
            break;
        case '6':
            manageSurgery();
            break;
        case '7':
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != '7');

    return 0;
}

