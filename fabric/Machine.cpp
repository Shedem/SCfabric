#include "Machine.h"
#include <iostream>
#include <fstream>
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
    // 1. Сохраняем Марку (make)
    int len_make = make ? strlen(make) : 0;
    fout.write(reinterpret_cast<const char*>(&len_make), sizeof(len_make));
    if (len_make > 0) fout.write(make, len_make);

    // 2. Сохраняем Модель (model)
    int len_model = model ? strlen(model) : 0;
    fout.write(reinterpret_cast<const char*>(&len_model), sizeof(len_model));
    if (len_model > 0) fout.write(model, len_model);

    // 3. Сохраняем Гос. номер (licensePlate)
    int len_lp = licensePlate ? strlen(licensePlate) : 0;
    fout.write(reinterpret_cast<const char*>(&len_lp), sizeof(len_lp));
    if (len_lp > 0) fout.write(licensePlate, len_lp);
}

void Machine::load(ifstream& fin) {
    int len = 0;

    // 1. Загружаем Марку (make)
    fin.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        delete[] make;
        make = new char[len + 1];
        fin.read(make, len);
        make[len] = '\0';
    }
    else {
        delete[] make;
        make = nullptr;
    }

    // 2. Загружаем Модель (model)
    fin.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        delete[] model;
        model = new char[len + 1];
        fin.read(model, len);
        model[len] = '\0';
    }
    else {
        delete[] model;
        model = nullptr;
    }

    // 3. Загружаем Гос. номер (licensePlate)
    fin.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        delete[] licensePlate;
        licensePlate = new char[len + 1];
        fin.read(licensePlate, len);
        licensePlate[len] = '\0';
    }
    else {
        delete[] licensePlate;
        licensePlate = nullptr;
    }
}

void Machine::edit() {
    cout << "\n--- Редактирование Машины ---" << endl;
    char buffer[256];

    // 1. Редактирование Марки
    cout << "Текущая марка: " << (make ? make : "N/A") << ". Введите новую: ";
    cin.ignore();
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) {
        setMake(buffer);
    }

    // 2. Редактирование Модели
    cout << "Текущая модель: " << (model ? model : "N/A") << ". Введите новую: ";
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) {
        setModel(buffer);
    }

    // 3. Редактирование Гос. номера
    cout << "Текущий Гос. номер: " << (licensePlate ? licensePlate : "N/A") << ". Введите новый: ";
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) {
        setLicensePlate(buffer);
    }

    cout << "Редактирование Машины завершено." << endl;
}