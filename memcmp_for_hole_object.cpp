#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// hole object
typedef struct _foo {
        unsigned char tag;
        union {
                double f;
                long i;
                char* p;
        } value;
} foo;
int main() {
    foo f1 = { 0, 0 };  // is not equal with foo f1 = {}; or foo f1 = {0}
    foo f2 = { 0, 0 };
    // show every byte
    const unsigned char* p = (unsigned char*)(&f1);
    for (unsigned char i = 0;i < sizeof(foo);i++) {
        printf("%u ", *(p + i));    // may be 0 100 109 176 254 127 0 0 0 0 0 0 0 0 0 0
    }
    printf("\n");
    p = (unsigned char*)(&f2);
    for (unsigned char i = 0;i < sizeof(foo);i++) {
        printf("%u ", *(p + i));    // may be 0 7 64 0 0 0 0 0 0 0 0 0 0 0 0 0
    }
    printf("\n");

    printf("%zd\n", sizeof(foo));   // 16 
    printf("%d\n", memcmp(&f1, &f2, sizeof(foo)));      // a rand value which is over 0
    printf("%d\n", memcmp(&f1, &f2, 1));                // 0

    return 0;
}