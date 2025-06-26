#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "BallChain.h"

// Проверка на вводимое целое число, обработка исключений
int IntegerInput() {
    int value;
    while (true) {
        std::string input;
        getline(std::cin, input);
        
        try {
            value = std::stoi(input);
            return value;
        } catch (...) {
            std::cerr << "Ошибка! Пожалуйста, введите целое число.\n";
        }
    }
}

// Запуск игры, основная логика
void RunGame() {
    BallChain chain;
    std::cout << "=== Игра 'Шарики' ===\n";

    while (true) {
        std::cout << "\n1. Добавить шарики\n"
                  << "2. Удалить цепочки\n"
                  << "3. Показать текущую цепочку\n"
                  << "4. Начать заново\n"
                  << "5. Выход\n"
                  << "Выберите действие: ";

        int choice = IntegerInput();

        switch (choice) {
            // Добавление шаров в список, с обработкой исключений
            case 1: {
                std::cout << "Введите цвета шариков (0-9 через пробел): ";
                std::string input;
                getline(std::cin, input);
                
                std::istringstream iss(input);
                int color;
                try {
                    while (iss >> color) {
                        if (color < 0 || color > 9) {
                            throw std::out_of_range("Цвет должен быть от 0 до 9");
                        }
                        chain.AddBall(color);
                    }
                }
                catch (std::out_of_range& e) {
                    std::cerr << "Ошибка: " << e.what() << "\n";
                }
                std::cout << "Текущая цепочка: ";
                chain.PrintChain();
                break;
            }
             // Удаление шаров из списка
            case 2: {
                int removed = chain.RemoveChains();
                std::cout << "Текущая цепочка: ";
                chain.PrintChain();
                if (removed > 0) {
                    std::cout << "Всего удалено шариков: " << removed << std::endl;
                } else {
                    std::cout << "Нет цепочек для удаления.\n";
                }
                break;
            }
            // Вывод текущего списка
            case 3:
                std::cout << "Текущая цепочка: ";
                chain.PrintChain();
                break;
            // Очистка списка, начать игру заново
            case 4:
                chain.Clear();
                std::cout << "Игра начата заново.\n";
                break;
            // Выход из программы
            case 5:
                return;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian"); // Подключение русского языка
    RunGame();
    return 0;
}