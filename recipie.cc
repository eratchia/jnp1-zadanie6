#include "recipie.h"

using std::initializer_list;
using std::unique_ptr;
using std::make_unique;

// instruction
recipie::iterator instruction::begin() const {
    instruction_iterator_impl imp(this, 0);
    return imp.clone();
}
recipie::iterator instruction::end() const{
    instruction_iterator_impl imp(this, 1);
    return imp.clone();
}
// instruction_iterator_impl
instruction::instruction_iterator_impl::instruction_iterator_impl(const instruction* _instr_ptr, bool _end) noexcept: instr_ptr(_instr_ptr), end(_end){}
unique_ptr<instruction::iterator::implementation> instruction::instruction_iterator_impl::clone() const noexcept {
    return make_unique<instruction_iterator_impl>(instr_ptr, end);
}
const instruction& instruction::instruction_iterator_impl::operator*() const noexcept {
    return *instr_ptr;
}
const instruction* instruction::instruction_iterator_impl::operator->() const noexcept {
    return instr_ptr;
}
instruction::instruction_iterator_impl& instruction::instruction_iterator_impl::operator++() noexcept {
    end = 1;
    return *this;
}
bool instruction::instruction_iterator_impl::operator==(const instruction::iterator::implementation& other) const noexcept {
    if (typeid(*this) != typeid(other))
        return false;
    auto instr_other = static_cast<const instruction_iterator_impl*>(&other);
    if (instr_ptr != instr_other->instr_ptr)
        return false;
    return end == instr_other->end;
}

// compose
compose::compose(initializer_list<recipie> recipies) {
    //instructions = recipies;
    //for (auto&& recipie: recipies) {
        //for (auto&& exec: recipie) {
            //exec.
        //}
    //}
}
recipie::iterator compose::begin() const {
    compose_iterator_impl imp(instructions.begin());
    return imp.clone();
}
recipie::iterator compose::end() const {
    compose_iterator_impl imp(instructions.end());
    return imp.clone();
}
// compose_iterator_impl
compose::compose_iterator_impl::compose_iterator_impl(inner_iterator _iter) noexcept: iter(_iter) {}
unique_ptr<compose::iterator::implementation> compose::compose_iterator_impl::clone() const noexcept {
    return make_unique<compose_iterator_impl>(iter);
}
const executable& compose::compose_iterator_impl::operator*() const noexcept {
    return iter->operator*();
}
const executable* compose::compose_iterator_impl::operator->() const noexcept {
    return iter->get();
}
compose::compose_iterator_impl& compose::compose_iterator_impl::operator++() noexcept {
    ++iter;
    return *this;
}
bool compose::compose_iterator_impl::operator==(const instruction::iterator::implementation& other) const noexcept {
    if (typeid(*this) != typeid(other))
        return false;
    return this->iter == static_cast<const compose_iterator_impl*>(&other)->iter;
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