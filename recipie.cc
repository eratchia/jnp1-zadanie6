#include <vector>
#include "recipie.h"

using std::vector;
using std::initializer_list;

class instruction: public recipie {
public:
    instruction* begin() {
        return this;
    }
    instruction* end() {
        return this+1;
    }
};

class compose: public recipie {
private:
    vector<instruction> instructions;
public:
    compose(initializer_list<recipie> recipies) {
        for (auto recipie: recipies) {
            for (instruction& instr: recipie) {
                instructions.push_back(instr);
            }
        }
    }
    instruction* begin() {
        return &(*instructions.begin());
    }
    instruction* end() {
        return &(*instructions.end());
    }
};

class move_forward: public instruction {
    move_forward() {}
    state next_state(const state& original) {
        state next = original;
        next.move_forward(1);
        return next;
    }
};

class move_backward: public instruction {
    move_backward() {};
    state next_state(const state& original) {
        state next = original;
        next.move_forward(-1);
        return next;
    }
};

class rotate_left: public instruction {
    rotate_left() {}
    state next_state(const state& original) {
        state next = original;
        next.turn_right(-1);
        return next;
    }
};

class rotate_right: public instruction {
    rotate_right() {}
    state next_state(const state& original) {
        state next = original;
        next.turn_right(1);
        return next;
    }
};