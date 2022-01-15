module;

#include <memory>
#include <unordered_map>
#include <utility>
#include <string>
#include <vector>
import Sensor;
import State;
import Direction;
import Instruction;

export module Rover;

export class RoverDidNotLandYetException : public std::exception {
    const char *what() const noexcept override {
        return "RoverDidNotLandYetException";
    }
};

export class Rover {
private:
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unordered_map<char, const recipe_t> recipes;
    State state;
    bool landed, stopped;
    friend class RoverBuilder;
    Rover(std::vector<std::unique_ptr<Sensor>> &&sensors,
          std::unordered_map<char, const recipe_t> &&recipes)
          : sensors(std::move(sensors)), recipes(std::move(recipes)),
            state({0, 0}, Direction()), landed(false), stopped(false) {}
    bool isInDanger() {
        for (auto &sens: sensors)
            if (!sens->is_safe(state.get_x(), state.get_y()))
                return true;
        return false;
    }
public:
    void execute(const std::string &commands) {
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
    void land(std::pair<coordinate_t, coordinate_t> coords, Direction dir) {
        landed = true;
        state = State(coords, dir);
    }
    friend std::ostream &operator<<(std::ostream &os, const Rover &rover) {
        if (!rover.landed)
            return os << "unknown";
        return os << rover.state << (rover.stopped ? " stopped" : "");
    }
};

export class RoverBuilder {
private:
    std::unordered_map<char, const recipe_t> recipes;
    std::vector<std::unique_ptr<Sensor>> sensors;
public:
    RoverBuilder &program_command(char name, const recipe_t &rec) {
        recipes.insert({name, rec});
        return *this;
    }
    RoverBuilder &add_sensor(std::unique_ptr<Sensor> sensor) {
        sensors.push_back(std::move(sensor));
        return *this;
    }
    Rover build() {
        return {std::move(sensors), std::move(recipes)};
    }
};

