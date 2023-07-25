#pragma once

template <typename T>
class AutoPtr {
public:
    explicit AutoPtr(T* ptr = nullptr) : ptr_(ptr) {}
    ~AutoPtr() { delete ptr_; }

    AutoPtr(AutoPtr& other) : ptr_(other.release()) {}
    template <typename U>
    AutoPtr(AutoPtr<U>& other) : ptr_(other.release()) {}

    AutoPtr& operator=(AutoPtr& other) {
        reset(other.release());
        return *this;
    }
    template <typename U>
    AutoPtr& operator=(AutoPtr<U>& other) {
        reset(other.release());
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }

    T* release() {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void reset(T* ptr = nullptr) {
        delete ptr_;
        ptr_ = ptr;
    }

private:
    T* ptr_;
};