#pragma once

#include "state.h"
#include <initializer_list>
#include <vector>
#include <list>
#include <memory>

class Instruction {
public:
    // Funkcja next_state przyjmuje stan i mówi, jak się on zmieni
    // po wykonaniu danej instrukcji
    virtual State next_state(const State &) const = 0;
};

// Typ recipe_t jest typem wykonywalnej przez łazik komendy. Dla każdej
// instrukcji istnieje funkcja, która zwraca recipe_t odpowiadające
// tej instrukcji.
using recipe_t = std::list<std::shared_ptr<Instruction>>;

recipe_t compose(std::initializer_list<recipe_t> init);

class MoveForward : public Instruction {
public:
    MoveForward();
    State next_state(const State &) const override;
};
recipe_t move_forward();

class MoveBackward : public Instruction {
public:
    MoveBackward();
    State next_state(const State &) const override;
};
recipe_t move_backward();

class RotateLeft : public Instruction {
public:
    RotateLeft();
    State next_state(const State &) const override;
};
recipe_t rotate_left();

class RotateRight : public Instruction {
public:
    RotateRight();
    State next_state(const State &) const override;
};
recipe_t rotate_right();
