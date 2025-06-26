#include "BallChain.h"
#include <stdexcept>
#include <iostream>


Ball::Ball(int color) : color(color), next(nullptr) {}

// ������ ���������� ���� ������
int Ball::GetColor() { 
    return color; 
}

// ������ ���������� ��������� �� ��������� �������
Ball* Ball::GetNext() { 
    return next; 
}

// ������ ������������� ��������� �� ��������� �������
void Ball::SetNext(Ball* nextNode) { 
    next = nextNode; 
}

// ����� ��� ��������� ������ ��� ��������
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

    // �����������
    BallChain::BallChain() : head(nullptr), tail(nullptr), size(0), totalRemoved(0) {}

    // ����������
    BallChain::~BallChain() {
        Clear();
    }

    // ���������� �������� � ������
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

    // ����� ��������� ������
    void BallChain::PrintChain() {
        Ball* current = head;
        while (current) {
            std::cout << current->GetColor() << " ";
            current = current->GetNext();
        }
        std::cout << std::endl;
    }

    // �������� �������
    int BallChain::RemoveChains() {
        int removed = 0;
        size_t start, end;

        while (FindChainToRemove(start, end)) {
            size_t chainLength = end - start + 1;
            removed += chainLength;

            std::cout << "��������� �������: ";
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

            std::cout << "(������� " << start << "-" << end << ")" << std::endl;
            std::cout << "������� ����� ��������: ";
            PrintChain();

            totalRemoved += removed;
        }
        return removed;
    }

    // ������ ���������� ���-�� ��������� ��������� ������
    int BallChain::GetTotalRemoved() {
        return totalRemoved;
    }

    // ������ ���������� ������ ������
    size_t BallChain::GetSize() {
        return size;
    }

    // ������ ������� ������, ��������� ���� �����
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