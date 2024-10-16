#include "PatternDetector.h"
#include "PatternEnum.h"
#include <iostream>
#include <algorithm>

PatternDetector::PatternDetector(Grid& grid) : grid(grid) {}



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
    bool patternLocked = false;

    while (true) {
        simulationCount++;
        grid.randomizeCells(startCells);

        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(grid);  // 保存初始状态

        for (int gen = 0; gen < generations; ++gen) {
            grid.evolve();
            simulationHistory.push_back(grid);  // 保存每次演化后的状态

            // 如果当前还没有锁定点，则全局搜索
            if (!patternLocked) {
                for (int i = 0; i < grid.getRowCount(); ++i) {
                    for (int j = 0; j < grid.getColCount(); ++j) {
                        if (isPatternAt(i, j, patternSequence[sequenceIndex])) {
                            lockedPosition = { i, j };  // 锁定当前位置
                            patternLocked = true;
                            sequenceIndex++;
                            break;
                        }
                    }
                    if (patternLocked) break;
                }
            }
            else {
                // 使用锁定点继续检测后续图案
                int lockedRow = lockedPosition.first;
                int lockedCol = lockedPosition.second;
                if (isPatternAt(lockedRow, lockedCol, patternSequence[sequenceIndex])) {
                    sequenceIndex++;
                    if (sequenceIndex == patternSequence.size()) {
                        std::cout << "成功检测到图案序列，在模拟 " << simulationCount
                            << " 中的第 " << gen + 1 << " 代" << std::endl;
                        for (size_t step = 0; step < simulationHistory.size(); ++step) {
                            std::cout << "第 " << step << " 代:" << std::endl;
                            simulationHistory[step].printGrid();
                        }
                        return true;
                    }
                }
                else {
                    patternLocked = false;  // 失败时重置锁定
                    sequenceIndex = 0;
                }
            }
        }
    }
    return false;
}