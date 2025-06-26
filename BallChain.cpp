#include "BallChain.h"
#include <stdexcept>
#include <iostream>


Ball::Ball(int color) : color(color), next(nullptr) {}

// Геттер Возвращает поле данных
int Ball::GetColor() { 
    return color; 
}

// Геттер Возвращает указатель на следующий элемент
Ball* Ball::GetNext() { 
    return next; 
}

// Сеттер устанавливает указатель на следующий элемент
void Ball::SetNext(Ball* nextNode) { 
    next = nextNode; 
}

// Поиск для фрагмента списка для удаления
bool BallChain::FindChainToRemove(size_t& start, size_t& end) {
        if (size < 3) {
            return false;
        }

        Ball* current = head;
        start = end = 0;
        int currentColor = head->GetColor();
        size_t count = 1;

        for (size_t i = 1; i < size; i++) {
            current = current->GetNext();
            if (current->GetColor() == currentColor) {
                count++;
                end = i;
            } 
            else {
                if (count >= 3) {
                    return true;
                }
                currentColor = current->GetColor();
                start = end = i;
                count = 1;
            }
        }

        return count >= 3;
    }

    // Конструктор
    BallChain::BallChain() : head(nullptr), tail(nullptr), size(0), totalRemoved(0) {}

    // Деструктор
    BallChain::~BallChain() {
        Clear();
    }

    // Добавление элемента в список
    void BallChain::AddBall(int color) {
        if (color < 0 || color > 9) {
            throw std::invalid_argument("Invalid color");
        }

        Ball* newBall = new Ball(color);
        if (!head) {
            head = tail = newBall;
        } 
        else {
            tail->SetNext(newBall);
            tail = newBall;
        }
        size++;
    }

    // Вывод элементов списка
    void BallChain::PrintChain() {
        Ball* current = head;
        while (current) {
            std::cout << current->GetColor() << " ";
            current = current->GetNext();
        }
        std::cout << std::endl;
    }

    // Удаление цепочек
    int BallChain::RemoveChains() {
        int removed = 0;
        size_t start, end;

        while (FindChainToRemove(start, end)) {
            size_t chainLength = end - start + 1;
            removed += chainLength;

            std::cout << "Удаленная цепочка: ";
            for (size_t i = 0; i < chainLength; i++) {
                if (start >= size) {
                    break;
                }

                Ball* prev = nullptr;
                Ball* current = head;

                for (size_t i = 0; i < start; i++) {
                    prev = current;
                    current = current->GetNext();
                }

                if (prev) {
                    prev->SetNext(current->GetNext());
                } else {
                    head = current->GetNext();
                }

                if (current == tail) {
                    tail = prev;
                }

                std::cout << current->GetColor() << " ";
                delete current;
                size--;
            }

            std::cout << "(позиции " << start << "-" << end << ")" << std::endl;
            std::cout << "Цепочка после удаления: ";
            PrintChain();

            totalRemoved += removed;
        }
        return removed;
    }

    // Геттер Возвращает кол-во удаленных элементов списка
    int BallChain::GetTotalRemoved() {
        return totalRemoved;
    }

    // Геттер Возвращает размер списка
    size_t BallChain::GetSize() {
        return size;
    }

    // Полная очистка списка, обнуление всех полей
    void BallChain::Clear() {
        Ball* current = head;
        while (current) {
            Ball* next = current->GetNext();
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
        totalRemoved = 0;
    }