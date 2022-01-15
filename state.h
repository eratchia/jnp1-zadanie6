#pragma once

#include <stdexcept>
#include <iostream>
#include <limits>
#include "direction.h"

using coordinate_t = long long;
const coordinate_t MAX_COORDINATE_T = __LONG_LONG_MAX__;
const coordinate_t MIN_COORDINATE_T = -__LONG_LONG_MAX__ - 1;

class OutOfBoundsException : public std::logic_error {
public:
    OutOfBoundsException() : std::logic_error("TriedToRemoveStemVirus") {};
};

class State {
private:
    coordinate_t x;
    coordinate_t y;
    Direction dir;
public:
    State(std::pair<coordinate_t, coordinate_t> point, Direction _dir);

    coordinate_t get_x() const;
    coordinate_t get_y() const;
    Direction get_dir() const;

    void move_forward(coordinate_t);
    void turn_right();
    void turn_left();

    void set_dir(Direction);
    void set_x(coordinate_t);
    void set_y(coordinate_t);

    friend std::ostream &operator<<(std::ostream &, const State &);
};