#pragma once 
#include <iostream> // Для вывода в консоль
#include <fstream>  // Для файловых потоков (понадобится для save/load)

// Используем стандартное пространство имен для удобства
using namespace std;

class Base {
public:
    // Конструктор
    Base();

    virtual ~Base();

    // Показать информацию об объекте
    virtual void show() = 0;

    // Сохранить объект в файл
    virtual void save(ofstream& fout) = 0;

    // Загрузить объект из файла
    virtual void load(ifstream& fin) = 0;

    // Редактировать поля объекта
    virtual void edit() = 0;
};
