
#include "libcsp.h"


char *sign_digest(unsigned char *p,unsigned int len)
	{
	static char bufs[10][20];
	static int bnum=0;
	char *ret;
	int i;
	static char *f="0123456789ABCDEF";

	ret= &(bufs[bnum++][0]);
	bnum%=10;
	for (i=0; i<len/2; i++)
		{
		ret[i*2]=f[(p[i]>>4)&0xf];
		ret[i*2+1]=f[p[i]&0xf];
		}
	ret[len]='\0';
	return(ret);
}


uint32_t xspapi_module_startup(xspapi_module **ext,  zrequest_externs_t *request)
{
	xspapi_module  *req = (xspapi_module*) *ext;
	int           fd=-1;
	time_t        t;
	struct tm *   r;
	char          buff[MAX_PATH];
	char          digest[SHA512_DIGEST_LENGTH];
	CSHA512_CTX   sha512_ctx;
do{
	if(request==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	req = (xspapi_module *) xmalloc( sizeof(xspapi_module));
	if(req==NULL){
		fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	memset(req, 0, sizeof(xspapi_module));
	
	//printf("Loading (%s)(%d) \n", __FILE__, __LINE__);
	
	t = time(NULL);
	r = localtime(&t);
	//printf("Loading (%s)(%d) \n", __FILE__, __LINE__);
	if(r == NULL){
		fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	sprintf(buff, "%d %d %d %d %d %d %d %d %d %d\0", 
	  r->tm_sec,
      r->tm_min,
      r->tm_hour,
      r->tm_mday,
      r->tm_mon,
      r->tm_year,
      r->tm_wday,
      r->tm_yday,
      r->tm_isdst,
	  rand() );
   //printf("Loading (%s)(%d) \n", __FILE__, __LINE__);
   CSHA512_Init(&sha512_ctx);
   CSHA512_Update(&sha512_ctx, buff, strlen(buff));
   CSHA512_Final(digest, &sha512_ctx);
   //printf("Loading (%s)(%d) \n", __FILE__, __LINE__);      
   req->file = (char *)xmalloc( strlen(CCSHOW(request->ServerRoot))+ strlen(sign_digest(digest,SHA512_DIGEST_LENGTH ))+16 );
   if(req->file==NULL){
		fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
   }
   //printf("Loading (%s)(%d) \n", __FILE__, __LINE__);  
   strcpy(req->file, CCSHOW(request->ServerRoot) );
   if(req->file[strlen(req->file)-1] != '/'){
   	  strcat(req->file, "/");
   }
   //printf("Loading (%s)(%d) \n", __FILE__, __LINE__);  
   strcat(req->file, sign_digest(digest,SHA512_DIGEST_LENGTH ));
   //printf("Loading (%s)(%d) \n", __FILE__, __LINE__);  
   //printf("FILE (%s) \n", req->file);
   fd = open(req->file, O_CREAT, 0);
   if(fd!=-1){
   	
   	  if(chmod(req->file, S_IXUSR | S_IRUSR | S_IWUSR  ) != 0){
	     fatal("chmod file", __FILE__, __FUNCTION__, __LINE__);
	     if(remove(req->file) != 0){
	 	    fatal("remove file", __FILE__, __FUNCTION__, __LINE__);
  	     }
	  }
       
      close(fd);
      fd= -1;
      
      
      break;
   }
}while(0);
   //printf("Loading (%s)(%d) \n", __FILE__, __LINE__);  
   
	*ext = (xspapi_module *) req;
	
	return 0;
}
uint32_t xspapi_module_cleanup(xspapi_module **ext)
{
	xspapi_module  *req = (xspapi_module*) *ext;
	
do{
	if(req==NULL){
		
		break;
	}
	if(remove(req->file) != 0){
	   fatal("remove file", __FILE__, __FUNCTION__, __LINE__);
  	}
  	     
	if(req->file!=NULL)
	   XCLEAN(req->file);
	   
	XCLEAN(req);
}while(0);
	*ext = (xspapi_module *) req;
	
	return 0;
}
uint32_t xspapi_module_read(xspapi_module **ext, char **buffer, uint32_t *length)
{
	int   fd =0;
	xspapi_module  *req = (xspapi_module*) *ext;
    char      *buff=(char *) *buffer;
    uint32_t  len=(uint32_t) *length;
    uint32_t  size;
    struct stat st;
do{	
    if(req == NULL){
    	fatal("segment memory", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}
	if(req->file==NULL)
	{
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
    if(access(req->file,0) != 0){
    	fatal("access file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
    fd = open(req->file, O_RDONLY, 0);
	if(fd!=-1){
		//lseek(fd, 0, SEEK_END);
		if(fstat(fd, &st)==-1){
			fatal("fstat file", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		len = st.st_size;
		if(len <= 0){
			fatal("length file", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		buff = (char *) xmalloc( len+6 );
		if(buff==NULL){
			fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		lseek(fd, 0, SEEK_SET);
		//lseek(fd, 0, SEEK_SET);
		if((size= read(fd, buff, len)) == -1)
		{
			fatal("read file", __FILE__, __FUNCTION__, __LINE__);
		}
		buff[size] ='\0';
		
		close(fd);
		fd = -1;
	}else{
		fatal("open file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	*buffer = (char *) buff;
	*length = size;
}while(0);
    if(fd!=-1){
    	close(fd), fd=-1;
	}

	*ext = (xspapi_module *) req;
	return 0;
}
uint32_t xspapi_module_append(xspapi_module **ext, const char *str, uint32_t len)
{
	int   fd =0;
	xspapi_module  *req = (xspapi_module*) *ext;
    uint32_t  size;
do{	
    if(req == NULL){
    	fatal("segment memory", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}
	if(req->file==NULL)
	{
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
    if(access(req->file,0) != 0){
    	fatal("access file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
    fd = open(req->file, O_APPEND | O_WRONLY, 0);
	if(fd!=-1){
		//lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_END);
		//lseek(fd, 0, SEEK_SET);
		if((size= write(fd, str, len)) == -1)
		{
			fatal("write file", __FILE__, __FUNCTION__, __LINE__);
		}
		
		close(fd);
		fd = -1;
	}else{
		fatal("open file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
}while(0);
    if(fd!=-1){
    	close(fd), fd=-1;
	}

	*ext = (xspapi_module *) req;
	return 0;
}
uint32_t xspapi_module_error(xspapi_module **ext, const char *str)
{
	int       fd = -1;
	uint32_t  size = 0;
	uint32_t  len = 0;
	uint32_t  i = 0;
	char      buff[MAX_PATH];
	struct stat  st;
	
    xspapi_module  *req = (xspapi_module*) *ext;
do{
	if(req==NULL){
		break;
	}
	if(req->file==NULL)
	{
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	req->cerrno = 0;
	
	sprintf(buff, "%s script line: %d\n", str, req->line);
	//printf("ERR (%s) \n", buff);
    if(access(req->file,0) != 0){
    	fatal("access file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
    fd = open(req->file, O_WRONLY, 0);
	if(fd!=-1){
		//lseek(fd, 0, SEEK_END);
		if(fstat(fd, &st)==-1){
			fatal("fstat file", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		len = st.st_size;
		if(len <= 0){
			fatal("length file", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		
		for(i=0;i<len;i++){
		  lseek(fd, i, SEEK_SET); 	
		  if((size= write(fd, " ", 1)) == -1)
		  {
			fatal("write file", __FILE__, __FUNCTION__, __LINE__);
		  }
	    }
		
		lseek(fd, 0, SEEK_SET);
		//lseek(fd, 0, SEEK_SET);
		if((size= write(fd, buff, strlen(buff))) == -1)
		{
			fatal("write file", __FILE__, __FUNCTION__, __LINE__);
		}
		
		close(fd);
		fd = -1;
	}else{
		fatal("open file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
}while(0);
    if(fd!=-1){
    	close(fd), fd=-1;
	}
	*ext = (xspapi_module *) req;	
	return 0;
}

uint32_t xspapi_module_response(xspapi_module **ext, const char *str)
{
	int       fd = -1;
	uint32_t  size = 0;
	uint32_t  len = 0;
	uint32_t  i = 0;
	char      buff[MAX_PATH];
	struct stat  st;
	
    xspapi_module  *req = (xspapi_module*) *ext;
do{
	if(req==NULL){
		break;
	}
	if(req->file==NULL)
	{
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	req->cerrno = 0;
	
	sprintf(buff, "%s\n", str);
	//printf("ERR (%s) \n", buff);
    if(access(req->file,0) != 0){
    	fatal("access file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
    fd = open(req->file, O_WRONLY, 0);
	if(fd!=-1){
		//lseek(fd, 0, SEEK_END);
		if(fstat(fd, &st)==-1){
			fatal("fstat file", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		len = st.st_size;
		if(len <= 0){
			fatal("length file", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		
		for(i=0;i<len;i++){
		  lseek(fd, i, SEEK_SET); 	
		  if((size= write(fd, " ", 1)) == -1)
		  {
			fatal("write file", __FILE__, __FUNCTION__, __LINE__);
		  }
	    }
		
		lseek(fd, 0, SEEK_SET);
		//lseek(fd, 0, SEEK_SET);
		if((size= write(fd, buff, strlen(buff))) == -1)
		{
			fatal("write file", __FILE__, __FUNCTION__, __LINE__);
		}
		
		close(fd);
		fd = -1;
	}else{
		fatal("open file", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
}while(0);
    if(fd!=-1){
    	close(fd), fd=-1;
	}
	*ext = (xspapi_module *) req;	
	return 0;	
	return 0;
}
