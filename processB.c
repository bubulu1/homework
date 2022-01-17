#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(void)
{
	struct flock lock;
	//创建文件
	int fdb = open("processB_files",O_RDWR|O_CREAT,0664);


	//修改文件锁属性
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	//使用自定义锁属性替换文件原有的B：采用阻塞设置方式
	printf("set processB lock:F_WRLCK\n");
	fcntl(fdb,F_SETLKW,&lock);
	printf("set processB lock F_WRLCK success...\n");
	
	//打开进程A资源文件
	int fda = open("processA_files",O_RDWR);
	//替换进程A锁属性文件：阻塞方式
	sleep(5);
	printf("set processA lock:F_WRLCK\n");
	fcntl(fda,F_SETLKW,&lock);
	printf("set processA lock F_WRLCK success...\n");
	
	//解锁
	lock.l_type = F_UNLCK;
	fcntl(fda,F_SETLK,&lock);
	fcntl(fdb,F_SETLK,&lock);
	printf("set lock F_UNLCK success...\n");


	close(fda);
	close(fdb);

	return 0;
}

