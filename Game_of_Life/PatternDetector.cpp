#include "PatternDetector.h"
#include "PatternEnum.h"
#include <iostream>
#include <algorithm>

PatternDetector::PatternDetector(Grid& grid) : grid(grid) {}

bool PatternDetector::detectPattern(const Pattern& pattern, int generations, int startCells) {
    int simulationCount = 0;

    // Continue random simulations until a matching pattern is found
    while (true) {
        simulationCount++;
        grid.randomizeCells(startCells);

        // To store the state of each simulation
        std::vector<Grid> simulationHistory;

        // Save the initial state
        simulationHistory.push_back(grid);

        for (int gen = 0; gen < generations; ++gen) {
            // Evolve to the next generation
            grid.evolve();

            // Save the evolved state
            simulationHistory.push_back(grid);

            // Check if the matching pattern is found
            if (checkPattern(pattern)) {
                std::cout << "Pattern found in simulation " << simulationCount << " at generation " << gen + 1 << ":" << std::endl;

                // Print the full simulation process
                for (int step = 0; step <= gen + 1; ++step) {
                    std::cout << "Generation " << step << ":" << std::endl;
                    simulationHistory[step].printGrid();
                }

                return true;
            }
        }
    }
}


bool PatternDetector::checkPattern(const Pattern& pattern) {
    for (int i = 0; i < grid.getRowCount(); ++i) {
        for (int j = 0; j < grid.getColCount(); ++j) {
            if (isPatternAt(i, j, pattern)) {
                return true;
            }
        }
    }
    return false;
}

bool PatternDetector::isPatternAt(int row, int col, const Pattern& pattern) {
    // Ensure that all offset positions of the pattern are live cells
    for (const auto& offset : pattern.offsets) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;

        // Check boundary conditions
        if (newRow < 0 || newRow >= grid.getRowCount() || newCol < 0 || newCol >= grid.getColCount()) {
            return false;
        }

        // Check if the corresponding position is a live cell
        if (grid.getCell(newRow, newCol).getState() == 0) {
            return false;
        }
    }

    // Ensure that adjacent cells outside the pattern are dead cells
    for (const auto& offset : pattern.offsets) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;

        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue;
                int neighborRow = newRow + di;
                int neighborCol = newCol + dj;

                // Check if neighboring cells are dead and not part of the pattern
                if (neighborRow >= 0 && neighborRow < grid.getRowCount() && neighborCol >= 0 && neighborCol < grid.getColCount()) {
                    bool isInPattern = false;
                    for (const auto& innerOffset : pattern.offsets) {
                        if (neighborRow == row + innerOffset.first && neighborCol == col + innerOffset.second) {
                            isInPattern = true;
                            break;
                        }
                    }
                    if (!isInPattern && grid.getCell(neighborRow, neighborCol).getState() == 1) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}
