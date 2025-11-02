#include "Machine.h"
#include <iostream>
#include <fstream> // для save/load
#include <cstring>

using namespace std;



Machine::Machine() {
    make = nullptr;
    model = nullptr;
    licensePlate = nullptr;
    cout << "Machine default constructor called" << endl;
}

Machine::Machine(const char* mk, const char* md, const char* lp) {
    make = new char[strlen(mk) + 1];
    strcpy(make, mk);

    model = new char[strlen(md) + 1];
    strcpy(model, md);

    licensePlate = new char[strlen(lp) + 1];
    strcpy(licensePlate, lp);

    cout << "Machine parameterized constructor called" << endl;
}

Machine::Machine(const Machine& other) {
    // Копирование Make
    make = (other.make) ? new char[strlen(other.make) + 1] : nullptr;
    if (make) strcpy(make, other.make);

    // Копирование Model
    model = (other.model) ? new char[strlen(other.model) + 1] : nullptr;
    if (model) strcpy(model, other.model);

    // Копирование License Plate
    licensePlate = (other.licensePlate) ? new char[strlen(other.licensePlate) + 1] : nullptr;
    if (licensePlate) strcpy(licensePlate, other.licensePlate);

    cout << "Machine copy constructor called" << endl;
}

Machine::~Machine() {
    
    delete[] make;
    delete[] model;
    delete[] licensePlate;
    cout << "Machine destructor called" << endl;
}



void Machine::setMake(const char* mk) {
    delete[] make;
    make = new char[strlen(mk) + 1];
    strcpy(make, mk);
}
char* Machine::getMake() {
    return make;
}

void Machine::setModel(const char* md) {
    delete[] model;
    model = new char[strlen(md) + 1];
    strcpy(model, md);
}
char* Machine::getModel() {
    return model;
}

void Machine::setLicensePlate(const char* lp) {
    delete[] licensePlate;
    licensePlate = new char[strlen(lp) + 1];
    strcpy(licensePlate, lp);
}
char* Machine::getLicensePlate() {
    return licensePlate;
}



// РЕАЛИЗАЦИЯ ВИРТУАЛЬНЫХ ФУНКЦИЙ (ЗАГЛУШКИ)


void Machine::show() {
    cout << "--- Машина ---" << endl;
    cout << "Марка: " << (make ? make : "N/A") << endl;
    cout << "Модель: " << (model ? model : "N/A") << endl;
    cout << "Гос. номер: " << (licensePlate ? licensePlate : "N/A") << endl;
}

void Machine::save(ofstream& fout) {
    cout << "Machine::save() (пока не реализовано)" << endl;
}

void Machine::load(ifstream& fin) {
    cout << "Machine::load() (пока не реализовано)" << endl;
}

void Machine::edit() {
    cout << "Machine::edit() (пока не реализовано)" << endl;
}