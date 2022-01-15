#pragma once

#include "state.h"
#include <initializer_list>
#include <vector>
#include <list>
#include <memory>

class Instruction {
public:
    virtual State next_state(const State&) const = 0;
};

std::list<std::shared_ptr<Instruction>> compose(std::initializer_list<std::list<std::shared_ptr<Instruction>>> init);

class MoveForward: public Instruction {
public:
    MoveForward();
    State next_state(const State&) const override;
};
std::list<std::shared_ptr<MoveForward>> move_forward();

class MoveBackward: public Instruction {
public:
    MoveBackward();
    State next_state(const State&) const override;
};
std::list<std::shared_ptr<MoveBackward>> move_backward();

class RotateLeft: public Instruction {
public:
    RotateLeft();
    State next_state(const State&) const override;
};
std::list<std::shared_ptr<RotateLeft>> rotate_left();

class RotateRight: public Instruction {
public:
    RotateRight();
    State next_state(const State&) const override;
};
std::list<std::shared_ptr<RotateRight>> rotate_right();
