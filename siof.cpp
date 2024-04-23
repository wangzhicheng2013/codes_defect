#include "siof.hpp"
char* handler::data = new char[1024];   // later than global variable initialization
void handler::load_data() {
    for (int i = 0;i < 10;i++) {
        data[i] = 'A' + i;  // crash here data is nullptr 
    }
}