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
    // ȷ��ͼ��������ƫ��λ�ö��ǻ�ϸ��
    for (const auto& offset : pattern.offsets) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;

        // ���߽�����
        if (newRow < 0 || newRow >= grid.getRowCount() || newCol < 0 || newCol >= grid.getColCount()) {
            return false;
        }

        // ����Ӧλ���Ƿ��ǻ�ϸ��
        if (grid.getCell(newRow, newCol).getState() == 0) {
            return false;
        }
    }

    // ȷ��ͼ��֮�������ϸ��������ϸ��
    for (const auto& offset : pattern.offsets) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;

        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue;
                int neighborRow = newRow + di;
                int neighborCol = newCol + dj;

                // ����ڽ���ϸ���Ƿ�����ϸ�������Ҳ���ͼ�������
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

    while (true&&!isDetected) {
        simulationCount++;
        grid.randomizeCells(startCells);

        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(grid);  // �����ʼ״̬

        for (int gen = 0; gen < generations; ++gen) {
            grid.evolve();
            simulationHistory.push_back(grid);  // ����ÿ���ݻ����״̬

            // �����ǰ��û�������㣬��ȫ������
            if (!patternLocked) {
                for (int i = 0; i < grid.getRowCount(); ++i) {
                    for (int j = 0; j < grid.getColCount(); ++j) {
                        if (isPatternAt(i, j, patternSequence[sequenceIndex])) {
                            lockedPosition = { i, j };  // ������ǰλ��
                            patternLocked = true;
                            sequenceIndex++;
                            break;
                        }
                    }
                    if (patternLocked) break;
                }
            }
            else if(!isDetected) {
                // ʹ�����������������ͼ��
                int lockedRow = lockedPosition.first;
                int lockedCol = lockedPosition.second;
                if (isPatternAt(lockedRow, lockedCol, patternSequence[sequenceIndex])&&!isDetected) {
                    sequenceIndex++;
                    if (sequenceIndex == patternSequence.size()&&!isDetected) {
                        isDetected = true;
                        if (!isPrinted)
                        {
                            std::cout << "�ɹ���⵽ͼ�����У���ģ�� " << simulationCount
                                << " �еĵ� " << gen + 1 << " ��" << std::endl;
                            for (size_t step = 0; step < simulationHistory.size(); ++step) {
                                if (!isPrinted) {
                                    std::cout << "�� " << step << " ��:" << std::endl;
                                    simulationHistory[step].printGrid();
                                }
                            }
                            isPrinted = true;
                            return true;
                        }
                    }
                }
                else {
                    patternLocked = false;  // ʧ��ʱ��������
                    sequenceIndex = 0;
                }
            }
        }
    }
    isDetected = false;
    return false;
}


bool PatternDetector::detectFirstPattern(const std::vector<Pattern>& sequence1, const std::vector<Pattern>& sequence2, int generations, int startCells) {
    // Use async to run both pattern detections in parallel
    auto future1 = std::async(&PatternDetector::detectPatternSequence, this, sequence1, generations, startCells);
    auto future2 = std::async(&PatternDetector::detectPatternSequence, this, sequence2, generations, startCells);

    // Wait for either of the pattern detection tasks to complete
    while (future1.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready &&
        future2.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
        // Keep checking until one of them finishes
    }

    // Check which pattern detected first
    //if (future1.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
    //    if (future1.get()) {
    //        std::cout << "Pattern Sequence 1 detected first!" << std::endl;
    //        return true;
    //    }
    //}
    //if (future2.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
    //    if (future2.get()) {
    //        std::cout << "Pattern Sequence 2 detected first!" << std::endl;
    //        return false;
    //    }
    //}

    return false;
}
