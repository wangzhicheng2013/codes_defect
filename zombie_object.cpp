
#include <stdio.h>
#include <string.h>
#include <iostream>
class Test {
private:
    char buf[16] = "123";
    int m = 10;
public:
    Test() {
        std::cout << "Test()" << std::endl;
    }
    ~Test() {
        std::cout << "~Test()" << std::endl;
    }
    void fun() {
        std::cout << "fun()" << std::endl;
        strcpy(buf, "5555555");
        m = 100;
        printf("%s\n", buf);
        printf("%zd\n", strlen(buf));
        std::cout << m << std::endl;
    }
};
void produce_zombie_object() {
    Test test;
    printf("test address:%p\n", &test);
    throw &test;     // will produce a temporary object 
}
void not_produce_zombie_object() {
    Test test;
    printf("test address:%p\n", &test);
    throw test;     // will produce a temporary object 
}
int main() {
    try {
        not_produce_zombie_object();
    }
    catch (Test* test) {                    // the temporary object will be deconstrcuted
        printf("test address:%p\n", test);  // is same with line:27
        test->fun();                        // zombie object pointer fun behavior is undefined
    }
    catch (Test& test) {
        printf("test address:%p\n", test);  // is not same with line:27
        test.fun();                         
    }
}