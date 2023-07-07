#include <stdio.h>
#include <iostream>
#include <memory>
int *old_ptr = new int(100);
std::unique_ptr<int> return_new_unique() {
    return std::unique_ptr<int>(new int(1000));
}
std::unique_ptr<int> return_old_unique() {
    return std::unique_ptr<int>(old_ptr);
}
void test_return_new_unique() {
    std::unique_ptr<int>p1(new int(0));
    std::unique_ptr<int>p2(nullptr);
    p1 = return_new_unique();         
    p2 = return_new_unique();
    std::cout << *p1 << std::endl;      // 1000
    std::cout << *p2 << std::endl;      // 1000
    // p1 and p2 have different address
    printf("%p\n", p1.get());           // 0xXXXXXX
    printf("%p\n", p2.get());           // 0xXXXXB1
}

void test_return_old_unique() {
    std::unique_ptr<int>p1(new int(0));
    std::unique_ptr<int>p2(nullptr);
    p1 = return_old_unique();         
    p2 = return_old_unique();
    std::cout << *p1 << std::endl;      // 100
    std::cout << *p2 << std::endl;      // 100
    // p1 and p2 have the same address
    printf("%p\n", p1.get());           // 0xXXXXXX
    printf("%p\n", p2.get());           // 0xXXXXXX
}
int main() {
    test_return_new_unique();       // ok
    test_return_old_unique();       // double free dectected
    
    return 0;
}