#pragma once

#include "state.h"
#include "type_iterator.h"
#include <initializer_list>
#include <vector>
#include <list>
#include <memory>

class executable {
public:
    virtual state next_state(const state&) = 0;
};

class recipie {
public:
    using iterator = type_iterator<const executable>;
    virtual iterator begin() const = 0;
    virtual iterator end() const = 0;
};

class instruction: public executable, public recipie {
private:
    class instruction_iterator_impl : public iterator::implementation { 
    private:
        bool end;
        const instruction* instr_ptr;
    public:
        instruction_iterator_impl(const instruction*, bool) noexcept;
        instruction_iterator_impl() = default; 

        std::unique_ptr<iterator::implementation> clone() const noexcept override;

        instruction_iterator_impl& operator++() noexcept override;
        const instruction& operator*() const noexcept override;
        const instruction* operator->() const noexcept override;
        bool operator==(const iterator::implementation&) const noexcept override;
    };
public:

    iterator begin() const override;
    iterator end() const override;
};

class compose: public recipie {
private:
    using inner_structure = std::list<std::unique_ptr<const executable>>;
    using inner_iterator = inner_structure::const_iterator;

    std::list<recipie> instructions;

    class compose_iterator_impl : public iterator::implementation { 
    private:
        inner_iterator iter;
    public:
        compose_iterator_impl(inner_iterator) noexcept;
        compose_iterator_impl() = default; 

        std::unique_ptr<iterator::implementation> clone() const noexcept override;

        virtual compose_iterator_impl& operator++() noexcept override;
        virtual const executable& operator*() const noexcept override;
        virtual const executable* operator->() const noexcept override;
        bool operator==(const iterator::implementation&) const noexcept override;
    };
public:

    compose(std::initializer_list<recipie>);
    iterator begin() const override;
    iterator end() const override;
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