#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <linux/rwsem.h>
#include <asm/uaccess.h>
#include "DriverFileOperations.h"
#include "DriverMain.h"
#include "ToolFunctions.h"

DEFINE_PER_CPU(long, gUsage) = 0;

int DriverOpen(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": open invoked, do nothing\n");
	return 0;
}

int DriverClose(struct inode *pslINode, struct file *pslFileStruct)
{

	DEBUG_PRINT(DEVICE_NAME ": close invoked, do nothing\n");

	return 0;
}

ssize_t DriverRead(struct file *pslFileStruct, char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": read invoked, do nothing\n");
	return 0;
}

ssize_t DriverWrite(struct file *pslFileStruct, const char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	int i;
	int j = 0;
	long *pUsage = NULL;

	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");

	pUsage = this_cpu_ptr((long *)(&gUsage));
	
	DEBUG_PRINT(DEVICE_NAME ": pUsage = 0x%lx", (unsigned long)pUsage);

	for(i = 0; i < 10; i++)
	{
		DEBUG_PRINT(DEVICE_NAME ": CPU %d base = %lx\n", i, __per_cpu_offset[i]);
	}

	DEBUG_PRINT(DEVICE_NAME ": NR_CPUS = %d\n", NR_CPUS);

	for_each_online_cpu(j)
	{
		DEBUG_PRINT(DEVICE_NAME " CPU %d per cpu base = %lx\n", j, __per_cpu_offset[j]);
	}

	return 0;
}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
	long *pUsage = NULL;

	DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");

	preempt_disable(); //关抢占，会不会另一个核此时在开抢占呢?不会，因为关的是这个核的
	pUsage = this_cpu_ptr((long *)(&gUsage));
	(*pUsage)++; //调用计数
	preempt_disable(); //开抢占
	
	DEBUG_PRINT(DEVICE_NAME "pUsage is: %lx", *pUsage); //打印总共调用次数

	return 0;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}
