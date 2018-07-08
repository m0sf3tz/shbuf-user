#ifndef PRU_IOCTL_H
#define PRU_IOCTL_H
#include <linux/ioctl.h>
#define SHBUF_IOC_MAGIC  's'


#define SPINLOCK_RESET           _IO(SHBUF_IOC_MAGIC, 1)


#endif
