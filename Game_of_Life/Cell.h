#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int state; // 0表示死细胞，1表示活细胞

public:
    // 默认构造函数
    Cell();

    // 构造函数
    Cell(int initState);

    // 获取细胞状态
    int getState() const;

    // 设置细胞状态
    void setState(int newState);

    // 打印细胞状态
    void printCell() const;
};

#endif
