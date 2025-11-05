#include "Machine.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

Machine::Machine() {
    make = nullptr;
    model = nullptr;
    licensePlate = nullptr;
    cout << "Machine default constructor called" << endl;
}

Machine::Machine(const char* mk, const char* md, const char* lp) {

    make = new char[strlen(mk) + 1];
    strcpy_s(make, strlen(mk) + 1, mk);

    model = new char[strlen(md) + 1];
    strcpy_s(model, strlen(md) + 1, md);

    licensePlate = new char[strlen(lp) + 1];
    strcpy_s(licensePlate, strlen(lp) + 1, lp);

    cout << "Machine parameterized constructor called" << endl;
}

Machine::Machine(const Machine& other) {
    // Копирование Make 
    if (other.make) {
        size_t len = strlen(other.make) + 1;
        make = new char[len];
        strcpy_s(make, len, other.make);
    }
    else {
        make = nullptr;
    }

    // Копирование Model
    if (other.model) {
        size_t len = strlen(other.model) + 1;
        model = new char[len];
        strcpy_s(model, len, other.model);
    }
    else {
        model = nullptr;
    }

    // Копирование License Plate
    if (other.licensePlate) {
        size_t len = strlen(other.licensePlate) + 1;
        licensePlate = new char[len];
        strcpy_s(licensePlate, len, other.licensePlate);
    }
    else {
        licensePlate = nullptr;
    }

    cout << "Machine copy constructor called" << endl;
}

Machine::~Machine() {
    delete[] make;
    delete[] model;
    delete[] licensePlate;
    cout << "Machine destructor called" << endl;
}


void Machine::setMake(const char* mk) {
    size_t dest_size = strlen(mk) + 1;
    delete[] make;
    make = new char[dest_size];
    strcpy_s(make, dest_size, mk);
}
char* Machine::getMake() { return make; }

void Machine::setModel(const char* md) {
    size_t dest_size = strlen(md) + 1;
    delete[] model;
    model = new char[dest_size];
    strcpy_s(model, dest_size, md);
}
char* Machine::getModel() { return model; }

void Machine::setLicensePlate(const char* lp) {
    size_t dest_size = strlen(lp) + 1;
    delete[] licensePlate;
    licensePlate = new char[dest_size];
    strcpy_s(licensePlate, dest_size, lp);
}
char* Machine::getLicensePlate() { return licensePlate; }



void Machine::show() {
    cout << "--- Машина ---" << endl;
    cout << "Марка: " << (make ? make : "N/A") << endl;
    cout << "Модель: " << (model ? model : "N/A") << endl;
    cout << "Гос. номер: " << (licensePlate ? licensePlate : "N/A") << endl;
}

void Machine::save(ofstream& fout) {
    fout << 3 << endl; // Тег типа: 3 (Machine)

    fout << (make ? make : "N/A") << endl;
    fout << (model ? model : "N/A") << endl;
    fout << (licensePlate ? licensePlate : "N/A") << endl;
}

void Machine::load(ifstream& fin) {
    string tempStr;

    if (!getline(fin, tempStr)) return;
    setMake(tempStr.c_str());

    if (!getline(fin, tempStr)) return;
    setModel(tempStr.c_str());

    if (!getline(fin, tempStr)) return;
    setLicensePlate(tempStr.c_str());
}

void Machine::edit() {
    cout << "\n--- Редактирование Машины ---" << endl;
    char buffer[256];
    const char* SKIP_SYMBOL = "-";


    // 1. Редактирование Марки
    cout << "Текущая марка: " << (make ? make : "N/A") << ". Введите новую (или '-' для пропуска): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) !=0 && strlen(buffer) > 0) {
        setMake(buffer);
    }

    // 2. Редактирование Модели
    cout << "Текущая модель: " << (model ? model : "N/A") << ". Введите новую (или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setModel(buffer);
    }

    // 3. Редактирование Гос. номера
    cout << "Текущий Гос. номер: " << (licensePlate ? licensePlate : "N/A") << ". Введите новый (или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setLicensePlate(buffer);
    }

    cout << "Редактирование Машины завершено." << endl;
}