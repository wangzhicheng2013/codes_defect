#include <iostream>
#include <string>
#include <tuple>
struct person {
    std::string name;
    int age;
    std::string hobby;
    friend std::ostream& operator << (std::ostream& os, const person& p) {
        os << p.name << " " << p.age << " " << p.hobby << std::endl;
        return os;
    }
};
int main() {
    person zhangsan{ "zhangsan", 18, "playing!"};
    const auto& [name, age, hobby] = zhangsan;              // const reference
    static_assert(!std::is_reference_v<decltype(name)>);    // name is value type 
    std::cout << (&name == &(zhangsan.name)) << std::endl;  // 1 the two addresses is the same
    //name = "lisi";  // error
    std::cout << zhangsan;
    std::tuple<std::string&, int&, std::string&>zhangsan_copy(zhangsan.name, zhangsan.age, zhangsan.hobby); 
    const auto& [name_tricky, age_tricky, hobby_tricky] = zhangsan_copy; // const reference
    static_assert(std::is_reference_v<decltype(name_tricky)>);  // reference type
    name_tricky = "lisi";   // can update
    std::cout << zhangsan;

    return 0;
}
