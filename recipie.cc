#include "recipie.h"

using std::initializer_list;
using std::unique_ptr;
using std::make_unique;

// Recipe
void Recipe::simplify() {};

// Instruction
Recipe::iterator Instruction::begin() const {
    InstructionIteratorImpl imp(this, 0);
    return imp.clone();
}
Recipe::iterator Instruction::end() const{
    InstructionIteratorImpl imp(this, 1);
    return imp.clone();
}
// InstructionIteratorImpl
Instruction::InstructionIteratorImpl::InstructionIteratorImpl(const Instruction* _instr_ptr, bool _end) noexcept: instr_ptr(_instr_ptr), end(_end){}
unique_ptr<Instruction::iterator::implementation> Instruction::InstructionIteratorImpl::clone() const noexcept {
    return make_unique<InstructionIteratorImpl>(instr_ptr, end);
}
const Instruction& Instruction::InstructionIteratorImpl::operator*() const noexcept {
    return *instr_ptr;
}
const Instruction* Instruction::InstructionIteratorImpl::operator->() const noexcept {
    return instr_ptr;
}
Instruction::InstructionIteratorImpl& Instruction::InstructionIteratorImpl::operator++() noexcept {
    end = 1;
    return *this;
}
bool Instruction::InstructionIteratorImpl::operator==(const Instruction::iterator::implementation& other) const noexcept {
    if (typeid(*this) != typeid(other))
        return false;
    auto instr_other = static_cast<const InstructionIteratorImpl*>(&other);
    if (instr_ptr != instr_other->instr_ptr)
        return false;
    return end == instr_other->end;
}

// Compose
std::unique_ptr<Compose> compose(initializer_list<std::unique_ptr<Recipe>> recipies) {
    for (auto&& recipie: recipies) {
        for(auto exec: *(recipie.get())) {

        }
    }
}
Recipe::iterator Compose::begin() const {
    ComposeIteratorImpl imp(instructions.begin());
    return imp.clone();
}
Recipe::iterator Compose::end() const {
    ComposeIteratorImpl imp(instructions.end());
    return imp.clone();
}
// ComposeIteratorImpl
Compose::ComposeIteratorImpl::ComposeIteratorImpl(inner_iterator _iter) noexcept: iter(_iter) {}
unique_ptr<Compose::iterator::implementation> Compose::ComposeIteratorImpl::clone() const noexcept {
    return make_unique<ComposeIteratorImpl>(iter);
}
const Executable& Compose::ComposeIteratorImpl::operator*() const noexcept {
    return iter->operator*();
}
const Executable* Compose::ComposeIteratorImpl::operator->() const noexcept {
    return iter->get();
}
Compose::ComposeIteratorImpl& Compose::ComposeIteratorImpl::operator++() noexcept {
    ++iter;
    return *this;
}
bool Compose::ComposeIteratorImpl::operator==(const Instruction::iterator::implementation& other) const noexcept {
    if (typeid(*this) != typeid(other))
        return false;
    return this->iter == static_cast<const ComposeIteratorImpl*>(&other)->iter;
}

// MoveForward
MoveForward::move_forward() {}
state MoveForward::next_state(const state& original) const {
    state next = original;
    next.move_forward(1);
    return next;
}

// MoveBackward
MoveBackward::move_backward() {};
state MoveBackward::next_state(const state& original) const {
    state next = original;
    next.move_forward(-1);
    return next;
}

// RotateLeft
RotateLeft::rotate_left() {}
state RotateLeft::next_state(const state& original) const {
    state next = original;
    next.turn_left();
    return next;
}

// RotateRight
RotateRight::rotate_right() {}
state RotateRight::next_state(const state& original) const {
    state next = original;
    next.turn_right();
    return next;
}