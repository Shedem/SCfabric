#pragma once
#include "Base.h"

class Worker : public Base {
private:
    char* fio;      // ФИО
    char* position; // Должность
    double salary;  // Зарплата
    char* address;  // Адрес
    char* phone;    // Телефон

public:
    
    Worker();
    Worker(const char* f, const char* p, double s, const char* a, const char* ph);
    Worker(const Worker& other);
    ~Worker();

    void setFio(const char* f);
    char* getFio();
    void setPosition(const char* p);
    char* getPosition();
    void setSalary(double s);
    double getSalary();
    void setAddress(const char* a);
    char* getAddress();
    void setPhone(const char* ph);
    char* getPhone();

    void show() override;
    void save(ofstream& fout) override;
    void load(ifstream& fin) override;
    void edit() override;
};