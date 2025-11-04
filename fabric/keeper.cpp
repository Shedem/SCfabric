#include "Keeper.h"
#include "Furniture.h" // Нужны для загрузки
#include "Worker.h"    // Нужны для загрузки
#include "Machine.h"   // Нужны для загрузки
#include <iostream>
#include <algorithm> // для std::copy, хотя можно и без него
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
    ofstream fout(filename, ios::binary | ios::trunc);
    if (!fout.is_open()) {
        throw FileOpenException(filename);
    }

    fout.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (int i = 0; i < size; ++i) {
        
        int typeTag = 0;
        if (dynamic_cast<Furniture*>(items[i])) {
            typeTag = 1;
        }
        else if (dynamic_cast<Worker*>(items[i])) {
            typeTag = 2;
        }
        else if (dynamic_cast<Machine*>(items[i])) {
            typeTag = 3;
        }

        fout.write(reinterpret_cast<const char*>(&typeTag), sizeof(typeTag));

        items[i]->save(fout);
    }

    fout.close();
    cout << "Data saved successfully to " << filename << endl;
}


void Keeper::loadFromFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        throw FileOpenException(filename);
    }

    if (items) {
        for (int i = 0; i < size; ++i) {
            delete items[i];
        }
        delete[] items;
    }
    size = 0;
    capacity = 10;
    items = new Base * [capacity];

    int itemsToLoad = 0;
    fin.read(reinterpret_cast<char*>(&itemsToLoad), sizeof(itemsToLoad));

    for (int i = 0; i < itemsToLoad; ++i) {
        
        if (size == capacity) {
            resize(capacity * 2);
        }

        int typeTag = 0;
        fin.read(reinterpret_cast<char*>(&typeTag), sizeof(typeTag));

        Base* newItem = nullptr;
        
        switch (typeTag) {
        case 1:
            newItem = new Furniture();
            break;
        case 2:
            newItem = new Worker();
            break;
        case 3:
            newItem = new Machine();
            break;
        default:
            cout << "ERROR: Unknown type tag encountered. Aborting load." << endl;
            
            fin.close();
            return;
        }

        newItem->load(fin);

        items[size++] = newItem;
    }

    fin.close();
    cout << "Data loaded successfully. Total items: " << size << endl;
}