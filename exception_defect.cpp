#include <iostream>
#include <exception>
class Exception : public std::exception {
public:
    const char* what() {
        return "exception!";
    }
};
class Test {
public:
    ~Test() {
        throw Exception();  // will crash
    }
};
void throw_exception_pointer() {
    throw new Exception();
}
void test_throw_exception_pointer() {
    try {
        throw_exception_pointer();
    }
    catch (Exception *e) {       // enter
        std::cerr << e->what() << std::endl;
        1 / 0;                   // exception not happen
        std::cout << (1 / 0);    // exception happen
        delete e;                // can not reach here memory leak
        std::cout << "delete exception pointer!" << std::endl;
    }
}
void test_exception_in_destruction_function() {
    try {
        Test test;              // exception in ~Test can not be caught
        throw Exception();  
    }
    catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
}
int main() {
    //test_throw_exception_pointer();
    test_exception_in_destruction_function();

    return 0;
}