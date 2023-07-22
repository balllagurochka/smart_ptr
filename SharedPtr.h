#pragma once

template <typename T>
class SharedPointer {
public:
    SharedPointer() :
        data_(nullptr), data_count_(new int(0)) { }
    explicit SharedPointer(T* data) :
        data_(data), data_count_(new int(1)) { }
    SharedPointer(const SharedPointer& other) :
        data_(other.data_),
        data_count_(other.data_count_) {
        ++(*data_count_);
    }

    ~SharedPointer() {
        release();
    }

    void release() {
        --(*data_count_);
        if (*data_count_ == 0) {
            delete data_;
            delete data_count_;
        }

    }

    void reset(T* const data) {
        release();
        data_ = data;
        data_count_ = new int(1);
    }

    T* get() const {
        return data_;
    }

    SharedPointer& operator=(const SharedPointer& other) {
        if (this->data_ != other.data_) {
            release();
            data_ = other.data_;
            data_count_ = other.data_count_;
            ++(*data_count_);
        }
        return *this;
    }

private:
    T* data_;
    int* data_count_;
};