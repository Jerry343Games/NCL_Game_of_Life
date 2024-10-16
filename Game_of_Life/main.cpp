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

// 检测图案的线程函数
bool detectPatternWithThread(PatternDetector& detector, const Pattern& pattern, int generations, int startCells, std::atomic<bool>& stopFlag, std::string& patternName) {
    int simulationCount = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, detector.getGrid().getRowCount() - 1);
    std::uniform_int_distribution<> disCol(0, detector.getGrid().getColCount() - 1);

    while (!stopFlag) {
        simulationCount++;
        detector.getGrid().randomizeCells(startCells);

        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(detector.getGrid());

        for (int gen = 0; gen < generations; ++gen) {
            detector.getGrid().evolve();
            simulationHistory.push_back(detector.getGrid());

            if (detector.checkPattern(pattern)) {
                stopFlag = true;
                std::cout << "Pattern (" << patternName << ") found in simulation " << simulationCount << " at generation " << gen + 1 << std::endl;
                for (size_t i = 0; i < simulationHistory.size(); ++i) {
                    std::cout << "Generation " << i << ":" << std::endl;
                    simulationHistory[i].printGrid();
                }
                return true;
            }

            if (stopFlag) {
                return false;
            }
        }
    }
    return false;
}

// 使用可变参数模板，接收任意数量的图案类型
template <typename... PatternTypes>
void FindWithPatterns(Grid grid, PatternTypes... patternTypes) {
    std::atomic<bool> stopFlag(false);
    std::vector<std::future<bool>> futures;

    auto detectPattern = [&](PatternType patternType) {
        Pattern pattern;
        pattern.offsets = getPatternOffsets(patternType);
        PatternDetector detector(grid);
        std::string patternName = patternTypeToString(patternType);
        futures.push_back(std::async(std::launch::async, detectPatternWithThread, std::ref(detector), pattern, 20, 30, std::ref(stopFlag), std::ref(patternName)));
        };

    // 使用fold expression展开图案参数，并启动线程
    (detectPattern(patternTypes), ...);

    // 等待任何一个图案被检测到
    for (auto& future : futures) {
        future.wait();
    }
}

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
            // 在这里传递任意数量的PatternType
            FindWithPatterns(grid, PatternType::TOAD_0, PatternType::TOAD_1, PatternType::BEEHIVE);
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
