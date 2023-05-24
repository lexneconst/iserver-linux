#include <iserver.h>

char logs_fatal[MAX_PATH];

void fatal_init(void)
{
	memset(logs_fatal,0,sizeof(logs_fatal));
}
void fatal_fini(void)
{
	
}
void fatal_clean(void)
{
    memset(logs_fatal,0,sizeof(logs_fatal));
}

void fatal(char *str, const char *file,const char *func, unsigned long line)
{
	sprintf(logs_fatal,"%s,%d\0", str, line);
     printf("%s! %s %s,%s %d \n", __FUNCTION__, str, file, func, line);
}

int    get_fatal(char *str)
{
    //char *logs_ptr = (char *) &str;
	if(str != NULL){
		strcpy(str, logs_fatal);
	}	
    return 0;
}
