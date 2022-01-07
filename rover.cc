#include "rover.h"

RoverBuilder &RoverBuilder::program_command(char name, const recipie &rec) {
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
    for (char command : commands) {
        auto it = recipies.find(command);
        if (it == recipies.end())
            return;
        // TODO reszta
    }
}

void Rover::land(std::pair<coordinate_t, coordinate_t> coords, Direction dir) {
    landed = true;
    s = state(coords, dir);
}

std::ostream &operator<<(std::ostream &os, const Rover &rover) {
    // TODO
    return os;
}
