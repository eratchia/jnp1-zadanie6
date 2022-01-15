module;

#include <initializer_list>
#include <vector>
#include <list>
#include <memory>
import State;

export module Instruction;

using std::initializer_list;
using std::unique_ptr;
using std::make_unique;
using std::make_shared;

export class Instruction {
public:
    virtual State next_state(const State &) const = 0;
};

export using recipe_t = std::list<std::shared_ptr<Instruction>>;

export recipe_t compose(std::initializer_list<recipe_t> recipe) {
    recipe_t res = {};
    for (auto instructions: recipe)
        res.splice(res.end(), instructions);
    return res;
}

export class MoveForward : public Instruction {
public:
    MoveForward() = default;

    State next_state(const State &original) const override {
        State next = original;
        next.move_forward(1);
        return next;
    }
};

export recipe_t move_forward() {
    return {make_shared<MoveForward>()};
}

export class MoveBackward : public Instruction {
public:
    MoveBackward() = default;

    State next_state(const State &original) const override {
        State next = original;
        next.move_forward(-1);
        return next;
    }
};

export recipe_t move_backward() {
    return {make_shared<MoveBackward>()};
}

export class RotateLeft : public Instruction {
public:
    RotateLeft() = default;

    State next_state(const State &original) const override {
        State next = original;
        next.turn_left();
        return next;
    }
};

export recipe_t rotate_left() {
    return {make_shared<RotateLeft>()};
}

export class RotateRight : public Instruction {
public:
    RotateRight() = default;

    State next_state(const State &original) const override {
        State next = original;
        next.turn_right();
        return next;
    }
};

export recipe_t rotate_right() {
    return {make_shared<RotateRight>()};
}
