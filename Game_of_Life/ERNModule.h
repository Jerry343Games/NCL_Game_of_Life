#ifndef ERN_MODULE_H
#define ERN_MODULE_H

#include "PatternEnum.h"

int getMinCells(SequenceType sequenceType);
std::pair<int, int> getMaxRowCol(SequenceType sequenceType);
int findMinCellsForPattern(int rows, int cols, int minCells, SequenceType sequenceType);

#endif // ERN_MODULE_H