#include "Instruction.h"

using std::initializer_list;
using std::unique_ptr;
using std::make_unique;
using std::make_shared;

// compose
recipe_t compose(std::initializer_list<recipe_t> recipe) {
    recipe_t res = {};
    for (auto instructions: recipe)
        res.splice(res.end(), instructions);
    return res;
}

// MoveForward
MoveForward::MoveForward() = default;
State MoveForward::next_state(const State& original) const {
    State next = original;
    next.move_forward(1);
    return next;
}
recipe_t move_forward() {
    return {make_shared<MoveForward>()};
}

// MoveBackward
MoveBackward::MoveBackward() = default;
State MoveBackward::next_state(const State& original) const {
    State next = original;
    next.move_forward(-1);
    return next;
}
recipe_t move_backward() {
    return {make_shared<MoveBackward>()};
}

// RotateLeft
RotateLeft::RotateLeft() = default;
State RotateLeft::next_state(const State& original) const {
    State next = original;
    next.turn_left();
    return next;
}
recipe_t rotate_left() {
    return {make_shared<RotateLeft>()};
}

// RotateRight
RotateRight::RotateRight() = default;
State RotateRight::next_state(const State& original) const {
    State next = original;
    next.turn_right();
    return next;
}
recipe_t rotate_right() {
    return {make_shared<RotateRight>()};
}