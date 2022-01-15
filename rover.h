#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include "state.h"
#include "Sensor.h"
#include "Instruction.h"
#include <string>

class RoverDidNotLandYetException : public std::exception {
    const char *what() const noexcept override {
        return "RoverDidNotLandYetException";
    }
};

class Rover {
private:
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unordered_map<char, const recipe_t &> recipes;
    State state;
    bool landed, stopped;
    friend class RoverBuilder;
    Rover(std::vector<std::unique_ptr<Sensor>> &&sensors,
          std::unordered_map<char, const recipe_t &> &&recipes)
          : sensors(std::move(sensors)), recipes(std::move(recipes)),
            state({0, 0}, Direction()), landed(false), stopped(false) {}
public:
    void execute(const std::string &);
    void land(std::pair<coordinate_t, coordinate_t>, Direction);
    friend std::ostream& operator<<(std::ostream &, const Rover &);
};

class RoverBuilder {
private:
    std::unordered_map<char, const recipe_t &> recipes;
    std::vector<std::unique_ptr<Sensor>> sensors;
public:
    RoverBuilder &program_command(char, const recipe_t &);
    RoverBuilder &add_sensor(std::unique_ptr<Sensor>);
    Rover build();
};

