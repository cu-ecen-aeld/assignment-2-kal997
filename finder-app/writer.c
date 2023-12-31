#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h> // unix standard header
#include<string.h>
#include<stdio.h>
#include<syslog.h>
int main(int argc, char** argv)
{
	int retVal;
	
	openlog(NULL, 0, LOG_USER);

	if(argc != 3)
	{
		syslog(LOG_ERR, "wrong number of arguments: %d\n", argc);
		retVal = 1;
	}
	else
	{
		char* file = argv[1];
		char* string = argv[2];
		int fd;
		
		fd = open(file, O_RDWR);
		if(fd == -1)
		{
			syslog(LOG_ERR, "can not open file: %s", file);
			retVal = 1;
			
		}
		else
		{
			ssize_t nr;
			int len = strlen(string);
			nr = write(fd,string, len);
			if(nr == -1)
			{
				syslog(LOG_WARNING, "string is not written %s", string);
				retVal = 1;
			}
			else if(nr != len)
			{
				syslog(LOG_WARNING, "string is not fully written %s", string);
				retVal = 1;
			}
			else
			{	
				syslog(LOG_DEBUG, "Writing %s to %s", string, file);
				retVal = 0;
			}
	
		
		}
	}
	
	closelog();
	return retVal;

}
