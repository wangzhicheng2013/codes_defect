#include <iostream>
class Base {
public:
    int a = 10;
    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
    }
    friend std::ostream& operator << (std::ostream &os, Base& base) {
        os << base.a << std::endl;
        return os;
    }
};
class Derive : public Base {
public:
    int b = 100;
    int c = 200;
    virtual ~Derive() {
        std::cout << "~Derive()" << std::endl;
    }
};
void show_array(std::ostream& os, Base array[], int n) {
    for (int i = 0;i < n;i++) {
        os << array[i];
    }
}
void delete_array(Base array[]) {
    delete[] array;
}
void test_show_array_ok() {
    const int N = 10;
    Base array[N];
    show_array(std::cout, array, N);
}
void test_show_array_error() {
    const int N = 10;
    Derive array[N];
    show_array(std::cout, array, N);
}
void test_delete_array_ok() {
    const int N = 10;
    Base* array = new Base[N];
    delete_array(array);
}
void test_delete_array_error() {
    const int N = 10;
    Base* array = new Derive[N];
    delete_array(array);
}
int main() {
    test_show_array_ok();
    test_show_array_error();
    test_delete_array_ok();
    test_delete_array_error();

    return 0;
}