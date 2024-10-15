#include "Grid.h"
#include "Pattern.h"
#include "PatternEnum.h"
#include "PatternDetector.h"
#include <iostream>
#include <thread>
#include <future>
#include <atomic>
#include <random>

bool detectPatternWithThread(PatternDetector& detector, const Pattern& pattern, int generations, int startCells, std::atomic<bool>& stopFlag, std::string& patternName) {
    int simulationCount = 0;

    // Use random device to generate a seed, ensuring each thread is independent
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, detector.getGrid().getRowCount() - 1);
    std::uniform_int_distribution<> disCol(0, detector.getGrid().getColCount() - 1);

    while (!stopFlag) {
        simulationCount++;
        detector.getGrid().randomizeCells(startCells);

        // Save the initial state
        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(detector.getGrid());

        for (int gen = 0; gen < generations; ++gen) {
            detector.getGrid().evolve();
            simulationHistory.push_back(detector.getGrid());

            if (detector.checkPattern(pattern)) {
                stopFlag = true;  // Set the stop flag to stop other threads

                // Print the process where the pattern was found
                std::cout << "Pattern (" << patternName << ") found in simulation " << simulationCount << " at generation " << gen + 1 << std::endl;
                for (size_t i = 0; i < simulationHistory.size(); ++i) {
                    std::cout << "Generation " << i << ":" << std::endl;
                    simulationHistory[i].printGrid();
                }

                return true;
            }

            // Stop the current thread if another thread found the target
            if (stopFlag) {
                return false;
            }
        }
    }
    return false;
}

void FindWithTwoPattern(PatternType pattern1Type, PatternType pattern2Type, Grid grid) {
    // Define two patterns for detection
    //PatternType pattern1Type = PatternType::TOAD;
    //PatternType pattern2Type = PatternType::BEEHIVE;

    // Get the offsets for both patterns
    Pattern pattern1;
    pattern1.offsets = getPatternOffsets(pattern1Type);

    Pattern pattern2;
    pattern2.offsets = getPatternOffsets(pattern2Type);

    PatternDetector detector1(grid);
    PatternDetector detector2(grid);

    std::atomic<bool> stopFlag(false);

    std::string pattern1Name = patternTypeToString(pattern1Type);
    std::string pattern2Name = patternTypeToString(pattern2Type);

    // Use threads to concurrently detect both patterns
    std::future<bool> future1 = std::async(std::launch::async, detectPatternWithThread, std::ref(detector1), pattern1, 20, 30, std::ref(stopFlag), std::ref(pattern1Name));
    std::future<bool> future2 = std::async(std::launch::async, detectPatternWithThread, std::ref(detector2), pattern2, 20, 30, std::ref(stopFlag), std::ref(pattern2Name));

    // Wait for any one pattern to be found to stop
    if (future1.wait_for(std::chrono::milliseconds(100)) == std::future_status::ready) {
        future1.get();
    }
    else if (future2.wait_for(std::chrono::milliseconds(100)) == std::future_status::ready) {
        future2.get();
    }
}

int main() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int rows = 30;
    int cols = 30;
    Grid grid(rows, cols);

    bool running = true;
    while (running) {
        // Print menu
        std::cout << "====== Conway's Game of Life Menu ======" << std::endl;
        std::cout << "1. Start random evolution" << std::endl;
        std::cout << "2. Pending" << std::endl;
        std::cout << "3. Exit program" << std::endl;
        std::cout << "Please choose an option (1-3):\n";

        int choice;
        std::cin >> choice;


        switch (choice) {
        case 1: {
            int steps, delay;
            std::cout << "Enter the number of steps for evolution: ";
            std::cin >> steps;
            grid.startRandomEvolution(steps, 200);
            break;
        }
        case 2: {

            FindWithTwoPattern(PatternType::TOAD, PatternType::BEEHIVE, grid);

            break;
        }
        case 3:
            running = false;
            break;
        default:
            std::cout << "Invalid choice, please enter a number between 1-3." << std::endl;
            break;
        }
    }

    return 0;
}
