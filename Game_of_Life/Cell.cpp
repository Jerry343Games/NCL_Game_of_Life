#include "Cell.h"
#include <iostream>

// 默认构造函数
Cell::Cell() : state(0) {}  // 默认情况下，状态为死细胞

// 带初始状态的构造函数
Cell::Cell(int initState) : state(initState) {}

// 获取细胞状态
int Cell::getState() const {
    return state;
}

// 设置细胞状态
void Cell::setState(int newState) {
    state = newState;
}

// 打印细胞状态
void Cell::printCell() const {
    std::cout << (state == 1 ? "Alive" : "Dead") << std::endl;
}
