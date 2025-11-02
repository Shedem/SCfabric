
#pragma once
#include "Base.h"

class Machine : public Base {
private:
    char* make;         // Марка
    char* model;        // Модель
    char* licensePlate; // Гос. номер

public:
    
    Machine();
    Machine(const char* mk, const char* md, const char* lp);
    Machine(const Machine& other);
    ~Machine();

    void setMake(const char* mk);
    char* getMake();
   
    void setModel(const char* md);
    char* getModel();
    void setLicensePlate(const char* lp);
    char* getLicensePlate();


    void show() override;
    void save(ofstream& fout) override;
    void load(ifstream& fin) override;
    void edit() override;
};