#pragma once

#include <initializer_list>
#include "state.h"
#include <vector>

class executable {
public:
    virtual state next_state(const state&) = 0;
};

class recipie {
public:
    virtual executable* begin() = 0;
    virtual executable* end() = 0;
};

class instruction: public executable, public recipie {
public:
    instruction* begin() override;
    instruction* end() override;
};

class compose: public recipie {
private:
    std::vector<executable> instructions;
public:
    compose(std::initializer_list<recipie>);
    executable* begin() override;
    executable* end() override;
};

class move_forward: public instruction {
public:
    move_forward();
    state next_state(const state&) override;
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