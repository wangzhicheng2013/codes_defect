#include <stdio.h>
#include <iostream>
typedef struct _Object {
    int a;
    int b;
} Object;
Object* init_object() {
    Object* obj = (Object*)malloc(sizeof(Object));
    if (!obj) {
        return nullptr;
    }
    return obj;
}
void uninit_object_not_good(Object *obj) {
    if (obj) {
        free(obj);
        obj = nullptr;
    }
}
void uninit_object(Object **obj) {
    if (*obj) {
        free(*obj);
        *obj = nullptr;
    }
}
int main() {
    Object *obj = init_object();
    if (!obj) {
        return 0;
    }
    obj->a = 1;
    obj->b = 2;
    std::cout << obj->a << " " << obj->b << std::endl;
    uninit_object_not_good(obj);    // obj memory has been free but obj is not null
    obj->a = 100;   // write in released memory
    obj->b = 200;
    obj = init_object(); // reuse the previously released memory
    std::cout << obj->a << " " << obj->b << std::endl;      // 100 200
    uninit_object(&obj);    // it is ok
    if (obj) {              // obj is null and can not reach here
        std::cout << obj->a << " " << obj->b << std::endl;
    }

    return 0;
}