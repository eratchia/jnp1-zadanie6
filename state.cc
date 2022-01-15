module;

#include <stdexcept>
#include <iostream>
#include <limits>
import Direction;

export module State;

export using coordinate_t = long long;
export const coordinate_t MAX_COORDINATE_T = __LONG_LONG_MAX__;
export const coordinate_t MIN_COORDINATE_T = -__LONG_LONG_MAX__ - 1;

export class OutOfBoundsException : public std::logic_error {
public:
    OutOfBoundsException() : std::logic_error("TriedToRemoveStemVirus") {};
};

void add(coordinate_t &a, coordinate_t &b) {
    if ((a > 0 && b > MAX_COORDINATE_T - a) ||
        (a < 0 && b < MIN_COORDINATE_T - a))
        throw OutOfBoundsException();
    a += b;
}

export class State {
private:
    coordinate_t x;
    coordinate_t y;
    Direction dir;
public:
    State(std::pair<coordinate_t, coordinate_t> point, Direction _dir):
            x(point.first), y(point.second), dir(_dir) {}

    coordinate_t get_x() const { return x; }
    coordinate_t get_y() const { return y; }
    Direction get_dir() const { return dir; }

    void move_forward(coordinate_t dist) {
        if (dir > Direction::EAST)
            dist = -dist;
        if (dir == Direction::NORTH || dir == Direction::SOUTH)
            add(y, dist);
        else
            add(x, dist);
    }

    void turn_right() {
        switch (dir) {
            case Direction::NORTH:
                dir = Direction::EAST;
                return;
            case Direction::EAST:
                dir = Direction::SOUTH;
                return;
            case Direction::SOUTH:
                dir = Direction::WEST;
                return;
            default /*WEST*/:
                dir = Direction::NORTH;
                break;
        }
    }

    void turn_left() {
        switch (dir) {
            case Direction::NORTH:
                dir = Direction::WEST;
                return;
            case Direction::EAST:
                dir = Direction::NORTH;
                return;
            case Direction::SOUTH:
                dir = Direction::EAST;
                return;
            default /*WEST*/:
                dir = Direction::SOUTH;
                break;
        }
    }

    void set_x(coordinate_t _x) { x = _x; }
    void set_y(coordinate_t _y) { y = _y; }
    void set_dir(Direction _dir) { dir = _dir; }

    friend std::ostream &operator<<(std::ostream &str, const State &state) {
        return str << "(" << state.x << ", " << state.y << ") " << state.dir;
    }
};