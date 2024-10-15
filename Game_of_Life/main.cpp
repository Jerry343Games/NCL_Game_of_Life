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

    // 使用随机设备来生成种子，确保每个线程都是独立的
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, detector.getGrid().getRowCount() - 1);
    std::uniform_int_distribution<> disCol(0, detector.getGrid().getColCount() - 1);

    while (!stopFlag) {
        simulationCount++;
        detector.getGrid().randomizeCells(startCells);

        // 保存初始状态
        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(detector.getGrid());

        for (int gen = 0; gen < generations; ++gen) {
            detector.getGrid().evolve();
            simulationHistory.push_back(detector.getGrid());

            if (detector.checkPattern(pattern)) {
                stopFlag = true;  // 设置停止标志，停止其他线程

                // 打印找到的图案过程
                std::cout << "Pattern (" << patternName << ") found in simulation " << simulationCount << " at generation " << gen + 1 << std::endl;
                for (size_t i = 0; i < simulationHistory.size(); ++i) {
                    std::cout << "Generation " << i << ":" << std::endl;
                    simulationHistory[i].printGrid();
                }

                return true;
            }

            // 如果另一个线程找到目标，则停止当前线程
            if (stopFlag) {
                return false;
            }
        }
    }
    return false;
}

void FindWithTwoPattern(PatternType pattern1Type, PatternType pattern2Type ,Grid grid) {
    // 定义两个图案进行检测
    //PatternType pattern1Type = PatternType::TOAD;
    //PatternType pattern2Type = PatternType::BEEHIVE;

    // 获取两个图案的偏移量
    Pattern pattern1;
    pattern1.offsets = getPatternOffsets(pattern1Type);

    Pattern pattern2;
    pattern2.offsets = getPatternOffsets(pattern2Type);

    PatternDetector detector1(grid);
    PatternDetector detector2(grid);

    std::atomic<bool> stopFlag(false);

    std::string pattern1Name = patternTypeToString(pattern1Type);
    std::string pattern2Name = patternTypeToString(pattern2Type);

    // 使用线程并发检测两个图案
    std::future<bool> future1 = std::async(std::launch::async, detectPatternWithThread, std::ref(detector1), pattern1, 20, 30, std::ref(stopFlag), std::ref(pattern1Name));
    std::future<bool> future2 = std::async(std::launch::async, detectPatternWithThread, std::ref(detector2), pattern2, 20, 30, std::ref(stopFlag), std::ref(pattern2Name));

    // 等待任意一个图案找到即可停止
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
        // 打印菜单
        std::cout << "====== Conway's Game of Life Menu ======" << std::endl;
        std::cout << "1. 开始随机演化" << std::endl;
        std::cout << "2. 待定" << std::endl;
        std::cout << "3. 退出程序" << std::endl;
        std::cout << "请选择一个选项（1-3）：\n";

        int choice;
        std::cin >> choice;


        switch (choice) {
        case 1: {
            int steps, delay;
            std::cout << "请输入演化的步数：";
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
            std::cout << "无效的选择，请输入1-3之间的数字。" << std::endl;
            break;
        }
    }

    return 0;
}
