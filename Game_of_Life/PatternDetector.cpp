#include "PatternDetector.h"
#include "PatternEnum.h"
#include <iostream>
#include <algorithm>
#include <future>
#include <iostream>

PatternDetector::PatternDetector(Grid& grid) : grid(grid) {}
bool isDetected = false;
bool isPrinted = false;

bool PatternDetector::isPatternAt(int row, int col, const Pattern& pattern) {
    // Ensure that all the offset positions in the pattern are alive cells
    for (const auto& offset : pattern.offsets) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;

        // Check boundary conditions
        if (newRow < 0 || newRow >= grid.getRowCount() || newCol < 0 || newCol >= grid.getColCount()) {
            return false;
        }

        // Check if the corresponding position is an alive cell
        if (grid.getCell(newRow, newCol).getState() == 0) {
            return false;
        }
    }

    // Ensure that the neighboring cells outside the pattern are dead cells
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

bool PatternDetector::detectPatternSequence(const std::vector<Pattern>& patternSequence, int generations, int startCells) {
    int sequenceIndex = 0;
    int simulationCount = 0;
    bool patternLocked = false;
    //isDetected = false;

    while (true && !isDetected) {
        simulationCount++;
        grid.randomizeCells(startCells);

        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(grid);  // Save initial state

        for (int gen = 0; gen < generations; ++gen) {
            grid.evolve();
            simulationHistory.push_back(grid);  // Save state after each evolution

            // If no locked point yet, perform a global search
            if (!patternLocked) {
                for (int i = 0; i < grid.getRowCount(); ++i) {
                    for (int j = 0; j < grid.getColCount(); ++j) {
                        if (isPatternAt(i, j, patternSequence[sequenceIndex])) {
                            lockedPosition = { i, j };  // Lock current position
                            patternLocked = true;
                            sequenceIndex++;
                            break;
                        }
                    }
                    if (patternLocked) break;
                }
            }
            else if (!isDetected) {
                // Continue detecting the next pattern using the locked point
                int lockedRow = lockedPosition.first;
                int lockedCol = lockedPosition.second;
                if (isPatternAt(lockedRow, lockedCol, patternSequence[sequenceIndex]) && !isDetected) {
                    sequenceIndex++;
                    if (sequenceIndex == patternSequence.size() && !isDetected) {
                        isDetected = true;
                        if (!isPrinted) {
                            std::cout << "Successfully detected the pattern sequence in simulation " << simulationCount
                                << " at generation " << gen + 1 << std::endl;
                            for (size_t step = 0; step < simulationHistory.size(); ++step) {
                                if (!isPrinted) {
                                    std::cout << "Generation " << step << ":" << std::endl;
                                    simulationHistory[step].printGrid();
                                }
                            }
                            isPrinted = true;
                            return true;
                        }
                    }
                }
                else {
                    patternLocked = false;  // Reset lock if detection fails
                    sequenceIndex = 0;
                }
            }
        }
    }
    isDetected = false;
    return false;
}

bool PatternDetector::detectFirstPattern(SequenceType sequenceType1, SequenceType sequenceType2, int generations, int startCells) {
    // Get the pattern sequences for both input SequenceTypes
    std::vector<Pattern> sequence1 = getPatternSequence(sequenceType1);
    std::vector<Pattern> sequence2 = getPatternSequence(sequenceType2);

    // Save the initial grid state before the simulation
    Grid initialGrid = grid;  // Assuming you have a proper copy constructor for Grid

    // Use async to run both pattern detections in parallel
    auto future1 = std::async(&PatternDetector::detectPatternSequence, this, sequence1, generations, startCells);
    auto future2 = std::async(&PatternDetector::detectPatternSequence, this, sequence2, generations, startCells);




    // Check which pattern was detected first
    bool result1 = future1.get();
    bool result2 = future2.get();

    if (result1) {
        std::cout << "Pattern Sequence " << sequenceToString(sequenceType1) << " detected first!" << std::endl;
        // Save the initial grid state to a file when detection is successful
        initialGrid.saveGridToFile("AutoSave_" + sequenceToString(sequenceType1) + ".txt");
        return true;
    }
    if (result2) {
        std::cout << "Pattern Sequence " << sequenceToString(sequenceType2) << " detected first!" << std::endl;
        // Save the initial grid state to a file when detection is successful
        initialGrid.saveGridToFile("AutoSave_" + sequenceToString(sequenceType2) + ".txt");
        return false;
    }

    std::cout << "Neither pattern detected!" << std::endl;

    return false;
}




bool PatternDetector::isPatternDetectedInGrid(const Pattern& pattern) {
    for (int row = 0; row < grid.getRowCount(); ++row) {
        for (int col = 0; col < grid.getColCount(); ++col) {
            if (isPatternAt(row, col, pattern)) {
                return true;  // Pattern found
            }
        }
    }
    return false;  // Pattern not found
}
