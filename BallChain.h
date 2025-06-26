#ifndef BALLCHAIN_H
#define BALLCHAIN_H

#include <cstddef> // ��� size_t

// ����� ���� ������ (Node)
class Ball {
private:
    int color; // ���� ������ (data)
    Ball* next; // ��������� �� ��������� ������� ������

public:
    Ball(int color);
    int GetColor();
    Ball* GetNext();
    void SetNext(Ball* nextNode);
};

// ����� ������������ ������
class BallChain {
private:
    Ball* head; // ��������� �� 1 ������� ������
    Ball* tail; // ��������� �� ��������� ������� ������
    size_t size; // ������ ������
    int totalRemoved; //���-�� ��������� ��������� ������

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