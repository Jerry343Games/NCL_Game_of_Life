#include "Grid.h"
#include "Pattern.h"
#include "PatternEnum.h"
#include "PatternDetector.h"
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
        std::cout << "2. Searching pattern" << std::endl;
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

            std::vector<Pattern> spaceshipSequence = {
                {getPatternOffsets(PatternType::GLIDER_0)},
                {getPatternOffsets(PatternType::GLIDER_1)},
                {getPatternOffsets(PatternType::GLIDER_2)},
                {getPatternOffsets(PatternType::GLIDER_3)}
            };

            PatternDetector detector(grid);
            detector.detectPatternSequence(spaceshipSequence, 30, 20);
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
