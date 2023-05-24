
#include "iserver.h"


const char *_server_variables[] =
{
"Version",
"Domain",
"ServerAddr",
"Connection",
"Timeout",
"ServerName",
"ServerRoot",
"DocumentDirectory",
"DocumentRoot",
"DocumentIndex",
"DocumentLastname",
"ServerLength",
"Charset",
"ContentType",
"Error",
"Warning",
"Access",
"Block",
"ModuleRoot",
"ModuleFile",

"SSLCert",
"SSLKey",
"SSLChain",
"SSLFile",
"SSLPath",
"SSLCrl",
"SSLXML", 
// FTP SERVER
"FTPServer"
};

char* _new_time()
{
    unsigned int ret = 1;
    char* p=NULL;
    
	const char *listdate[12] = {"Jan","Fab","Mar","Apr","May","Jun","Juk",
	                            "Aug","Sep","Oct","Nov","Dec" };
    const char *listweek[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"}; 
    //#ifdef UNIX_BS
    time_t t=0;
    struct tm  *tss;
  //  char datetime[] = "[%d.%m.%Y] [%H:%M.%S]";
  //	char datetime_final[128];
    //#else
    //SYSTEMTIME  systime;
    //#endif
    // printf("> $$$$c \n");
do{
    if(p!=NULL){
       fatal("memory new allocate ", __FILE__,__FUNCTION__, __LINE__);
    }
    p = (char*) emalloc( 48 );
    if(p == NULL){
       fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    
    time(&t);
    // printf("> $$$$x \n");
    //#ifdef UNIX_BS
    //mktime(tss);
    tss = localtime(&t);
    if(tss==NULL){
       fatal("localtime",__FILE__,__FUNCTION__,__LINE__);
       break;
    }
    // strftime(datetime_final, 127, datetime, tm);
    //printf("> $$$$6 \n");
    
    if(tss->tm_wday>0)
	  tss->tm_wday -= 1;
	  if(tss->tm_wday>=7){
	  	  fatal("segment memory failed.,", __FILE__, __FUNCTION__, __LINE__);
	  	  ret =0;
		  break;
	  }
	  if(tss->tm_mon >0)
	  tss->tm_mon -= 1;
	  if(tss->tm_mon >= 12){
	  	  fatal("segment memory failed.,", __FILE__, __FUNCTION__, __LINE__);
		  ret = 0;
		  break;
	  }
	   
 	  sprintf(p, "%s %02d/%s/%04d %02d:%02d:%02d GMT %d\0",  
	       listweek[tss->tm_wday] , 
		   tss->tm_mday , 
		   listdate[tss->tm_mon], 
	       tss->tm_year ,
	       tss->tm_hour , 
		   tss->tm_min, 
		   tss->tm_sec,
		   tss->tm_isdst
	   );
    //#else
    //GetSystemTime(&systime);
      
    /*if(systime.wDayOfWeek>0)
	  systime.wDayOfWeek -= 1;
	  if(systime.wDayOfWeek>=7){
	  	  fatal("segment memory failed.,", __FILE__, __FUNCTION__, __LINE__);
	  	  ret =0;
		  break;
	  }
	  if(systime.wMonth>0)
	  systime.wMonth -= 1;
	  if(systime.wMonth >= 12){
	  	  fatal("segment memory failed.,", __FILE__, __FUNCTION__, __LINE__);
		  ret = 0;
		  break;
	  }
	   
 	  sprintf(p, "%s %02d/%s/%04d %02d:%02d:%02d GMT +7\0",  
	       listweek[systime.wDayOfWeek] , 
		   systime.wDay, 
		   listdate[systime.wMonth], 
		   systime.wYear,
	       systime.wHour, 
		   systime.wMinute, 
		   systime.wSecond
	   );
	 #endif 
     */
}while(0);
    //#ifdef CLEAN_VS
    //if(tss!=NULL)
    //CLEAN(tss);
    //#endif
    
	//printf("> %s \n", __FUNCTION__);
    if(!ret)
      CLEAN(p);
      
    return p;
}

int cserver_mod(char *str)
{
    //printf("LINE[%s]\n", str);
  do{
    if(server==NULL){
       fatal("heap allocate ", __FILE__, __FUNCTION__, __LINE__);
       break;              
    }
    _conf_copy(&server, str);
  }while(0);
}

void cserver_load(iserver_config **s)
{
     //printf("> %s \n", __FUNCTION__);
     iserver_config *p = (iserver_config *) *s;
     char  *ptr=NULL, *str=NULL;
     char  *lpszroot = p->argv;
     char  *szfile=NULL;
     
     do{
         if(lpszroot==NULL){
		    fatal("segment memory", __FILE__, __FUNCTION__, __LINE__);
			break;
		 }
		 if((strstr(lpszroot, "."))==NULL){
		 
		  if((ptr=strrchr(lpszroot, '/'))!=NULL){
            *ptr=0;
             ptr=NULL;
      
          if((str=strrchr(lpszroot, '/'))!=NULL){
            str+=1;
            *str=0;
             str=NULL;
            //printf("ptr[%s] \n", lpszroot);
         
             strcat(lpszroot, "conf");
           } 
          }
         }else{ 
            strcat(lpszroot, "/conf");
         }
		// printf("> %s - %s\n", p->argv, lpszroot);
     
     
      }while(0);
        *s = p;
        
do{
      if(lpszroot==NULL){
		  fatal("segment memory", __FILE__, __FUNCTION__, __LINE__);
		  break;
	  }
      if(server!=NULL){
          fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
      }
      server = (zconfig_server_t*) emalloc( sizeof(zconfig_server_t));
      if(server==NULL){
         fatal("allocate memory ", __FILE__, __FUNCTION__,__LINE__);
         break;
      }
      _conf_null(&server);
      
      if(bio_sign)
      {
          //printf("SSL Server [%s]\n", __FUNCTION__);
          _conf_load(lpszroot, "rhttps.conf", cserver_mod);
      }else{
          _conf_load(lpszroot, "rhttp.conf", cserver_mod);
      }
      
      if(szfile!=NULL){
          fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);                 
      }
      szfile = (char *) emalloc(strlen(lpszroot)+16);
      if(szfile == NULL){
         fatal("allocate memory",__FILE__,__FUNCTION__,__LINE__);
         break;          
      }
      strcpy(szfile,lpszroot);
      strcat(szfile, "/rtypes.conf");
      //printf(">%s]\n", sztype);
      request_inittype(szfile);
      
      //strcpy(szfile,lpszroot);
      //strcat(szfile,"\\HTTP_STATUS.HTML");
      
      //request_initpage(szfile);
      
      //strcpy(szfile,lpszroot);
      //strcat(szfile,"\\HTTP_GRDIR.HTML");
      //request_initdir(szfile);
      
      //printf("**********************************************\n");
      
}while(0);

}

unsigned int get_filesize(int fd)
{
   struct stat ts;
   //memset(&ts, 0, sizeof(ts));
   if(fstat(fd, &ts)==-1){ 
      fatal("open length", __FILE__,__FUNCTION__,__LINE__);
      return 0;
   }
   return (int)ts.st_size;
}


uint32_t  _conf_readline(const char *buff,cserver_string mod)
{
   unsigned int ret=1;
    unsigned int length;
    unsigned int len=0,cnt=0;
    unsigned int i,j;
    
    char         *ptr=NULL,*str=NULL, *pstr=NULL;
    char         *buffer= NULL, *sbuf=NULL;
	
do{	
	length = strlen(buff);
    if(length <= 0){
       fatal("size of memory ", __FILE__, __FUNCTION__, __LINE__);
       ret=0;
       break;
    }
    
    if(buffer!=NULL){
        fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
    }
	buffer = (char *) emalloc( length );
    if(buffer ==NULL){
       fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
       ret =0;
       break;
    }
    if(sbuf!=NULL){
        fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
    }
    sbuf = (char *) emalloc( length+128 );
    if(sbuf == NULL){
       fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
       ret = 0;
       break;
    }
    strcpy(buffer, buff);
    
    //kusage("initialized", __FILE__, __FUNCTION__, __LINE__);
    
    length = strlen(buffer);
    for(i=0;i<length;i++ ){
        if(buffer[i] == '\n') len += 1;
    }
    
    //printf("=====[%s]=====\n", buffer);
    //kusage("initialized", __FILE__, __FUNCTION__, __LINE__);
    //printf("==========================\n"); 	  
	for(i=0;i<len;i++){
     	if((ptr = strchr(buffer,'\n')) != NULL){
               ptr = ptr + 1;
               str = _new_str(ptr);
               *ptr = 0;   
               ptr = NULL;
               if((ptr = strchr(buffer,'\n'))!= NULL && strlen(buffer)>5){
                 *ptr = 0;
                 ptr = NULL;
                 
                 //printf("CJ[%s]\n", buffer );
                 
                 if(strncmp(buffer,";",1) ==0 || 
				    strncmp(buffer,"#",1) ==0 ||
					strncmp(buffer,"@",1) ==0 ||
					strncmp(buffer,"/",1) ==0 ||
					strncmp(buffer,"[",1) ==0){
                                          
				      // SKIP		
				 }else{
				 	//if(strncmp(buffer,"PW",2)==0){
				 		//printf("LD[%s]\n", buffer );
				 		
                         if((pstr = strchr(buffer,'='))!=NULL){
				 		     //  #ifdef __BUGS__
                             //  printf("DEBUG FUNCTION[%s] LINE[%d] \n", __FUNCTION__, __LINE__);  
                             //   #endif
				 		     if(buffer[strlen(buffer)-1] == '\r')
				 		        buffer[strlen(buffer)-1] ='\0';
				 		     
                             if(buffer[0] == '$') buffer+=1;
                             //printf("buffer[%s]\n", buffer);
                             memset(sbuf, 0, length);
                             for(j=0;j<strlen(buffer);j++){
                                if(buffer[j]!= ' '){
                                   strncat(sbuf, buffer+j, 1);
                                }
                                
                             }
                             //printf("BUFFER[%s]\n", sbuf);    
                             //sbuf[cnt] ='\0';
				 		    if(mod!=NULL)
				 		          mod(sbuf);
							//printf("+OK[%s]\n", buffer );
				 		   // OK
				 			// OK
				 		}else{
				 		   //fatalW("Analyze Unknown Line ",
						   //       i+2, __FILE__ , __FUNCTION__, __LINE__);
				 		   CLEAN(str);
				 		   return i+2;	
				 		}
				 		
				 		
				 		
				 		
				 	//}else{
				 		//printf("[%s]\n", buffer);
				 	//	printf("[WARN] Analyze Unknown Line <%d> <%d, %s>\n",
					//	      i+2, __LINE__, __FUNCTION__);
				 	//	free(str);
				 	//	return i+2;
				 	//}
				 }
				 
				 
               }
              strcpy(buffer,str ); 
     
        }
    }
    //printf("==========================\n");
    //kusage("initialized", __FILE__, __FUNCTION__, __LINE__);
}while(0);

    CLEAN(buffer);
    CLEAN(sbuf);
      
    return ret; 
}


uint32_t  _conf_load(const char *root, const char *file, cserver_string mod)
{
    char       *ptr = NULL;
    uint32_t    length =0, size=0;
    int         fd= -1;
    char        *buffer = NULL;
    
do{
    length = strlen(root)+ strlen(file) ;
    
    if(ptr!=NULL){
       fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
    }
    ptr = (char *) emalloc( length+ 3 );       
    if(ptr == NULL){
       fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    strcpy(ptr, root);
    if(ptr[strlen(ptr)-1] != '/')
      strcat(ptr,"/");
    strcat( ptr, file );
    
    printf("ptr[%s]\n", ptr);
	
    fd = open(ptr, O_RDONLY,0);
    if(fd == -1){
       fatal("opening file. ", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    lseek(fd, 0, SEEK_END);
    length = get_filesize(fd);
    lseek(fd, 0, SEEK_SET);
    
    
    if(buffer!=NULL){
       fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
    }
    buffer = (char *) emalloc( length);
    if(buffer == NULL){
       fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    
    if((size=read(fd, buffer, length))<=0){
       fatal("readfile.. ", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    buffer[size]='\0';
    //printf("=================================================\n");
    _conf_readline( buffer, mod);
    //printf("> [%s][%s] \n", root, file);
    
}while(0);
    CLEAN(buffer);
    
    if(fd!=-1) close(fd);
    
    return 0;
}
char* _anycfg_value(char *data, unsigned int seek_flags)
{
    unsigned int ret=1;
    unsigned int i=0;
    
	unsigned int length = strlen(data);
	 if(seek_flags){  // END
	 	do{
	 		if(data[strlen(data)-1] == ' ')
	 		   data[strlen(data)-1] = '\0';
	 		else 
	 		   break;
	 	}while(--length);
	 }else{            // BEGIN
	 	//printf("[IMG] [%s] \n", data);
	 	for(i=0;i<length;i++){
	 		if(*data ==' ')
	 		   *data++;
	        else
	          continue;
	 	}
	 	//printf("[EXP] [%s] \n", data);
	 }
	 
	 return data;
}
uint32_t  _conf_copy(zconfig_server_t **info, const char *buff)
{
    unsigned int ret=0;
    unsigned int index;
    char         *ptr=NULL;
    char         *str=NULL;
    char         *pstr=NULL;
    //
    char         *buffer = NULL;
    unsigned int  length =0;
    zconfig_server_t   *server = (zconfig_server_t*) *info;
    #define zis NULL
do{
	length= strlen(buff);
	
	if(buffer!=NULL){
         fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
    }
	buffer = (char *) emalloc( length );
    if(buffer == NULL){
      fatal("allocate memory failed.,", __FILE__, __FUNCTION__, __LINE__);
      ret = 0;
      break;
    }
    
    strcpy(buffer, buff);
    //printf("_%s_[%s] \n",__FUNCTION__, buffer);
    
    if(strncmp(buffer, _server_variables[0] , 
	           strlen(_server_variables[0]))==0)   // Version:
	{
	   ptr = buffer + strlen(_server_variables[0])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);	
	   
	   CCNEW(server->Version , ptr);
	   //printf("PTR[%s]\n", ptr );   
       
       ret = 1;        	
	}else if(strncmp(buffer, _server_variables[1] , 
	           strlen(_server_variables[1]))==0)   // Domain:
	{
	   ptr = buffer + strlen(_server_variables[1])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->Domain ,ptr);
	   //printf("PTR[%s]\n", ptr );  
       
       ret = 1;          	
	}else if(strncmp(buffer, _server_variables[2] , 
	          strlen(_server_variables[2]))==0)   // ServerAddr:
	{
	   ptr = buffer + strlen(_server_variables[2])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
	   
	   pstr = strdup(ptr);
	   if((ptr = strchr(pstr,':'))!=NULL ){
		ptr += 1;
		//printf("Port> %ws \n", wptr);
		CCNEW(server->ServerPort , ptr);
		
		*ptr = 0;
		ptr = NULL;
		if(pstr[strlen(pstr)-1]==':')
		   pstr[strlen(pstr)-1] ='\0';
		  //printf("Addr> %ws \n", wpstr);
          str =_anycfg_value(pstr, TRUE);
	      ptr =_anycfg_value(str, FALSE);
  
		  CCNEW(server->ServerAddr , ptr);
		
	   }
	   //printf("PTR[%s]\n", ptr );   
       
       ret = 1;        	
	}else if(strncmp(buffer, _server_variables[3] , 
	           strlen(_server_variables[3]))==0)   // Connection:
	{
	   ptr = buffer + strlen(_server_variables[3])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->Connection , ptr);
	   //printf("PTR[%s]\n", ptr );   
       
       ret = 1;         	
	}else if(strncmp(buffer, _server_variables[4] , 
	           strlen(_server_variables[4]))==0)   // GatewayTimeout:
	{
	   ptr = buffer + strlen(_server_variables[4])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->ServerTimeout , ptr);
	   //printf("PTR[%s]\n", ptr );  
       
       ret = 1;          	
	}else if(strncmp(buffer, _server_variables[5] , 
	           strlen(_server_variables[5]))==0)   // ServerName:
	{
	   ptr = buffer + strlen(_server_variables[5])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->ServerName , ptr);
	   //printf("PTR[%s]\n", ptr );  
       
       ret = 1;          	
	}else if(strncmp(buffer, _server_variables[6] , 
	           strlen(_server_variables[6]))==0)   // ServerRoot:
	{
	   ptr = buffer + strlen(_server_variables[6])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   for(index=0;index<strlen(ptr);index++){
	   	   if(ptr[index] == '\\') ptr[index]='/';
	   }	   
	   if(ptr[strlen(ptr)-1] != '/'){
          CCNEWPAD(server->ServerRoot, ptr, "/");
       }else{
          CCNEW(server->ServerRoot, ptr);
        }
        
        if(CCSTAT(server->ServerRoot, '/')){
	   	   CCREMOVE(server->ServerRoot, 1);
	   }
       //printf("PTR[%s]\n", ptr );     
       
       ret = 1;       	
	}else if(strncmp(buffer, _server_variables[7] , 
	           strlen(_server_variables[7]))==0)   // DocumentDirectory:
	{
	   ptr = buffer + strlen(_server_variables[7])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   for(index=0;index<strlen(ptr);index++){
	   	   if(ptr[index] == '\\') ptr[index]='/';
	   }	   
	   if(ptr[strlen(ptr)-1] != '/'){
	   	  CCNEWPAD(server->DocumentDirectory, ptr, "/" );
	   }else{
          CCNEW(server->DocumentDirectory, ptr);
       }
	   //printf("PTR[%s]\n", ptr );     
	   if(CCSTAT(server->DocumentDirectory, '/')){
	   	   CCREMOVE(server->DocumentDirectory, 1);
	   }
       //if(server->DocumentDirectory[strlen(server->DocumentDirectory)-1] == '/'){ 
       //   server->DocumentDirectory[strlen(server->DocumentDirectory)-1] = '\0';                                                     
       //}
       ret = 1;       	
	}else if(strncmp(buffer, _server_variables[8] , 
	           strlen(_server_variables[8]))==0)   // DocumentRoot:
	{
	   ptr = buffer + strlen(_server_variables[8])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   for(index=0;index<strlen(ptr);index++){
	   	   if(ptr[index] == '\\') ptr[index]='/';
	   }
	   if(ptr[strlen(ptr)-1] != '/'){
	      CCNEWPAD(server->DocumentRoot,ptr, "/");
       }else{
          CCNEW(server->DocumentRoot,ptr);
	   }//printf("PTR[%s]\n", ptr );
        
       if(CCSTAT(server->DocumentRoot, '/')){
	   	   CCREMOVE(server->DocumentRoot, 1);
	   }
       //if(server->DocumentRoot[strlen(server->DocumentRoot)-1] == '/'){ 
       //   server->DocumentRoot[strlen(server->DocumentRoot)-1] = '\0';                                                     
       //}
        ret = 1;             	
	}else if(strncmp(buffer, _server_variables[9] , 
	           strlen(_server_variables[9]))==0)   // DocumentIndex:
	{
	   ptr = buffer + strlen(_server_variables[9])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
        CCNEW(server->DocumentIndex, ptr);
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;            	
	}else if(strncmp(buffer, _server_variables[10] , 
	           strlen(_server_variables[10]))==0)   // DocumentLastName:
	{
	   ptr = buffer + strlen(_server_variables[10])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
	    CCNEW(server->DocumentName ,ptr);
	    if(server->DocumentName==NULL){
	    	fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
	    }
	    
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;              	
	}else if(strncmp(buffer, _server_variables[11] , 
	           strlen(_server_variables[11]))==0)   // DocumentLength:
	{
	   ptr = buffer + strlen(_server_variables[11])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
        CCNEW(server->RequestLength , ptr);
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;               	
	}else if(strncmp(buffer, _server_variables[12] , 
	           strlen(_server_variables[12]))==0)   // Charset:
	{
	   ptr = buffer + strlen(_server_variables[12])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->ContentCharset ,ptr);
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;               	
	}else if(strncmp(buffer, _server_variables[13] , 
	           strlen(_server_variables[13]))==0)   // ContentType:
	{
	   ptr = buffer + strlen(_server_variables[13])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->ContentType , ptr);
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;               	
	}else if(strncmp(buffer, _server_variables[14] , 
	           strlen(_server_variables[14]))==0)   // error:
	{
	   ptr = buffer + strlen(_server_variables[14])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->hFileError ,ptr);
	   //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;               	
	}else if(strncmp(buffer, _server_variables[15] , 
	           strlen(_server_variables[15]))==0)   // warning:
	{
	   ptr = buffer + strlen(_server_variables[15])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
      CCNEW(server->hFileWarn ,ptr);
	  //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;               	
	}else if(strncmp(buffer, _server_variables[16] , 
	           strlen(_server_variables[16]))==0)   // access:
	{
	   ptr = buffer + strlen(_server_variables[16])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
      CCNEW(server->hFileAccess ,ptr);
	  // printf("PTR[%s]\n", ptr ); 
       
        ret = 1;                	
	}else if(strncmp(buffer, _server_variables[17] , 
	           strlen(_server_variables[17]))==0)   // ipblock:
	{
	   ptr = buffer + strlen(_server_variables[17])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   

	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;                	
	}else if(strncmp(buffer, _server_variables[18] , 
	           strlen(_server_variables[18]))==0)   // module root:
	{
	   ptr = buffer + strlen(_server_variables[18])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->ModuleRoot ,ptr);
	   // printf("PTR[%s]\n", ptr ); 
       
        ret = 1;               	
	}else if(strncmp(buffer, _server_variables[19] , 
	           strlen(_server_variables[19]))==0)   // module index:
	{
	   ptr = buffer + strlen(_server_variables[19])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
        CCNEW(server->ModuleFile ,ptr);
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1;   
    }else if(strncmp(buffer, _server_variables[20] , 
	           strlen(_server_variables[20]))==0)   // module index:
	{
	   
       ptr = buffer + strlen(_server_variables[20])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
      CCNEW(server->SSLCert ,ptr);
    
	   //printf("PTR[%s]\n", ptr ); 
       
        ret = 1; 
    }else if(strncmp(buffer, _server_variables[21] , 
	           strlen(_server_variables[21]))==0)   // module index:
	{
	   ptr = buffer + strlen(_server_variables[21])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->SSLKey ,ptr);
    
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1; 
    }else if(strncmp(buffer, _server_variables[22] , 
	           strlen(_server_variables[22]))==0)   // module index:
	{
	    ptr = buffer + strlen(_server_variables[22])+1;
	    str =_anycfg_value(ptr, TRUE);
	    ptr =_anycfg_value(str, FALSE);		
	   
        CCNEW(server->SSLChain ,ptr);
    
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1; 
    }else if(strncmp(buffer, _server_variables[23] , 
	           strlen(_server_variables[23]))==0)   // module index:
	{
	    ptr = buffer + strlen(_server_variables[23])+1;
	    str =_anycfg_value(ptr, TRUE);
	    ptr =_anycfg_value(str, FALSE);		
	   
        CCNEW(server->SSLFile ,ptr);
    
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1; 
    }	else if(strncmp(buffer, _server_variables[24] , 
	           strlen(_server_variables[23]))==0)   // module index:
	{
	    ptr = buffer + strlen(_server_variables[24])+1;
	    str =_anycfg_value(ptr, TRUE);
	    ptr =_anycfg_value(str, FALSE);		
	   
        CCNEW(server->SSLPath ,ptr);
    
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1; 
    }
	
	else if(strncmp(buffer, _server_variables[25] , 
	           strlen(_server_variables[23]))==0)   // module index:
	{
	    ptr = buffer + strlen(_server_variables[23])+1;
	    str =_anycfg_value(ptr, TRUE);
	    ptr =_anycfg_value(str, FALSE);		
	   
        CCNEW(server->SSLCrl ,ptr);
    
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1; 
    }else if(strncmp(buffer, _server_variables[26] , 
	           strlen(_server_variables[24]))==0)   // module index:
	{
	   ptr = buffer + strlen(_server_variables[24])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
       CCNEW(server->SSLXml ,ptr);
    
	    //printf("PTR[%s]\n", ptr ); 
       
        ret = 1; 
                            	
	}
	
    #ifdef __FTP_SERVER__
    else if(kstrncmp(buffer, _server_variables[25] ,  // FTP SERVER
	           kstrlen(_server_variables[25]))==0)   // module index:
	{
	   ptr = buffer + kstrlen(_server_variables[25])+1;
	   str =_anycfg_value(ptr, TRUE);
	   ptr =_anycfg_value(str, FALSE);		
	   
	   
	   pstr = kstrdup(ptr);
	   if((ptr = kstrchr(pstr,':'))!=NULL ){
		ptr += 1;
		//printf("Port> %ws \n", wptr);
		CCNEWPAD(server->FileServerPort ,ptr);
		
		*ptr = 0;
		ptr = NULL;
		if(pstr[kstrlen(pstr)-1]==':')
		   pstr[kstrlen(pstr)-1] ='\0';
		  //printf("Addr> %ws \n", wpstr);
		  CCNEW(server->FileServerAddr, pstr);
		
	   }
	   //printf("PTR[%s]\n", ptr );   
       
       ret = 1;        	              	
	                             	
	                        	
	}
    #endif
    else{
      fatal("insert empty handle", __FILE__, __FUNCTION__, __LINE__);
      ret = 1;
    } 
    
       
}while(0);
    
    *info = server;
    
    CLEAN(buffer);
    
    return ret;
}



