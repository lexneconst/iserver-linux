#include "iserver.h"

uint32_t path_check_folder(unsigned short st)
{
	if (((st >> 8) & 0xff)-1 == ((S_IFDIR>> 8) & 0xff)) return 1;
	return 0;
}

char     *  request_ascii(const char *buffer)
{
     char          *ptr=(char *) buffer;
     unsigned int   i=0, length= strlen(buffer);
     unsigned char  byte =0;
     
     do{
        if(ptr==NULL) break;
        
        for(;;){
            if(length >= i) break;
            byte = ptr[i];
            if((byte>31)&&(byte<127)){ 
               
            }else{
               return NULL;
            }
            
            i+= 1;      
        }
        
     }while(0);
     
     return  ptr;
}
char * request_pathdecrypt( char * s)
{
    char *  c = (char *)s;
    char *  b = s;
    unsigned int i,l=0;
    //printf("[%s] <%s> \n", __FUNCTION__, c);
    
    for(i=0;i<=strlen(c);i++){
      
       if(strncmp(c+i, "%20",3)==0){
          i += 2;
          b[l] = ' ';
       }else
       if(strncmp(c+i, "%60",3)==0){
          i+= 2;             
          b[l] = '`';
       }else{
          b[l] = c[i];
       }
       l+=1;
       //printf(">> [%s] [%s]\n", b, c);
    }
    //printf("[%s] <%s> \n", __FUNCTION__, b);
    
    return b;
}


uint32_t request_search_file(const char *file)
{
   unsigned long p=0; // file found
   struct stat st;
   int  s=-1, c=-1;
   
   memset(&st, 0, sizeof(struct stat));
do{
   //if(file[strlen(file)-1] == '/')
   //{
   //    p =2;
   //    break;
   //}
   s = open(file, O_RDONLY);
   if(s != -1){
      p= 1;
      break;
   }
   
   c = stat(file, &st);
   #ifdef DEBUG_H
   printf("[%s] (%s) STAT[%d][%d] \n", __FUNCTION__,file, c, st.st_mode );
   #endif
   if(c == -1){ 
     p = 0; // not found
     break;
   }
   #ifdef DEBUG_H
   printf("[%s] (%s) STAT[%d][%d] \n", __FUNCTION__,file, ((S_IFDIR>> 8) & 0xff), ((st.st_mode >> 8) & 0xff)-1 );
   #endif
   if(path_check_folder(st.st_mode)){ 
     p = 2; // directory
     break;
   }
   
}while(0);

   if(s!=-1)
     close(s), s=-1;
   //if(c!=-1)
   //  close(c), c=-1;
   //printf("[%s] <%s> \n", __FUNCTION__, file);   
      
   return p;
}


char *search_listpad(const char * s)
{
    char * b = (char *) s;
    char * p =NULL;
    
    if((p = strchr(b, ','))!= NULL){
       *p=0;
       p=NULL;
    }else{
       b=NULL;
    }
    
    return b;
}
uint32_t request_search_fileindex(_MGC_STRING s, const char* f,int *mode)
{
     char*  b=NULL;
     unsigned int pad =0;
     char*  c=NULL;
     
     *mode = 0;
     //printf("%s, %s\n", __FUNCTION__, s);
     
do{
    for(;;){
       b = search_listpad(f+pad);
       if(b == NULL){
       	  //printf("%x \n", b); 
       	  break;
	   }
       pad += strlen(b)+1;
       //printf("%s, %s\n", __FUNCTION__, s);
       if(c !=NULL){
           fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
           break;
       }
       c = (char*) emalloc( strlen(CCSHOW(s))+ strlen(b) + 2);
       if(c != NULL){
          
          strcpy(c, CCSHOW(s));
          strcat(c, b);
          
          #ifdef DEBUG_H
          printf("%s=%s\n", __FUNCTION__, c);
          #endif
          
          if(access(c, 0) == 0){
              // true file
              *mode = 1;
              //printf("c:[%s] \n", c);
              CCRENEW(s, c);
              CLEAN(c);
			  return 1;
              //break;
          }
          
          CLEAN(c);
          //if(c!=NULL)
          //  free_t(c), c=NULL;
       }else{
       	 fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
       	 break;
	   }
       //printf("[%s] <%s%s>\n", __FUNCTION__, s, b);
     
    }
}while(0); 
     //printf("[%s] {%s} {%s} \n", __FUNCTION__, s, f);
	 return 0;
}
uint32_t request_search_filename(_MGC_STRING  s, const char* f,int *status)
{
     char*  b=NULL;
     unsigned int pad =0;
     char*  c=NULL;
     
     *status = 0;
do{
    for(;;){
       b = search_listpad(f+pad);
       if(b == NULL) break;
       pad += strlen(b)+1;
       
       if(c != NULL){
           fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
       }
       c = (char*) emalloc( strlen(CCSHOW(s))+ strlen(b) + 32);
       if(c != NULL){
          
          strcpy(c, CCSHOW(s));
          strcat(c, b);
          #ifdef DEBUG_H
          printf("%s=%s\n",__FUNCTION__, c);
          #endif
		  if(access(c, 0) == 0){
              // true file
              *status = 1;
              //printf("c:[%s] \n", c);
              CCRENEW(s, c);
              CLEAN(c);
			  return 1;
              //break;
          }
          CLEAN(c);
          //if(c!=NULL)
           // free_t(c), c=NULL;
       }
       //printf("[%s] <%s%s>\n", __FUNCTION__, s, b);
     
    }
}while(0); 
     *status = 0;
     //printf("[%s] {%s} {%s} \n", __FUNCTION__, s, f);
     return 0;
}

