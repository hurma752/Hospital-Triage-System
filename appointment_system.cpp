#include "appointment_system.h"

using namespace std;

Doctor doctors[MAX_DOCTORS];
int numDoctors = 0;

void initializeDoctors() {
    doctors[numDoctors++] = { "Dr. Aisha", nullptr, 0 };
    doctors[numDoctors++] = { "Dr. Omar", nullptr, 0 };
    doctors[numDoctors++] = { "Dr. Ahmed", nullptr, 0 };
    doctors[numDoctors++] = { "Dr. Yasmin", nullptr, 0 };
}

bool isDoctorAvailable(Doctor& doctor, const string& date) {
    int count = 0;
    Appointment* current = doctor.appointments;
    while (current != nullptr) {
        if (current->date == date) {
            count++;
        }
        current = current->next;
    }
    return count < MAX_DAILY_SLOTS;
}

bool isValidDate(const string& date) {
    if (date.length() != 10) {
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') {
                return false;
            }
        }
        else {
            if (!isdigit(date[i])) {
                return false;
            }
        }
    }
    return true;
}

bool isValidTime(const string& time) {
    stringstream ss(time);
    int hours, minutes;
    char colon;
    if (!(ss >> hours >> colon >> minutes)) {
        return false;
    }
    return (colon == ':' && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59);
}

void bookAppointment() {
    cout << "\nAvailable Doctors:\n";
    for (int i = 0; i < numDoctors; ++i) {
        cout << i + 1 << ". " << doctors[i].name << endl;
    }
    cout << "Select a doctor (1-" << numDoctors << "): ";
    int docIndex;
    cin >> docIndex;

    if (docIndex >= 1 && docIndex <= numDoctors) {
        Doctor& selectedDoctor = doctors[docIndex - 1];

        if (selectedDoctor.numAppointments >= MAX_APPOINTMENTS_PER_DOCTOR) {
            cout << "\nMaximum appointments per doctor reached for " << selectedDoctor.name << "!\n";
            return;
        }

        string date;
        bool validDate = false;
        do {
            cout << "\nEnter date (YYYY-MM-DD): ";
            cin >> date;
            validDate = isValidDate(date);
            if (!validDate) {
                cout << "Invalid date format! Please enter date in YYYY-MM-DD format.\n";
            }
        } while (!validDate);

        if (!isDoctorAvailable(selectedDoctor, date)) {
            cout << "\nMaximum appointments reached for " << selectedDoctor.name << " on " << date << "!\n";
            return;
        }

        string time;
        bool validTime = false;
        do {
            cout << "Enter time (HH:MM): ";
            cin >> time;
            validTime = isValidTime(time);
            if (!validTime) {
                cout << "Invalid time format! Please enter time in HH:MM format.\n";
            }
        } while (!validTime);

        cout << "Enter patient name: ";
        string patientName;
        cin.ignore();
        getline(cin, patientName);

        cout << "Enter contact details: ";
        string contactDetails;
        getline(cin, contactDetails);

        cout << "Enter description: ";
        string description;
        getline(cin, description);

        Appointment* newAppointment = new Appointment;
        newAppointment->date = date;
        newAppointment->time = time;
        newAppointment->description = description;
        newAppointment->completed = false;
        newAppointment->patientName = patientName;
        newAppointment->contactDetails = contactDetails;
        newAppointment->next = nullptr;

        if (selectedDoctor.appointments == nullptr) {
            selectedDoctor.appointments = newAppointment;
        }
        else {
            Appointment* current = selectedDoctor.appointments;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newAppointment;
        }

        selectedDoctor.numAppointments++;
        cout << "\nAppointment booked successfully!\n";
    }
    else {
        cout << "\nInvalid doctor selection.\n";
    }
}

void completeAppointment() {
    cout << "\nAvailable Doctors:\n";
    for (int i = 0; i < numDoctors; ++i) {
        cout << i + 1 << ". " << doctors[i].name << endl;
    }
    cout << "Select a doctor (1-" << numDoctors << "): ";
    int docIndex;
    cin >> docIndex;

    if (docIndex >= 1 && docIndex <= numDoctors) {
        Doctor& selectedDoctor = doctors[docIndex - 1];
        cout << "Enter index of appointment to mark as completed (1-" << selectedDoctor.numAppointments << "): ";
        int index;
        cin >> index;

        if (index >= 1 && index <= selectedDoctor.numAppointments) {
            Appointment* current = selectedDoctor.appointments;
            for (int i = 1; i < index; ++i) {
                current = current->next;
            }
            current->completed = true;
            cout << "\nAppointment marked as completed.\n";
        }
        else {
            cout << "\nInvalid appointment index.\n";
        }
    }
    else {
        cout << "\nInvalid doctor selection.\n";
    }
}

void cancelAppointment() {
    cout << "\nAvailable Doctors:\n";
    for (int i = 0; i < numDoctors; ++i) {
        cout << i + 1 << ". " << doctors[i].name << endl;
    }
    cout << "Select a doctor (1-" << numDoctors << "): ";
    int docIndex;
    cin >> docIndex;

    if (docIndex >= 1 && docIndex <= numDoctors) {
        Doctor& selectedDoctor = doctors[docIndex - 1];
        cout << "Enter index of appointment to cancel (1-" << selectedDoctor.numAppointments << "): ";
        int index;
        cin >> index;

        if (index >= 1 && index <= selectedDoctor.numAppointments) {
            if (index == 1) {
                Appointment* temp = selectedDoctor.appointments;
                selectedDoctor.appointments = selectedDoctor.appointments->next;
                delete temp;
            }
            else {
                Appointment* current = selectedDoctor.appointments;
                for (int i = 1; i < index - 1; ++i) {
                    current = current->next;
                }
                Appointment* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
            selectedDoctor.numAppointments--;
            cout << "\nAppointment canceled successfully.\n";
        }
        else {
            cout << "\nInvalid appointment index.\n";
        }
    }
    else {
        cout << "\nInvalid doctor selection.\n";
    }
}

void displayAppointments() {
    cout << "\nAvailable Doctors:\n";
    for (int i = 0; i < numDoctors; ++i) {
        cout << i + 1 << ". " << doctors[i].name << endl;
    }
    cout << "Select a doctor (1-" << numDoctors << "): ";
    int docIndex;
    cin >> docIndex;

    if (docIndex >= 1 && docIndex <= numDoctors) {
        const Doctor& selectedDoctor = doctors[docIndex - 1];
        cout << "\nAppointments for " << selectedDoctor.name << ":\n";
        if (selectedDoctor.numAppointments == 0) {
            cout << "No appointments scheduled.\n";
        }
        else {
            cout << "--------------------------------------\n";
            cout << "| Date       | Time  | Patient Name  |\n";
            cout << "--------------------------------------\n";
            Appointment* current = selectedDoctor.appointments;
            int index = 1;
            while (current != nullptr) {
                cout << "| " << current->date << " | " << current->time << " | " << current->patientName << endl;
                cout << "--------------------------------------\n";
                cout << "| Contact Details: " << current->contactDetails << endl;
                cout << "| Description: " << current->description << endl;
                cout << "| Status: " << (current->completed ? "Completed" : "Pending") << endl;
                cout << "--------------------------------------\n";
                cout << endl;
                current = current->next;
                index++;
            }
        }
    }
    else {
        cout << "\nInvalid doctor selection.\n";
    }
}
