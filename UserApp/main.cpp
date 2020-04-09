#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

//__thread int x = 5;

void CallIoctl()
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";
	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return;
	}

	ret = ioctl(fd, 1, 0);	
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return;	
	}

	close(fd);
}

void *thread(void *arg)
{
	//x++;

	long i = (long)arg;
	if(i == 1)
	{
		/*
		sleep(3);
		cout << "thread 1: x = " << x << endl;

		unsigned long addr = (unsigned long)(&x);
		cout << "thread 1: addr of x = 0x" << hex << addr << endl;
		*/
		CallIoctl();
	}
	else
	{
		/*
		sleep(5);
		cout << "thread 2: x = " << x << endl;

		unsigned long addr = (unsigned long)(&x);
		cout << "thread 2: addr of x = 0x" << hex << addr << endl;
		*/
		CallIoctl();
	}

	return (void *)0;
}

int main()
{
	pthread_t tid1;
	if(pthread_create(&tid1, NULL, thread, (void *)1) != 0)
	{
		cout << "pthread_create error" << endl;
		return 0;
	}

	pthread_t tid2;
	if(pthread_create(&tid2, NULL, thread, (void *)2) != 0)
	{
		cout << "pthread_create error" << endl;
		return 0;
	}

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);

	return 0;
}
