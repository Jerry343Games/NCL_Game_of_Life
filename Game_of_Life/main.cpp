#include "Grid.h"
#include "Pattern.h"
#include "PatternEnum.h"
#include "PatternDetector.h"
#include "ERNModule.h"
#include <iostream>
#include <thread>
#include <future>
#include <atomic>
#include <random>
#include <vector>
#include <tuple>


int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int rows = 30;
    int cols = 30;
    Grid grid(rows, cols);
    

    bool running = true;
    while (running) {
        std::cout << "\n============ Function Menu =============" << std::endl;
        std::cout << "1. Start random evolution" << std::endl;
        std::cout << "2. Searching pattern Block & Beehive" << std::endl;
        std::cout << "3. Searching pattern Blinker & Toad" << std::endl;
        std::cout << "4. Searching pattern Glider & Spaceship" << std::endl;
        std::cout << "5. Caculate ERN by SequenceType" << std::endl;
        std::cout << "6. Exit program" << std::endl;
        std::cout << "Please choose an option (1-6):\n";
        std::cout << "===========================================" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string loadChoice;
            std::cout << "Do you want to load the grid from a saved file? (y/n): ";
            std::cin >> loadChoice;
            if (loadChoice == "y" || loadChoice == "Y") {
                // Load the grid from a file
                std::string filename;
                std::cout << "Enter the filename (in Save/ folder, e.g., grid_state.txt): ";
                std::cin >> filename;
                grid.loadGridFromFile(filename);
            }
            else {
                // Randomize the grid
                grid.randomizeCells(100);
            }
            int steps, delay;
            std::cout << "Enter the number of steps for evolution: ";
            std::cin >> steps;
            grid.startRandomEvolution(steps, 200);
            break;
        }
        case 2: {
            PatternDetector detector(grid);
            detector.detectFirstPattern(SequenceType::BLOCK, SequenceType::BEEHIVE, 30, 30);
            break;
        }
        case 3: {
            PatternDetector detector(grid);
            detector.detectFirstPattern(SequenceType::TOAD, SequenceType::BLINKER, 30, 30);
            break;
        }
        case 4: {
            PatternDetector detector(grid);
            detector.detectFirstPattern(SequenceType::GLIDER, SequenceType::LWSS, 30, 30);
            break;
        }
        case 5: {
            std::string inputSequence;
            std::cout << "Enter the sequence name (TOAD, BLOCK, BEEHIVE, BLINKER, GLIDER, LWSS): ";//
            std::cin >> inputSequence;

            // Convert user input to SequenceType
            SequenceType sequence = getSequenceTypeFromInput(inputSequence);

            // Calculate the minimum number of cells
            int minCell = findMinCellsForPattern(getMaxRowCol(sequence).first, getMaxRowCol(sequence).second, 3, sequence);

            // Calculate the ERN
            int ERN = minCell + getMaxRowCol(sequence).first + getMaxRowCol(sequence).second;
            std::cout << "ERN(" << sequenceToString(sequence) << ") = " << getMaxRowCol(sequence).first << " + " << getMaxRowCol(sequence).second << " + " << minCell << " = " << ERN << std::endl;

            break;
        }
        case 6:
            running = false;
            break;
        default:
            std::cout << "Invalid choice, please enter a number between 1-6: ";
            break;
        }
    }

    return 0;
}
