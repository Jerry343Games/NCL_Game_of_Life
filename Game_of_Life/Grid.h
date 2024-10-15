#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int rows;
    int cols;
    std::vector<std::vector<int>> targetPattern; // ����Ŀ��ͼ��

public:
    // ���캯��
    Grid(int r, int c);

    // ��ȡĳ��λ�õ�ϸ��
    Cell& getCell(int row, int col);

    // ����ĳ��λ�õ�ϸ��״̬
    void setCellState(int row, int col, int state);

    // ��ӡ��ǰ����״̬
    void printGrid() const;

    void randomizeCells(int numberOfCells);

    void evolve();

    void startRandomEvolution(int steps, int delay);

    int getRowCount() const;

    int getColCount() const;

};

#endif // GRID_H