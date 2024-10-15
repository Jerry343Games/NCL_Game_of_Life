#ifndef PATTERN_ENUM_H
#define PATTERN_ENUM_H

#include <vector>
#include <utility>
#include <string>

// Enum class that contains all the patterns
enum class PatternType {
    BLOCK,
    BEEHIVE,
    TOAD,
    GLIDER
};

// Returns the corresponding pattern offsets based on the enum type
inline std::vector<std::pair<int, int>> getPatternOffsets(PatternType type) {
    switch (type) {
    case PatternType::BLOCK:
        return { {0, 0}, {0, 1}, {1, 0}, {1, 1} }; // Block pattern
    case PatternType::BEEHIVE:
        return { {0, 1}, {0, 2}, {1, 0}, {1, 3}, {2, 1}, {2, 2} }; // Beehive pattern
    case PatternType::TOAD:
        return { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2} }; // Toad pattern
    case PatternType::GLIDER:
        return { {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2} }; // Glider pattern
    default:
        return {}; // Default return empty pattern
    }
}

// Method to convert enum type to string
inline std::string patternTypeToString(PatternType type) {
    switch (type) {
    case PatternType::BLOCK:
        return "BLOCK";
    case PatternType::BEEHIVE:
        return "BEEHIVE";
    case PatternType::TOAD:
        return "TOAD";
    case PatternType::GLIDER:
        return "GLIDER";
    default:
        return "UNKNOWN";
    }
}

#endif
