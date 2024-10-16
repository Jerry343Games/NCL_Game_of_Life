#include "PatternDetector.h"
#include "PatternEnum.h"
#include <iostream>
#include <algorithm>

PatternDetector::PatternDetector(Grid& grid) : grid(grid) {}

bool PatternDetector::detectPattern(const Pattern& pattern, int generations, int startCells) {
    int simulationCount = 0;

    // �������ģ�⣬ֱ���ҵ�ƥ���ͼ��
    while (true) {
        simulationCount++;
        grid.randomizeCells(startCells);

        // ���ڱ���ÿ��ģ���״̬
        std::vector<Grid> simulationHistory;

        // �����ʼ״̬
        simulationHistory.push_back(grid);

        for (int gen = 0; gen < generations; ++gen) {
            // �ݻ�����һ��
            grid.evolve();

            // �����ݻ����״̬
            simulationHistory.push_back(grid);

            // ����Ƿ��ҵ�ƥ���ͼ��
            if (checkPattern(pattern)) {
                std::cout << "Pattern found in simulation " << simulationCount << " at generation " << gen + 1 << ":" << std::endl;

                // ��ӡ������ģ�����
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

    while (true) {
        simulationCount++;
        grid.randomizeCells(startCells);

        // ���ڱ���ģ���״̬
        std::vector<Grid> simulationHistory;
        simulationHistory.push_back(grid);  // �����ʼ״̬

        for (int gen = 0; gen < generations; ++gen) {
            grid.evolve();
            simulationHistory.push_back(grid);  // ����ÿ���ݻ����״̬

            // ����Ƿ��ҵ��������е���һ��ͼ��
            if (checkPattern(patternSequence[sequenceIndex])) {
                sequenceIndex++;
                if (sequenceIndex == patternSequence.size()) {
                    // �ɹ���⵽������ͼ������
                    std::cout << "�ɹ���⵽ͼ�����У���ģ�� " << simulationCount
                        << " �еĵ� " << gen + 1 << " ��" << std::endl;

                    // ��ӡ������ģ�����
                    for (size_t step = 0; step < simulationHistory.size(); ++step) {
                        std::cout << "�� " << step << " ��:" << std::endl;
                        simulationHistory[step].printGrid();
                    }

                    return true;
                }
            }
            else {
                sequenceIndex = 0;  // ������ʧ�ܣ�������������
            }
        }
    }
    return false;
}
