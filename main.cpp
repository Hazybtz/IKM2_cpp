#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "BallChain.h"

// �������� �� �������� ����� �����, ��������� ����������
int IntegerInput() {
    int value;
    while (true) {
        std::string input;
        getline(std::cin, input);
        
        try {
            value = std::stoi(input);
            return value;
        } catch (...) {
            std::cerr << "������! ����������, ������� ����� �����.\n";
        }
    }
}

// ������ ����, �������� ������
void RunGame() {
    BallChain chain;
    std::cout << "=== ���� '������' ===\n";

    while (true) {
        std::cout << "\n1. �������� ������\n"
                  << "2. ������� �������\n"
                  << "3. �������� ������� �������\n"
                  << "4. ������ ������\n"
                  << "5. �����\n"
                  << "�������� ��������: ";

        int choice = IntegerInput();

        switch (choice) {
            // ���������� ����� � ������, � ���������� ����������
            case 1: {
                std::cout << "������� ����� ������� (0-9 ����� ������): ";
                std::string input;
                getline(std::cin, input);
                
                std::istringstream iss(input);
                int color;
                try {
                    while (iss >> color) {
                        if (color < 0 || color > 9) {
                            throw std::out_of_range("���� ������ ���� �� 0 �� 9");
                        }
                        chain.AddBall(color);
                    }
                }
                catch (std::out_of_range& e) {
                    std::cerr << "������: " << e.what() << "\n";
                }
                std::cout << "������� �������: ";
                chain.PrintChain();
                break;
            }
             // �������� ����� �� ������
            case 2: {
                int removed = chain.RemoveChains();
                std::cout << "������� �������: ";
                chain.PrintChain();
                if (removed > 0) {
                    std::cout << "����� ������� �������: " << removed << std::endl;
                } else {
                    std::cout << "��� ������� ��� ��������.\n";
                }
                break;
            }
            // ����� �������� ������
            case 3:
                std::cout << "������� �������: ";
                chain.PrintChain();
                break;
            // ������� ������, ������ ���� ������
            case 4:
                chain.Clear();
                std::cout << "���� ������ ������.\n";
                break;
            // ����� �� ���������
            case 5:
                return;
            default:
                std::cout << "�������� �����. ���������� �����.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian"); // ����������� �������� �����
    RunGame();
    return 0;
}