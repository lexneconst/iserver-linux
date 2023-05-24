
#include "iserver.h"

uint32_t  script_readline(const char *buff,const char *data, char *out_name);

uint32_t script_cache(const char *url)
{
	uint32_t ret = 0;
	uint32_t i=0;
do{
	if(url==NULL){
		break;
	}
	
	if(strlen(url)< CACHE_LENGTH || strlen(url)> CACHE_LENGTH)
	{
		
		break;
	}
	
	for(i=0;i<strlen(url);i++){
		
		if(strstr(url,"@")!=NULL || strstr(url,".")!=NULL || strstr(url,"?")!=NULL ||
		   strstr(url,"/")!=NULL || strstr(url, "\\")!=NULL || strstr(url,"!")!=NULL||
		   strstr(url,"#")!=NULL || strstr(url, "$")!=NULL || strstr(url,",")!=NULL
		)
		{
			
		   return ret;
		}
	}
	
	ret = 1;
}while(0);
	
	return ret;
}

char *script_getpath(const char *str, uint32_t *size)
{
	char *ptr=(char *) str;
	uint32_t  c=0;
	uint32_t  i=0;
	uint32_t  l=0;
	
	l = strlen(str);
	do{
		if(c>= 2){
		    ptr+= l;
			break;
		}
		if(ptr[l] == '/'){
		    c++;
		}
		i++;
		l--;
	}while(l>0);
	
	return ptr;
}

