#include "Grid.h"
#include <iostream>
#include <cstdlib> // For random number generation
#include <ctime>   // For setting random seed
#include <iostream>
#include <windows.h>
#include <random>  // Using C++11 random library

// Constructor
Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, std::vector<Cell>(cols)); // Initialize cells as dead cells
    std::srand(std::time(nullptr)); // Use the current time as a seed for random numbers
}

void Grid::randomizeCells(int numberOfCells) {
    // Use random device to generate a seed, ensuring randomness in each run
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, rows - 1);
    std::uniform_int_distribution<> disCol(0, cols - 1);

    int placedCells = 0;

    // Ensure that numberOfCells does not exceed the total number of grid cells
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

// Get a cell at a specific position
Cell& Grid::getCell(int row, int col) {
    return cells[row][col];
}

int Grid::getRowCount() const {
    return rows;
}

int Grid::getColCount() const {
    return cols;
}

// Set the state of a cell at a specific position
void Grid::setCellState(int row, int col, int state) {
    cells[row][col].setState(state);
}

// Evolution step
void Grid::evolve() {
    std::vector<std::vector<int>> newStates(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = 0;

            // Iterate through the 8 surrounding directions
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue; // Skip the cell itself

                    int newRow = i + di;
                    int newCol = j + dj;

                    // Check boundaries
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                        liveNeighbors += cells[newRow][newCol].getState();
                    }
                }
            }

            // Update state based on Conway's Game of Life rules
            if (cells[i][j].getState() == 1) {
                // Live cell
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newStates[i][j] = 0; // Cell dies
                }
                else {
                    newStates[i][j] = 1; // Remain alive
                }
            }
            else {
                // Dead cell
                if (liveNeighbors == 3) {
                    newStates[i][j] = 1; // Dead cell becomes alive
                }
            }
        }
    }

    // Update cell states
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].setState(newStates[i][j]);
        }
    }
}

// Print the current grid state
void Grid::printGrid() const {
    // Print the top row of dots
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
                std::cout << " "; // Space represents a dead cell
            }
            std::cout << ".";
        }
        std::cout << std::endl;
    }
}

// Encapsulated random evolution function
void Grid::startRandomEvolution(int steps, int delay) {
    randomizeCells(100);
    for (int i = 0; i < steps; ++i) {
        // Clear the screen
        system("cls");

        // Print the current grid state
        printGrid();

        // Evolve to the next generation
        evolve();

        // Pause for a certain amount of time
        Sleep(delay); // Pause for delay milliseconds on Windows systems
    }
}
