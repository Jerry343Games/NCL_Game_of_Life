#include "Grid.h"
#include <iostream>
#include <cstdlib> // 用于随机数生成
#include <ctime>   // 用于设置随机种子
#include <iostream>
#include <windows.h>
#include <random>  // 使用 C++11 的随机库


// 构造函数
Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, std::vector<Cell>(cols)); // 初始化细胞为死细胞
    std::srand(std::time(nullptr)); // 使用当前时间作为随机数种子
}

void Grid::randomizeCells(int numberOfCells) {
    // 使用随机设备来生成种子，确保每次随机都是不同的
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, rows - 1);
    std::uniform_int_distribution<> disCol(0, cols - 1);

    int placedCells = 0;

    // 确保 numberOfCells 不超过网格的总数
    int totalCells = rows * cols;
    if (numberOfCells > totalCells) {
        numberOfCells = totalCells;
    }

    while (placedCells < numberOfCells) {
        int randomRow = disRow(gen);
        int randomCol = disCol(gen);

        if (cells[randomRow][randomCol].getState() == 0) {
            cells[randomRow][randomCol].setState(1);
            placedCells++;
        }
    }
}


// 获取某个位置的细胞
Cell& Grid::getCell(int row, int col) {
    return cells[row][col];
}

int Grid::getRowCount() const {
    return rows;
}

int Grid::getColCount() const {
    return cols;
}


// 设置某个位置的细胞状态
void Grid::setCellState(int row, int col, int state) {
    cells[row][col].setState(state);
}

// 演化步骤
void Grid::evolve() {
    std::vector<std::vector<int>> newStates(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = 0;

            // 遍历周围8个方向
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue; // 跳过自己

                    int newRow = i + di;
                    int newCol = j + dj;

                    // 检查边界
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                        liveNeighbors += cells[newRow][newCol].getState();
                    }
                }
            }

            // 根据Conway's Game of Life的规则更新状态
            if (cells[i][j].getState() == 1) {
                // 活细胞
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newStates[i][j] = 0; // 细胞死亡
                }
                else {
                    newStates[i][j] = 1; // 保持活状态
                }
            }
            else {
                // 死细胞
                if (liveNeighbors == 3) {
                    newStates[i][j] = 1; // 死细胞变成活细胞
                }
            }
        }
    }

    // 更新细胞状态
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].setState(newStates[i][j]);
        }
    }
}

// 打印当前网格状态
void Grid::printGrid() const {
    // 打印顶行的点
    for (int j = 0; j <= cols; ++j) {
        std::cout << ". ";
    }
    std::cout << std::endl;

    for (int i = 0; i < rows; ++i) {
        std::cout << ".";
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j].getState() == 1) {
                std::cout << "O";
            }
            else {
                std::cout << " "; // 空格表示死细胞
            }
            std::cout << ".";
        }
        std::cout << std::endl;
    }
}

// 封装的随机演化功能
void Grid::startRandomEvolution(int steps, int delay) {
    randomizeCells(100);
    for (int i = 0; i < steps; ++i) {
        // 清屏
        system("cls");

        // 打印当前网格状态
        printGrid();

        // 演化到下一代
        evolve();

        // 暂停一段时间
        Sleep(delay); // Windows系统下暂停delay毫秒
    }
}


