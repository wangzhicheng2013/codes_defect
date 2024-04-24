#include "siof.hpp"
handler global_handler; // will call load_data()
int main() {
    // todo
    if (global_handler.data != nullptr) {
        delete global_handler.data;
        global_handler.data = nullptr;
    }
    
    return 0;
}