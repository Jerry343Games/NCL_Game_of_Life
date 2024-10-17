#include "Grid.h"
#include "Pattern.h"
#include "PatternEnum.h"
#include "ERNModule.h"
#include "PatternDetector.h"
#include <algorithm> 
#include <random>
#include <iostream>


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

    // Get the target pattern sequence (we'll only check the first pattern in this example)
    std::vector<Pattern> patternSequence = getPatternSequence(sequenceType);

    // Iterate and increase the number of cells until the pattern is found
    int currentCells = minCells;

    while (true) {
        std::cout << "Trying with " << currentCells << " alive cells." << std::endl;

        for (int attempt = 0; attempt < 1000000; ++attempt) {
            // Clear the grid before starting a new attempt to avoid leftover cells
            grid.clearGrid();

            // Randomly generate the current number of alive cells
            grid.randomizeCells(currentCells);

            // Store the initial grid state for this attempt
            std::vector<Grid> evolutionSteps;  // Vector to store each grid state
            evolutionSteps.push_back(grid);    // Store the initial state

            // Run evolution for a fixed number of generations
            for (int gen = 0; gen < 20; ++gen) {
                grid.evolve();
                evolutionSteps.push_back(grid);  // Store each evolved state

                // Check if the current grid matches the target pattern
                if (detector.isPatternDetectedInGrid(patternSequence[0])) {
                    std::cout << "Found the target pattern in attempt " << attempt + 1 << " with " << currentCells << " alive cells!" << std::endl;

                    // Print the initial state of the grid
                    std::cout << "Initial grid state for attempt " << attempt + 1 << ":" << std::endl;
                    evolutionSteps[0].printGrid();  // Print the initial grid state

                    // Print each evolution step
                    for (int i = 1; i < evolutionSteps.size(); ++i) {
                        std::cout << "Grid after generation " << i << ":" << std::endl;
                        evolutionSteps[i].printGrid();  // Print each evolved state
                    }

                    return currentCells;  // Return the number of cells when the pattern is found
                }
            }
        }

        // If the pattern isn't found after 100 attempts, increase the number of alive cells
        currentCells++;
    }
}