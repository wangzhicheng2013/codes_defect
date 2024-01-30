#include <stdio.h>
#include <string.h>
void test_src_is_same_with_dest() {
    char src[4] = "abc";
    char dest[4] = "123";
    strncpy(dest, src, strlen(src));
    printf("src:%s,dest:%s\n", src, dest);
    printf("src len:%zd,dest len:%zd\n", strlen(src), strlen(dest));
}
void test_src_is_less_than_dest() {
    char src[4] = "abc";
    char dest[7] = "123456";
    strncpy(dest, src, strlen(src));
    printf("src:%s,dest:%s\n", src, dest);
    printf("src len:%zd,dest len:%zd\n", strlen(src), strlen(dest));
}
void test_src_is_more_than_dest() {
    char src[4] = "abc";
    char dest[3] = "12";
    strncpy(dest, src, strlen(dest));             // will copy ab to dest
    printf("src:%s,dest:%s\n", src, dest);
    printf("src len:%zd,dest len:%zd\n", strlen(src), strlen(dest));
}
void test_defective_copy1() {
    char src[4] = "gho";
    char dest[7] = "abcdef";
    strncpy(dest, src, sizeof(dest));             // will add some \0 to dest end and elpase more time
    printf("src:%s,dest:%s\n", src, dest);
    printf("src len:%zd,dest len:%zd\n", strlen(src), strlen(dest));
}
void test_defective_copy2() {
    char src[1024 * 4] = "";
    for (int i = 0;i < sizeof(src) - 1;i++) {
        src[i] = 'A';
    }
    char dest[3] = "ab";
    char tmp[16] = { 0 };
    strncpy(dest, src, sizeof(src));             // dest space will crash
    printf("src:%s,dest:%s\n", src, dest);
    printf("src len:%zd,dest len:%zd\n", strlen(src), strlen(dest));
    printf("tmp:%s, len:%zd\n", tmp, strlen(tmp));
}
int main() {
    test_src_is_same_with_dest();
    test_src_is_less_than_dest();
    test_src_is_more_than_dest();
    test_defective_copy1();
    test_defective_copy2();

    return 0;
}