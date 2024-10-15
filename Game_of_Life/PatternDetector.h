#ifndef PATTERNDETECTOR_H
#define PATTERNDETECTOR_H

#include "Grid.h"
#include "Pattern.h"

class PatternDetector {
public:
    PatternDetector(Grid& grid);
    bool detectPattern(const Pattern& pattern, int generations, int startCells);

    // 新增公共方法获取 grid 引用
    Grid& getGrid() {
        return grid;
    }
    bool checkPattern(const Pattern& pattern);

private:
    Grid& grid;
    //bool checkPattern(const Pattern& pattern);
    bool isPatternAt(int row, int col, const Pattern& pattern);

};

#endif
