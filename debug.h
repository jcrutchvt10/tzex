#ifndef _DEBUG_H
#define _DEBUG_H

#include <linux/errno.h>
#include <linux/err.h>

#define logd(fmt, args...)	printk("tz_exploit : %s "fmt, __FUNCTION__, ##args)


#endif // _DEBUG_H