#include "linux/version.h"

int main()
{
	if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0))
		return 0;
	else
		return 1;
}
