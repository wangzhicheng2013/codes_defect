#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void crash_action1() {
    int *p = (int *)malloc(2 * sizeof(int));
    if (!p) {
        return;
    }
    int* q = (int *)realloc(p + 2, 3 * sizeof(int));    // crash here as p + 2 is invalid
}
void crash_action2() {
    int *p = (int *)malloc(2 * sizeof(int));
    if (!p) {
        return;
    }
    p[0] = 10;
    p[1] = 100;
    free(p);
    printf("p = %p, p[0] = %d, p[1] = %d\n", p, p[0], p[1]);   // 10, 100
    p = (int *)realloc(p, 6 * sizeof(int));         // crash here p is released
    if (!p) {
        return;
    }
    for (int i = 0;i < 6;i++) {
        p[i] = i * 1000;
    }
    free(p);
}
void memory_leak_action3() {
    int *p = (int *)malloc(2 * sizeof(int));
    if (!p) {
        return;
    }
    p[0] = 10;
    p[1] = 100;
    printf("p = %p, p[0] = %d, p[1] = %d\n", p, p[0], p[1]);   // 10, 100
    p = (int *)realloc(p, 6 * sizeof(int));                    // p changed
    if (!p) {
        return;
    }
    printf("p = %p, p[0] = %d, p[1] = %d\n", p, p[0], p[1]);   // 10, 100
    for (int i = 0;i < 6;i++) {
        p[i] = i * 1000;
    }
    free(p);                                        // memory leak
}
void memory_free_action4() {
    int *p = (int *)malloc(2 * sizeof(int));
    if (!p) {
        return;
    }
    p[0] = 10;
    p[1] = 100;
    printf("p = %p, p[0] = %d, p[1] = %d\n", p, p[0], p[1]);   // 10, 100
    p = (int *)realloc(p, sizeof(int));                        // p not changed
    if (!p) {
        return;
    }
    p[0] = 1000;
    printf("p = %p, p[0] = %d, p[1] = %d\n", p, p[0], p[1]);   // 1000, 100
    free(p);                                                   // memory is free
}
int main() {
    return 0;
}