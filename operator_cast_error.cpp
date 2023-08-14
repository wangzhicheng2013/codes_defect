#include <iostream>
#include <vector>
#include <cassert>
template <class T>
class Array {
private:
    std::vector<T>array_;
public:
    explicit Array(size_t sz) {
        if (0 == sz) {
            array_.resize(3);
        }
        else {
            array_.resize(sz);
        }
    }
    explicit Array(size_t sz, const T& val) {
        array_.resize(sz, val);
    }
    void push(const T& e) {
        array_.push_back(e);
    }
    T& operator[] (size_t index) {
        assert(index < array_.size());
        return array_[index];
    }
    const T& operator[] (size_t index) const {
        assert(index < array_.size());
        return array_[index];
    }
    size_t size() const {
        return array_.size();
    }
    friend bool operator != (const Array<T>&one, const Array<T>&other) {
        return !(one == other);
    }
    friend bool operator == (const Array<T>&one, const Array<T>&other) {
        std::cout << "Call operator ==" << std::endl;
        if (one.size() != other.size()) {
            return false;
        }
        int size = one.size();
        for (int i = 0;i < size;i++) {
            if (one[i] != other[i]) {
                return false;
            }
        }
        return true;
    }
};

template <class T>
class BadArray {
private:
    std::vector<T>array_;
public:
    BadArray(size_t sz) {
        if (0 == sz) {
            array_.resize(3);
        }
        else {
            array_.resize(sz);
        }
    }
    BadArray(size_t sz, const T& val) {
        array_.resize(sz, val);
    }
    void push(const T& e) {
        array_.push_back(e);
    }
    T& operator[] (size_t index) {
        assert(index < array_.size());
        return array_[index];
    }
    const T& operator[] (size_t index) const {
        assert(index < array_.size());
        return array_[index];
    }
    size_t size() const {
        return array_.size();
    }
    friend bool operator != (const BadArray<T>&one, const BadArray<T>&other) {
        return !(one == other);
    }
    friend bool operator == (const BadArray<T>&one, const BadArray<T>&other) {
        std::cout << "Call operator ==" << std::endl;
        if (one.size() != other.size()) {
            return false;
        }
        int size = one.size();
        for (int i = 0;i < size;i++) {
            if (one != other[i]) {      // write code error
                return false;
            }
        }
        return true;
    }
};

void test_array() {
    size_t n = 3;
    Array<int>A(n, n), B(n, n);
    if (A == B) {
        std::cout << "A is equal with B!" << std::endl;
    }   
}
void test_badarray() {
    size_t n = 3;
    BadArray<int>A(n, n), B(n, n);
    if (A == B) {
        std::cout << "A is equal with B!" << std::endl;
    }  
}
int main() {
    test_array();       // ok
    test_badarray();    // exhausting stack space

    return 0;
}