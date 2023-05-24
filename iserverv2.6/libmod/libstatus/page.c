#include "iserver.h"


char   *page=NULL;

uint32_t request_initpage(const char *file)
{
      unsigned int ret = 0;
      int          fd = -1;
      unsigned int length =0,size= 0;
do{
      if(file == NULL){
          fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
           break;
      }
      fd = open(file, O_RDONLY, 0 );
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
      
      if(page!=NULL){
           fatal("memory new allocate", __FILE__ ,__FUNCTION__, __LINE__);
      }               
      page = (char *) emalloc( length);
      if(page ==NULL){
          fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      
      if((size = read(fd, page, length))<0){
          fatal("read memory failed.,", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      page[size]='\0';
      
      //printf("> Length [%d] [%d]\n", length, size );
      //printf("[%s]\n", page);
     
}while(0);
      
      if(fd!=-1)
        close(fd);
      
      return ret;
}

char*  request_pageLength(const char *serverstatus, const char *servername)
{
     uint32_t   length=0;
     char       *ptr=NULL;
     
   do{
      if(page==NULL){
         fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
         break;
      }
      if(serverstatus==NULL){
      	fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
      	break;
	  }
	  if(servername==NULL){
	  	 fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
	  	 break;
	  }
      length = strlen(page)+ strlen(serverstatus)+strlen(servername);
      
      ptr = _new_str("XXXXXXXXXXX");
      sprintf(ptr,"%d\0",length);
      
   }while(0);
   
      return ptr;
}


uint32_t request_readpage(char *str, const char *status, const char *name, uint32_t length)
{ 
   uint32_t    size =0;
   do{
       if(str==NULL){
          fatal("heap allocate ",__FILE__,__FUNCTION__,__LINE__);
          break;
       }
       sprintf(str, page, status, name);
       size = strlen(page) + strlen(status) + strlen(name);
       //printf("[%s]", str);
       //printf("[%d,%d]\n", length, strlen(str));
       str[size-2]='\0';
       
   }while(0);
   
   return size-2;
}
