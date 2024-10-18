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
            maxRow = std::max(maxRow, offset.first); 
            maxCol = std::max(maxCol, offset.second);  
        }
    }

    // Return a pair containing the maximum row and column
    return { maxRow + 1, maxCol + 1 };
}

// Get the minimum number of alive cells for a given SequenceType
int getMinCells(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int minCells = INT_MAX;

    for (const Pattern& pattern : patterns) {
        int cellCount = pattern.offsets.size(); 
        minCells = std::min(minCells, cellCount);  // Keep the minimum number of cells
    }

    return minCells;
}

int findMinCellsForPattern(int rows, int cols, int minCells, SequenceType sequenceType) {

    Grid grid(rows, cols);
    PatternDetector detector(grid);

    std::vector<Pattern> patternSequence = getPatternSequence(sequenceType);
    size_t patternCount = patternSequence.size();

    int currentCells = minCells;

    while (true) {
        std::cout << "Trying with " << currentCells << " alive cells." << std::endl;

        for (int attempt = 0; attempt < 500000; ++attempt) {
            grid.clearGrid();
            grid.randomizeCells(currentCells);

            std::vector<Grid> evolutionSteps;
            evolutionSteps.push_back(grid);

            // Run evolution for a fixed number of generations
            for (int gen = 0; gen < 20; ++gen) {
                grid.evolve();
                evolutionSteps.push_back(grid);

                // Loop through each possible starting point in the pattern sequence
                for (size_t startPatternIndex = 0; startPatternIndex < patternCount; ++startPatternIndex) {
                    bool fullCycleMatched = true;

                    // Check the full pattern cycle
                    for (size_t step = 0; step < patternCount; ++step) {
                        size_t currentPatternIndex = (startPatternIndex + step) % patternCount;

                        // If the current pattern is not detected, break the loop and continue with the next starting pattern
                        if (!detector.isPatternDetectedInGrid(patternSequence[currentPatternIndex])) {
                            fullCycleMatched = false;
                            break;
                        }

                        // Evolve the grid further for each pattern check
                        if (step < patternCount - 1) {
                            grid.evolve();
                            evolutionSteps.push_back(grid);
                        }
                    }

                    // If a full cycle is matched, output the results
                    if (fullCycleMatched) {
                        std::cout << "Full pattern cycle detected starting from step " << startPatternIndex
                            << " in attempt " << attempt + 1 << " with " << currentCells << " alive cells!" << std::endl;

                        std::cout << "Initial grid state for attempt " << attempt + 1 << ":" << std::endl;
                        std::cout << evolutionSteps[0];  

                        // Print each evolution step
                        for (int i = 1; i < evolutionSteps.size(); ++i) {
                            std::cout << "Grid after generation " << i << ":" << std::endl;
                            std::cout << evolutionSteps[i]; 
                        }

                        return currentCells;
                    }
                }
            }
        }

        // increase the number of trying alive cells if over 1,000,000 times attempt
        currentCells++;
    }
}
