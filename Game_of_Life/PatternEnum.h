#ifndef PATTERN_ENUM_H
#define PATTERN_ENUM_H

#include <vector>
#include <utility>
#include <string>

// ö���࣬�������е�ͼ��
enum class PatternType {
    BLOCK,
    BEEHIVE,
    TOAD,
    GLIDER
};

// ����ö�����ͷ��ض�Ӧ��ͼ��ƫ��
inline std::vector<std::pair<int, int>> getPatternOffsets(PatternType type) {
    switch (type) {
    case PatternType::BLOCK:
        return { {0, 0}, {0, 1}, {1, 0}, {1, 1} }; // Block ͼ��
    case PatternType::BEEHIVE:
        return { {0, 1}, {0, 2}, {1, 0}, {1, 3}, {2, 1}, {2, 2} }; // Beehive ͼ��
    case PatternType::TOAD:
        return { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2} }; // Toad ͼ��
    case PatternType::GLIDER:
        return { {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2} }; // Glider ͼ��
    default:
        return {}; // Ĭ�Ϸ��ؿ�ͼ��
    }
}

// ö������ת��Ϊ�ַ����ķ���
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