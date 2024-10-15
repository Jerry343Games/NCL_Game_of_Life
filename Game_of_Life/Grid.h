#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int rows;
    int cols;
    std::vector<std::vector<int>> targetPattern; // 保存目标图案

public:
    // 构造函数
    Grid(int r, int c);

    // 获取某个位置的细胞
    Cell& getCell(int row, int col);

    // 设置某个位置的细胞状态
    void setCellState(int row, int col, int state);

    // 打印当前网格状态
    void printGrid() const;

    void randomizeCells(int numberOfCells);

    void evolve();

    void startRandomEvolution(int steps, int delay);

    int getRowCount() const;

    int getColCount() const;

};

#endif // GRID_H