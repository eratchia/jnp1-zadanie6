#pragma once

#include "state.h"
#include "type_iterator.h"
#include <initializer_list>
#include <vector>
#include <list>
#include <memory>

class Executable {
public:
    virtual state next_state(const state&) const = 0;
};

class Recipe {
public:
    using iterator = TypeIterator<const Executable>;
    virtual iterator begin() const = 0;
    virtual iterator end() const = 0;
    void simplify();
};

class Instruction: public Executable, public Recipe {
private:
    class InstructionIteratorImpl : public iterator::implementation { 
    private:
        bool end;
        const Instruction* instr_ptr;
    public:
        InstructionIteratorImpl(const Instruction*, bool) noexcept;
        InstructionIteratorImpl() = default; 

        std::unique_ptr<iterator::implementation> clone() const noexcept override;

        InstructionIteratorImpl& operator++() noexcept override;
        const Instruction& operator*() const noexcept override;
        const Instruction* operator->() const noexcept override;
        bool operator==(const iterator::implementation&) const noexcept override;
    };
public:

    iterator begin() const override;
    iterator end() const override;
};

class Compose: public Recipe {
private:
    using inner_structure = std::list<std::unique_ptr<const Executable>>;
    using inner_iterator = inner_structure::const_iterator;

    inner_structure instructions;

    class ComposeIteratorImpl : public iterator::implementation { 
    private:
        inner_iterator iter;
    public:
        ComposeIteratorImpl(inner_iterator) noexcept;
        ComposeIteratorImpl() = default; 

        std::unique_ptr<iterator::implementation> clone() const noexcept override;

        virtual ComposeIteratorImpl& operator++() noexcept override;
        virtual const Executable& operator*() const noexcept override;
        virtual const Executable* operator->() const noexcept override;
        bool operator==(const iterator::implementation&) const noexcept override;
    };
public:

    Compose() = delete;

    iterator begin() const override;
    iterator end() const override;
    friend std::shared_ptr<Compose> compose(std::initializer_list<std::shared_ptr<Recipe>>);
};
std::shared_ptr<Compose> compose(std::initializer_list<std::shared_ptr<Recipe>>);

class MoveForward: public Instruction {
private:
    MoveForward();
public:
    state next_state(const state&) const override;
    friend std::shared_ptr<MoveForward> move_forward();
};
std::shared_ptr<MoveForward> move_forward();

class MoveBackward: public Instruction {
private:
    MoveBackward();
public:
    state next_state(const state&) const override;
    friend std::shared_ptr<MoveBackward> move_backward();
};
std::shared_ptr<MoveBackward> move_backward();

class RotateLeft: public Instruction {
private:
    RotateLeft();
public:
    state next_state(const state&) const override;
    friend std::shared_ptr<RotateLeft> rotate_left();
};
std::shared_ptr<RotateLeft> rotate_left();

class RotateRight: public Instruction {
private:
    RotateRight();
public:
    state next_state(const state&) const override;
    friend std::shared_ptr<Compose> rotate_right();
};
std::shared_ptr<Compose> rotate_right();