char *script_search(zrequest_externs_t *request, uint32_t status)
{
	char *cpath = NULL;
	char *str = NULL;
	uint32_t   mode =1;
do{
	#ifdef DEBUG_H
	printf("status :: %d , %s\n", status, path);
    #endif
	if(status == 100 || status == 200 || status != 200){
        
        #ifdef DEBUG_H
      	printf("DIR = %s (%s) \n", __FUNCTION__, path);
      	#endif
      	
       cpath = (char *) emalloc( strlen(CCSHOW(request->PathTranslated))+2) ;
       if(cpath==NULL){
      		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
      		break;
	   }
       strcpy(cpath, CCSHOW(request->PathTranslated));	
	   if(cpath[strlen(cpath)-1] != '/'){
	      strcat(cpath, "/");
       }
       
	   str  =(char *) emalloc( strlen(cpath)+ strlen(SCRIPTFILE)+6 );
	   if(str==NULL){
	   	    fatal("allocate memory ",__FILE__, __FUNCTION__, __LINE__);
			break;
	   }	
	   
	   strcpy(str, cpath);
	   strcat(str, SCRIPTFILE);
	   if(access(str,0)!=-1){
	   	 CLEAN(cpath);
		 return str;
	   }
	   
       if(status == 100){
       	   break;
	   }
       
	   strcpy(str, CCSHOW(request->DocumentRoot ));
	   if(str[strlen(str)-1] != '/'){
	      strcat(str, "/");
       }
       strcat(str, SCRIPTFILE);
       #ifdef DEBUG_H
       printf(".htaccess(%s)\n", str);
       #endif
       
	   if(access(str,0)!=-1){
	   	 CLEAN(cpath);
		 return str;
	   }
	   
	   #ifdef DEBUG_H
	   printf("FILE (%s) \n", str);
	   #endif
	   
	   
	   break;    
	 
	  
    }
}while(0);
   
   CLEAN(str);
   CLEAN(cpath);   
   
   return NULL;
}
uint32_t script_header(sapi_header *header)
{
	uint32_t   status = 0;
	uint32_t   i=0;
	uint32_t   count =0;
	sapi_header *next=NULL, *prev=NULL;
	
	
do{
	if(header==NULL){
		
		break;
	}
	status = header->count;
	
	if(header->saveid!=0 || header->saveid != header->count)
	{
		status = header->count = header->saveid;
	}
	if(header->count < 0){
	   status = header->count = header->saveid;
	}
	#ifdef DEBUG_H
	printf("header count (%d) - (%d)\n", status, header->saveid);
	#endif
	if(status <=0){
	   status =0;
	   break;
	}
	if(status == header->number){
		//printf("back end %d,%d \n", status, header->number);
		header->count -= 1;
		break;
	}
	
	prev = header;
	for(i=0;i<=status;i++){
		
		if(prev == NULL){
			break;
		}
		next = prev->next;
		
		if(next == NULL){
			break;
		}
		//printf("prev (%x) next(%x) \n", prev, next);
		
		prev->count = status - 1;
		if(i==0){
			header->count = prev->count;
			if(prev->count <= 0) header->count = status - 1;
		}
		
		if(next!=NULL){
		   //memcpy(prev, next, sizeof(sapi_header));	
	      if(prev->data!=NULL && next->data!=NULL){
	      	 // memcpy(prev->data, next->data, sizeof(sapi_buffer));
	      	 if(prev->data->buffer!=NULL && next->data->buffer!=NULL){
	      	    
	      	    //printf("[%s,%s]\n", prev->data->buffer, next->data->buffer);
	      	   //prev->data->buffer = (char *) realloc(next->data->buffer,  next->data->length+2);
	      	   //if(prev->data->buffer==NULL){
	      	   //	   fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
			   //}else{
			   	 //printf("prev(%s)next(%s)\n",prev->data->buffer, next->data->buffer);
			   	 //if(prev->data->buffer!=NULL) CLEAN(prev->data->buffer);
			   	 //printf("[%s::%s]\n", prev->data->buffer, next->data->buffer);
		         strncpy(prev->data->buffer,next->data->buffer, strlen(next->data->buffer));
		         prev->data->buffer[strlen(next->data->buffer)]='\0';
		         
		         prev->data->length = next->data->length;
		         prev->count = header->number - count;
				 prev->number= header->number;
				 prev->saveid= header->saveid -1;
				    
                  if(count == status-1){
                  	//printf("END %d,%d \n", count, status);
                    if(next!=NULL){
        	          if(next->data!=NULL){
		                 if(next->data->buffer!=NULL){
        		            CLEAN(next->data->buffer);
        		            next->data->length=0;
        		            next->count = 0;
        		            next->saveid= 0;
        		            next->number= 0;
			             }
			            CLEAN(next->data);
			         }
         	        CLEAN(next);
	        	   }
	        	   
				   header->count = count; 
	        	   header->saveid= count;
	        	   
	              }
		         count+=1;
		         
	          //}
			}
		  }
        }
        
	    prev = next;
	}

        	
	
}while(0);
    
    if(header!=NULL){
      if(header->data!=NULL){
        if(header->data->buffer!=NULL){
		   //printf("(%s)\n", header->data->buffer);
		}
      }
    } 
    
    //if(header!=NULL)
    //   printf("SAVE (%d),(%d),(%d)\n", header->count, header->saveid, header->number);
    
	if(status == 0) goto END;
    if(header!=NULL){
	  if(header->count > 0 ){
	    if(header->count == header->number){
	    	header->count -= 1;
		}
	  }
	  header->saveid = header->count;    
   }
  END: 
	return status;
}


