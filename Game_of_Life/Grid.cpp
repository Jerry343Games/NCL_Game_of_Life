#include "Grid.h"
#include <iostream>
#include <cstdlib> // �������������
#include <ctime>   // ���������������
#include <iostream>
#include <windows.h>
#include <random>  // ʹ�� C++11 �������


// ���캯��
Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, std::vector<Cell>(cols)); // ��ʼ��ϸ��Ϊ��ϸ��
    std::srand(std::time(nullptr)); // ʹ�õ�ǰʱ����Ϊ���������
}

void Grid::randomizeCells(int numberOfCells) {
    // ʹ������豸���������ӣ�ȷ��ÿ��������ǲ�ͬ��
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, rows - 1);
    std::uniform_int_distribution<> disCol(0, cols - 1);

    int placedCells = 0;

    // ȷ�� numberOfCells ���������������
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


// ��ȡĳ��λ�õ�ϸ��
Cell& Grid::getCell(int row, int col) {
    return cells[row][col];
}

int Grid::getRowCount() const {
    return rows;
}

int Grid::getColCount() const {
    return cols;
}


// ����ĳ��λ�õ�ϸ��״̬
void Grid::setCellState(int row, int col, int state) {
    cells[row][col].setState(state);
}

// �ݻ�����
void Grid::evolve() {
    std::vector<std::vector<int>> newStates(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = 0;

            // ������Χ8������
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue; // �����Լ�

                    int newRow = i + di;
                    int newCol = j + dj;

                    // ���߽�
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                        liveNeighbors += cells[newRow][newCol].getState();
                    }
                }
            }

            // ����Conway's Game of Life�Ĺ������״̬
            if (cells[i][j].getState() == 1) {
                // ��ϸ��
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newStates[i][j] = 0; // ϸ������
                }
                else {
                    newStates[i][j] = 1; // ���ֻ�״̬
                }
            }
            else {
                // ��ϸ��
                if (liveNeighbors == 3) {
                    newStates[i][j] = 1; // ��ϸ����ɻ�ϸ��
                }
            }
        }
    }

    // ����ϸ��״̬
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].setState(newStates[i][j]);
        }
    }
}

// ��ӡ��ǰ����״̬
void Grid::printGrid() const {
    // ��ӡ���еĵ�
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
                std::cout << " "; // �ո��ʾ��ϸ��
            }
            std::cout << ".";
        }
        std::cout << std::endl;
    }
}

// ��װ������ݻ�����
void Grid::startRandomEvolution(int steps, int delay) {
    randomizeCells(100);
    for (int i = 0; i < steps; ++i) {
        // ����
        system("cls");

        // ��ӡ��ǰ����״̬
        printGrid();

        // �ݻ�����һ��
        evolve();

        // ��ͣһ��ʱ��
        Sleep(delay); // Windowsϵͳ����ͣdelay����
    }
}


