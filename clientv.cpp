#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>

using namespace std;

int main()
{
	struct iovec iov[3];
	char myfifo[]="myfifo";
	mkfifo(myfifo,0666);
	int fd;
	fd=open(myfifo,O_RDWR);
	char buff[100];
	
	for(int i=0;i<3;i++)
	{
		iov[i].iov_base=buff;
		iov[i].iov_len=sizeof(buff);
	}
	write(fd,"i m client 1",13);
	cout<<"waiting for data...\n";

	pid_t p1;
	read(fd,buff,100);
	p1=atoi(buff);
	cout<<p1<<endl;
	sleep(2);
	int n=readv(fd,iov,3);
	if(n==-1)
	{
		perror("\nreadv iov error");
	}
	else
	{
		cout<<"RECEIVED DATA : \n\n";
		for(int i=0;i<3;i++)
		{
			cout<<endl<<i+1<<"->"<<(char *) iov[i].iov_base<<"->"<<iov[i].iov_len;
			sleep(2);
		}
	}
	cout<<"\nsent SIGINT signal to p1";
	kill(p1,SIGINT);
	close(fd);
	unlink(myfifo);
	return 0;
}     
