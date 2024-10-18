#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int state; 

public:
    
    Cell();

    // constructor
    Cell(int initState);

    int getState() const;

    void setState(int newState);

    void printCell() const;
};

#endif
