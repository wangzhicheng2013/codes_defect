#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <iostream>
int main() {
    // create a file
    FILE *fp = fopen("./test.txt", "w+");
    if (!fp) {
        return -1;
    }
    int size = 100000;
    char* buf = (char*)malloc(sizeof(char) * size);
    if (!buf) {
        fclose(fp);
        return -1;
    }
    for (int i = 0;i < size;i++) {
        buf[i] = 'a';
    }
    fwrite(buf, size, 1, fp);
    fclose(fp);
    // use select to monitor file
    fd_set fds;
    FD_ZERO(&fds);
    int fd = open("./test.txt", O_RDWR, 0);
    if (fd < 0) {
        std::cout << "can not open file:./test.txt" << std::endl;
        return -1;
    }
    FD_SET(fd, &fds);
    struct timeval timeout = { 0, 100000 };  // 100 ms
    remove("./test.txt");   // delete the file
    for (int i = 0;i < 10;i++) {
        int ret = select(fd + 1, &fds, &fds, 0, &timeout);
        if (ret < 0) {
            std::cout << "select error!" << std::endl;
            close(fd);
            return 0;
        }
        if (0 == ret) {
            std::cout << "select timeout!" << std::endl;
            close(fd);
            return 0;
        }
        if (FD_ISSET(fd, &fds)) {       // can reach here
            std::cout << "select ok!" << std::endl;
            memset(buf, 0, sizeof(buf));
            // only the first time can show the correct result
            std::cout << "read size:" << read(fd, buf, size) << std::endl;
            std::cout << "read:" << buf << std::endl;
            for (int i = 0;i < size;i++) {
                buf[i] = 'b';
            }
            std::cout << "write size:" << write(fd, buf, size) << std::endl;
        }
        sleep(1);
    }
    close(fd);
    free(buf);
    std::cout << "fd = " << fd << std::endl;
    fd = open("./test.txt", O_RDWR, 0);
    close(fd);
    std::cout << "fd = " << fd << std::endl;        // -1

    return 0;
}