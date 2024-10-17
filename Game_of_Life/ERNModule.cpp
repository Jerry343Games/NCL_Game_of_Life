#include "Grid.h"
#include "Pattern.h"
#include "PatternEnum.h"
#include "ERNModule.h"
#include <algorithm>  // For std::max and std::min

// ����Pattern��������������
int getMaxGrid(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int maxGridCells = 0;
    
    for (const Pattern& pattern : patterns) {
        int maxRow = 0;
        int maxCol = 0;

        // ����ÿ��Pattern�е�����ƫ�������ҵ�����к��е�ƫ��ֵ
        for (const auto& offset : pattern.offsets) {
            maxRow = std::max(maxRow, offset.first);
            maxCol = std::max(maxCol, offset.second);
        }

        // ���㵱ǰPattern�������С������������*������
        int gridCells = (maxRow + 1) * (maxCol + 1);  // +1 ����Ϊ������0��ʼ
        maxGridCells = std::max(maxGridCells, gridCells);  // �������������
    }
    
    return maxGridCells;
}

// ��ȡĳ��SequenceType�е���С��ϸ����
int getMinCells(SequenceType sequenceType) {
    std::vector<Pattern> patterns = getPatternSequence(sequenceType);
    int minCells = INT_MAX;

    for (const Pattern& pattern : patterns) {
        int cellCount = pattern.offsets.size();  // ���㵱ǰģʽ�еĻ�ϸ����
        minCells = std::min(minCells, cellCount);  // ������С��ϸ����
    }

    return minCells;
}
