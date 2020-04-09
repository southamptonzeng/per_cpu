#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

#define NUM_THREADS 15

// 多线程调用函数
void *pthread_fx( void *args ) {

    int fd = 0; // 文件描述符
    // 打开文件
    if((fd = open("/dev/msg_printer", O_RDWR)) < 0) {
        cerr << strerror(errno) << endl;
        return (void*) 0;
    }

    ioctl(fd, 1, 0);

    // 关闭文件
    close(fd);

    return (void*) 0;
}

int main() {

    int ret = 0;
    
    // 开启多线程
    pthread_t tids[NUM_THREADS];
    for ( int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create( &tids[i], NULL, pthread_fx, NULL);
        if ( ret != 0 ) {
            cout << "pthread_create error" << endl;
        }
    }

    // 回收线程资源
    for ( int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(tids[i], NULL);
    }
    
    return 0;
}
