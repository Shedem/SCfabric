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
    // 1. Сохраняем Тип (type)
    int len_type = type ? strlen(type) : 0;
    fout.write(reinterpret_cast<const char*>(&len_type), sizeof(len_type));
    if (len_type > 0) fout.write(type, len_type);

    // 2. Сохраняем Габариты (примитивные типы)
    fout.write(reinterpret_cast<const char*>(&height), sizeof(height));
    fout.write(reinterpret_cast<const char*>(&width), sizeof(width));
    fout.write(reinterpret_cast<const char*>(&depth), sizeof(depth));

    // 3. Сохраняем Цвет (color)
    int len_color = color ? strlen(color) : 0;
    fout.write(reinterpret_cast<const char*>(&len_color), sizeof(len_color));
    if (len_color > 0) fout.write(color, len_color);

    // 4. Сохраняем Материал (material)
    int len_mat = material ? strlen(material) : 0;
    fout.write(reinterpret_cast<const char*>(&len_mat), sizeof(len_mat));
    if (len_mat > 0) fout.write(material, len_mat);

    // 5. Сохраняем Стоимость
    fout.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
}

void Furniture::load(ifstream& fin) {
    int len = 0;

    // Вспомогательная функция для загрузки char*
    auto load_char_ptr = [&](char*& ptr) {
        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            delete[] ptr;
            ptr = new char[len + 1];
            fin.read(ptr, len);
            ptr[len] = '\0';
        }
        else {
            delete[] ptr;
            ptr = nullptr;
        }
        };

    // 1. Загружаем Тип
    load_char_ptr(type);

    // 2. Загружаем Габариты
    fin.read(reinterpret_cast<char*>(&height), sizeof(height));
    fin.read(reinterpret_cast<char*>(&width), sizeof(width));
    fin.read(reinterpret_cast<char*>(&depth), sizeof(depth));

    // 3. Загружаем Цвет
    load_char_ptr(color);

    // 4. Загружаем Материал
    load_char_ptr(material);

    // 5. Загружаем Стоимость
    fin.read(reinterpret_cast<char*>(&cost), sizeof(cost));
}

void Furniture::edit() {
    cout << "\n--- Редактирование Мебели ---" << endl;
    char buffer[256];
    double new_value;

    // 1. Тип
    cout << "Текущий тип: " << (type ? type : "N/A") << ". Введите новый: ";
    cin.ignore();
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) setType(buffer);

    // 2. Габариты 
    cout << "Текущая высота: " << height << ". Введите новую (число): ";
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) {
        try {
            new_value = std::stod(buffer);
            setDimensions(new_value, width, depth); // меняем только высоту
        }
        catch (...) {
            cout << "Ошибка ввода. Высота не изменена." << endl;
        }
    }

    // 3. Цвет
    cout << "Текущий цвет: " << (color ? color : "N/A") << ". Введите новый: ";
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) setColor(buffer);

    // 4. Материал
    cout << "Текущий материал: " << (material ? material : "N/A") << ". Введите новый: ";
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) setMaterial(buffer);

    // 5. Стоимость
    cout << "Текущая стоимость: " << cost << ". Введите новую (число): ";
    cin.getline(buffer, 256);
    if (strlen(buffer) > 0) {
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