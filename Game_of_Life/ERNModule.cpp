#include "Grid.h"
#include "Pattern.h"
#include "PatternEnum.h"
#include "ERNModule.h"
#include <algorithm>  // For std::max and std::min

// 计算Pattern所需的最大网格数
int getMaxGrid(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int maxGridCells = 0;
    
    for (const Pattern& pattern : patterns) {
        int maxRow = 0;
        int maxCol = 0;

        // 遍历每个Pattern中的所有偏移量，找到最大行和列的偏移值
        for (const auto& offset : pattern.offsets) {
            maxRow = std::max(maxRow, offset.first);
            maxCol = std::max(maxCol, offset.second);
        }

        // 计算当前Pattern所需的最小网格数（行数*列数）
        int gridCells = (maxRow + 1) * (maxCol + 1);  // +1 是因为索引从0开始
        maxGridCells = std::max(maxGridCells, gridCells);  // 保留最大网格数
    }
    
    return maxGridCells;
}

// 获取某个SequenceType中的最小活细胞数
int getMinCells(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int minCells = INT_MAX;

    for (const Pattern& pattern : patterns) {
        int cellCount = pattern.offsets.size();  // 计算当前模式中的活细胞数
        minCells = std::min(minCells, cellCount);  // 保留最小的细胞数
    }

    return minCells;
}
