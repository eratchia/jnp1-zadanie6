#pragma once

#include <initializer_list>
#include "state.h"

class recipie;

class instruction: public recipie {
public:
    virtual state next_state(state);
    instruction* begin();
    instruction* end();
};

class recipie {
public:
    virtual instruction* begin();
    virtual instruction* end();
};

class compose: public recipie {
private:
    std::vector<instruction> instructions;
public:
    compose(std::initializer_list<recipie>);
    instruction* begin();
    instruction* end();
};

class move_forward: public instruction {
public:
    move_forward();
    state next_state(const state&);
};

class move_backward: public instruction {
public:
    move_backward();
    state next_state(const state&);
};

class rotate_left: public instruction {
public:
    rotate_left();
    state next_state(const state&);
};

class rotate_right: public instruction {
public:
    rotate_right();
    state next_state(const state&);
};