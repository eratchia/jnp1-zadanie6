#pragma once

#include<memory>

template<class T> 
class type_iterator_impl {
private:
    
public:
    virtual std::unique_ptr<type_iterator_impl> clone() const noexcept = 0;

    virtual type_iterator_impl<T>& operator++() noexcept = 0;
    virtual T& operator*() const noexcept = 0;
    virtual T* operator->() const noexcept = 0;

    virtual bool operator==(const type_iterator_impl<T>&) const noexcept = 0;
};

template<class T>
class type_iterator {
public:
    using implementation = type_iterator_impl<T>;
private:
    std::unique_ptr<implementation> impl;
public:
    type_iterator(std::unique_ptr<implementation>);

    T& operator*() const noexcept;
    T* operator->() const noexcept;

    type_iterator<T>& operator++() noexcept;
    type_iterator<T> operator++(int) noexcept;

    bool operator==(const type_iterator<T>&) const noexcept;
    bool operator!=(const type_iterator<T>&) const noexcept = default;
};

template<class T>
type_iterator<T>::type_iterator(std::unique_ptr<type_iterator<T>::implementation> _impl) {
    impl = std::move(_impl);
};

template<class T>
T& type_iterator<T>::operator*() const noexcept {
    return impl.get()->operator*();
}

template<class T>
T* type_iterator<T>::operator->() const noexcept {
    return impl.get()->operator->();
}

template<class T>
type_iterator<T>& type_iterator<T>::operator++() noexcept {
    impl.get()->operator++();
    return *this;
}

template<class T>
type_iterator<T> type_iterator<T>::operator++(int) noexcept {
    type_iterator<T> old = type_iterator<T>(impl.clone());
    impl.get()->operator++();
    return old;
}

template<class T>
bool type_iterator<T>::operator==(const type_iterator<T>& other) const noexcept {
    return impl.get()->operator==(*other.impl.get());
}