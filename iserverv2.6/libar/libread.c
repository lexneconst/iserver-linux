#include "iserver.h"

#define STREAM_BINARY 0
#define STREAM_TEXT   1

uint32_t 
request_cflags(const char *path)
{
    char *ptr = NULL;
    char *last= NULL;
    unsigned int ret = STREAM_BINARY;
    
    struct stat ts;
    int    fd;
    
do{
   //memset(&ts, 0, sizeof(ts));
   fd = open(path, O_RDONLY, 0);
   if(fd == -1){
      fatal("open file", __FILE__,__FUNCTION__,__LINE__);      
      break;
   }
   
   if(fstat(fd, &ts)==-1){ 
      fatal("open length", __FILE__,__FUNCTION__,__LINE__);
      break;
      //return 0;
   }
   
   /*if(ts.st_mode == O_BINARY){
      printf(">>>>>>>>>>>>>> \n");
   }else
   if(ts.st_mode == O_TEXT){
      printf("<<<<<<<<<<<<<< \n");
   }else{*/
    /* printf("> %s \n", path);
     printf("> %x %x\n", ts.st_mode, ts.st_mode>>8); 
     printf("> %x\n", ts.st_gid ); 
     printf("> %x\n", ts.st_uid );
   */
   
   
}while(0);
  
   if(fd!=-1) close(fd);
  
   //return (int)ts.st_size;
   
do{    
    if(path == NULL) break;
    if((last=strrchr(path, '.')) != NULL){    
        if(strcmp(last, ".html") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".htm") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".js") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".css") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".txt") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".shtml") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".asc") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".htt") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".java") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".jsx") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".jsp") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".jspx") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".php") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".php3") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".php4") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".php5") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".asp") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".aspx") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".xhtml") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".xht") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".xsl") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".xml") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".xslt") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".vbs") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".xht") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".c") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".cpp") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".c++") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".hpp") == 0){
            ret = STREAM_TEXT;
            break;
         }else
         if(strcmp(last,".h") == 0){
            ret = STREAM_TEXT;
            break;
         }
    }
}while(0);

    return ret;
}

uint32_t  request_read(char *path,char *buffer,uint32_t  length)
{
     int fd=-1;
     uint32_t   size = 0;
     
   do{
       if(path==NULL){
          fatal("path null",__FILE__,__FUNCTION__,__LINE__);
          break;
       }
       if(buffer==NULL){
          fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
          break;
       }
       
       
      fd = open(path, O_RDONLY);
      if(fd == -1){
           fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
           break;
      }
      //lseek(fd, 0, SEEK_END);
      //length = get_filesize(fd);
      //lseek(fd, 0, SEEK_SET);
      
      if(length <= 0){
          fatal("get filelength ", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      
      if((size = read(fd, buffer, length))<0){
          fatal("read memory failed.,", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
	  
	  
      //printf("> Length [%d] [%d]\n", length,size);
      //printf("[%s]\n", page);
      //'if(size < length)
       //  buffer[size]='\0';
      
   }while(0);
      
      if(fd!=-1)
        close(fd);
       
   if(request_cflags(path)>0){  return size;  }
   return length;
}
