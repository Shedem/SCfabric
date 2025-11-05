#define NOMINMAX
#include "Keeper.h"
#include "Furniture.h"
#include "Worker.h"
#include "Machine.h"
#include <iostream>
#include <limits> // Для очистки потока cin
#include <clocale>
#include <windows.h>

using namespace std;

// Функция для добавления нового элемента
void addNewItem(Keeper& keeper) {
    int choice;
    cout << "\n--- Добавление нового элемента ---" << endl;
    cout << "1. Мебель (Furniture)" << endl;
    cout << "2. Работник (Worker)" << endl;
    cout << "3. Машина (Machine)" << endl;
    cout << "Выберите тип: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера

    Base* newItem = nullptr;

    try {
        if (choice == 1) {
            char type[100], color[100], material[100];
            double h, w, d, c;

            cout << "Введите тип мебели: "; cin.getline(type, 100);
            cout << "Введите высоту: "; cin >> h;
            cout << "Введите ширину: "; cin >> w;
            cout << "Введите глубину: "; cin >> d;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите цвет: "; cin.getline(color, 100);
            cout << "Введите материал: "; cin.getline(material, 100);
            cout << "Введите стоимость: "; cin >> c;

            newItem = new Furniture(type, h, w, d, color, material, c);

        }
        else if (choice == 2) {
            char fio[100], position[100], address[100], phone[100];
            double s;

            cout << "Введите ФИО: "; cin.getline(fio, 100);
            cout << "Введите должность: "; cin.getline(position, 100);
            cout << "Введите зарплату: "; cin >> s;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите адрес: "; cin.getline(address, 100);
            cout << "Введите телефон: "; cin.getline(phone, 100);

            newItem = new Worker(fio, position, s, address, phone);

        }
        else if (choice == 3) {
            char make[100], model[100], licensePlate[100];

            cout << "Введите марку: "; cin.getline(make, 100);
            cout << "Введите модель: "; cin.getline(model, 100);
            cout << "Введите гос. номер: "; cin.getline(licensePlate, 100);

            newItem = new Machine(make, model, licensePlate);

        }
        else {
            cout << "Неверный выбор типа." << endl;
            return;
        }

        if (newItem) {
            keeper.add(newItem);
        }

    }
    catch (const exception& e) {
        // Здесь можно использовать свои классы исключений
        cerr << "Ошибка ввода данных: " << e.what() << endl;
        // Если объект создан, но произошла ошибка ввода, его нужно удалить
        delete newItem;
        cin.clear(); // Сброс флагов ошибок cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Имя файла для сохранения
    const char* filename = "factory_data.txt";
    // Создаем единственный объект-контейнер
    Keeper factoryKeeper;
    int choice = -1;

    // Главный цикл программы
    while (choice != 0) {
        cout << "\n=======================================" << endl;
        cout << "      СИСТЕМА УПРАВЛЕНИЯ ФАБРИКОЙ" << endl;
        cout << "=======================================" << endl;
        cout << "1. Добавить новый элемент" << endl;
        cout << "2. Удалить элемент по индексу" << endl;
        cout << "3. Показать все элементы" << endl;
        cout << "4. Редактировать элемент по индексу" << endl;
        cout << "5. Сохранить данные в файл" << endl;
        cout << "6. Загрузить данные из файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        if (!(cin >> choice)) {
            // Обработка неверного ввода (не числа)
            cout << "Ошибка ввода. Пожалуйста, введите число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
            case 1:
                addNewItem(factoryKeeper);
                break;
            case 2: {
                int index;
                cout << "Введите индекс элемента для удаления (0 до " << factoryKeeper.getSize() - 1 << "): ";
                cin >> index;
                factoryKeeper.remove(index);
                break;
            }
            case 3:
                factoryKeeper.showAll();
                break;
            case 4: {
                int index;
                cout << "Введите индекс элемента для редактирования (0 до " << factoryKeeper.getSize() - 1 << "): ";
                cin >> index;
                factoryKeeper.editItem(index);
                break;
            }
            case 5:
                factoryKeeper.saveToFile(filename);
                break;
            case 6:
                factoryKeeper.loadFromFile(filename);
                break;
            case 0:
                cout << "Выход из программы. Деструктор Keeper очистит всю память." << endl;
                break;
            default:
                cout << "Неизвестная команда. Попробуйте еще раз." << endl;
            }
        }
        catch (const Keeper::KeeperException& e) {
            // Ловит IndexOutOfRangeException и FileOpenException
            cout << "ОШИБКА КОНТЕЙНЕРА/ФАЙЛА: " << e.what() << endl;
        }
        catch (const std::exception& e) {
            // Ловит ошибки, связанные с вводом (например, std::stod в edit/add)
            cout << "ОШИБКА ВВОДА ДАННЫХ: " << e.what() << endl;
        }
        catch (...) {
            cout << "Произошла неизвестная критическая ошибка." << endl;
        }
    }

    return 0;
}