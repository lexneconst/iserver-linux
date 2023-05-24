#include "iserver.h"

char   *grfront=NULL;
char   *grback=NULL;
uint32_t  grfront_size = 0;
uint32_t  grback_size = 0;
char      *grdir=NULL;

uint32_t request_initdir(const char *file)
{
      unsigned int ret = 0;
      int          fd = -1;
      unsigned int length =0,size= 0;
      
      char *ptr=NULL,*str=NULL;
      uint32_t   l=0;
	  uint32_t   i=0;
      
     // grdir = _new_str(file);
      
do{
      //printf("> ^%s\n", file);
      
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
      
      if(grdir!=NULL){
           fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
      }
      grdir = (char *) emalloc( length+1 );
      if(grdir ==NULL){
          fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      
      if((size = read(fd, grdir, length))<0){
          fatal("read memory failed.,", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      grdir[size]='\0';
      
     
      //printf("> Length [%d] [%d]\n", length, size );
      //printf("[%s]\n", page);
     ptr =  _new_str(grdir);
     if((str = strchr(ptr, '['))!=NULL){
        *str=0;
        str=NULL;
        
        grfront      = _new_str(ptr);
        grfront_size = strlen(grfront);
        grfront[grfront_size]='\0';
        
		i = 0;
	    l = strlen(grfront);
	    do{
		   if(grfront[l]=='>'){
		      break;
		   }
		   grfront[l] ='\0';  
		   i++;
		   --l;
	    }while(l>0);
	    
		grfront_size-=i;
		
     }
     CLEAN(ptr);
    
     ptr = _new_str(grdir);
     if((str = strchr(ptr, ']'))!=NULL){
         str+=1;
       
         grback      = _new_str(str);
         grback_size = strlen(grback);
         grback[grback_size] = '\0';
         
     }
     CLEAN(ptr);
   
    
     CLEAN(grdir);
}while(0);
      
      if(fd!=-1)
        close(fd);
       
      return ret;
}



uint32_t request_dirinit(void)
{
   do{
      if(grfront==NULL){
         fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
         break; 
      }
      if(grback==NULL){
         fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
         break;
      }
   }while(0);
}

uint32_t request_dirfini(void)
{

}


#define DIRPARSENT1 "<tr><td><img src=\"%s\"></td><td valign=\"top\"><a href=\"%s\">Parent Directory</a></td> <td align=\"right\">-</td><td align=\"right\"> </td><td align=\"right\"></td></tr></br>\r\n\0"
#define DIRPARSENT2 "<tr><td><img src=\"%s\"></td><td valign=\"top\"><a href=\"%s\">Parent Directory</a></td> <td align=\"right\">-</td> <td align=\"right\"></td><td align=\"right\"></td></tr></br>\r\n\0"
#define DIRCHILD1   "<tr><td><img src=\"%s\"></td><td valign=\"top\"><a href=\"%s\">%s</a></td> <td align=\"right\"> %s </td> <td align=\"right\"> %s </td><td align=\"right\"></td></tr></br>\r\n\0"
#define DIRCHILD2   "<tr><td><img src=\"%s\"></td><td valign=\"top\"><a href=\"%s/%s\">%s</a></td> <td align=\"right\"> %s </td> <td align=\"right\"> %s </td><td align=\"right\"></td></tr></br>\r\n\0"
#define DIRCHILD3   "<tr><td><img src=\"%s\"></td><td valign=\"top\"><a href=\"%s%s\">%s</a></td> <td align=\"right\"> %s </td> <td align=\"right\"> %s </td><td align=\"right\"></td></tr></br>\r\n\0"
//#define DIRCHILD4   "<tr><td valign=\"top\"><a href=\"%s%s\">%s</a></td> <td align=\"right\"> %s </td> <td align=\"right\"> - </td></tr>\0"
#define K_SIZE  1000
#define M_SIZE  100000
#define G_SIZE  1000000000
#define T_SIZE  1000000000000000


char   *covert_size(uint32_t size)
{
     char   buff[64];
     if(size >= G_SIZE){
         sprintf(buff,"%dG", size/G_SIZE);
         //printf("^(%dK) %s \n", size, buff);
     }else
     if(size >= M_SIZE){
        //printf("^(M) \n", __FUNCTION__);
        sprintf(buff, "%dM", size/M_SIZE);
     }else
     if(size >= K_SIZE){
        //printf("^(G) \n", __FUNCTION__);
        sprintf(buff, "%dK", size/K_SIZE);
     #ifdef _TT_
     }else
     if(size > T_SIZE){
        //printf("^(T) \n", __FUNCTION__);
        sprintf(buff, "%dT", size/T_SIZE);
     #endif
     }else{
        sprintf(buff,"%d", size);
     }
     return _new_str(buff);
}
       
typedef struct _imagedir_t {
	char *name;
	char *value;
}imagedir_t;      

uint32_t get_lastfile(const char *name){
	
	char *ptr=NULL;
	if((ptr=strrchr(name, "."))!=NULL){
		ptr+=1;
		if(strcmp(ptr,"jpg") ==0) return 1;
		if(strcmp(ptr,"png") ==0) return 1;
		if(strcmp(ptr,"bmp") ==0) return 1;
		if(strcmp(ptr,"jpeg")==0) return 1;
		if(strcmp(ptr,"gif")==0) return 1;
		if(strcmp(ptr,"ico")==0) return 1;
	}
	return 0;
}
 
char *get_imgdir(const char *name, int st){
    uint32_t c=0;
	const imagedir_t file[] = {
	    {"file","/icons/file.gif"},
		{"top","/icons/top.gif"},
		{"img", "/icons/image.gif"},
	    {"dir", "/icons/folder.gif"},
	    {NULL, NULL},
	    NULL, NULL
	};
	
	while(&(file[c])!=NULL && file[c].name != NULL){
	    
	    if(strcmp(name, "..") ==0 && strcmp(file[c].name, "top") ==0 ){
	    	return file[c].value;
		}else
		if(st == _A_SUBDIR && strcmp(file[c].name, "dir" )==0)
		{
			return file[c].value;
		}else
		if(get_lastfile(name) && strcmp(file[c].name, "img")==0){
			return file[c].value;
		}
	    
	    c++;	
	}
	//printf("name(%s)\n", name);	
    
    return file[0].value;
}	
                    
long request_dirliststart(char *path)
{
     char*     file=NULL, *buffer=NULL;
     uint32_t  length=0;
     long      hfdl;
     struct _finddata_t fds;
  do{
     if(path==NULL){
        fatal("stack memory ", __FILE__,__FUNCTION__,__LINE__);
        break;
     }          
     length = strlen(path)+16;
     
     if(file!=NULL){
          fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
     }
     file = (char *) emalloc( length);
     if(file==NULL){
        fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
        break;   
     }
     sprintf(file,"%s*.*", path);
     
     hfdl = _findfirst(file, &fds);
     if(hfdl==-1){
        fatal("open file", __FILE__,__FUNCTION__,__LINE__);
        break;
     }   
     
     if(strcmp(fds.name,".")==0 )
     {
     }else{
        
     } 
  }while(0);
     CLEAN(file);
  //   buffer=  _new_str("XXXXXXXXXXXXX");
     
     return hfdl;

}

char* request_dirlistloop(long *hfd,const char *path,  uint32_t *size)
{
    char       *buffer=NULL,*ptr,*str=NULL,*ssize=NULL, date[64];
    uint32_t   length =0;
    struct _finddata_t fds;
    struct tm*         tsm;
    long    hfdl= (long)*hfd;
    unsigned ret=0;
    const char *listdate[12] = {"Jan","Fab","Mar","Apr","May","Jun","Juk",
	                            "Aug","Sep","Oct","Nov","Dec" };
    const char *listweek[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"}; 
    uint32_t    l=0;
	uint32_t    i=0;
	
 do{   
    if(hfdl <= 0){
        fatal("invalid handler", __FILE__,__FUNCTION__,__LINE__);
        break;
    }
    if(_findnext(hfdl, &fds)==-1){ 
        break;   
    }
    
    
    tsm = localtime(&fds.time_create);    
    sprintf(date, "%2d:%2d:%2d %s %2d/%s/%4d \n",
                     tsm->tm_hour, tsm->tm_min, tsm->tm_sec,
                     listweek[tsm->tm_wday],
                     tsm->tm_mday, listdate[tsm->tm_mon], tsm->tm_year+1900
                     );
    
    if(strncmp(fds.name, "..", 2)==0){
        length = strlen(get_imgdir(fds.name, fds.attrib))+ strlen(DIRPARSENT1)+ strlen( fds.name ) + strlen(date)+ strlen(path);
    }else{
        length = strlen(get_imgdir(fds.name, fds.attrib))+ strlen(DIRCHILD1) + strlen( fds.name)+strlen(fds.name)+strlen(path) + strlen(date);
    }
    //printf("> %s \n", fds.name);
    if(buffer!=NULL){
        fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
    }
    buffer = (char *) emalloc( length + 8 );
    if(buffer == NULL){
        fatal("allocate memory", __FILE__,__FUNCTION__,__LINE__);
        break;
    }
    memset(buffer,0, length);
    //printf("path: (%s) \n", path);
    
    if(strncmp(fds.name, "..", 2)==0){
        if(strlen(path)>2){
           //printf("======================\n");
           str = (char *)_new_str( path );
           if(str[strlen(str)-1]=='/')
              str[strlen(str)-1] = '\0';
           
           if((ptr = strrchr(str,'/'))!=NULL){
                *ptr=0;
                ptr = NULL;
               //*ptr=0;                   
               
               //printf("> (*%s) \n", str);
               if( strlen(path)>=2 && strlen(str)>=2){
                  sprintf(buffer, DIRPARSENT2, get_imgdir(fds.name, fds.attrib), str, fds.name);   
               }else{
                  sprintf(buffer, DIRPARSENT1, get_imgdir(fds.name, fds.attrib), fds.name);
               }
               //printf("(%s)\n", buffer);
               
               CLEAN(str);
           }
           	
        }else{   
           sprintf(buffer, DIRPARSENT1, get_imgdir(fds.name, fds.attrib), fds.name);
        }
    }else{
        ssize = covert_size(fds.size);
        
        if(path[strlen(path)-1] == '/'){
          sprintf(buffer, DIRCHILD3, get_imgdir(fds.name, fds.attrib), path,fds.name, fds.name, date, ssize );
        }else{
          if(strlen(path)>2){
             sprintf(buffer, DIRCHILD2,  get_imgdir(fds.name, fds.attrib), path, fds.name, fds.name, date, ssize );
          }else{
             sprintf(buffer, DIRCHILD1, get_imgdir(fds.name, fds.attrib), fds.name, fds.name, date, ssize);
          }
        }
        CLEAN(ssize);
    }
	
	ptr = _new_str(buffer);
    i = 0;
	l = strlen(ptr);
	do{
		if(ptr[i]=='<'){
		   ptr+= i;
		   break;
		}
		i++;
		--l;
	}while(l>0);
	
	strcpy(buffer, ptr);
	length -= i;
	
	CLEAN(ptr);
	
    //printf("==[%s]==[%s]\n", __FUNCTION__, buffer);
    ret = 1;
    
}while(0);
    *size = length;
    
    *hfd=hfdl;
    
    return buffer;
}
uint32_t request_dirlistend(long *hfd)
{
  long  hfdl = (long) *hfd;
  do{
     if(hfdl) _findclose(hfdl),hfdl=-1;
  }while(0);
     *hfd = hfdl;
     
     return 0;
}
         


uint32_t request_getfrontsize(char *path){ return grfront_size+strlen(path)+8;  }

uint32_t request_getfront(char *buffer, uint32_t length, const char *path)
{
    uint32_t   size = 0;
    
    do{
       if(buffer==NULL){
           fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
           break;
       }
       sprintf(buffer, grfront, path, path);
       size = strlen(grfront) + strlen(path) + strlen(path) - 2;
       
	   buffer[size]= '\0';
          
    }while(0);
    
    return size-2;
}

uint32_t request_getbacksize(
   const char *name,const char *ver, const char *os, const char *addr, char *port)
{  
         
         return grback_size+strlen(name)+strlen(ver)+strlen(os)+strlen(addr)+strlen(port)+2; 
}

uint32_t request_getback(char *buffer, uint32_t length, 
   const char *name,const char *ver, const char *os, const char *addr, char *port)
{
    uint32_t  size=0;
    do{
       if(buffer==NULL){
           fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
           break;
       }
       
       sprintf(buffer, grback, name, ver, os, addr, port);
       size = strlen(grback) + strlen(name) + strlen(ver) + 
              strlen(os) + strlen(addr)+ strlen(port);
       //if(size > 0) buffer[size] = '\0';
       
       //printf("%s\n", buffer);
       //printf("size (%d)\n", size); 
       
    }while(0);
    
    return size-9;
}
