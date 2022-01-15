module Rover;
#include <memory>
#include <unordered_map>
#include <utility>
#include <string>

RoverBuilder &RoverBuilder::program_command(char name, const recipe_t &rec) {
    recipes.insert({name, rec});
    return *this;
}

RoverBuilder &RoverBuilder::add_sensor(std::unique_ptr<Sensor> sensor) {
    sensors.push_back(std::move(sensor));
    return *this;
}

Rover RoverBuilder::build() {
    return {std::move(sensors), std::move(recipes)};
}

bool Rover::isInDanger() {
    for (auto &sens: sensors)
        if (!sens->is_safe(state.get_x(), state.get_y()))
            return true;
    return false;
}

void Rover::execute(const std::string &commands) {
    if (!landed)
        throw RoverDidNotLandYetException();
    stopped = true;
    if (isInDanger())
        return;
    for (char command: commands) {
        auto it = recipes.find(command);
        if (it == recipes.end())
            return;
        for (auto &exec: it->second) {
            state = exec->next_state(state);
            if (isInDanger())
                return;
        }
    }
    stopped = false;
}

void Rover::land(std::pair<coordinate_t, coordinate_t> coords, Direction dir) {
    landed = true;
    state = State(coords, dir);
}

std::ostream &operator<<(std::ostream &os, const Rover &rover) {
    if (!rover.landed)
        return os << "unknown";
    return os << rover.state << (rover.stopped ? " stopped" : "");
}
