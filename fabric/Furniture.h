#pragma once
#include "Base.h"
#include <string> 

class Furniture : public Base {
private:
    
    char* type;     // Тип мебели
    double height;  // Габариты
    double width;
    double depth;
    char* color;    // Цвет
    char* material; // Материал
    double cost;    // Стоимость

public:
    // Конструкторы и деструктор 
    Furniture();                          
    Furniture(const char* t, double h, double w, double d, const char* c, const char* m, double co); 
    Furniture(const Furniture& other);    
    ~Furniture();                         


    void setType(const char* t);
    char* getType();

    // Габариты
    void setDimensions(double h, double w, double d);
    double getHeight();
    double getWidth();
    double getDepth();

    // Цвет
    void setColor(const char* c);
    char* getColor();

    // Материал
    void setMaterial(const char* m);
    char* getMaterial();

    // Стоимость
    void setCost(double co);
    double getCost();
    

    void show() override;
    void save(ofstream& fout) override;
    void load(ifstream& fin) override;
    void edit() override;
};