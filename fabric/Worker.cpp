#include "Worker.h"
#include <iostream>
#include <fstream> // для save/load
#include <cstring>

using namespace std;


Worker::Worker() : salary(0) {
    fio = nullptr;
    position = nullptr;
    address = nullptr;
    phone = nullptr;
    cout << "Worker default constructor called" << endl;
}

Worker::Worker(const char* f, const char* p, double s, const char* a, const char* ph)
    : salary(s) {
    fio = new char[strlen(f) + 1];
    strcpy(fio, f);

    position = new char[strlen(p) + 1];
    strcpy(position, p);

    address = new char[strlen(a) + 1];
    strcpy(address, a);

    phone = new char[strlen(ph) + 1];
    strcpy(phone, ph);

    cout << "Worker parameterized constructor called" << endl;
}

Worker::Worker(const Worker& other) : salary(other.salary) {
    // Копирование FIO
    fio = (other.fio) ? new char[strlen(other.fio) + 1] : nullptr;
    if (fio) strcpy(fio, other.fio);

    // Копирование Position
    position = (other.position) ? new char[strlen(other.position) + 1] : nullptr;
    if (position) strcpy(position, other.position);

    // Копирование Address
    address = (other.address) ? new char[strlen(other.address) + 1] : nullptr;
    if (address) strcpy(address, other.address);

    // Копирование Phone
    phone = (other.phone) ? new char[strlen(other.phone) + 1] : nullptr;
    if (phone) strcpy(phone, other.phone);

    cout << "Worker copy constructor called" << endl;
}

Worker::~Worker() {
    
    delete[] fio;
    delete[] position;
    delete[] address;
    delete[] phone;
    cout << "Worker destructor called" << endl;
}



void Worker::setFio(const char* f) {
    delete[] fio;
    fio = new char[strlen(f) + 1];
    strcpy(fio, f);
}
char* Worker::getFio() {
    return fio;
}

void Worker::setPosition(const char* p) {
    delete[] position;
    position = new char[strlen(p) + 1];
    strcpy(position, p);
}
char* Worker::getPosition() {
    return position;
}

void Worker::setSalary(double s) {
    salary = s;
}
double Worker::getSalary() {
    return salary;
}

void Worker::setAddress(const char* a) {
    delete[] address;
    address = new char[strlen(a) + 1];
    strcpy(address, a);
}
char* Worker::getAddress() {
    return address;
}

void Worker::setPhone(const char* ph) {
    delete[] phone;
    phone = new char[strlen(ph) + 1];
    strcpy(phone, ph);
}
char* Worker::getPhone() {
    return phone;
}


void Worker::show() {
    cout << "--- Работник ---" << endl;
    cout << "ФИО: " << (fio ? fio : "N/A") << endl;
    cout << "Должность: " << (position ? position : "N/A") << endl;
    cout << "Зарплата: " << salary << endl;
    cout << "Адрес: " << (address ? address : "N/A") << endl;
    cout << "Телефон: " << (phone ? phone : "N/A") << endl;
}

void Worker::save(ofstream& fout) {
    cout << "Worker::save() (пока не реализовано)" << endl;
}

void Worker::load(ifstream& fin) {
    cout << "Worker::load() (пока не реализовано)" << endl;
}

void Worker::edit() {
    cout << "Worker::edit() (пока не реализовано)" << endl;
}