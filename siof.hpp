#pragma once
class handler {
public:
    static char* data;
public:
    handler() {
        load_data();
    }
    void load_data();
};