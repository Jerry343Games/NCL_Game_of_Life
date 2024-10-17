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
        std::cout << "====== Conway's Game of Life Menu ======" << std::endl;
        std::cout << "1. Start random evolution" << std::endl;
        std::cout << "2. Searching pattern Block & Beehive" << std::endl;
        std::cout << "3. Searching pattern Blinker & Toad" << std::endl;
        std::cout << "4. Searching pattern Glider & Spaceship" << std::endl;
        std::cout << "5. Caculate ERN by SequenceType" << std::endl;
        std::cout << "6. Exit program" << std::endl;
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
            PatternDetector detector(grid);
            detector.detectFirstPattern(getPatternSequence(SequenceType::BLOCK), getPatternSequence(SequenceType::BEEHIVE), 30, 30);

            break;
        }
        case 3: {
            PatternDetector detector(grid);
            detector.detectFirstPattern(getPatternSequence(SequenceType::TOAD), getPatternSequence(SequenceType::BLINKER), 30, 30);

            break;
        }
        case 4: {
            PatternDetector detector(grid);
            detector.detectFirstPattern(getPatternSequence(SequenceType::GLIDER), getPatternSequence(SequenceType::SPACESHIP), 30, 30);
            break;
        }
        case 5: {
            SequenceType glider = SequenceType::TOAD;
            int gliderMaxCells = getMaxGrid(glider);
            int gliderMinCells = getMinCells(glider);

            std::cout << "Glider最大活细胞数: " << gliderMaxCells << std::endl;
            std::cout << "Glider最小活细胞数: " << gliderMinCells << std::endl;

            SequenceType spaceship = SequenceType::SPACESHIP;
            int spaceshipMaxCells = getMaxGrid(spaceship);
            int spaceshipMinCells = getMinCells(spaceship);

            std::cout << "Spaceship最大活细胞数: " << spaceshipMaxCells << std::endl;
            std::cout << "Spaceship最小活细胞数: " << spaceshipMinCells << std::endl;
            running = false;
            break;
        }
        case 6:
            running = false;
            break;
        default:
            std::cout << "Invalid choice, please enter a number between 1-3." << std::endl;
            break;
        }
    }

    return 0;
}
