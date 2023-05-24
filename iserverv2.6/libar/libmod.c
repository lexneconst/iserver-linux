
#include <iserver.h>

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

char * getmoduledir(void)
{
	char *ptr=NULL;
	char *file=NULL;
	uint32_t length = MAX_PATH;
    uint32_t size = 0;
    char *args[20];
do{	
	file = (char *) emalloc( length);
	if(file==NULL){
	   fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
	   break;
	}
	//getcwd(szfile, sizeof(szfile) );
	  
    sprintf(args,"/proc/%d/exe", getpid());
    size= readlink(args, file, MAX_PATH);
    file[size] ='\0';
    //printf("[%s]\n", file);

	if((ptr=strrchr(file, '\\' ))!=NULL) 
  	 { 	
  	    *ptr =0;
  	    ptr= NULL;
		
		length = strlen(file);
	}else
	if((ptr=strrchr(file, '/'))!=NULL){
	    *ptr=0;
		ptr=NULL;
		
		length = strlen(file);
	}
	   
	file[length] = '\0';
	
}while(0);
	return file;
}
