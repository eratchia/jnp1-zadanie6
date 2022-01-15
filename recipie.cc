#include "recipie.h"

using std::initializer_list;
using std::unique_ptr;
using std::make_unique;

// compose
std::list<std::shared_ptr<Instruction>> compose(std::initializer_list<std::list<std::shared_ptr<Instruction>>> recipe) {
    std::list<std::shared_ptr<Instruction>> res = {};
    for (auto instructions: recipe)
        res.splice(res.end(), instructions);
    return res;
}

// MoveForward
MoveForward::MoveForward() {}
State MoveForward::next_state(const State& original) const {
    State next = original;
    next.move_forward(1);
    return next;
}
std::list<std::shared_ptr<MoveForward>> move_forward() {
    return {std::make_shared<MoveForward>()};
}

// MoveBackward
MoveBackward::MoveBackward() {};
State MoveBackward::next_state(const State& original) const {
    State next = original;
    next.move_forward(-1);
    return next;
}
std::list<std::shared_ptr<MoveBackward>> move_backward() {
    return {std::make_shared<MoveBackward>()};
}

// RotateLeft
RotateLeft::RotateLeft() {}
State RotateLeft::next_state(const State& original) const {
    State next = original;
    next.turn_left();
    return next;
}
std::list<std::shared_ptr<RotateLeft>> rotate_left() {
    return {std::make_shared<RotateLeft>()};
}

// RotateRight
RotateRight::RotateRight() {}
State RotateRight::next_state(const State& original) const {
    State next = original;
    next.turn_right();
    return next;
}
std::list<std::shared_ptr<RotateRight>> rotate_right() {
    return {std::make_shared<RotateRight>()};
}