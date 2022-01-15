#include "state.h"

void add(coordinate_t& a, coordinate_t& b) {
    if ((a > 0 && b > MAX_COORDINATE_T - a) || (a < 0 && b < MIN_COORDINATE_T - a))
        throw OutOfBoundsException();
    a += b;    
}

State::State(std::pair<coordinate_t, coordinate_t> point, Direction _dir): 
    x(point.first), y(point.second), dir(_dir) {}

coordinate_t State::get_x() const {return x;}
coordinate_t State::get_y() const {return y;}
Direction State::get_dir() const {return dir;}

void State::set_x(coordinate_t _x) {x = _x;}
void State::set_y(coordinate_t _y) {y = _y;}
void State::set_dir(Direction _dir) {dir = _dir;}

void State::move_forward(coordinate_t dist) {
    if (dir > Direction::EAST)
        dist = -dist;
    if (dir == Direction::NORTH || dir == Direction::SOUTH)
        add(x, dist);
    else 
        add(y, dist);
}
void State::turn_right() {
    switch (dir){
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

void State::turn_left() {
    switch (dir){
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

std::ostream& operator<<(std::ostream& str, const State& state) {
    return str << "(" << state.x << ", " << state.y << ") " << state.dir;
}
