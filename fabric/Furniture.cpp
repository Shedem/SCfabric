#include "Furniture.h"
#include <iostream>
#include <fstream>
#include <cstring> // Для работы с C-строками (strcpy, strlen)

using namespace std;


Furniture::Furniture() : height(0), width(0), depth(0), cost(0) {
    type = nullptr;
    color = nullptr;
    material = nullptr;
    cout << "Furniture default constructor called" << endl;
}

Furniture::Furniture(const char* t, double h, double w, double d, const char* c, const char* m, double co)
    : height(h), width(w), depth(d), cost(co) {

    type = new char[strlen(t) + 1];
    strcpy(type, t);

    color = new char[strlen(c) + 1];
    strcpy(color, c);

    material = new char[strlen(m) + 1];
    strcpy(material, m);

    cout << "Furniture parameterized constructor called" << endl;
}

Furniture::Furniture(const Furniture& other)
    : height(other.height), width(other.width), depth(other.depth), cost(other.cost) {

    // Копируем 'type'
    type = (other.type) ? new char[strlen(other.type) + 1] : nullptr;
    if (type) strcpy(type, other.type);

    // Копируем 'color'
    color = (other.color) ? new char[strlen(other.color) + 1] : nullptr;
    if (color) strcpy(color, other.color);

    // Копируем 'material'
    material = (other.material) ? new char[strlen(other.material) + 1] : nullptr;
    if (material) strcpy(material, other.material);

    cout << "Furniture copy constructor called" << endl;
}

Furniture::~Furniture() {
 
    delete[] type;
    delete[] color;
    delete[] material;
    cout << "Furniture destructor called" << endl;
}


void Furniture::setType(const char* t) {
    delete[] type;
    type = new char[strlen(t) + 1];
    strcpy(type, t);
}
char* Furniture::getType() {
    return type;
}

void Furniture::setDimensions(double h, double w, double d) {
    height = h;
    width = w;
    depth = d;
}
double Furniture::getHeight() {
    return height;
}
double Furniture::getWidth() {
    return width;
}
double Furniture::getDepth() {
    return depth;
}

void Furniture::setColor(const char* c) {
    delete[] color;
    color = new char[strlen(c) + 1];
    strcpy(color, c);
}
char* Furniture::getColor() {
    return color;
}

void Furniture::setMaterial(const char* m) {
    delete[] material;
    material = new char[strlen(m) + 1];
    strcpy(material, m);
}
char* Furniture::getMaterial() {
    return material;
}

void Furniture::setCost(double co) {
    cost = co;
}
double Furniture::getCost() {
    return cost;
}



void Furniture::show() {
    cout << "--- Мебель ---" << endl;
    cout << "Тип: " << (type ? type : "N/A") << endl;
    cout << "Габариты (ВxШxГ): " << height << "x" << width << "x" << depth << endl;
    cout << "Цвет: " << (color ? color : "N/A") << endl;
    cout << "Материал: " << (material ? material : "N/A") << endl;
    cout << "Стоимость: " << cost << endl;
}

void Furniture::save(ofstream& fout) {
    cout << "Furniture::save() (пока не реализовано)" << endl;
    // Здесь будет код сохранения в файл
}

void Furniture::load(ifstream& fin) {
    cout << "Furniture::load() (пока не реализовано)" << endl;
    // Здесь будет код загрузки из файла
}

void Furniture::edit() {
    cout << "Furniture::edit() (пока не реализовано)" << endl;
    // Здесь будет код для редактирования полей
}