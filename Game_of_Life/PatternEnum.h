#ifndef PATTERN_ENUM_H
#define PATTERN_ENUM_H

#include <vector>
#include <utility>
#include <string>

// 枚举类，包含所有的图案
enum class PatternType {
    BLOCK,
    BEEHIVE,
    TOAD,
    GLIDER
};

// 根据枚举类型返回对应的图案偏移
inline std::vector<std::pair<int, int>> getPatternOffsets(PatternType type) {
    switch (type) {
    case PatternType::BLOCK:
        return { {0, 0}, {0, 1}, {1, 0}, {1, 1} }; // Block 图案
    case PatternType::BEEHIVE:
        return { {0, 1}, {0, 2}, {1, 0}, {1, 3}, {2, 1}, {2, 2} }; // Beehive 图案
    case PatternType::TOAD:
        return { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2} }; // Toad 图案
    case PatternType::GLIDER:
        return { {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2} }; // Glider 图案
    default:
        return {}; // 默认返回空图案
    }
}

// 枚举类型转换为字符串的方法
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