#pragma once

#include <initializer_list>
#include "state.h"

class executable {
public:
    virtual state next_state(const state&);
};

class recipie {
public:
    virtual executable* begin();
    virtual executable* end();
};

class instruction: public executable, public recipie {
public:
    instruction* begin();
    instruction* end();
};

class compose: public recipie {
private:
    std::vector<executable> instructions;
public:
    compose(std::initializer_list<recipie>);
    executable* begin();
    executable* end();
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