uint32_t request_search_directory(_MGC_STRING s, int *mode)
{
    struct stat st;
    char*  c=NULL;
    unsigned int length;
    
	*mode = 2;
    
do{ 
    //printf("cccccccccccccccccccccc\n");
    if(s==NULL){
       fatal("heap allocate",__FILE__,__FUNCTION__,__LINE__);
       break;
    }
    length = strlen(CCSHOW(s));
    
    if(c !=NULL){
        fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
    }
    c = (char*) emalloc( length +2 );
    if(c == NULL)
    {
       fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    //printf("cccccccccccccccccccccc\n");
    strcpy(c, CCSHOW(s) );
    if(c[strlen(c)-1]!='/')
    strcat(c, "/");
    
    //b= (char *)c;
    #ifdef DEBUG_H
    printf("%s=%s\n", __FUNCTION__, c);
    #endif
	//printf("cccccccccccccccccccccc\n");
    if(stat(c, &st)!=-1){
      if( path_check_folder(st.st_mode)){
      	  *mode = 0;
      	  break;
	  } 
    }
    if(access(CCSHOW(s), 0) == 0){
      *mode=  1;
      break;
    }
    //
    //if(b!=NULL)
    //  free_t(b), b=NULL;
      
}while(0);
    //CLEAN(c);  
    if(*mode==2){ 
       CLEAN(c);
       return 0; 
    }else 
	if(*mode==1){
	   CLEAN(c);
	   return 0;
    }else{ 
       //CLEAN(s);
       CCRENEW(s, c);
       CLEAN(c);
       return 1;
    }
}


uint32_t  request_path(zrequest_externs_t **s)
{
    zrequest_externs_t  *p = (zrequest_externs_t *) *s;
    int  status = 503;
    int  mode = 0;
    
    do{
         
        if(p==NULL){
           fatal("heap allocate ",__FILE__,__FUNCTION__,__LINE__);
           break;
        }
        //printf("::::::::::::::::::::::\n");  
        CCNEWADD(p->PathTranslated, p->DocumentRoot, p->FileSelf);
        //printf("PATH::%s\n", CCSHOW(p->PathTranslated));
		if(CCCHECK(p->PathTranslated))
        {
            fatal("segment memory failed.,", __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        CCCLONE(p->FullPathTranslated , p->PathTranslated);
        //printf("PATH::%s\n", CCSHOW(p->PathTranslated));
        //printf("::::::::::::::::::::::\n");  
        CCNEW( p->PathTranslated, request_pathdecrypt(CCSHOW( p->PathTranslated)));
        
//        /printf("PATH::%s\n", CCSHOW(p->PathTranslated));
        
        status = request_search_file(CCSHOW(p->PathTranslated));  
		#ifdef DEBUG_H
		printf("%s, %d=%s \n", __FUNCTION__, status, CCSHOW(p->PathTranslated));  
        #endif
		if(status == 2){ // directory search indexfile
		    status = 100;
            //printf("STATUS: 2 (%s) \n", p->PathTranslated);
             if(CCSTAT(p->PathTranslated,'/')){
                 request_search_fileindex( 
                     p->PathTranslated, 
                     CCSHOW(p->FileIndexName), &mode);
                 if(mode == 1){
                 	status =200;
                 	break;
				 }
            }else{
            	status = 100;
                request_search_directory( 
                             p->PathTranslated ,
							 &mode);
            	if(mode == 0){
            	   #ifdef DEBUG_H
				   printf("-FILE (%s) , mode(%d) \n",CCSHOW(p->PathTranslated), mode);  	
			       #endif
				   request_search_fileindex( 
                      p->PathTranslated , 
                      CCSHOW(p->FileIndexName), &mode);
                   #ifdef DEBUG_H
				   printf("+FILE (%s) , mode(%d) \n", CCSHOW(p->PathTranslated), mode);  
                   #endif
				   if(mode == 1){
                   	  status =200;
				   }
			    }else{
				   if(status != 404) status = 100;
		        }
			}
            //printf("^%s \n", p->PathTranslated);
            //p->PathTranslated = _new_str(p->PathTranslated);  
           
            break;               
        }else if(status == 1){ // skip
           //printf("STATUS: 1 (%s) \n", p->PathTranslated);
           ///p->PathTranslated = _new_str(p->PathTranslated);
           status = 200;
           break;
        }else if(status == 0){ // not found search lastfile and directory
            //printf("STATUS: 0 (%s) \n", p->PathTranslated);
              if(CCSTAT(p->PathTranslated,'/')){
                  request_search_fileindex( 
                    p->PathTranslated, 
                    CCSHOW(p->FileIndexName),
                    &mode);
                 if(mode == 0)
                  {
                      status = 404;
                     // printf("**************************\n");
                      //p->PathTranslated = _new_str( p->PathTranslated ); // lastfile name found
                   //   break;
                  }else{
                     status = 200;
                  }
                  break;
			  }else{
			  	#ifdef DEBUG_H
			  	printf("FILENAME(%s) = (%s) \n", CCSHOW(p->PathTranslated), __FUNCTION__);
			  	#endif
				request_search_directory( 
                             p->PathTranslated ,
							 &mode);
				#ifdef DEBUG_H
				printf("MODE (%d) PATH(%s) \n", mode, CCSHOW(p->PathTranslated));
				#endif
				if(mode == 0){
                   status = 100;
                    request_search_fileindex( 
                            p->PathTranslated ,
						    CCSHOW(p->FileIndexName) ,
						    &mode );
				   if(mode == 1)
                   {
                   	    status = 200;
                   	    break;
			       }
                   break;
                }else if(mode == 1){
				   status = 200;
				   break;
                }else if(mode == 2){
					 #ifdef DEBUG_H
					 printf("FILENAME(%s) = (%s) \n", CCSHOW(p->PathTranslated), __FUNCTION__);
                     #endif
					    request_search_filename( 
                           p->PathTranslated, 
                           CCSHOW(p->FileLastName),
                           &mode);
              //printf("MODE (%d) (%s) \n", mode, p->PathTranslated);     
              //printf("::::::::::::::::::::::\n"); 
                    if(mode == 0)
                    {
                       status = 404;   
                    }else{
                       status = 200;
                    }
              }
           }
           // p->PathTranslated = _new_str( p->PathTranslated ); // not found 
            //break;
        }
        
        
    }while(0);
    
    request_checkfile(CCSHOW(p->PathTranslated), &status);
    //printf("++%d,PATH[%s]\n",status, p->PathTranslated);
    
    *s = p;
    
    return status;
}

uint32_t request_checkfile(const char *path, uint32_t *status)
{
   long  hfd;
   char *ptr=NULL;
   uint32_t    flage=0;
  
   do{
     //printf("> CHK(%s) \n", path);
     
     if((flage= access(path,0)) == 0){
        //printf("CTS [%x]\n", flage);
        
        if((ptr=strstr(path,"//"))!=NULL){
           *status = 404;
        }else
        if((ptr=strstr(path,"/\\"))!=NULL){
           *status = 404;
        }else
        if((ptr=strstr(path,"./"))!=NULL){
           *status = 404;
        }
        
        
     }else{
        *status = 404;
        //printf("XTS [%x]\n", flage);
     }
     
     /*ptr = (char *) emalloc( length+1 );
     if(ptr == NULL){
         *status = 503;
         break;
     } 
     sprintf(ptr,"%s/*.*\0", path);
     printf("> CP(%s) \n", ptr); 
     hfd = _findfirst(ptr, &fds);
     if(hfd == -1){
         *status = 404;
         printf(" PTR [%x] \n", hfd);
         break;
     }else{
        if(_findnext(hfd, &fds)==-1){ 
           printf(" ETR [%x] \n", hfd);
           break;
         }
          printf(" CTR [%x] \n", hfd);
     }
     _findclose(hfd);
      
     CLEAN(ptr);
     *///if(access(path, 0) == 0){
     //    break;
     //}
     //*status = 404;
   }while(0);
  
   
   return 0;
}


