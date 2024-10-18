#include "Cell.h"
#include <iostream>

// default constructor
Cell::Cell() : state(0) {} 

// constructor with initial state
Cell::Cell(int initState) : state(initState) {}

// get cell state
int Cell::getState() const {
    return state;
}

// Set cell state
void Cell::setState(int newState) {
    state = newState;
}

// Print cell state
void Cell::printCell() const {
    std::cout << (state == 1 ? "Alive" : "Dead") << std::endl;
}
