#pragma once
#include "Base.h" 
#include <iostream>
#include <fstream>

class Keeper {
private:
    // Динамический массив указателей на базовый класс
    Base** items;
    int size;       // Текущее количество элементов
    int capacity;   // Максимальная вместимость массива

    // Вспомогательная функция для увеличения размера массива
    void resize(int newCapacity);

public:
    
    Keeper(int initialCapacity = 10);
    ~Keeper();

    void add(Base* newItem);
    void remove(int index);
    void showAll();
    void editItem(int index);
    int getSize() const { return size; }

    void saveToFile(const char* filename);

    void loadFromFile(const char* filename);

    //Исключения (понадобятся позже)

    class IndexOutOfRangeException {};
    class FileOpenException {};
};