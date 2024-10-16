#ifndef PATTERN_ENUM_H
#define PATTERN_ENUM_H

#include <vector>
#include <utility>
#include <string>

// Enum class that contains all the patterns
enum class PatternType {
    BLOCK,
    BEEHIVE,
    BLINK_0,
    BLINK_1,
    TOAD_0,
    TOAD_1,
    GLIDER_0,
    GLIDER_1,
    GLIDER_2,
    GLIDER_3,
    LWSS_0,
    LWSS_1,
};



// Returns the corresponding pattern offsets based on the enum type
inline std::vector<std::pair<int, int>> getPatternOffsets(PatternType type) {
    switch (type) {
    case PatternType::BLOCK:
        return { {0, 0}, {0, 1}, {1, 0}, {1, 1} }; // Block pattern
    case PatternType::BEEHIVE:
        return { {0, 1}, {0, 2}, {1, 0}, {1, 3}, {2, 1}, {2, 2} }; 
    case PatternType::BLINK_0:
        return { {1, 0}, {1, 1}, {1, 2} };//Blink pattern
    case PatternType::BLINK_1:
        return { {0, 1}, {1, 1}, {2, 1} };
    case PatternType::TOAD_0:
        return { {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2} }; // Toad pattern 
    case PatternType::TOAD_1:
        return { {0, 2}, {1, 0}, {1, 3}, {2, 0}, {2, 3}, {3, 1} }; 
    case PatternType::GLIDER_0:
        return { {0, 2}, {1, 0}, {1, 2}, {2, 1}, {2, 2} }; // Glider pattern 
    case PatternType::GLIDER_1:
        return { {0, 1}, {1, 2}, {1, 3}, {2, 1}, {2, 2} }; 
    case PatternType::GLIDER_2:
        return { {0, 2}, {1, 3}, {2, 1}, {2, 2}, {2, 3} }; 
    case PatternType::GLIDER_3:
        return { {1, 1}, {1, 3}, {2, 2}, {2, 3}, {3, 2} }; 
    case PatternType::LWSS_0:
        return { {0, 0}, {0, 3}, {1, 4}, {2, 0}, {2, 4},{3, 1}, {3, 2}, {3, 3}, {3, 4} }; // Spaceship pattern
    case PatternType::LWSS_1:
        return { {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 3},{1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 1}, {3, 2} }; 
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
    case PatternType::BLINK_0:
        return "BLINK_0";
    case PatternType::BLINK_1:
        return "BLINK_1";
    case PatternType::TOAD_0:
        return "TOAD_0";
    case PatternType::TOAD_1:
        return "TOAD_1";
    case PatternType::LWSS_0:
        return "LWSS_0";
    case PatternType::LWSS_1:
        return "LWSS_1";
    default:
        return "UNKNOWN";
    }
}

#endif
