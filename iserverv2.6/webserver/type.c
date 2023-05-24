#include "iserver.h"

char   *rtype=NULL;

uint32_t request_inittype(const char *file)
{
      unsigned int ret = 0;
      int          fd = -1;
      unsigned int length =0;
do{
      if(file == NULL){
          fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
           break;
      }
      fd = open(file, O_RDONLY);
      if(fd == -1){
           fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
           break;
      }
      lseek(fd, 0, SEEK_END);
      length = get_filesize(fd);
      lseek(fd, 0, SEEK_SET);
      
      if(length <= 0){
          fatal("get filelength ", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      
      if(rtype!=NULL){
          fatal("memory new allocate ", __FILE__ ,__FUNCTION__, __LINE__);
      }
      rtype = (char *) emalloc( length+1);
      if(rtype ==NULL){
          fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      
      if(read(fd, rtype, length)<0){
          fatal("read memory failed.,", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      
      
}while(0);
      
      if(fd!=-1)
        close(fd);
      
      return ret;
}

char *request_contentType(const char *path, const char *type)
{
    char *ptr=NULL, *str=NULL;
    char  *last = (char *) path;
    char  *s = NULL;
    unsigned int pad = 0;
    
do{
    if(path == NULL){
           fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
           break;
      }
    if(type == NULL){
           fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
           break;
      }
    s = _new_str(type);
    if(s == NULL){
       fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
     
    if((last=strrchr(path, '.')) != NULL){
       //printf("lastname [%s] [%s] \n", last, path);
       while(1){
         if(pad >= strlen(type)) break;
         str = s + pad;
         if(strncmp(str, last , strlen(last))==0){
              //printf("=== [%s] \n", s); 
              
              if((ptr = strchr( str, '\n'))!=NULL){
                  *ptr=0;
                  ptr=NULL;
                  
                  str += strlen(last);
                  if(str[0] == '=') str+=1;
                  if(str[0] == ' ') str+=1;
                 // printf("ptr[%s] \n", str);
                  if(str[strlen(str)-1] =='\r')
                     str[strlen(str)-1] = '\0';
                 
                  ptr = _new_str(str);
                  //printf("[%s] \n", str); 
                  break;   
              }else{
                 //printf("[%s] [%s]\n", ptr, str); 
              }
              
         }
         pad+= 1;
         
       }
       
    }else{
       break;
    }
    
}while(0);
    if(s!=NULL)
      CLEAN(s);
      
    if(ptr==NULL)
      ptr= _new_str("application/x-oct-stream");
    
    return ptr;
}

char * request_contentLength(const char *path)
{
    int  fd;
    uint32_t   length=0;
    char *ptr=NULL;
    
  do{  
    if(path==NULL){
    	fatal("segment memory", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}
    fd = open(path, O_RDONLY,0);
    if(fd == -1){
       fatal("opening file. ", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    lseek(fd, 0, SEEK_END);
    length = get_filesize(fd);
    lseek(fd, 0, SEEK_SET);
    
  }while(0);
    close(fd);
    
    ptr = _new_str("XXXXXXXXXXXXXX");
    sprintf(ptr,"%d\0", length);
    
    return ptr;
}



char*  request_getheader(unsigned int code)
{ 
    unsigned int  length=0;
    char  buffer[1024];
    char *ptr;
    
	switch(code){
      case 200: strcpy(buffer,"HTTP/1.1 200 OK\0");
      break;
      case 201: strcpy(buffer,"HTTP/1.1 201 Created\0");      
      break;
      case 204: strcpy(buffer,"HTTP/1.1 204 No Content\0");
      break;
      case 205: strcpy(buffer,"HTTP/1.1 205 Reset Content\0");
      break;
      case 206: strcpy(buffer,"HTTP/1.1 206 Partial Content\0");
      break;
      case 400: strcpy(buffer,"HTTP/1.1 400 Bad Request\0");
      break;
      case 401: strcpy(buffer,"HTTP/1.1 401 Unautorized\0");
      break;
      case 403: strcpy(buffer,"HTTP/1.1 403 Forbidden\0");
      break;
      case 404: strcpy(buffer,"HTTP/1.1 404 Not Found\0");
      break;
      case 405: strcpy(buffer,"HTTP/1.1 405 Method Not Allowed\0");
      break;
      case 406: strcpy(buffer,"HTTP/1.1 406 Not Acceptable\0");
      break;
      case 407: strcpy(buffer,"HTTP/1.1 407 Proxy Authentication required\0");
      break;
      case 408: strcpy(buffer,"HTTP/1.1 408 Request Timeout\0");
      break;
      case 411: strcpy(buffer,"HTTP/1.1 411 Length Requestd\0");
      break;
      case 413: strcpy(buffer,"HTTP/1.1 413 Request Entity Too Large\0");
      break;
      case 414: strcpy(buffer,"HTTP/1.1 414 Request URL Too Long\0");
      break;
      case 415: strcpy(buffer,"HTTP/1.1 415 Unsupportrd Media Type\0");
      break;
      case 500: strcpy(buffer,"HTTP/1.1 500 Internal Server Error\0");
      break;
      case 501: strcpy(buffer,"HTTP/1.1 501 Not Implemented\0");
      break;
      case 502: strcpy(buffer,"HTTP/1.1 502 Bad Gateway\0");
      break;
      case 503: strcpy(buffer,"HTTP/1.1 503 Service Unavailable\0");
      break;
      case 504: strcpy(buffer,"HTTP/1.1 504 Gateway Timeout\0");
      break;
      case 505: strcpy(buffer,"HTTP/1.1 505 HTTP Version Not Supported\0");
      break;
      default:
         strcpy(buffer,"HTTP/1.1 404 NOT FOUND\0");
      break;
    }
	//printf("===========================================\n");
    
    return _new_str(buffer);
}

char * request_getstatus(unsigned int code)
{
    unsigned int length=0;
    char  buffer[1024];
    char *ptr;
    
    switch(code){
      case 200: strcpy(buffer,"Status: 200 OK\0");
      break;
      case 201: strcpy(buffer,"Status: 201 Created\0");      
      break;
      case 204: strcpy(buffer,"Status: 204 No Content\0");
      break;
      case 205: strcpy(buffer,"Status: 205 Reset Content\0");
      break;
      case 206: strcpy(buffer,"Status: 206 Partial Content\0");
      break;
      case 400: strcpy(buffer,"Status: 400 Bad Request\0");
      break;
      case 401: strcpy(buffer,"Status: 401 Unautorized\0");
      break;
      case 403: strcpy(buffer,"Status: 403 Forbidden\0");
      break;
      case 404: strcpy(buffer,"Status: 404 Not Found\0");
      break;
      case 405: strcpy(buffer,"Status: 405 Method Not Allowed\0");
      break;
      case 406: strcpy(buffer,"Status: 406 Not Acceptable\0");
      break;
      case 407: strcpy(buffer,"Status: 407 Proxy Authentication required\0");
      break;
      case 408: strcpy(buffer,"Status: 408 Request Timeout\0");
      break;
      case 411: strcpy(buffer,"Status: 411 Length Requestd\0");
      break;
      case 413: strcpy(buffer,"Status: 413 Request Entity Too Large\0");
      break;
      case 414: strcpy(buffer,"Status: 414 Request URL Too Long\0");
      break;
      case 415: strcpy(buffer,"Status: 415 Unsupportrd Media Type\0");
      break;
      case 500: strcpy(buffer,"Status: 500 Internal Server Error\0");
      break;
      case 501: strcpy(buffer,"Status: 501 Not Implemented\0");
      break;
      case 502: strcpy(buffer,"Status: 502 Bad Gateway\0");
      break;
      case 503: strcpy(buffer,"Status: 503 Service Unavailable\0");
      break;
      case 504: strcpy(buffer,"Status: 504 Gateway Timeout\0");
      break;
      case 505: strcpy(buffer,"Status: 505 HTTP Version Not Supported\0");
      break;
      default:
         strcpy(buffer,"Status: 404 Not Found\0");
      break;
    }
    //printf("===========================================\n");
    
	return _new_str(buffer);	
}
