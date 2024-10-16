#ifndef PATTERNDETECTOR_H
#define PATTERNDETECTOR_H

#include "Grid.h"
#include "Pattern.h"

class PatternDetector {
public:
    PatternDetector(Grid& grid);

    // New public method to get a reference to the grid
    Grid& getGrid() {
        return grid;
    }
    bool detectPatternSequence(const std::vector<Pattern>& patternSequence, int generations, int startCells);


private:
    Grid& grid;
    bool isPatternAt(int row, int col, const Pattern& pattern);
    std::pair<int, int> lockedPosition = { -1, -1 };  // 新增的锁定位置
};

#endif