uint32_t script_startup(script_server *client, zrequest_externs_t *request, const char *path)
{
    char   buffer[MAX_PATH];
    char   *ptr=NULL;
    uint32_t length=0;
	uint32_t size = 0;
	
do{
	if(client==NULL){
		fatal("segment memory " ,__FILE__, __FUNCTION__, __LINE__);
		break;
	}
	client->status = 0;
	
	client->buffer = (sapi_buffer *) emalloc( sizeof(sapi_buffer));
	if(client->buffer==NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	client->buffer->length=0;
	
	//printf("path:: %s \n", path);
	client->buffer->length = request_contentLength(path);
	client->buffer->buffer = (char *) emalloc( client->buffer->length +2);
	if(buffer==NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	
	
	if(!request_read(path, client->buffer->buffer, client->buffer->length)){
	   if(access(path, 0)==0){
	      client->status = 101;
	      break;
	   }
	}
	
	#ifdef DEBUG_H
	printf("READ=%s\n", path);
	#endif
	
	if(access(CCSHOW(request->PathTranslated),0) ==0){
       #ifdef DEBUG_H
	   printf("ACCESS_200=%s\n", CCSHOW(request->PathTranslated));                                        // 200 
       #endif
	   client->status = 200;
	   script_readline(client->buffer->buffer, "200=", client->buffer->buffer);		
	   break;
	}
	
	#ifdef DEBUG_H
	printf("ACCESS_404=%s\n", CCSHOW(request->PathTranslated));	                                       // 404
	#endif
	
	if(strlen(CCSHOW(request->UrlCache))==CACHE_LENGTH && script_cache(CCSHOW(request->UrlCache)) ){
	   client->status = 200;
	   script_readline(client->buffer->buffer, "200=", client->buffer->buffer);		
	   break;
	}
	
	//printf("FOUND(%s)\n", CCSHOW(request->PathTranslated));
	length = strlen(CCSHOW(request->ServerRoot)) + strlen(CCSHOW(request->FileSelf));
	//printf("[%s][%s]\n", CCSHOW(request->ServerRoot), CCSHOW(request->FileSelf));
	ptr = (char *) emalloc( length + 2);
	if(ptr==NULL){
		fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	strcpy(ptr, CCSHOW(request->ServerRoot));
	if(ptr[strlen(ptr) -1] == '/'){
		ptr[strlen(ptr)-1] ='\0';
	}
	strcat(ptr, script_getpath(CCSHOW(request->FileSelf), &size));
	ptr[length-size] = '\0';
	
	//printf(">> %s\n", ptr);
	if(access(ptr, 0) == 0){
		CCNEW(request->PathTranslated, ptr);
		//printf(">> %s\n", CCSHOW(request->PathTranslated) );
	    client->status = 200;
	    CLEAN(ptr);
		break;
	}
	CLEAN(ptr);
	
	if(script_readline(client->buffer->buffer, "404=", client->buffer->buffer)){
	   //strcpy(client->buffer->buffer, buffer);
	   client->status = 404;
	   break;
	}
	
	
	if(access(path, 0)==0){
	   client->status = 101;
	   break;
	}
	
}while(0);
	return 0;
}
uint32_t script_execute(script_server *client, zrequest_externs_t **req_ext, uint32_t *status)
{
	
	char *ptr=NULL, *str=NULL;
	zrequest_externs_t *request = (zrequest_externs_t *) *req_ext;
	
	*status = 0;
	
do{
    if(client==NULL){
    	fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}	
	if(request==NULL){
    	fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);		
		break;
	}
	
	if(client->buffer==NULL){
    	fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);		
		break;
	}
	if(client->buffer->buffer==NULL){
    	fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);		
		break;
	}
	
	if(request==NULL){
    	fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);		
		break;
	}
	
	//printf(">> %s\n", CCSHOW(request->PathTranslated));
	//if(client->status == 200){
		
	//	break;
	//}
	if(client->status == 101){
	    
		break;
	}
	
	#ifdef DEBUG_H
	printf("DATA(%s) \n", client->buffer->buffer);
	#endif
	if(strncmp(client->buffer->buffer,"200=", 4) ==0){
		*status = 200;
		
		#ifdef DEBUG_H
		printf("Cache [%s]\n", request->UrlCache);
		#endif
		
		if((ptr=strstr(client->buffer->buffer,"200="))!=NULL && 
		    strlen(CCSHOW(request->UrlCache)) == CACHE_LENGTH && script_cache(CCSHOW(request->UrlCache))){
		    
		    ptr+= 4;
		    //str = _new_str(request->PathTranslated);
		    //CLEAN(request->PathTranslated);
		    
		    str = (_MGC_STRING) emalloc( strlen(CCSHOW(request->DocumentRoot) )+ strlen(ptr)+5 );
		    if(str!=NULL){
		    	strcpy(str, CCSHOW(request->DocumentRoot));
		    	if(str[strlen(str)-1] != '/'){
		    		strcat(str, "/");
				}
		    	strcat(str, ptr);
		    	
		    	#ifdef DEBUG_H
				printf("PATH:%s\n", str);
		    	#endif
		    	
		    	if(access(str,0) ==0){
		    		
		    		//CLEAN(CCSHOW(request->PathTranslated);
		    		//request->PathTranslated= _new_str(str);
		    		CCRENEW(request->PathTranslated, str);
		    		
		    		*status = 200;
				}else{
					
					//CLEAN(request->PathTranslated);
					//request->PathTranslated = _new_str(str);
					CLEAN(str);
				}
		    	
			}else{
				//request->PathTranslated = _new_str(str);
				//CLEAN(str);
			}
				
		}
		
	}else
	if(strncmp(client->buffer->buffer,"404=",4) ==0){
	   *status = 200;
	   
	   if((ptr=strstr(client->buffer->buffer,"404="))!=NULL){
		    
		    ptr+= 4;
		    //str = _new_str(request->PathTranslated);
		    //CLEAN(request->PathTranslated);
		    
		    str = (_MGC_STRING) emalloc( strlen(CCSHOW(request->DocumentRoot))+ strlen(ptr)+5 );
		    if(str!=NULL){
		    	strcpy(str, CCSHOW(request->DocumentRoot));
		    	if(str[strlen(str)-1] != '/'){
		    		strcat(str, "/");
				}
		    	strcat(str, ptr);
		    	
		    	#ifdef DEBUG_H
		    	printf("PATH:%s\n", str);
		    	#endif
		    	
		    	if(access(str,0) ==0){
		    		
		    		*status = 404;
		    		
		    		//CLEAN(request->PathTranslated);
		    		//request->PathTranslated = _new_str(str);
		    		CCRENEW(request->PathTranslated, str);
		    		
					CLEAN(str);
		    		
		    		break;
				}else{
					*status = 200;
					
					//CLEAN(request->PathTranslated);
					//request->PathTranslated = _new_str(str);
					CLEAN(str);
					
					break;
				}
		    	
			}else{
				//request->PathTranslated = _new_str(str);
				//CLEAN(str);
				
				break;
			}
				
		}	
	}
	
	
	if(client->status == 200 && access(CCSHOW(request->PathTranslated),0) ==0){
		*status =200;
		break;
	}
	
}while(0);
    
    if(client!=NULL)
    {
     	if(client->buffer!=NULL)
     	{
     		if(client->buffer->buffer)
     		   CLEAN(client->buffer->buffer);
     		   
		    CLEAN(client->buffer);
		}
		//CLEAN(client);
    }   
    
    #ifdef DEBUG_H
	printf("SPATH(%s)\n", CCSHOW(request->PathTranslated));
    #endif
    
    *req_ext = (zrequest_externs_t*) request;
    
	return 0;
}
uint32_t script_cleanup(script_server *client)
{
do{
	if(client==NULL){
		break;
	}
	
	if(client->buffer!=NULL){
		
		CLEAN(client->buffer->buffer);
		client->buffer->length =0;
		
		CLEAN(client->buffer);
	}
	
}while(0);
	return 0;
}

