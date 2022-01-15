#pragma once
#include <iostream>

enum class Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

inline std::ostream& operator<<(std::ostream& os, const Direction& d) {
    switch(d) {
        case Direction::NORTH:
            return os << "NORTH";
        case Direction::EAST:
            return os << "EAST";
        case Direction::SOUTH:
            return os << "SOUTH";
        default: /*WEST*/
            return os << "WEST";
    }
}