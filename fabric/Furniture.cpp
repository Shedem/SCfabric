#include "Furniture.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>    // Для std::stod
#include <stdexcept> 

using namespace std;

// ===================================
// 1. КОНСТРУКТОРЫ И ДЕСТРУКТОР
// ===================================

// 1. Конструктор по умолчанию
Furniture::Furniture() : height(0), width(0), depth(0), cost(0) {
    type = nullptr;
    color = nullptr;
    material = nullptr;
    cout << "Furniture default constructor called" << endl;
}

// 2. Конструктор с параметрами
Furniture::Furniture(const char* t, double h, double w, double d, const char* c, const char* m, double co)
    : height(h), width(w), depth(d), cost(co) {

    // Выделяем память и копируем строки (Используем strcpy_s)
    type = new char[strlen(t) + 1];
    strcpy_s(type, strlen(t) + 1, t);

    color = new char[strlen(c) + 1];
    strcpy_s(color, strlen(c) + 1, c);

    material = new char[strlen(m) + 1];
    strcpy_s(material, strlen(m) + 1, m);

    cout << "Furniture parameterized constructor called" << endl;
}

Furniture::Furniture(const Furniture& other)
    : height(other.height), width(other.width), depth(other.depth), cost(other.cost) {

    // Копируем 'type'
    if (other.type) {
        size_t len = strlen(other.type) + 1;
        type = new char[len];
        strcpy_s(type, len, other.type);
    }
    else {
        type = nullptr;
    }

    // Копируем 'color'
    if (other.color) {
        size_t len = strlen(other.color) + 1;
        color = new char[len];
        strcpy_s(color, len, other.color);
    }
    else {
        color = nullptr;
    }

    // Копируем 'material'
    if (other.material) {
        size_t len = strlen(other.material) + 1;
        material = new char[len];
        strcpy_s(material, len, other.material);
    }
    else {
        material = nullptr;
    }

    cout << "Furniture copy constructor called" << endl;
}

Furniture::~Furniture() {
    delete[] type;
    delete[] color;
    delete[] material;
    cout << "Furniture destructor called" << endl;
}

void Furniture::setType(const char* t) {
    size_t dest_size = strlen(t) + 1;
    delete[] type;
    type = new char[dest_size];
    strcpy_s(type, dest_size, t);
}
char* Furniture::getType() {
    return type;
}

void Furniture::setDimensions(double h, double w, double d) {
    height = h;
    width = w;
    depth = d;
}
double Furniture::getHeight() { return height; }
double Furniture::getWidth() { return width; }
double Furniture::getDepth() { return depth; }

void Furniture::setColor(const char* c) {
    size_t dest_size = strlen(c) + 1;
    delete[] color;
    color = new char[dest_size];
    strcpy_s(color, dest_size, c);
}
char* Furniture::getColor() { return color; }

void Furniture::setMaterial(const char* m) {
    size_t dest_size = strlen(m) + 1;
    delete[] material;
    material = new char[dest_size];
    strcpy_s(material, dest_size, m);
}
char* Furniture::getMaterial() { return material; }

void Furniture::setCost(double co) { cost = co; }
double Furniture::getCost() { return cost; }



void Furniture::show() {
    cout << "--- Мебель ---" << endl;
    cout << "Тип: " << (type ? type : "N/A") << endl;
    cout << "Габариты (ВxШxГ): " << height << "x" << width << "x" << depth << endl;
    cout << "Цвет: " << (color ? color : "N/A") << endl;
    cout << "Материал: " << (material ? material : "N/A") << endl;
    cout << "Стоимость: " << cost << endl;
}

void Furniture::save(ofstream& fout) {
    fout << 1 << endl; // Тег типа: 1 (Furniture)

    fout << (type ? type : "N/A") << endl;
    fout << height << endl;
    fout << width << endl;
    fout << depth << endl;
    fout << (color ? color : "N/A") << endl;
    fout << (material ? material : "N/A") << endl;
    fout << cost << endl;
}

void Furniture::load(ifstream& fin) {
    string tempStr;
    double tempDouble;

    // 1. Тип (type)
    if (!getline(fin, tempStr)) return;
    setType(tempStr.c_str());

    // 2. Габариты (numbers)
    if (!(fin >> tempDouble)) return;
    height = tempDouble;
    if (!(fin >> tempDouble)) return;
    width = tempDouble;
    if (!(fin >> tempDouble)) return;
    depth = tempDouble;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    // 3. Цвет (color)
    if (!getline(fin, tempStr)) return;
    setColor(tempStr.c_str());

    // 4. Материал (material)
    if (!getline(fin, tempStr)) return;
    setMaterial(tempStr.c_str());

    // 5. Стоимость (number)
    if (!(fin >> tempDouble)) return;
    cost = tempDouble;
    fin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

void Furniture::edit() {
    cout << "\n--- Редактирование Мебели ---" << endl;
    char buffer[256];
    double new_value;
    const char* SKIP_SYMBOL = "-"; // Символ пропуска

    // 1. Тип
    cout << "Текущий тип: " << (type ? type : "N/A") << ". Введите новый (или '-' для пропуска): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(buffer, 256);
    // Проверка на символ пропуска и непустой ввод
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setType(buffer);
    }

    // 2. Габариты (Высота)
    cout << "Текущая высота: " << height << ". Введите новую (число, или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        try {
            new_value = std::stod(buffer);
            height = new_value;
        }
        catch (...) {
            cout << "Ошибка ввода. Высота не изменена." << endl;
        }
    }
   
    // Ширина
    cout << "Текущая ширина: " << width << ". Введите новую (число, или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        try {
            new_value = std::stod(buffer);
            width = new_value;
        }
        catch (...) {
            cout << "Ошибка ввода. Ширина не изменена." << endl;
        }
    }
    // Глубина
    cout << "Текущая глубина: " << depth << ". Введите новую (число, или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        try {
            new_value = std::stod(buffer);
            depth = new_value;
        }
        catch (...) {
            cout << "Ошибка ввода. Глубина не изменена." << endl;
        }
    }

    // 3. Цвет
    cout << "Текущий цвет: " << (color ? color : "N/A") << ". Введите новый (или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setColor(buffer);
    }

    // 4. Материал
    cout << "Текущий материал: " << (material ? material : "N/A") << ". Введите новый (или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        setMaterial(buffer);
    }

    // 5. Стоимость
    cout << "Текущая стоимость: " << cost << ". Введите новую (число, или '-' для пропуска): ";
    cin.getline(buffer, 256);
    if (strcmp(buffer, SKIP_SYMBOL) != 0 && strlen(buffer) > 0) {
        try {
            new_value = std::stod(buffer);
            setCost(new_value);
        }
        catch (...) {
            cout << "Ошибка ввода. Стоимость не изменена." << endl;
        }
    }

    cout << "Редактирование Мебели завершено." << endl;
}