uint32_t script_run(sapi_header **req_header, sapi_buffer **req_buffer, char *path, zrequest_externs_t *request ){
	 
	uint32_t    status = 0; 
	uint32_t    ebool  = 0;
	uint32_t    length = 0;
	uint32_t    i=0;
	char        buff[MAX_PATH];
	sapi_header *next=NULL, *prev=NULL;
	
	sapi_header *header = (sapi_header*) *req_header;
	sapi_buffer *buffer = (sapi_buffer*) *req_buffer;
	
	
	script_server   script_request;
do{
	
	header = (sapi_header*) emalloc( sizeof(sapi_header));
	if(header == NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	buffer = (sapi_buffer*) emalloc( sizeof(sapi_buffer));
	if(buffer==NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	
	script_startup(&script_request, request, path);
	script_execute(&script_request, &request, &status);
	script_cleanup(&script_request);
	
	header->data= NULL;
	buffer->buffer=NULL;
	
	#ifdef DEBUG_H
	printf("CPath(%s)\n", CCSHOW(request->PathTranslated));
	#endif
	
	if(status == 200){
	    
		break;
	}else
	if(status == 404){
		
		break;
	}
	
	header->count = 0;
	prev = header;
	
	if(prev==NULL){
		
		break;
	}
	if(prev==NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	prev->data = (sapi_buffer *) emalloc( sizeof(sapi_buffer));
	if(prev->data ==NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	strcpy(buff,"HTTP/1.2 200 OK\r\n");
	prev->data->buffer = _new_str1(buff, 64 );
	prev->data->length = strlen(buff);
	
	prev->next = NULL;
	
	header->count+= 1;
					
	for(i=0;i<=6;i++){

		if(ebool){
			
			break;
		}
		next = ( sapi_header *) emalloc( sizeof( sapi_header ));
		if(next==NULL){
			fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		next->data = (sapi_buffer *) emalloc( sizeof(sapi_buffer));
		if(next->data ==NULL){
			fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		next->next = NULL;
		
		TRY:
		switch(i){
			case 0:
				if(CCSHOW(request->RequestTimes)!=NULL){
				    sprintf(buff,"Date: %s\r\n", CCSHOW(request->RequestTimes));
                    next->data->buffer = _new_str1(buff, 64);
				    next->data->length = strlen(buff);
				    
				    header->count+= 1;
				}else{
					
					i+= i;
					
					goto TRY;
				}
				
			break;
			case 1:
				if(CCSHOW(request->ServerName)!=NULL){
                    sprintf(buff,"Server: %s\r\n", CCSHOW(request->ServerName));
                    next->data->buffer = _new_str1(buff, 64);
				    next->data->length = strlen(buff);
				    
				    header->count+= 1;
                }else{
					
					i+= i;
					
					goto TRY;
				}
			break;
			case 2:
				strcpy(buff,"Accept-Ranges: bytes\r\n");
				next->data->buffer = _new_str1(buff, 64);
				next->data->length = strlen(buff);
				
				header->count+= 1;
			break;
			case 3:
				strcpy(buff,"Connection: close\r\n");
				next->data->buffer = _new_str1(buff, 64);
				next->data->length = strlen(buff);
				
				header->count+= 1;
			break;
			case 4:
				
				if(request->ContentType!=NULL){
                   sprintf(buff,"Content-Type: %s;\r\n", CCSHOW(request->ContentType));
                   next->data->buffer = _new_str1(buff, 64);
			  	   next->data->length = strlen(buff);
				
				   header->count+= 1;
				   
				   ebool = 1;
                }else{
					
					i+= i;
				}
			break;
		}
		
		
		prev->next = next;
		prev = next;
	}
	
	
	if(buffer!=NULL){
		
	     strcpy(buff, "access denied\0");
		 buffer->buffer = _new_str(buff);
		 buffer->length = strlen(buff);
		 
	}
	
	 
}while(0);
    header->number =header->count;
    header->saveid =header->count;
    
    *req_header = (sapi_header*) header;
    *req_buffer = (sapi_buffer*) buffer;
    
	CLEAN(path);
	 
	return status;
}

uint32_t script_clean(sapi_header *header, sapi_buffer *buffer)
{

do{
     if(header!=NULL){
     	if(header->data!=NULL)
     	{
     	   if(header->data->buffer!=NULL)
       	      CLEAN(header->data->buffer);
     	   header->data->length=0;
     	   CLEAN(header->data);
        }
		header->count = 0;
		header->number = 0;
	 }
     
     if(buffer!=NULL){
     	CLEAN(buffer->buffer);
     	buffer->length = 0;
	 }

}while(0);

	 return 0;	
}


uint32_t  script_readline(const char *buff,const char *data, char *out_name)
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
				 		    if(strncmp(sbuf,data, strlen(data) )==0){
				 		    	strcpy(out_name, sbuf);
								ret= 1;
								break;
							 }
							 //if(mod!=NULL)
				 		    //      mod(sbuf);
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
