#include "Keeper.h"
#include "Furniture.h" 
#include "Worker.h"    
#include "Machine.h"   
#include <iostream>
#include <algorithm> 
#include <cstring>
#include <stdexcept>

using namespace std;

Keeper::Keeper(int initialCapacity) : size(0), capacity(initialCapacity) {
    if (capacity <= 0) capacity = 10; // Защита от нулевого размера

    items = new Base * [capacity];
    cout << "Keeper constructor called. Initial capacity: " << capacity << endl;
}

Keeper::~Keeper() {
    cout << "Keeper destructor called. Deleting all items..." << endl;
    // 1. Освобождаем память, занимаемую каждым объектом
    for (int i = 0; i < size; ++i) {
        delete items[i];
    }
    // 2. Освобождаем память, занимаемую самим массивом указателей
    delete[] items;
    items = nullptr;
    size = 0;
    capacity = 0;
}

void Keeper::resize(int newCapacity) {
    if (newCapacity <= size) return;

    Base** newItems = new Base * [newCapacity];

    for (int i = 0; i < size; ++i) {
        newItems[i] = items[i];
    }

    delete[] items;
    items = newItems;
    capacity = newCapacity;
    cout << "Keeper resized to: " << capacity << endl;
}

void Keeper::add(Base* newItem) {
    if (size == capacity) {
        
        resize(capacity * 2);
    }
    items[size] = newItem;
    size++;
    cout << "Item added. Total items: " << size << endl;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw IndexOutOfRangeException(index, size - 1);
    }

    // 1. Удаляем сам объект
    delete items[index];

    for (int i = index; i < size - 1; ++i) {
        items[i] = items[i + 1];
    }

    size--;
    cout << "Item at index " << index << " removed. Total items: " << size << endl;
}

void Keeper::showAll() {
    if (size == 0) {
        cout << "Контейнер пуст." << endl;
        return;
    }
    cout << "\n--- СОДЕРЖИМОЕ ФАБРИКИ (" << size << " элементов) ---" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "[" << i << "] ";
        
        items[i]->show();
        cout << "---------------------------------------" << endl;
    }
}

void Keeper::editItem(int index) {
    if (index < 0 || index >= size) {
        throw IndexOutOfRangeException(index, size - 1);
    }
   
    items[index]->edit();
}

void Keeper::saveToFile(const char* filename) {
    
    ofstream fout(filename, ios::out | ios::trunc); 
    if (!fout.is_open()) {
        throw FileOpenException(filename);
    }

    fout << size << endl; // Запись количества элементов

    for (int i = 0; i < size; ++i) {
        // Виртуальный вызов save(), который записывает тег и данные
        items[i]->save(fout);
    }

    fout.close();
    cout << "Данные успешно сохранены в файл: " << filename << endl;
}


void Keeper::loadFromFile(const char* filename) {
    
    ifstream fin(filename, ios::in);
    if (!fin.is_open()) {
        throw FileOpenException(filename);
    }

    // 1. Очистка старых данных
    for (int i = 0; i < size; ++i) {
        delete items[i];
    }
    size = 0;

    // 2. Чтение общего количества
    int newSize;
    if (!(fin >> newSize)) {
        cout << "ОШИБКА: Не удалось прочитать количество элементов." << endl;
        return;
    }
    fin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    if (newSize > capacity) {
        resize(newSize);
    }

    // 3. Цикл загрузки элементов
    for (int i = 0; i < newSize; ++i) {
        int typeTag;
        // Читаем тег типа
        if (!(fin >> typeTag)) break;
        fin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        Base* newItem = nullptr;

        // Динамическое создание пустого объекта
        switch (typeTag) {
        case 1: newItem = new Furniture(); break;
        case 2: newItem = new Worker(); break;
        case 3: newItem = new Machine(); break;
        default: continue;
        }

        if (newItem) {
            
            newItem->load(fin);

            // Если массив не переполнен
            if (size < capacity) {
                items[size++] = newItem;
            }
            else {
                delete newItem; // Защита от переполнения
            }
        }
    }

    fin.close();
    cout << "Данные успешно загружены из файла: " << filename << ". Всего элементов: " << size << endl;
}