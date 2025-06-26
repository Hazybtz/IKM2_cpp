#ifndef BALLCHAIN_H
#define BALLCHAIN_H

#include <cstddef> // Для size_t

// Класс узла списка (Node)
class Ball {
private:
    int color; // Поле данных (data)
    Ball* next; // Указатель на следующий элемент списка

public:
    Ball(int color);
    int GetColor();
    Ball* GetNext();
    void SetNext(Ball* nextNode);
};

// Класс односвязного списка
class BallChain {
private:
    Ball* head; // Указатель на 1 элемент списка
    Ball* tail; // Указатель на последний элемент списка
    size_t size; // Размер списка
    int totalRemoved; //Кол-во удаленных элементов списка

    bool FindChainToRemove(size_t& start, size_t& end);

public:
    BallChain();
    ~BallChain();
    void AddBall(int color);
    void PrintChain();
    int RemoveChains();
    int GetTotalRemoved();
    size_t GetSize();
    void Clear();
};

#endif