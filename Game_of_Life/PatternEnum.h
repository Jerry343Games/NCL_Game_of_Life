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
    LWSS_2,
    LWSS_3
};

enum class SequenceType {
    BLOCK,
    BEEHIVE,
    BLINKER,
    TOAD,
    GLIDER,
    SPACESHIP,
};


// Returns the corresponding pattern offsets based on the enum type
inline std::vector<std::pair<int, int>> getPatternOffsets(PatternType type) {
    switch (type) {
    case PatternType::BLOCK:
        return { {0, 0}, {0, 1}, {1, 0}, {1, 1} }; // Block pattern
    
    case PatternType::BEEHIVE:
        return { {0, 1}, {0, 2}, {1, 0}, {1, 3}, {2, 1}, {2, 2} };//Beehive pattern
    
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
        return { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {2, 0},{2, 4}, {3, 4}, {4, 0}, {4, 3} }; // Spaceship pattern
    case PatternType::LWSS_1:
        return { {0, 2}, {0, 3}, {1, 1}, {1, 2}, {1, 3},{1, 4}, {2, 1}, {2, 2}, {2, 4}, {2, 5}, {3, 3}, {3, 4} }; 
    case PatternType::LWSS_2:
        return { {0, 1}, {0, 4}, {1, 5}, {2, 1}, {2, 5},{3, 2}, {3, 3}, {3, 4}, {3, 5} }; // Spaceship pattern
    case PatternType::LWSS_3:
        return { {1, 4}, {1, 5}, {2, 2}, {2, 3}, {2, 5},{2, 6}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {4, 3}, {4, 4} };
    default:
        return {}; // Default return empty pattern
    }
}

inline std::vector<Pattern> getPatternSequence(SequenceType sequenceType) {
    switch (sequenceType) {
    case SequenceType::BLOCK:
        return {
            {getPatternOffsets(PatternType::BLOCK)},
            {getPatternOffsets(PatternType::BLOCK)}
        };
    case SequenceType::BEEHIVE:
        return {
            {getPatternOffsets(PatternType::BEEHIVE)},
            {getPatternOffsets(PatternType::BEEHIVE)}
        };
    case SequenceType::BLINKER:
        return{
            {getPatternOffsets(PatternType::BLINK_0)},
            {getPatternOffsets(PatternType::BLINK_1)}
        };
    case SequenceType::TOAD:
        return{
            {getPatternOffsets(PatternType::TOAD_0)},
            {getPatternOffsets(PatternType::TOAD_1)}
        };
    case SequenceType::GLIDER:
        return {
            {getPatternOffsets(PatternType::GLIDER_0)},
            {getPatternOffsets(PatternType::GLIDER_1)},
            {getPatternOffsets(PatternType::GLIDER_2)},
            {getPatternOffsets(PatternType::GLIDER_3)}
        };
    case SequenceType::SPACESHIP:
        return {
            {getPatternOffsets(PatternType::LWSS_0)},
            {getPatternOffsets(PatternType::LWSS_1)},
            {getPatternOffsets(PatternType::LWSS_2)},
            {getPatternOffsets(PatternType::LWSS_3)}
        };
    default:
        return {};
    }
}

// Method to convert enum type to string
inline std::string sequenceToString(SequenceType type) {
    switch (type) {
    case SequenceType::BLOCK:
        return "BLOCK";
    case SequenceType::BEEHIVE:
        return "BEEHIVE";
    case SequenceType::BLINKER:
        return "BLINKER";
    case SequenceType::TOAD:
        return "TOAD";
    case SequenceType::GLIDER:
        return "GLIDER";
    case SequenceType::SPACESHIP:
        return "SPACESHIP";
    default:
        return "UNKNOWN";
    }
}


#endif
