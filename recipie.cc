#include <vector>
#include "recipie.h"

using std::initializer_list;

// instruction
instruction* instruction::begin() {
    return this;
}
instruction* instruction::end() {
    return this+1;
}

// compose
compose::compose(initializer_list<recipie> recipies) {
    for (auto recipie: recipies)
        for (auto& instr: recipie)
            instructions.push_back(instr);
}
executable* compose::begin() {
    return &(*instructions.begin());
}
executable* compose::end() {
    return &(*instructions.end());
}

// move_forward
move_forward::move_forward() {}
state move_forward::next_state(const state& original) {
    state next = original;
    next.move_forward(1);
    return next;
}

// move_backward
move_backward::move_backward() {};
state move_backward::next_state(const state& original) {
    state next = original;
    next.move_forward(-1);
    return next;
}

// rotate_left
rotate_left::rotate_left() {}
state rotate_left::next_state(const state& original) {
    state next = original;
    next.turn_left();
    return next;
}

// rotate_right
rotate_right::rotate_right() {}
state rotate_right::next_state(const state& original) {
    state next = original;
    next.turn_right();
    return next;
}