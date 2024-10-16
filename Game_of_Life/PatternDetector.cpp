#include "PatternDetector.h"
#include "PatternEnum.h"
#include <iostream>
#include <algorithm>

PatternDetector::PatternDetector(Grid& grid) : grid(grid) {}

bool PatternDetector::detectPattern(const Pattern& pattern, int generations, int startCells) {
    int simulationCount = 0;

    // 继续随机模拟，直到找到匹配的图案
    while (true) {
        simulationCount++;
        grid.randomizeCells(startCells);

        // 用于保存每次模拟的状态
        std::vector<Grid> simulationHistory;

        // 保存初始状态
        simulationHistory.push_back(grid);

        for (int gen = 0; gen < generations; ++gen) {
            // 演化到下一代
            grid.evolve();

            // 保存演化后的状态
            simulationHistory.push_back(grid);

            // 检查是否找到匹配的图案
            if (checkPattern(pattern)) {
                std::cout << "Pattern found in simulation " << simulationCount << " at generation " << gen + 1 << ":" << std::endl;

                // 打印完整的模拟过程
                for (int step = 0; step <= gen + 1; ++step) {
                    std::cout << "Generation " << step << ":" << std::endl;
                    simulationHistory[step].printGrid();
                }

                return true;
            }
        }
    }
}


bool PatternDetector::checkPattern(const Pattern& pattern) {
    for (int i = 0; i < grid.getRowCount(); ++i) {
        for (int j = 0; j < grid.getColCount(); ++j) {
            if (isPatternAt(i, j, pattern)) {
                return true;
            }
        }
    }
    return false;
}

bool PatternDetector::isPatternAt(int row, int col, const Pattern& pattern) {
    // 确保图案的所有偏移位置都是活细胞
    for (const auto& offset : pattern.offsets) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;

        // 检查边界条件
        if (newRow < 0 || newRow >= grid.getRowCount() || newCol < 0 || newCol >= grid.getColCount()) {
            return false;
        }

        // 检查对应位置是否是活细胞
        if (grid.getCell(newRow, newCol).getState() == 0) {
            return false;
        }
    }

    // 确保图案之外的相邻细胞都是死细胞
    for (const auto& offset : pattern.offsets) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;

        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue;
                int neighborRow = newRow + di;
                int neighborCol = newCol + dj;

                // 检查邻近的细胞是否是死细胞，并且不在图案标记内
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

    while (true) {
        simulationCount++;
        grid.randomizeCells(startCells);

        // 用于保存模拟的状态
        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(grid);  // 保存初始状态

        for (int gen = 0; gen < generations; ++gen) {
            grid.evolve();
            simulationHistory.push_back(grid);  // 保存每次演化后的状态

            // 检查是否找到了序列中的下一个图案
            if (checkPattern(patternSequence[sequenceIndex])) {
                sequenceIndex++;
                if (sequenceIndex == patternSequence.size()) {
                    // 成功检测到完整的图案序列
                    std::cout << "成功检测到图案序列，在模拟 " << simulationCount
                        << " 中的第 " << gen + 1 << " 代" << std::endl;

                    // 打印完整的模拟过程
                    for (size_t step = 0; step < simulationHistory.size(); ++step) {
                        std::cout << "第 " << step << " 代:" << std::endl;
                        simulationHistory[step].printGrid();
                    }

                    return true;
                }
            }
            else {
                sequenceIndex = 0;  // 如果检测失败，重置序列索引
            }
        }
    }
    return false;
}
