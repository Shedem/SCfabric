#pragma once
#include "Base.h" 
#include <iostream>
#include <fstream>
#include <stdexcept> 
#include <string>   

class Keeper {
private:
    Base** items;
    int size;
    int capacity;

    void resize(int newCapacity);

public:
    // --- 1. Базовый класс для всех исключений Keeper ---
    class KeeperException : public std::runtime_error {
    public:
        // Конструктор, который передает сообщение в базовый класс
        KeeperException(const std::string& msg) : std::runtime_error(msg) {}
    };

    // --- 2. Исключение: Индекс вне диапазона ---
    class IndexOutOfRangeException : public KeeperException {
    public:
        IndexOutOfRangeException(int index, int max)
            : KeeperException("ОШИБКА: Указанный индекс " + std::to_string(index) +
                " находится вне допустимого диапазона [0-" + std::to_string(max) + "].") {
        }
    };

    // --- 3. Исключение: Ошибка открытия файла ---
    class FileOpenException : public KeeperException {
    public:
        FileOpenException(const std::string& filename)
            : KeeperException("ОШИБКА: Не удалось открыть файл '" + filename + "' для операции сохранения/загрузки.") {
        }
    };

    Keeper(int initialCapacity = 10);
    ~Keeper();
    void add(Base* newItem);
    void remove(int index);
    void showAll();
    void editItem(int index);
    int getSize() const { return size; }
    void saveToFile(const char* filename);
    void loadFromFile(const char* filename);
};