uint32_t  _conf_infow( zconfig_server_t *info)
{
    if(info==NULL) return 0;
    CPRINT("ServerDomain", CCSHOW(info->Domain ));
    CPRINT("ServerVersion", CCSHOW(info->Version ));
    CPRINT("ServerAddr", CCSHOW(info->ServerAddr ));
    CPRINT("ServerPort", CCSHOW(info->ServerPort ));
    
    #ifdef __FTP_SERVER__
    CPRINT("FileServerAddr", CCSHOW(info->FileServerAddr ));
    CPRINT("FileServerPort", CCSHOW(info->FileServerPort ));
    //char                  *zserveraddr;
    //char                  *zserverport;
    #endif
    
    CPRINT("Connection", CCSHOW(info->Connection ));
    CPRINT("ServerTimeout", CCSHOW(info->ServerTimeout ));
    CPRINT("ServerName", CCSHOW(info->ServerName ));
    CPRINT("ServerRoot", CCSHOW(info->ServerRoot ));
    CPRINT("DocumentRoot", CCSHOW(info->DocumentRoot ));
    CPRINT("DocumentDirectory", CCSHOW(info->DocumentDirectory ));
    CPRINT("DocumentIndex", CCSHOW(info->DocumentIndex ));
    CPRINT("DocumentName", CCSHOW(info->DocumentName ));
    CPRINT("RequestLength", CCSHOW(info->RequestLength ));
    
    CPRINT("ContentCharset", CCSHOW(info->ContentCharset ));
    CPRINT("ContentType", CCSHOW(info->ContentType ));
    CPRINT("ModuleRoot", CCSHOW(info->ModuleRoot ));
    CPRINT("ModuleFile", CCSHOW(info->ModuleFile ));
    
    
    CPRINT("hFileError", CCSHOW(info->hFileError ));
    CPRINT("hFileWarn", CCSHOW(info->hFileWarn ));
    CPRINT("hFileAccess", CCSHOW(info->hFileAccess )); 
    
    if(bio_sign){
    #ifndef SSL_C
    CHKDSK(info->SSLCert,__LINE__)  CPRINT("SSLCert", CCSHOW(info->SSLCert )); CHKEND
    CHKDSK(info->SSLKey,__LINE__)  CPRINT("SSLKey", CCSHOW(info->SSLKey )); CHKEND
    CHKDSK(info->SSLChain,__LINE__)  CPRINT("SSLChain", CCSHOW(info->SSLChain )); CHKEND
    CHKDSK(info->SSLFile,__LINE__)  CPRINT("SSLFile", CCSHOW(info->SSLFile )); CHKEND
    CHKDSK(info->SSLPath,__LINE__)  CPRINT("SSLPath", CCSHOW(info->SSLPath )); CHKEND
    CHKDSK(info->SSLCrl,__LINE__)  CPRINT("SSLCrl", CCSHOW(info->SSLCrl )); CHKEND
    CHKDSK(info->SSLXml,__LINE__)  CPRINT("SSLXml", CCSHOW(info->SSLXml )); CHKEND
    #endif 
    }
    
}
uint32_t  _conf_null(zconfig_server_t **info)
{
   uint32_t  ret=0;
   zconfig_server_t  *infow = (zconfig_server_t*) *info;
do{
   
   if(infow == NULL){
      fatal("stack memory failed", __FILE__, __FUNCTION__, __LINE__);
      break;
   }          
    CCNULL( infow->Domain );
    CCNULL( infow->Version );
    CCNULL( infow->ServerAddr );
    CCNULL( infow->ServerPort );
    
    #ifdef __FTP_SERVER__
    CCNULL( infow->FileServerAddr );
    CCNULL( infow->FileServerPort );
    //char                  *zserveraddr;
    //char                  *zserverport;
    #endif
    
    CCNULL( infow->Connection );
    CCNULL( infow->ServerTimeout );
    CCNULL( infow->ServerName );
    CCNULL( infow->ServerRoot );
    CCNULL( infow->DocumentRoot );
    CCNULL( infow->DocumentDirectory );
    CCNULL( infow->DocumentIndex );
    CCNULL( infow->DocumentName );
    CCNULL( infow->RequestLength );
    
    CCNULL( infow->ContentCharset );
    CCNULL( infow->ContentType );
    CCNULL( infow->ModuleRoot );
    CCNULL( infow->ModuleFile );
    
    CCNULL( infow->SSLCert );
    CCNULL( infow->SSLKey );
    CCNULL( infow->SSLChain );
    
    CCNULL( infow->SSLFile );
    CCNULL( infow->SSLPath );
    
    CCNULL( infow->SSLCrl );
    CCNULL( infow->SSLXml );
    CCNULL( infow->hFileError );
    CCNULL( infow->hFileWarn );
    CCNULL( infow->hFileAccess ); 
      
}while(0);
   
   *info = infow;
      
   return ret;
    
}

