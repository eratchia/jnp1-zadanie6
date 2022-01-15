#include "rover.h"

RoverBuilder &RoverBuilder::program_command(char name, const Recipie &rec) {
    r.insert({name, rec});
    return *this;
}

RoverBuilder &RoverBuilder::add_sensor(std::unique_ptr<Sensor> sensor) {
    s.push_back(std::move(sensor));
    return *this;
}

Rover RoverBuilder::build() {
    return {std::move(s), std::move(r)};
}

void Rover::execute(const std::string &commands) {
    if (!landed)
        throw RoverDidNotLandYetException();
    stopped = false;
    for (char command : commands) {
        auto it = recipies.find(command);
        if (it == recipies.end())
            return;
        for (auto &exec : it->second) {
            s = exec.next_state(s);
            for (auto &sens : sensors)
                if (!sens->is_safe(s.get_x(), s.get_y())) {
                    stopped = true;
                    return;
                }
        }
    }
}

void Rover::land(std::pair<coordinate_t, coordinate_t> coords, Direction dir) {
    landed = true;
    s = state(coords, dir);
}

std::ostream &operator<<(std::ostream &os, const Rover &rover) {
    if (!rover.landed)
        return os << "unknown";
    os << "(" << rover.s.get_x() << ", " << rover.s.get_y() << ") ";
    switch (rover.s.get_dir()) {
        case Direction::EAST:
            os << "EAST";
            break;
        case Direction::WEST:
            os << "WEST";
            break;
        case Direction::NORTH:
            os << "NORTH";
            break;
        case Direction::SOUTH:
            os << "SOUTH";
            break;
    }
    if (rover.stopped)
        os << " stopped";
    return os;
}
