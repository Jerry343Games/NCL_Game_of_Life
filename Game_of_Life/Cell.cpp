#include "Cell.h"
#include <iostream>

// Ĭ�Ϲ��캯��
Cell::Cell() : state(0) {}  // Ĭ������£�״̬Ϊ��ϸ��

// ����ʼ״̬�Ĺ��캯��
Cell::Cell(int initState) : state(initState) {}

// ��ȡϸ��״̬
int Cell::getState() const {
    return state;
}

// ����ϸ��״̬
void Cell::setState(int newState) {
    state = newState;
}

// ��ӡϸ��״̬
void Cell::printCell() const {
    std::cout << (state == 1 ? "Alive" : "Dead") << std::endl;
}
