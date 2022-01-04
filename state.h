#pragma once

#include <stdexcept>
#include <iostream>
#include "direction.h"

using coordinate_t = long long;

class OutOfBoundsException: public std::logic_error {
public:
    OutOfBoundsException(): std::logic_error("TriedToRemoveStemVirus") {};
};

class state {
public:
    coordinate_t get_x();
    coordinate_t get_y();
    Direction get_dir();
    void move_forward(coordinate_t);
    void turn_right(coordinate_t);
    void set_dir(Direction);
    void set_x(Direction);
    void set_y(Direction);
    friend std::ostream& operator<<(std::ostream&, state&);
};