uint32_t  _conf_clean(zconfig_server_t **info)
{
   uint32_t  ret=0;
   zconfig_server_t  *infow = (zconfig_server_t*) *info;
do{
   
   if(infow == NULL){
      fatal("stack memory failed", __FILE__, __FUNCTION__, __LINE__);
      break;
   }
   
    CCLEAN( infow->Domain );
    CCLEAN( infow->Version );
    CCLEAN( infow->ServerAddr );
    CCLEAN( infow->ServerPort );
    
    #ifdef __FTP_SERVER__
    CCLEAN( infow->FileServerAddr );
    CCLEAN( infow->FileServerPort );
    //char                  *zserveraddr;
    //char                  *zserverport;
    #endif
    
    CCLEAN( infow->Connection );
    CCLEAN( infow->ServerTimeout );
    CCLEAN( infow->ServerName );
    CCLEAN( infow->ServerRoot );
    CCLEAN( infow->DocumentRoot );
    CCLEAN( infow->DocumentDirectory );
    CCLEAN( infow->DocumentIndex );
    CCLEAN( infow->DocumentName );
    CCLEAN( infow->RequestLength );
    
    CCLEAN( infow->ContentCharset );
    CCLEAN( infow->ContentType );
    CCLEAN( infow->ModuleRoot );
    CCLEAN( infow->ModuleFile );
    
    CCLEAN( infow->SSLCert );
    CCLEAN( infow->SSLKey );
    CCLEAN( infow->SSLChain );
    CCLEAN( infow->SSLFile );
    CCLEAN( infow->SSLPath );
    CCLEAN( infow->SSLCrl );
    CCLEAN( infow->SSLXml );
    CCLEAN( infow->hFileError );
    CCLEAN( infow->hFileWarn );
    CCLEAN( infow->hFileAccess );   
   
    CLEAN(infow);
}while(0);
   
   *info = infow;
      
   return ret;
}
