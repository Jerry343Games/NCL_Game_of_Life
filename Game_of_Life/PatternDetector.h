#ifndef PATTERNDETECTOR_H
#define PATTERNDETECTOR_H

#include "Grid.h"
#include "Pattern.h"

class PatternDetector {
public:
    PatternDetector(Grid& grid);
    bool detectPattern(const Pattern& pattern, int generations, int startCells);

    // New public method to get a reference to the grid
    Grid& getGrid() {
        return grid;
    }
    bool checkPattern(const Pattern& pattern);

private:
    Grid& grid;
    bool isPatternAt(int row, int col, const Pattern& pattern);

};

#endif

