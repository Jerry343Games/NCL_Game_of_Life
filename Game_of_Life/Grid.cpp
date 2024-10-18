#include "Grid.h"
#include <iostream>
#include <cstdlib> // For random number generation
#include <ctime>   // For setting random seed
#include <iostream>
#include <windows.h>
#include <random>  // Using C++11 random library
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <conio.h>

// Constructor
Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, std::vector<Cell>(cols)); // Initialize cells as dead cells
    std::srand(std::time(nullptr)); // Use the current time as a seed for random numbers
}


// Method to save the grid's alive cell coordinates to a file
void Grid::saveGridToFile(const std::string& filename) const {
    // Ensure that the Save directory exists
    std::filesystem::create_directories("Save");

    // Open the file in the Save/ folder for writing
    std::ofstream file("Save/" + filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving: " << filename << std::endl;
        return;
    }

    // Iterate through the grid and save the coordinates of alive cells
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (cells[row][col].getState() == 1) {  // If the cell is alive
                file << row << " " << col << std::endl;  // Save the row and column of the alive cell
            }
        }
    }

    file.close();
    std::cout << "Grid saved to Save/" << filename << std::endl;
}

void Grid::loadGridFromFile(const std::string& filename) {
    // Open the file for reading
    std::ifstream file("Save/" + filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Clear the current grid state
    clearGrid();

    // Read the alive cell coordinates from the file and set them in the grid
    int row, col;
    while (file >> row >> col) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            cells[row][col].setState(1);  // Set the cell to alive
        }
        else {
            std::cerr << "Invalid cell coordinates in file: (" << row << ", " << col << ")" << std::endl;
        }
    }

    file.close();
    std::cout << "Grid loaded from Save/" << filename << std::endl;
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
    // Randomize the grid initially
    //randomizeCells(100);

    // Evolve the grid step by step
    for (int step = 0; step < steps; ++step) {
        // Clear the screen (Windows specific; adapt for other platforms)
        system("cls");

        printGrid();

        evolve();

        // Pause a while
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));

        // Check if the user wants to pause and save
        if (_kbhit()) {  
            char key = _getch();
            if (key == 'p' || key == 'P') {
                std::cout << "\nPaused.\nPress M back to Menu\nDo you want to save the grid state? (y/n):\n ";
                char saveChoice;
                std::cin >> saveChoice;

                if (saveChoice == 'y' || saveChoice == 'Y') {
                    // Save the grid state
                    std::string filename;
                    std::cout << "Enter the filename to save the grid (e.g., grid_state.txt): ";
                    std::cin >> filename;
                    saveGridToFile(filename);  // Save the grid to file
                }
                else if (saveChoice == 'm'||saveChoice == 'M')
                {
                    return;
                }

                std::cout << "Press any key to resume the evolution..." << std::endl;
                _getch();  
            }
        }
    }
}

void Grid::clearGrid() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].setState(0);  // Set all cells to dead (0)
        }
    }
}


std::ostream& operator<<(std::ostream& os, const Grid& grid) {
    // Print the first row of dots (border)
    for (int j = 0; j <= grid.cols; ++j) {
        os << ". ";
    }
    os << std::endl;

    // Print each row of cells with dots at the boundaries
    for (int i = 0; i < grid.rows; ++i) {
        os << ".";
        for (int j = 0; j < grid.cols; ++j) {
            
            os << (grid.cells[i][j].getState() == 1 ? "O" : " ") << ".";
        }
        os << std::endl;
    }

    return os;
}

