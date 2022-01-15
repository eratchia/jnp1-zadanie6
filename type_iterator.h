#pragma once

#include<memory>

template<class T> 
class TypeIteratorImpl {
private:
    
public:
    virtual std::unique_ptr<TypeIteratorImpl> clone() const noexcept = 0;

    virtual TypeIteratorImpl<T>& operator++() noexcept = 0;
    virtual T& operator*() const noexcept = 0;
    virtual T* operator->() const noexcept = 0;

    virtual bool operator==(const TypeIteratorImpl<T>&) const noexcept = 0;
};

template<class T>
class TypeIterator {
public:
    using implementation = TypeIteratorImpl<T>;
private:
    std::unique_ptr<implementation> impl;
public:
    TypeIterator(std::unique_ptr<implementation>);

    T& operator*() const noexcept;
    T* operator->() const noexcept;

    TypeIterator<T>& operator++() noexcept;
    TypeIterator<T> operator++(int) noexcept;

    bool operator==(const TypeIterator<T>&) const noexcept;
    bool operator!=(const TypeIterator<T>&) const noexcept = default;
};

template<class T>
TypeIterator<T>::TypeIterator(std::unique_ptr<TypeIterator<T>::implementation> _impl) {
    impl = std::move(_impl);
};

template<class T>
T& TypeIterator<T>::operator*() const noexcept {
    return impl.get()->operator*();
}

template<class T>
T* TypeIterator<T>::operator->() const noexcept {
    return impl.get()->operator->();
}

template<class T>
TypeIterator<T>& TypeIterator<T>::operator++() noexcept {
    impl.get()->operator++();
    return *this;
}

template<class T>
TypeIterator<T> TypeIterator<T>::operator++(int) noexcept {
    TypeIterator<T> old = TypeIterator<T>(impl.clone());
    impl.get()->operator++();
    return old;
}

template<class T>
bool TypeIterator<T>::operator==(const TypeIterator<T>& other) const noexcept {
    return impl.get()->operator==(*other.impl.get());
}