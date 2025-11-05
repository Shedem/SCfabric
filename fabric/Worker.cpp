#include "Worker.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>   
#include <stdexcept> 
#include <iomanip>

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
    strcpy_s(fio, strlen(f) + 1, f);

    position = new char[strlen(p) + 1];
    strcpy_s(position, strlen(p) + 1, p);

    address = new char[strlen(a) + 1];
    strcpy_s(address, strlen(a) + 1, a);

    phone = new char[strlen(ph) + 1];
    strcpy_s(phone, strlen(ph) + 1, ph);

    cout << "Worker parameterized constructor called" << endl;
}

Worker::Worker(const Worker& other) : salary(other.salary) {
    // Копирование FIO 
    if (other.fio) {
        size_t len = strlen(other.fio) + 1;
        fio = new char[len];
        strcpy_s(fio, len, other.fio);
    }
    else {
        fio = nullptr;
    }

    // Копирование Position
    if (other.position) {
        size_t len = strlen(other.position) + 1;
        position = new char[len];
        strcpy_s(position, len, other.position);
    }
    else {
        position = nullptr;
    }

    // Копирование Address
    if (other.address) {
        size_t len = strlen(other.address) + 1;
        address = new char[len];
        strcpy_s(address, len, other.address);
    }
    else {
        address = nullptr;
    }

    // Копирование Phone
    if (other.phone) {
        size_t len = strlen(other.phone) + 1;
        phone = new char[len];
        strcpy_s(phone, len, other.phone);
    }
    else {
        phone = nullptr;
    }

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
    size_t dest_size = strlen(f) + 1;
    delete[] fio;
    fio = new char[dest_size];
    strcpy_s(fio, dest_size, f);
}
char* Worker::getFio() { return fio; }

void Worker::setPosition(const char* p) {
    size_t dest_size = strlen(p) + 1;
    delete[] position;
    position = new char[dest_size];
    strcpy_s(position, dest_size, p);
}
char* Worker::getPosition() { return position; }

void Worker::setSalary(double s) { salary = s; }
double Worker::getSalary() { return salary; }

void Worker::setAddress(const char* a) {
    size_t dest_size = strlen(a) + 1;
    delete[] address;
    address = new char[dest_size];
    strcpy_s(address, dest_size, a);
}
char* Worker::getAddress() { return address; }

void Worker::setPhone(const char* ph) {
    size_t dest_size = strlen(ph) + 1;
    delete[] phone;
    phone = new char[dest_size];
    strcpy_s(phone, dest_size, ph);
}
char* Worker::getPhone() { return phone; }



void Worker::show() {
    cout << "--- Работник ---" << endl;
    cout << "ФИО: " << (fio ? fio : "N/A") << endl;
    cout << "Должность: " << (position ? position : "N/A") << endl;
    cout << "Зарплата: " << salary << endl;
    cout << "Адрес: " << (address ? address : "N/A") << endl;
    cout << "Телефон: " << (phone ? phone : "N/A") << endl;
}

void Worker::save(ofstream& fout) {
    fout << 2 << endl; // Тег типа: 2 (Worker)

    fout << (fio ? fio : "N/A") << endl;
    fout << (position ? position : "N/A") << endl;
    fout << salary << endl;
    fout << (address ? address : "N/A") << endl;
    fout << (phone ? phone : "N/A") << endl;
}

void Worker::load(ifstream& fin) {
    string tempStr;
    double tempDouble;

    // 1. FIO
    if (!getline(fin, tempStr)) return;
    setFio(tempStr.c_str());

    // 2. Position
    if (!getline(fin, tempStr)) return;
    setPosition(tempStr.c_str());

    // 3. Salary (number)
    if (!(fin >> tempDouble)) return;
    salary = tempDouble;
    fin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    // 4. Address
    if (!getline(fin, tempStr)) return;
    setAddress(tempStr.c_str());

    // 5. Phone
    if (!getline(fin, tempStr)) return;
    setPhone(tempStr.c_str());
}

void Worker::edit() {
    cout << "\n--- Редактирование Работника ---" << endl;
    char buffer[256];
    double new_salary;
    const char* SKIP_SYMBOL = "-"; // Символ пропуска

    // 1. FIO
    cout << "Текущее ФИО: " << (fio ? fio : "N/A") << ". Введите новое (или '-' для пропуска): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setFio(buffer);
    }

    // 2. Должность
    cout << "Текущая должность: " << (position ? position : "N/A") << ". Введите новую (или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setPosition(buffer);
    }

    // 3. Зарплата (Числовой ввод)
    cout << "Текущая зарплата: " << fixed << setprecision(2) << salary << ". Введите новую (число, или '-' для пропуска): ";
    cout.unsetf(ios_base::floatfield);
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        try {
            new_salary = std::stod(std::string(buffer));
            setSalary(new_salary);
        }
        catch (const std::exception& e) {
            cout << "Ошибка ввода: Введено нечисловое значение или слишком большое число. Зарплата не изменена." << endl;
        }
    }

    // 4. Адрес
    cout << "Текущий адрес: " << (address ? address : "N/A") << ". Введите новый (или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setAddress(buffer);
    }

    // 5. Телефон
    cout << "Текущий телефон: " << (phone ? phone : "N/A") << ". Введите новый (или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setPhone(buffer);
    }

    cout << "Редактирование Работника завершено." << endl;
}