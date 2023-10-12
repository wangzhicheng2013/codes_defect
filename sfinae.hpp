#include <iostream>
#include <type_traits>
class counter {
public:
    virtual void inc() = 0;
};
template <class T>
class general_counter : public counter {
private:
    T obj_;
public:
    general_counter(const T& obj) : obj_(obj) {}
    virtual void inc() override {
        std::cout << "general counter increase!" << std::endl;
    }
};
// complied error!
// function define is the same!
/*
template <typename T>
void inc(T& t) {
    t.increase();
}
template <typename T>
void inc(T& t) {
    ++t;
}
*/
template <typename T>
void inc(T& t, std::enable_if_t<std::is_base_of<counter, T>::value>* = nullptr) {
    t.inc();
    std::cout << "call inc(T& t, std::enable_if_t<std::is_base_of<counter, T>::value>* = nullptr)!" << std::endl;
}
template <typename T>
void inc(T& t, std::enable_if_t<std::is_integral<T>::value>* = nullptr) {
    ++t;
    std::cout << "call inc(T& t, std::enable_if_t<std::is_integral<T>::value>* = nullptr)!" << std::endl;
}
int main() {
    int a = 1;
    general_counter<int>gc(a);
    inc(a); 
    inc(gc);

    return 0;
}