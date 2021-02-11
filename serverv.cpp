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
	signal(SIGINT,SIG_DFL);
	struct iovec ov[3];	
	char myfifo[]="myfifo";
	int k=mkfifo(myfifo,0666);
	int fd;
	fd=open(myfifo,O_RDWR);
	int rfd;
	if((rfd=open("file.txt",O_RDWR))<=0)
		perror("error");

	for(int i=0;i<3;i++)
	{	char *buff=(char *)malloc(100);
		ov[i].iov_base=buff;			
		ov[i].iov_len=sizeof(buff);
		free(buff);
	}
	cout<<"waiting for client\n";
	char buff[100];
	read(fd,buff,100);
	cout<<buff<<endl;
	sleep(3);
	cout<<"sending pid to p2\n";
	pid_t p1=getpid();
	string s=to_string(p1);
	const char* c=s.c_str();
	write(fd,c,strlen(c));
	cout<<c<<endl;
	//sleep(5);
	
	int n=readv(rfd,ov,3);	
	if(n==-1)
	{
		perror("\nreadv ov error");
	}
	else
	{
		cout<<"\nsending data using writev to client ";
		writev(fd,ov,3);
		
	}
	cout<<"data is written\n";
	while(1);
	return 0;

}
