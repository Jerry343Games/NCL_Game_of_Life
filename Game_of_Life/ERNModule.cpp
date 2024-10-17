#include "Grid.h"
#include "Pattern.h"
#include "PatternEnum.h"
#include "ERNModule.h"
#include "PatternDetector.h"
#include <algorithm> 
#include <random>
#include <iostream>

// Calculate the maximum grid cells required for a Pattern
int getMaxGrid(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int maxGridCells = 0;

    for (const Pattern& pattern : patterns) {
        int maxRow = 0;
        int maxCol = 0;

        // Iterate through the offsets in each Pattern to find the maximum row and column offset
        for (const auto& offset : pattern.offsets) {
            maxRow = std::max(maxRow, offset.first);
            maxCol = std::max(maxCol, offset.second);
        }

        // Calculate the minimum grid size required for the current Pattern (rows * columns)
        int gridCells = (maxRow + 1) * (maxCol + 1);  // +1 because indexing starts from 0
        maxGridCells = std::max(maxGridCells, gridCells);  // Keep the maximum grid size
    }

    return maxGridCells;
}

// Return the maximum row and column required for a given SequenceType
std::pair<int, int> getMaxRowCol(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int maxRow = 0;
    int maxCol = 0;

    for (const Pattern& pattern : patterns) {
        for (const auto& offset : pattern.offsets) {
            maxRow = std::max(maxRow, offset.first);  // Find the maximum row offset
            maxCol = std::max(maxCol, offset.second);  // Find the maximum column offset
        }
    }

    // Return a pair containing the maximum row and column
    return { maxRow + 1, maxCol + 1 };  // +1 because indexing starts from 0
}

// Get the minimum number of alive cells for a given SequenceType
int getMinCells(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int minCells = INT_MAX;

    for (const Pattern& pattern : patterns) {
        int cellCount = pattern.offsets.size();  // Calculate the number of alive cells in the current pattern
        minCells = std::min(minCells, cellCount);  // Keep the minimum number of cells
    }

    return minCells;
}

int findMinCellsForPattern(int rows, int cols, int minCells, SequenceType sequenceType) {
    // Create a grid with the specified dimensions
    Grid grid(rows, cols);
    PatternDetector detector(grid);

    // Get the target pattern sequence
    std::vector<Pattern> patternSequence = getPatternSequence(sequenceType);

    // Iterate and increase the number of cells until the pattern is found
    int currentCells = minCells;

    while (true) {
        std::cout << "Trying with " << currentCells << " alive cells." << std::endl;

        for (int attempt = 0; attempt < 10000; ++attempt) {
            // Randomly generate the current number of alive cells

            // Run pattern detection
            if (detector.detectPatternSequence(patternSequence, 100, currentCells)) {
                std::cout << "Found the target pattern cycle with " << currentCells << " alive cells!" << std::endl;
                return currentCells;  // Return the number of cells when the pattern is found
            }
        }

        // If the pattern isn't found after 100 attempts, increase the number of alive cells
        currentCells++;
    }
}
