#pragma once
class handler {
private:
    static char* data;
public:
    handler() {
        load_data();
    }
    void load_data();
};