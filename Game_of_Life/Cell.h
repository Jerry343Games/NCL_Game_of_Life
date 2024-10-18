#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int state; // 0表示死细胞，1表示活细胞

public:
    
    Cell();

    // constructor
    Cell(int initState);

    int getState() const;

    void setState(int newState);

    void printCell() const;
};

#endif
