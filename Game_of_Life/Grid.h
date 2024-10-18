#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"
#include <string>;
#include <iostream>
class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int rows;
    int cols;
    std::vector<std::vector<int>> targetPattern; // 保存目标图案

public:

    Grid(int r, int c);

    // get cell by pos
    Cell& getCell(int row, int col);

    // set cell by pos
    void setCellState(int row, int col, int state);

    void printGrid() const;

    void randomizeCells(int numberOfCells);

    void evolve();

    void startRandomEvolution(int steps, int delay);

    int getRowCount() const;

    int getColCount() const;

    void clearGrid();

    void saveGridToFile(const std::string& filename) const;

    void loadGridFromFile(const std::string& filename);


    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);

};

#endif