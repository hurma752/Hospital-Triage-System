#ifndef APPOINTMENT_SYSTEM_H
#define APPOINTMENT_SYSTEM_H

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

const int MAX_DOCTORS = 5;
const int MAX_DAILY_SLOTS = 5;
const int MAX_APPOINTMENTS_PER_DOCTOR = 3;

struct Appointment {
    std::string date;
    std::string time;
    std::string description;
    bool completed;
    std::string patientName;
    std::string contactDetails;
    Appointment* next;
};

struct Doctor {
    std::string name;
    Appointment* appointments;
    int numAppointments;
};

extern Doctor doctors[MAX_DOCTORS];
extern int numDoctors;

void initializeDoctors();
bool isDoctorAvailable(Doctor& doctor, const std::string& date);
bool isValidDate(const std::string& date);
bool isValidTime(const std::string& time);
void bookAppointment();
void completeAppointment();
void cancelAppointment();
void displayAppointments();

#endif // APPOINTMENT_SYSTEM_H