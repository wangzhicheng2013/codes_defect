#include <stdlib.h>
#include <iostream>
#include <chrono>
struct time_elapse {
    void start() {
        start_ = std::chrono::steady_clock::now();
    }
    double end() {
        std::chrono::duration<double>dura = std::chrono::steady_clock::now() - start_;
        return dura.count();
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> start_ = std::chrono::steady_clock::now();
};
class Base {
public:
    virtual void vfun() {}
};
class Derived : public Base {
public:
    virtual void vfun() override {}
};
void call_vfun(Base* p) {
    p->vfun();
}
// ./Test 1000000000
// call base fun:5.2597
// call derived fun:5.25928
int main(int argc, char** argv) {
    if (argc != 2) {
        return -1;
    }
    int loop = atoi(argv[1]);
    Base* base = new Base;
    Base* derived = new Derived;
    time_elapse te;
    te.start();
    for (int i = 0;i < loop;i++) {
        call_vfun(base);
    }
    std::cout << "call base fun:" << te.end() << std::endl;

    te.start();
    for (int i = 0;i < loop;i++) {
        call_vfun(derived);
    }
    std::cout << "call derived fun:" << te.end() << std::endl;

    delete base;
    delete derived;
    
    return 0;
}