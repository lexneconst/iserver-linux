
#include "iserver.h"

zmodule_stack_t *module_stack=NULL;


uint32_t cstrcmp(const char *dst, const char *src){

do{
    if(dst==NULL){
    	fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}
	if(src==NULL){
		fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	if(strcmp(dst, src) == 0) return 0;

}while(0);

	return 1;
}
     	
uint32_t request_module_script(zrequest_externs_t *request, iserver_module *controls, uint32_t status)
{
	char      *buffer=NULL;
	uint32_t  length = 0;
	uint32_t  size = 0;
	uint32_t  iret = 0;
	uint32_t  bsign = 0;
	
	#ifdef DEBUG_H
	printf("STATUS(%d),PATH::%s\n",status, CCSHOW(request->PathTranslated) );
	#endif
do{
	if(status == 200 ){
	
  	  length =  atoi(CCSHOW(request->ContentLength)) ;
      if(length <= 0){
        fatal("server length", __FILE__, __FUNCTION__, __LINE__);
        break;
      }
             //strcpy(buff,"Hello world!");
      if(buffer != NULL){
        fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
      }     
      buffer = (char *) emalloc( length+2 );
      if(buffer==NULL){
        fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
        break;
      }
             //printf("*************************\n");
      size = request_read(
                CCSHOW(request->PathTranslated), 
                buffer, 
                length );
                
      #ifdef DEBUG_H
      printf("%s::%d, %d \n", __FUNCTION__, size, length);
      #endif
      
	  do{
	  	  if(!size || size <= 0) break;
	  	  if(!length || length <= 0 ) break;
	  	  TRY:
	  	  if(bsign==0){
	  	     if(strstr(buffer, "#>")!=NULL){
	  	       iret += 1;	
	           bsign = 1;
	           
	  	       goto TRY;
			 }else{
			 	
			 	break;
			 }
	      }else if(bsign==1){
	        if(strstr(buffer, "<#")!=NULL){
	      	  iret += 1;
	      	  bsign += 1;
	      	  break;
		   }else{
		   	
		   	  break;
		   }
	      }else if(bsign ==2){
	      	  break;
		  }else{
		  	  break;
		  }
	  	  
	  	  length-=2;
	  	  size -=2;
	  	  
	  	  goto TRY;
	  }while(0);
	      
      CLEAN(buffer);
    }
}while(0);

	if(iret==2) return 1;
	return 0;
}

/*uint32_t module_access_icons(zrequest_externs_t **request){
	
	zrequest_externs_t *ext = (zrequest_externs_t *) *request;
do{
	if(ext ==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	if(ext->ServerCode!= 200 || ext->ServerCode != 100){
	  
	  CCNEWADD(ext->PathTranslated, ext->ServerRoot, ext->FileSelf );
	
	  printf("ICONS(%s)\n", CCSHOW(ext->PathTranslated) );
    }
}while(0);
    
    * request = (zrequest_externs_t *) ext;
	
	return 0;
}
*/
uint32_t onserver(iserver_module *b, iserver_config *s)
{
    uint32_t  length=0,size = 0;
    char      *buffer=NULL,buff[MAX_PATH];
    char      *ptr=NULL;
    zrequest_externs_t    *request=NULL;
    sapi_server            sapi_request;
    long                   hfd;
    char                   *path=NULL;
    uint32_t               state = 0;
    struct stat            st;
    // stage1 request externsion
    char                   fatal_str[MAX_PATH];
    char                   *realtime_str=NULL;

	fatal_init();
    

 do{
    
    if(b == NULL){ 
        fatal("module file", __FILE__,__FUNCTION__,__LINE__); 
        break; 
    }
    if(s == NULL){ 
         fatal("module file", __FILE__,__FUNCTION__,__LINE__); 
         break; 
    }
    if(s->_s==-1){ 
          fatal("socket error", __FILE__,__FUNCTION__,__LINE__); 
          break; 
    }
    
    einit(NULL);
    
    s->status = 503;
    
    if(server==NULL){ 
          fatal("heap allocate",__FILE__,__FUNCTION__,__LINE__); 
          s->status = 401;
          break; 
    }
    if(request!=NULL){
        fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__); 
        s->status = 401;
    } 
   
    request = (zrequest_externs_t*)emalloc(sizeof(zrequest_externs_t));
    if(request==NULL){
         fatal("allocate memory", __FILE__,__FUNCTION__,__LINE__);
         s->status = 403;
         break;
    }
    request_init(&request);
    request_startup(&request,server);
    
    length =  atoi(CCSHOW(server->RequestLength));
    if(length <= 0) {
       fatal("request length", __FILE__, __FUNCTION__,__LINE__);
       s->status = 403;
       break;
    }
    if(buffer != NULL){
        fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
        s->status = 401;
    }
    buffer = (char *) emalloc( length );
    if(buffer == NULL){
       fatal("alloate memory ", __FILE__, __FUNCTION__, __LINE__);
       s->status = 401;
       break;
    }
    
    if(atoi(CCSHOW(server->ServerTimeout))<=0){
       fatal("server timeout", __FILE__,__FUNCTION__,__LINE__);
        s->status = 504;
       break;
    }
    if(b->ctime!=NULL){
     if(b->ctime(s, atoi(CCSHOW(server->ServerTimeout)))){
       fatal("server time out", __FILE__,__FUNCTION__,__LINE__);
       s->status = 504;
       break;
     }
    }else{
    	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}
    
    if(b->cread!=NULL){
     if(b->cread(s,buffer, length) <= 0){
       fatal("read buffer", __FILE__,__FUNCTION__,__LINE__);
       s->status = 403;
       break;
     }
    }else{
       fatal("stack module handle ", __FILE__, __FUNCTION__, __LINE__);
	   break;
	}
   // printf(" #$ %s \n", buffer);
    if(libsec_verify(buffer)!=0){
       s->status = 503;
       break;
    }
    buffer = request_ascii(buffer);
    //printf(" ======================== \n");
     
    request_client(&request, buffer, &s->status);
    if(s->status != 503){
       fatal("server gateway", __FILE__,__FUNCTION__,__LINE__);
       s->status = 504;
       break;
    }
     //printf(" ======================== \n");
    //b->cremote(s, request->RemoteAddr);
    
    while(1){
       if(b->cread!=NULL){
        if(b->cread(s,buffer, length) <= 0){
          //fatal("read function", __FILE__,__FUNCTION__,__LINE__);
          break;
        }
       }else{
       	  fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
       	  break;
	   }
       //printf(" #C (%s)\n",buffer);
       request_externs(&request, buffer);
    }
    
    s->status = request_path(&request);
    //printf("==== %d\n", s->status);
    
 //}while(0);
    //printf("request init raw buffer \n");
     CLEAN(buffer);
    //printf("request clean raw buffer \n");
 // do{  
    if(!CCCHECK(request->ServerAddr)){
        fatal("old memory ", __FILE__, __FUNCTION__, __LINE__);
    }
    //CCNEW(request->ServerAddr , "XXX.XXX.XXX.XXX");
    if(!CCCHECK(request->RemoteAddr)){
        fatal("old memory ", __FILE__, __FUNCTION__, __LINE__);
    }
    //CCNEW(request->RemoteAddr  , "XXX.XXX.XXX.XXX");
    if(b->cipaddr!=NULL){
       b->cipaddr(s, request->ServerAddr, request->RemoteAddr);
    }else{
    	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}
    //printf("SERVER: %s , %s \n",request->ServerAddr,  request->RemoteAddr);
    //caccess(NULL);

     
     #ifdef  DBG_SH
     request_info(&request);
     #endif
     
     request->ServerCode = s->status;
     //if(s->status == 100)
     //request_checkfile(request->PathTranslated, &s->status);
     //module_access_icons(&request);
     
     if((path = script_search(request, s->status ))!=NULL)
     {
     	  state = script_run(&sapi_request.header, &sapi_request.buffer, path, request);
     	  #ifdef DEBUG_H
	      printf("request_%d_path = (%s)\n", state, CCSHOW(request->PathTranslated));
	      #endif
	      
     	  #ifdef DEBUG_H
		  printf("SERVER STATE (%d) \n", state);
     	  #endif
		  if(state == 200){
		      script_clean(sapi_request.header, sapi_request.buffer);
		      //CLEAN(path);
		      
			  #ifdef DEBUG_H
	          printf("request_path = (%s)\n", CCSHOW(request->PathTranslated));
	          #endif
	          
		      if(access(CCSHOW(request->PathTranslated),0) ==0){
		      	
		      	  s->status = 200;
			  }
		      
		      goto CHECK_SCRIPT_200;
		  }else
		  if(state == 404){
		  	   #ifdef DEBUG_H
	           printf("request_path = (%s)\n", CCSHOW(request->PathTranslated));
	           #endif
	          
		  	   script_clean(sapi_request.header, sapi_request.buffer);
		      //CLEAN(path);
		      
		       if(access(CCSHOW(request->PathTranslated),0) ==0){
		      	
		      	  s->status = 200;
			   }
		      
		       goto CHECK_SCRIPT_200;
		      
		  	   break;
		  	   //CLEAN(path);
		  }else
		  if(state == 0){
		  	  while(script_header(sapi_request.header)>0){
		  	  	 if(sapi_request.header!=NULL && sapi_request.header->data!=NULL){
					 
				      if(b->cwrite!=NULL){
					  
				  	      b->cwrite(s, sapi_request.header->data->buffer, sapi_request.header->data->length );
				          #ifdef DEBUG_H
				          printf("Header:%s ", sapi_request.header->data->buffer);
				          #endif
				      }else{
				      	  fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
				      	  break;
					  }
			      }
			  }
		  	  strcpy(buff,"\r\n");
		  	  if(b->cwrite!=NULL){
			
                 b->cwrite(s,buff, strlen(buff));
              }else{
              	 fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
              	 break;
			  }
              if(sapi_request.buffer!=NULL){
			  
                 b->cwrite(s, sapi_request.buffer->buffer, sapi_request.buffer->length);
                 #ifdef DEBUG_H
                 printf("Body:%s \n", sapi_request.buffer->buffer );
		  	     #endif
		      }else{
		      	 fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
		      	 break;
			  }
			  script_clean(sapi_request.header, sapi_request.buffer);
			  
			  //CLEAN(path);
			  
		  	  break;
		  }else{
		      script_clean(sapi_request.header, sapi_request.buffer);
		  }
	 }
      
     CHECK_SCRIPT_200:
     
	 #ifndef DEBUG_H
	 printf("+request_path = (%s)\n", CCSHOW(request->PathTranslated));
	 #endif
	 	
    ptr = request_getheader(s->status);
    CCNEW(request->ServerHeader , ptr);
    CLEAN(ptr);
    ptr = request_getstatus(s->status);
    CCNEW(request->ServerStatus , ptr);
    CLEAN(ptr);
     
    if(s->status == 200){
       ptr = request_contentType(CCSHOW(request->PathTranslated), rtype );
       CCNEW(request->ContentType , ptr);
       CLEAN(ptr);
       ptr = request_contentLength(CCSHOW(request->PathTranslated));
       CCNEW(request->ContentLength , ptr);
       CLEAN(ptr);
    }else 
    if(s->status != 100 && s->status != 200){
       if(!CCCHECK(request->ContentType)){
          fatal("old memory ", __FILE__, __FUNCTION__, __LINE__);
       }
       CCNEW(request->ContentType , "text/html;");
       ptr = zmod_request_pageLength(module_stack, CCSHOW(request->ServerStatus), CCSHOW(request->ServerSoftware));
	   CCNEW(request->ContentLength , ptr);
       CLEAN(ptr);
    }else{
       if(!CCCHECK(request->ContentType)){
           fatal("old memory ", __FILE__, __FUNCTION__, __LINE__);
       }
       CCNEW(request->ContentType,"text/html;");
       if(!CCCHECK(request->ContentLength)){
           fatal("old memory ", __FILE__, __FUNCTION__, __LINE__);
       }
       CCNEW(request->ContentLength ,"0");
    }
    if(CCSHOW(request->RequestMethod)==NULL){
          fatal("method request", __FILE__,__FUNCTION__,__LINE__);
          s->status = 405;
          break;
    }
	 #ifndef DEBUG_H
	 printf("-request_path = (%s)\n", CCSHOW(request->PathTranslated));
	 #endif
     //printf("Status(%d)Path(%s)\n", s->status, CCSHOW(request->PathTranslated));
     
     if(zmod_request_module_script(module_stack, request)){
     	  
     	  #ifdef DEBUG_H
		  printf("Module Request (%s) \n", CCSHOW(request->PathTranslated));
     	  #endif
     	  
     	  zmod_csp_module_startup(module_stack, &sapi_request, request);
     	  zmod_csp_module_execute(module_stack, &sapi_request);
     	  
     	  while(script_header(sapi_request.header)>0){
     	  	if(sapi_request.header!=NULL){
     	  	  if(sapi_request.header->data!=NULL){
     	  	    if(sapi_request.header->data->buffer!=NULL){
			      b->cwrite(s, sapi_request.header->data->buffer, sapi_request.header->data->length );
				  //printf("header(%s) \n", sapi_request.header->data->buffer);	
			    }else{
			    	fatal("buffer memory", __FILE__, __FUNCTION__, __LINE__);	
				}
		      }else{
		      	   fatal("buffer memory", __FILE__, __FUNCTION__, __LINE__);	
			  }
		    }else{
		    	fatal("buffer memory", __FILE__, __FUNCTION__, __LINE__);	
			}
		  }
		  strcpy(buff,"\r\n");
          b->cwrite(s,buff, strlen(buff));
          if(sapi_request.buffer!=NULL){
           if(sapi_request.buffer->buffer!=NULL){
     	      b->cwrite(s, sapi_request.buffer->buffer , sapi_request.buffer->length);
     	      //printf("buffer(%s) \n", sapi_request.buffer->buffer);
	       }else{
	       	  fatal("buffer memory", __FILE__, __FUNCTION__, __LINE__);
		   }
	     }else{
	     	fatal("buffer memory", __FILE__, __FUNCTION__, __LINE__);
		 }
		  	      
     	  zmod_csp_module_cleanup(module_stack, &sapi_request);
     	
     	  break;
	 }
	 
     
     if(stat(CCSHOW(request->PathTranslated), &st) !=-1 ){
     	 if( path_check_folder(st.st_mode)){ 
              s->status = 100;
         }
	 }

     #ifdef DEBUG_H
	 printf("Status(%d)Path(%s)\n", s->status, CCSHOW(request->PathTranslated));
	 #endif

     strcpy(buff,"HTTP/1.2 200 OK\r\n");
     if(b->cwrite!=NULL){
	    b->cwrite(s,buff, strlen(buff));
     }else{
     	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
     	break;
	 }
     if(CCSHOW(request->RequestTimes)!=NULL){
        sprintf(buff,"Date: %s\r\n", CCSHOW(request->RequestTimes));
        if(b->cwrite!=NULL){
           b->cwrite(s,buff, strlen(buff));
        }else{
        	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
        	break;
		}
     }
     if(CCSHOW(request->ServerName)!=NULL){
         sprintf(buff,"Server: %s\r\n", CCSHOW(request->ServerName));
         if(b->cwrite!=NULL){
           b->cwrite(s,buff, strlen(buff));
        }else{
        	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
        	break;
		}
     }
     strcpy(buff,"Accept-Ranges: bytes\r\n");
     if(b->cwrite!=NULL){
        b->cwrite(s,buff, strlen(buff));
     }else{
        fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
        break;
	 }
     
    /* if(request->ContentLength!=NULL){
        sprintf(buff,"Content-Length: %d\r\n",request->ContentLength);
        b->cwrite(s,buff, strlen(buff));
     } */
     
     strcpy(buff,"Connection: close\r\n");
     if(b->cwrite!=NULL){
        b->cwrite(s,buff, strlen(buff));
     }else{
        fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
        break;
	 }
     if(!CCCHECK(request->ContentType)){
     	//printf("%s::\n", CCSHOW(request->ContentType));
        if(s->status == 100){
           strcpy(buff,"Content-Type: text/html;\r\n");
	    }else{
		   sprintf(buff,"Content-Type: %s;\r\n", CCSHOW(request->ContentType) );
		}
		
        if(b->cwrite!=NULL){
           b->cwrite(s,buff, strlen(buff));
        }else{
        	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
        	break;
		}
     }
     strcpy(buff,"\r\n");
     if(b->cwrite!=NULL){
        b->cwrite(s,buff, strlen(buff));
     }else{
        fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
        break;
	 }
     
     	
    // printf("> status(%d) url(%s) \n",s->status, request->RequestUri);
    // printf("> path (%s) \n", request->PathTranslated);
     /*
	 if(libcsp_check(request->PathTranslated)){
           
           buffer = (char *)libcsp_startup(request, buffer , &size);
           
           if(buffer==NULL){
               fatal("buffer segment", __FILE__, __FUNCTION__ ,__LINE__);
               
           }
           if(size <= 0){
               fatal("sizeof segment", __FILE__, __FUNCTION__, __LINE__);
           }
           b->cwrite(s,buffer, size);
           
           libcsp_cleanup(buffer);
           //printf("CSP LIB \n");
           
           break;
     }*/
     
   
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_HEAD_STR)==0){
          
     }else
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_GET_STR)==0){
          #ifdef DEBUG_H
		  printf("GET - Status (%d) (%s)\n", s->status, CCSHOW(request->PathTranslated));
		  #endif
          if(s->status == 200){
             
             
             length =  atoi(CCSHOW(request->ContentLength)) ;
             if(length <= 0){
                  fatal("server length", __FILE__, __FUNCTION__, __LINE__);
                  break;
             }
             //strcpy(buff,"Hello world!");
             if(buffer != NULL){
                 fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
             }     
             buffer = (char *) emalloc( length+16 );
             if(buffer==NULL){
                 fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
                 break;
             }
             //printf("*************************\n");
             size = request_read(
                       CCSHOW(request->PathTranslated), 
                       buffer, 
                       length );
             //request_readpage(buffer, 
             //         request->ServerStatus, 
             //         request->ServerSoftware, 
             //         atoi( request->ContentLength ));
             //printf("*************************\n"); 
             
             if(b->cwrite!=NULL){
			 
                b->cwrite(s, buffer, size);
             }else{
             	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
             	break;
			 }
			 //b->cdone(s);
             
             //printf("buffer[%s]\n", buffer);
             //printf("*************************\n");
             CLEAN(buffer);
          
          }else 
          if(s->status != 100 && s->status != 200){
             //strcpy(buff,"Server Gateway");    
            
             length =  atoi(CCSHOW(request->ContentLength)) ;
             
             if(buffer!=NULL){
                 fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
             }
             buffer = (char *) emalloc( length );
             if(buffer==NULL){
                 fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
                 break;
             }
             size = zmod_request_readpage(module_stack, buffer, request );
              
             if(b->cwrite!=NULL){
			 
			   b->cwrite(s, buffer, size );
             }else{
             	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
             	break;
			 }
			 //b->cdone(s);
             
             //printf("buffer[%s]\n", buffer);
             
             CLEAN(buffer);
          }else
          if(s->status == 100){
             
             zmod_request_dirinit(module_stack);
             length = zmod_request_getfrontsize(module_stack, CCSHOW(request->FileSelf));
             
             if(buffer!=NULL){
                  fatal("memory new allocate", __FILE__, __FUNCTION__, __LINE__);
             }
             buffer = (char *) emalloc( length+16 );
             if(buffer==NULL){
                 fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
                 break;
             }
             
             size = zmod_request_getfront(module_stack, buffer, length, CCSHOW(request->FileSelf));
             b->cwrite(s, buffer, size );
             
             CLEAN(buffer);
             
             hfd = zmod_request_dirliststart(module_stack, CCSHOW(request->PathTranslated));
             while((buffer=(char*)zmod_request_dirlistloop(module_stack, &hfd,CCSHOW(request->FileSelf), &size))!=NULL){
                //printf("^%s \n", buffer);
                if(buffer!=NULL) {
				   if(b->cwrite!=NULL){
				   
				     b->cwrite(s, buffer, size );
				   }else{
				   	 fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
				   	 break;
				   }
                }
				CLEAN(buffer);
                //printf("=====================\n");
             }
             CLEAN(buffer);
             zmod_request_dirlistend(module_stack, &hfd);
           
             //printf(">>>>>>>>>>>>>>>>>>>>>>>>>\n");
             
             if(request->HTTPHostName==NULL){
             length = zmod_request_getbacksize(module_stack, 
                               CCSHOW(request->ServerSoftware),  
                               CCSHOW(request->ServerVersion),
                               CCSHOW(request->ServerOS),
                               CCSHOW(request->RemoteAddr),
                               CCSHOW(request->ServerPort));
             }else{
             length = zmod_request_getbacksize(module_stack,
                               CCSHOW(request->ServerSoftware),  
                               CCSHOW(request->ServerVersion),
                               CCSHOW(request->ServerOS),
                               CCSHOW(request->HTTPHostName) ,
                               CCSHOW(request->ServerPort));
             }
             
             if(buffer!=NULL){
                 fatal("memory new allocate ", __FILE__, __FUNCTION__, __LINE__);
             }
             buffer = (char *) emalloc( length+16 );
             if(buffer==NULL){
                 fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
                 break;
             }
             if(request->HTTPHostName==NULL){
             size = zmod_request_getback(module_stack, buffer, length, 
                               CCSHOW(request->ServerSoftware),  
                               CCSHOW(request->ServerVersion),
                               CCSHOW(request->ServerOS),
                               CCSHOW(request->RemoteAddr),
                               CCSHOW(request->ServerPort));
             }else{
             size = zmod_request_getback(module_stack, buffer, length, 
                               CCSHOW(request->ServerSoftware),  
                               CCSHOW(request->ServerVersion),
                               CCSHOW(request->ServerOS),
                               CCSHOW(request->HTTPHostName) ,
                               CCSHOW(request->ServerPort));
             }
             if(b->cwrite!=NULL){
			 
			   b->cwrite(s, buffer, size );
             }else{
             	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
             	break;
			 }
             CLEAN(buffer);
             
             
             zmod_request_dirfini(module_stack);
             
             //b->cdone(s);
             //printf("*************************\n");
          }
                                                   
     }else
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_POST_STR)==0){
          
          //printf("> #(%s) \n", request->HTTPCookie);
          //printf("> $(%s) \n", request->
          if(s->status == 200){
             
             length =  atoi(CCSHOW(request->ContentLength)) ;
             //strcpy(buff,"Hello world!"); 
             
             if(buffer!=NULL){
                 fatal("memory new allocate", __FILE__,__FUNCTION__,__LINE__);
             }    
             buffer = (char *) emalloc( length+16 );
             if(buffer==NULL){
                 fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
                 break;
             }
             
             size = request_read(
                       CCSHOW(request->PathTranslated), 
                       buffer, 
                       length );
             //request_readpage(buffer, 
             //         request->ServerStatus, 
             //         request->ServerSoftware, 
             //         atoi( request->ContentLength ));
             if(b->cwrite!=NULL){
			 
               b->cwrite(s, buffer, size);
             }else{
             	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
             	break;
			 }
			 //b->cdone(s);
             
             //printf("buffer[%s]\n", buffer);
             
             CLEAN(buffer);
          
          }else 
          if(s->status != 100 && s->status != 200){
             //strcpy(buff,"Server Gateway");    
             length =  atoi(CCSHOW(request->ContentLength)) ;
             
             if(buffer!=NULL){
                fatal("memory new allocate ", __FILE__,__FUNCTION__,__LINE__);
             }
             buffer = (char *) emalloc( length );
             if(buffer==NULL){
                 fatal("allocate memory ",__FILE__,__FUNCTION__,__LINE__);
                 break;
             }
             size = zmod_request_readpage(module_stack, buffer, request);
              
             if(b->cwrite!=NULL) {
             	
			   b->cwrite(s, buffer, size );
             }else{
             	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
             	break;
			 }
			 //b->cdone(s);
             
             //printf("buffer[%s]\n", buffer);
             
             CLEAN(buffer);
          }
                                                           
     }else
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_PUT_STR)==0){
                                                           
     }else
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_TRACE_STR)==0){
                                                           
     }else
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_DELETE_STR)==0){
                                                           
     }else
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_OPTIONS_STR)==0){
                                                           
     }else
     if(cstrcmp(CCSHOW(request->RequestMethod),METHOD_PROPFIND_STR)==0){
                                                           
     }     
   }while(0);
     
//     /script_clean(sapi_request.header, sapi_request.buffer);
     
     if(CCCHECK(request->RemoteAddr) && CCCHECK(request->ServerAddr)){
		// if() CCNEW(request->ServerAddr,"XXX.XXX.XXX.XXX");
     	//CCNEW(request->RemoteAddr, "XXX.XXX.XXX.XXX");
     	if(b->cipaddr!=NULL){
		   b->cipaddr(s, request->ServerAddr, request->RemoteAddr);
        }else{
        	fatal("stack module handle", __FILE__, __FUNCTION__, __LINE__);
		}
	 }

     get_fatal(fatal_str);
     realtime_str = get_realtime();
	 zlogs_data zlogs = {
	     CCSHOW(request->RemoteAddr),
	     CCSHOW(request->RequestUri),
	     fatal_str,
	     realtime_str,
	 };
     ulogs_access(&zlogs);
     CLEAN(realtime_str);

     b->cdone(s);
     //printf("*************************$$$#2\n");
     request_fini(&request);
     CLEAN(request);
     CLEAN(buffer);
     
     efini(NULL);
     //printf("*************************$$$#3\n");

     fatal_clean();
     fatal_fini();
}


uint32_t  request_module(iserver_module *b, iserver_config *s, void *d)
{
          

}

unsigned long externs_long(const char *buffer)
{
     int i;
      const char *reqdata[] = {
          "Accept:",
          "Accept-Language:",
          "Accept-Charset:",
          "User-Agent:",
          "Accept-Encoding:",
          "Host:",
          "Connection:",
          "Pragma:",
          "Cache-Control:",
          "Referer:",
          "Cookie:" ,
          "Content-Type:",
          "Keep-Alive" 
          };
    /*
     if(strncmp(buffer, "Accept", 6) ==0 ){
      for( i=0;i<11;i++)
      {
       printf("[%s] %x \n", __FUNCTION__, kstrlen(reqdata[i]));
      }          
    }
    */
    //printf(">> %s\n", buffer);
    
    if(strncmp(buffer, reqdata[0], strlen(reqdata[0] )) ==0){
         return HTTPACCEPT;
    }
    if(strncmp(buffer, reqdata[1], strlen(reqdata[1] )) ==0){
         return HTTPACCEPTLANGUAGE;
    }
    if(strncmp(buffer, reqdata[2], strlen(reqdata[2] )) ==0){
         return HTTPACCEPTCHARSET;
    }   
    if(strncmp(buffer, reqdata[3], strlen(reqdata[3] )) ==0){
         return HTTPUSERAGENT;
    } 
    if(strncmp(buffer, reqdata[4], strlen(reqdata[4] )) ==0){
         return HTTPACCEPTENCODING;
    }     
    if(strncmp(buffer, reqdata[5], strlen(reqdata[5] )) ==0){
        /// printf("%s=%s\n", buffer, reqdata[5]);
         //printf("=========================\n");
         return HTTPHOSTNAME;
    }   
    if(strncmp(buffer, reqdata[6], strlen(reqdata[6] )) ==0){
         return HTTPCONNECTION;
    }
    if(strncmp(buffer, reqdata[7], strlen(reqdata[7] )) ==0){
         return HTTPPRAGMA;
    }     
    if(strncmp(buffer, reqdata[8], strlen(reqdata[8] )) ==0){
         return HTTPCACHECONTROL;
    }    
    if(strncmp(buffer, reqdata[9], strlen(reqdata[9] )) ==0){
         return HTTPREFERER;
    }   
    if(strncmp(buffer, reqdata[10], strlen(reqdata[10] )) ==0){
         return HTTPCOOKIE;
    }
    if(strncmp(buffer, reqdata[11], strlen(reqdata[11] )) == 0){
         //printf("%s=%s\n", buffer, reqdata[11]);
         return HTTPCONTENTTYPE;
    }
    if(strncmp(buffer, reqdata[12], strlen(reqdata[12] )) == 0){
         //printf("%s=%s\n", buffer, reqdata[11]);
         return HTTPKEEPALIVE;
    }
    return 0;
}
unsigned long externs_size(unsigned long p)
{
    if(p == HTTPACCEPT){
         return (HTTPACCEPT >> 8) & 0xff;
    }
    if(p == HTTPACCEPTLANGUAGE){
         return (HTTPACCEPTLANGUAGE >> 8) & 0xff;
    }
    if(p == HTTPACCEPTCHARSET){
         return (HTTPACCEPTCHARSET >> 8) & 0xff;
    }   
    if(p == HTTPUSERAGENT){
         return (HTTPUSERAGENT >> 8) & 0xff;
    } 
    if(p == HTTPACCEPTENCODING){
         return (HTTPACCEPTENCODING >> 8) & 0xff;
    }     
    if(p == HTTPHOSTNAME){
         return (HTTPHOSTNAME >> 8) & 0xff;
    }   
    if(p == HTTPCONNECTION){
         return (HTTPCONNECTION >> 8) & 0xff;
    }
    if(p == HTTPPRAGMA){
         return (HTTPPRAGMA >> 8) & 0xff;
    }     
    if(p == HTTPCACHECONTROL){
         return (HTTPCACHECONTROL >> 8) & 0xff;
    }    
    if(p == HTTPREFERER){
         return (HTTPREFERER >> 8) & 0xff;
    }   
    if(p == HTTPCOOKIE){
         return (HTTPCOOKIE >> 8) & 0xff;
    }
    if(p == HTTPCONTENTTYPE){
         return (HTTPCONTENTTYPE >> 8) & 0xff;
    }
    return 0;
}

char *externs_new(unsigned long p, const char *buffer)
{
    char *ptr=(char *) buffer;
    
    if(externs_long(buffer) == p){
       
       ptr += externs_size(p);
       //printf("[%s][%s] \n", buffer, ptr);
       if(ptr[0] == ' ') ptr+=1;
       
       return _new_str(ptr); 
    }else{
       //printf("[%x][%s]\n",p, buffer);
    }
       
    return NULL;
}

uint32_t request_startup(zrequest_externs_t **s, zconfig_server_t *c)
{
   zrequest_externs_t *p = (zrequest_externs_t*) *s;
   
  do{
    if(p == NULL){
       fatal("heap allocate ",__FILE__,__FUNCTION__,__LINE__);
       break;
            
    }
    if(c == NULL){
       fatal("heap allocate ",__FILE__,__FUNCTION__,__LINE__);
       break;
    }
    if(!CCCHECK(p->ServerOS)){             fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
    CCNEW(p->ServerOS        , SERVER_OS) ;
    if(!CCCHECK(p->ServerSoftware)){        fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
    CCNEW(p->ServerSoftware   ,SERVER_SOFTWARE) ; //SERVER_SOFTWARE;
	if(!CCCHECK(p->ServerName)){            fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
    CCCLONE(p->ServerName       , c->ServerName) ;     //SERVER_NAME;
    if(!CCCHECK(p->ServerVersion)){         fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
	CCNEW(p->ServerVersion    , SERVER_VERSION);  //SERVER_VERSION
	if(!CCCHECK(p->ServerProtocol)){        fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
	CCNEW(p->ServerProtocol   ,"TCP") ; //SERVER_PROTOCOL;
	if(!CCCHECK(p->ServerAddress)){         fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
	CCCLONE(p->ServerAddress    ,c->ServerAddr);   // SERVER_ADDRESS
	if(!CCCHECK(p->ServerPort)){            fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
	CCCLONE(p->ServerPort       ,c->ServerPort);     //SERVER_PORT;
	if(!CCCHECK(p->ServerAdmin)){           fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
	CCNEW(p->ServerAdmin      , SERVER_ADMINWH);    //SERVER_ADMIN;
	if(!CCCHECK(p->GatewayInterface)){      fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
	CCNEW(p->GatewayInterface  , SERVER_GATEWAY);//GATEWAY_INTERFACE;
	if(!CCCHECK(p->DocumentRoot)){          fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
	CCCLONE(p->DocumentRoot     , c->DocumentRoot);    //DOCUMENT_ROOT;
	if(!CCCHECK(p->ServerRoot)){            fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
    CCCLONE(p->ServerRoot      , c->ServerRoot);
    //if(p->ServerName!=NULL){            fatal("old memory ", __FILE__, __FUNCTION__, __LINE__); }
    
    CCNEWPAD(p->FileIndexName    ,CCSHOW(c->DocumentIndex),",");
    CCNEWPAD(p->FileLastName     ,CCSHOW(c->DocumentName),",");
    //printf("> $$$$$$$ \n");
    CCNEW(p->RequestTimes     , _new_time());
    //printf("> $$$$$$$ \n");
    if(CCCHECK(c->ContentType )) { fatal("content type",__FILE__,__FUNCTION__,__LINE__); }else{
    CCNEWPAD(p->DefaultContentType , CCSHOW(c->ContentType), "," ); }
    if(CCCHECK(c->ContentCharset)) { fatal("content charset",__FILE__,__FUNCTION__,__LINE__); }else{
    CCNEWPAD(p->DefaultCharset     , CCSHOW(c->ContentCharset), "," ); }
   
   }while(0);
   
   *s = p; 
   //printf("> $$$$$$$ \n");
   return 0;
}
uint32_t  request_externs(zrequest_externs_t **s, const char *buffer)
{
   char    *ptr=NULL;
   zrequest_externs_t *p = (zrequest_externs_t *) *s ;
   do{
      if(p == NULL){
       fatal("heap allocate ",__FILE__,__FUNCTION__,__LINE__);
       break;      
      }             
	  //printf("buffer: %s \n", buffer);
	     
      if(CCCHECK(p->HTTPAccept) && (ptr=externs_new(HTTPACCEPT, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPAccept , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPAccept_language) && (ptr=externs_new(HTTPACCEPTLANGUAGE, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPAccept_language , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPAccept_charset) && (ptr=externs_new(HTTPACCEPTCHARSET, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPAccept_charset  , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPUserAgent) && (ptr=externs_new(HTTPUSERAGENT, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPUserAgent       , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPWebBrowser) && (ptr=externs_new(HTTPWEBBROWSER, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPWebBrowser      , ptr ); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPAccept_encoding) && (ptr=externs_new(HTTPACCEPTENCODING, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPAccept_encoding , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPHostName)  && (ptr=externs_new(HTTPHOSTNAME, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPHostName        , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPConnection) && (ptr= externs_new(HTTPCONNECTION, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPConnection      , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPPragma) && (ptr=externs_new(HTTPPRAGMA, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPPragma          , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPCacheControl) && (ptr=externs_new(HTTPCACHECONTROL, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPCacheControl    , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPReferer) && (ptr=externs_new(HTTPREFERER, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPReferer         , ptr); CLEAN(ptr); CCEND
      if(CCCHECK(p->HTTPCookie) && (ptr=externs_new(HTTPCOOKIE, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPCookie          , ptr); CLEAN(ptr); CCEND
      
      if(!CCCHECK(p->HTTPContentType) && (ptr=externs_new(HTTPCONTENTTYPE, buffer))!=NULL)
      CCSTART CCNEW(p->HTTPContentType     , ptr); CLEAN(ptr); CCEND
      
      
    }while(0);
      
      *s = p;   
      
      return 0;        
}


char* method_new(const char *pstr)
{
    if(strncmp(pstr,"GET ",4 )==0){ 
        return _new_str("GET");        
	}else 
	if(strncmp(pstr,"HEAD ",5)==0){ 
	    return _new_str("HEAD");
	}else 
    if(strncmp(pstr,"POST ",5)==0){ 
	    return _new_str("POST");
	}else 
	if(strncmp(pstr,"PUT ",4)==0){
	    return _new_str("PUT");
	}else 
	if(strncmp(pstr,"DELETE ",7)==0){ 
	    return _new_str("DELETE");
	}else 
	if(strncmp(pstr,"TRACE ",6)==0){
	    return _new_str("TRACE");
	}else 
	if(strncmp(pstr,"OPTIONS ",8)==0){
	    return _new_str("OPTIONS"); 
	}else 
	if(strncmp(pstr,"PROPFIND ",9)==0){ 
	    return _new_str("PROPFIND"); 
	}else{
		return NULL;
	}
	return NULL;
}
unsigned long method_long(const char *pstr)
{
    //printf("[%s(%s)] \n", __FUNCTION__, pstr);
    
    if(strncmp(pstr,"GET",3 )==0){ 
        return METHOD_GET;  
	}else 
	if(strncmp(pstr,"HEAD",4)==0){ 
	    return METHOD_HEAD;
	}else 
    if(strncmp(pstr,"POST",4)==0){ 
	    return METHOD_POST;
	}else 
	if(strncmp(pstr,"PUT",3)==0){
	    return METHOD_PUT;
	}else 
	if(strncmp(pstr,"DELETE",6)==0){ 
	    return METHOD_DELETE;
	}else 
	if(strncmp(pstr,"TRACE",5)==0){
	    return METHOD_TRACE;
	}else 
	if(strncmp(pstr,"OPTIONS",7)==0){
	    return METHOD_OPTIONS; 
	}else 
	if(strncmp(pstr,"PROPFIND",8)==0){ 
	    return METHOD_PROPFIND; 
	}else{
		return 0;
	}
	return 0;    
}
unsigned long method_size(unsigned long p)
{
    //printf("%s[%x] \n", __FUNCTION__, p);
          
    if(p == METHOD_GET){ 
        return (METHOD_GET >> 8) & 0xff;  
	}else 
	if(p == METHOD_HEAD){ 
	    return (METHOD_HEAD >> 8) & 0xff;
	}else 
    if(p ==  METHOD_POST){ 
	    return (METHOD_POST >> 8) & 0xff;
	}else 
	if(p == METHOD_PUT){
	    return (METHOD_PUT >> 8) & 0xff;
	}else 
	if(p == METHOD_DELETE){ 
	    return (METHOD_DELETE >> 8) & 0xff;
	}else 
	if(p == METHOD_TRACE){
	    return (METHOD_TRACE >> 8) & 0xff;
	}else 
	if(p == METHOD_OPTIONS){
	    return (METHOD_OPTIONS >> 8) & 0xff; 
	}else 
	if(p == METHOD_PROPFIND){ 
	    return (METHOD_PROPFIND >> 8) & 0xff; 
	}else{
		return 0;
	}
	return 0;    
}

uint32_t  request_client(zrequest_externs_t  **s, const char *buffer, int *status)
{
    zrequest_externs_t *p = (zrequest_externs_t *) *s;
    char    *ptr=NULL,*pstr=(char *)buffer;
    int      method;
    
    do{
       if(p == NULL){
         fatal("heap allocate ",__FILE__,__FUNCTION__,__LINE__);
         break;   
       }      
       CCNEW(p->RequestUri , buffer);
            
       if((ptr=strstr(pstr, " HTTP/1"))==NULL){
           *status = 505;
       }else{
         *ptr=0;
         ptr =NULL;
       }
       //printf("**********************************\n");
        ptr = method_new(pstr);
        CCNEW(p->RequestMethod, ptr );
        CLEAN(ptr);
        if(CCCHECK(p->RequestMethod)){
             *status = 405;
             break;
        }
       //printf("**********************************\n"); 
        method = method_long(CCSHOW(p->RequestMethod));
        if(!method)
        {
             *status = 405;
              break;
         }
       //printf("**********************************\n");
            //printf(" -- >> [%d] \n", method_size(reqw->method));
       pstr += method_size(method);
       if(pstr[strlen(pstr)-1] =='/')
              pstr+= 1;
       if(pstr[0] ==' ' ) pstr+=1;
       
       CCNEW(p->ScriptName , pstr);
            
       if((ptr=strchr(pstr,'?'))!=NULL){
	   
           CCNEW(p->QueryString , ptr );
           if(CCCHECK(p->QueryString)){
                break;
           }   
		      *ptr=0;
              ptr=NULL;
        }
        
        CCNEW(p->FileSelf , pstr );
        CCNEW(p->FileSelf , request_pathdecrypt(CCSHOW(p->FileSelf)));
        
        if(pstr[0] == '/')
           pstr+= 1;
           
        CCNEW(p->UrlCache , pstr );
        if(!CCCHECK(p->UrlCache) && strlen(CCSHOW(p->UrlCache))==CACHE_LENGTH && script_cache(CCSHOW(p->UrlCache)) ){ 
		   //
		}else{
			CCCLEAR(p->UrlCache);
		}
        //if(p->FileSelf[0]==' ')
         //  p->FileSelf+=1;
        CCNEW(p->FileQuery ,  pstr );                
      // printf("> EXT %s \n", buffer);
   }while(0);
   
   *s = p;
   return 0;
}

uint32_t  request_init(zrequest_externs_t **s){
	zrequest_externs_t *p=(zrequest_externs_t*)*s;
  do{  
    if(p==NULL){
        fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
        break;
    }
    CCNULL(p->ServerOS);
    CCNULL(p->ServerSoftware); //SERVER_SOFTWARE;
	CCNULL(p->ServerName);     //SERVER_NAME;
	CCNULL(p->ServerVersion);   //SERVER_VERSION
	CCNULL(p->ServerProtocol); //SERVER_PROTOCOL;
	CCNULL(p->ServerAddress);   // SERVER_ADDRESS
	CCNULL(p->ServerPort);     //SERVER_PORT;
	CCNULL(p->ServerAdmin);    //SERVER_ADMIN;
	CCNULL(p->GatewayInterface);//GATEWAY_INTERFACE;
	CCNULL(p->DocumentRoot);    //DOCUMENT_ROOT;
	CCNULL(p->ServerRoot);
	
	CCNULL(p->PathTranslated);  //PATH_TRANSLATED;
	CCNULL(p->FullPathTranslated);
	CCNULL(p->RequestMethod);   //REQUEST_METHOD;  10
	CCNULL(p->RequestUri);      //REQUEST_URI;
	CCNULL(p->ScriptName);      //SCRIPT_NAME;
	CCNULL(p->FileSelf);         //PHP_SELF;
	CCNULL(p->FileQuery);        // FILE_QUERY
	CCNULL(p->QueryString);     //QUERY_STRING;
	
	CCNULL(p->UrlCache);
	
	CCNULL(p->ServerAddr);
	CCNULL(p->RemoteAddr);      //REMOTE_ADDR;
	CCNULL(p->ServerStatus);      //REMOTE_ADDR;
	CCNULL(p->ServerHeader);      //REMOTE_ADDR;
	CCNULL(p->ContentLength);   //CONTENT_LENGTH;
	CCNULL(p->ContentType);     //CONTENT_TYPE;
	CCNULL(p->Charset);
	
	CCNULL(p->DefaultContentType);  //CONTENT_TYPE;
	CCNULL(p->DefaultCharset);
	
    CCNULL(p->AuthType);        //AUTH_TYPE;
	CCNULL(p->EntityPath);      //ENTITY_PATH;        20
	CCNULL(p->RemoteUser);      //REMOTE_USER;
	CCNULL(p->ServerHost);      //SERVER_HOST
	CCNULL(p->HTTPHostName);        // HTTP_HOSTNAME
	CCNULL(p->HTTPCookie);      //HTTP_COOKIE;
	CCNULL(p->HTTPUserAgent);  //HTTP_USER_AGENT;
	CCNULL(p->HTTPWebBrowser);  //HTTP_WEBBROWSER ; DEFINE BY Lexne
	CCNULL(p->HTTPReferer);     //HTTP_REFERER;
	CCNULL(p->HTTPAccept);      //HTTP_ACCEPT;
	CCNULL(p->HTTPConnection);   // HTTP_CONNECTION
	CCNULL(p->HTTPAccept_language); //HTTP_ACCEPT_LANGUAGE;  30
	CCNULL(p->HTTPAccept_charset);  //HTTP_ACCEPT_CHARSET;
	CCNULL(p->HTTPAccept_encoding); //HTTP_ACCEPT_ENCODING;
	
	CCNULL(p->HTTPContentType);
	CCNULL(p->KeepAlive);
	//PHP_AUTH_USER
	//PHP_AUTH_PW
	//AUTH_TYPE
	
	CCNULL(p->HTTPPragma);
	CCNULL(p->HTTPCacheControl);
	
	CCNULL(p->RequestTimes);
    
    CCNULL(p->FileLastName);
    CCNULL(p->FileIndexName);
    
    }while(0);
     
    *s = p;
    
    return 0;
}
uint32_t  request_fini(zrequest_externs_t **s){
	zrequest_externs_t *p=(zrequest_externs_t*)*s;
  do{  
    if(p==NULL){
        fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
        break;
    }
    CCLEAN(p->ServerOS);
    CCLEAN(p->ServerSoftware); //SERVER_SOFTWARE;
	CCLEAN(p->ServerName);     //SERVER_NAME;
	CCLEAN(p->ServerVersion);   //SERVER_VERSION
	CCLEAN(p->ServerProtocol); //SERVER_PROTOCOL;
	CCLEAN(p->ServerAddress);   // SERVER_ADDRESS
	CCLEAN(p->ServerPort);     //SERVER_PORT;
	CCLEAN(p->ServerAdmin);    //SERVER_ADMIN;
	CCLEAN(p->GatewayInterface);//GATEWAY_INTERFACE;
	CCLEAN(p->DocumentRoot);    //DOCUMENT_ROOT;
	CCLEAN(p->ServerRoot);
	
	CCLEAN(p->PathTranslated);  //PATH_TRANSLATED;
	CCLEAN(p->FullPathTranslated);
	CCLEAN(p->RequestMethod);   //REQUEST_METHOD;  10
	CCLEAN(p->RequestUri);      //REQUEST_URI;
	CCLEAN(p->ScriptName);      //SCRIPT_NAME;
	CCLEAN(p->FileSelf);         //PHP_SELF;
	CCLEAN(p->FileQuery);        // FILE_QUERY
	CCLEAN(p->QueryString);     //QUERY_STRING;
	
	CCLEAN(p->UrlCache);
	
	CCLEAN(p->ServerAddr); 
	CCLEAN(p->RemoteAddr);      //REMOTE_ADDR;
	CCLEAN(p->ServerStatus);      //REMOTE_ADDR;
	CCLEAN(p->ServerHeader);      //REMOTE_ADDR;
	CCLEAN(p->ContentLength);   //CONTENT_LENGTH;
	CCLEAN(p->ContentType);     //CONTENT_TYPE;
	CCLEAN(p->Charset);
	
	CCLEAN(p->DefaultContentType);  //CONTENT_TYPE;
	CCLEAN(p->DefaultCharset);
	
    CCLEAN(p->AuthType);        //AUTH_TYPE;
	CCLEAN(p->EntityPath);      //ENTITY_PATH;        20
	CCLEAN(p->RemoteUser);      //REMOTE_USER;
	CCLEAN(p->ServerHost);      //SERVER_HOST
	CCLEAN(p->HTTPHostName);        // HTTP_HOSTNAME
	CCLEAN(p->HTTPCookie);      //HTTP_COOKIE;
	CCLEAN(p->HTTPUserAgent);  //HTTP_USER_AGENT;
	CCLEAN(p->HTTPWebBrowser);  //HTTP_WEBBROWSER ; DEFINE BY Lexne
	CCLEAN(p->HTTPReferer);     //HTTP_REFERER;
	CCLEAN(p->HTTPAccept);      //HTTP_ACCEPT;
	CCLEAN(p->HTTPConnection);   // HTTP_CONNECTION
	CCLEAN(p->HTTPAccept_language); //HTTP_ACCEPT_LANGUAGE;  30
	CCLEAN(p->HTTPAccept_charset);  //HTTP_ACCEPT_CHARSET;
	CCLEAN(p->HTTPAccept_encoding); //HTTP_ACCEPT_ENCODING;
	
	CCLEAN(p->HTTPContentType);
	CCLEAN(p->KeepAlive);
	//PHP_AUTH_USER
	//PHP_AUTH_PW
	//AUTH_TYPE
	
	CCLEAN(p->HTTPPragma);
	CCLEAN(p->HTTPCacheControl);
	
	CCLEAN(p->RequestTimes);
    
    CCLEAN(p->FileLastName);
    CCLEAN(p->FileIndexName);
    
    }while(0);
     
    *s = p;
    
   return 0;
}


uint32_t  request_info(zrequest_externs_t **s){
	zrequest_externs_t *p=(zrequest_externs_t*)*s;
  do{  
    if(p==NULL){
        fatal("heap allocate ", __FILE__,__FUNCTION__,__LINE__);
        break;
    }
    CHKDSK(p->ServerOS,__LINE__) CPRINT("ServerOS", CCSHOW(p->ServerOS)); CHKEND//SERVER_SOFTWARE;  
    
    CHKDSK(p->ServerSoftware,__LINE__) CPRINT("ServerSoftware",CCSHOW(p->ServerSoftware));CHKEND //SERVER_SOFTWARE;
	CHKDSK(p->ServerName,__LINE__) CPRINT("ServerName",CCSHOW(p->ServerName));    CHKEND //SERVER_NAME;
	CHKDSK(p->ServerVersion,__LINE__) CPRINT("ServerVersion",CCSHOW(p->ServerVersion));   CHKEND//SERVER_VERSION
	CHKDSK(p->ServerProtocol,__LINE__) CPRINT("ServerProtocol",CCSHOW(p->ServerProtocol)); CHKEND//SERVER_PROTOCOL;
	CHKDSK(p->ServerAddress,__LINE__) CPRINT("ServerAddress",CCSHOW(p->ServerAddress));   CHKEND// SERVER_ADDRESS
	CHKDSK(p->ServerPort,__LINE__) CPRINT("ServerPort",CCSHOW(p->ServerPort));     CHKEND//SERVER_PORT;
	CHKDSK(p->ServerAdmin,__LINE__) CPRINT("ServerAdmin",CCSHOW(p->ServerAdmin));    CHKEND//SERVER_ADMIN;
	CHKDSK(p->GatewayInterface,__LINE__) CPRINT("GateWayInterface",CCSHOW(p->GatewayInterface)); CHKEND//GATEWAY_INTERFACE;
	CHKDSK(p->DocumentRoot,__LINE__) CPRINT("DocumentRoot",CCSHOW(p->DocumentRoot));    CHKEND//DOCUMENT_ROOT;
	CHKDSK(p->ServerRoot,__LINE__) CPRINT("ServerRoot",CCSHOW(p->ServerRoot)); CHKEND
	
	CHKDSK(p->PathTranslated,__LINE__) CPRINT("PathTranslated",CCSHOW(p->PathTranslated));  CHKEND//PATH_TRANSLATED;
	CHKDSK(p->FullPathTranslated,__LINE__) CPRINT("FullPathTranslated",CCSHOW(p->FullPathTranslated)); CHKEND
	CHKDSK(p->RequestMethod,__LINE__) CPRINT("RequestMethod",CCSHOW(p->RequestMethod));   CHKEND//REQUEST_METHOD;  10
	CHKDSK(p->RequestUri,__LINE__) CPRINT("RequestUri", CCSHOW(p->RequestUri));      CHKEND//REQUEST_URI;
	CHKDSK(p->ScriptName,__LINE__) CPRINT("ScriptName",CCSHOW(p->ScriptName));      CHKEND//SCRIPT_NAME;
	CHKDSK(p->FileSelf,__LINE__) CPRINT("FileSelf", CCSHOW(p->FileSelf));         CHKEND//PHP_SELF;
	CHKDSK(p->FileQuery,__LINE__) CPRINT("FileQuery", CCSHOW(p->FileQuery));        CHKEND// FILE_QUERY
	CHKDSK(p->QueryString,__LINE__) CPRINT("QueryString",CCSHOW(p->QueryString));     CHKEND//QUERY_STRING;
	
	CHKDSK(p->UrlCache,__LINE__) CPRINT("URLCache", CCSHOW(p->UrlCache));      CHKEND
	
	CHKDSK(p->ServerAddr,__LINE__) CPRINT("ServerAddr",CCSHOW(p->ServerAddr));  CHKEND
	CHKDSK(p->RemoteAddr,__LINE__) CPRINT("RemoteAddr",CCSHOW(p->RemoteAddr));  CHKEND    //REMOTE_ADDR;
	CHKDSK(p->ServerHeader,__LINE__) CPRINT("ServerHeader",CCSHOW(p->ServerHeader));  CHKEND
	CHKDSK(p->ServerStatus,__LINE__) CPRINT("ServerStatus",CCSHOW(p->ServerStatus));  CHKEND    //REMOTE_ADDR;
	CHKDSK(p->ContentLength,__LINE__) CPRINT("ContentLength",CCSHOW(p->ContentLength)); CHKEND  //CONTENT_LENGTH;
	CHKDSK(p->ContentType,__LINE__) CPRINT("ContentType",CCSHOW(p->ContentType));    CHKEND //CONTENT_TYPE;
	CHKDSK(p->Charset,__LINE__) CPRINT("Charset",CCSHOW(p->Charset)); CHKEND
	
	CHKDSK(p->DefaultContentType,__LINE__) CPRINT("DefaultContentType",CCSHOW(p->DefaultContentType)); CHKEND //CONTENT_TYPE;
	CHKDSK(p->DefaultCharset,__LINE__) CPRINT("DefaultCharset",CCSHOW(p->DefaultCharset)); CHKEND
	
    CHKDSK(p->AuthType, __LINE__) CPRINT("AuthType",CCSHOW(p->AuthType));      CHKEND  //AUTH_TYPE;
	CHKDSK(p->EntityPath, __LINE__) CPRINT("EntityPath",CCSHOW(p->EntityPath));   CHKEND   //ENTITY_PATH;        20
	CHKDSK(p->RemoteUser, __LINE__) CPRINT("RemoteUser",CCSHOW(p->RemoteUser));   CHKEND   //REMOTE_USER;
	CHKDSK(p->ServerHost, __LINE__) CPRINT("ServerHost",CCSHOW(p->ServerHost));    CHKEND  //SERVER_HOST
	CHKDSK(p->HTTPHostName, __LINE__) CPRINT("HTTPHostName",CCSHOW(p->HTTPHostName));  CHKEND      // HTTP_HOSTNAME
	CHKDSK(p->HTTPCookie, __LINE__) CPRINT("HTTPCookie",CCSHOW(p->HTTPCookie));     CHKEND //HTTP_COOKIE;
	CHKDSK(p->HTTPUserAgent, __LINE__) CPRINT("HTTPUserAgent",CCSHOW(p->HTTPUserAgent));  CHKEND //HTTP_USER_AGENT;
	CHKDSK(p->HTTPWebBrowser, __LINE__) CPRINT("HTTPWebBrowser",CCSHOW(p->HTTPWebBrowser)); CHKEND //HTTP_WEBBROWSER ; DEFINE BY Lexne
	CHKDSK(p->HTTPReferer, __LINE__) CPRINT("HTTPReferer",CCSHOW(p->HTTPReferer));     CHKEND//HTTP_REFERER;
	CHKDSK(p->HTTPAccept, __LINE__) CPRINT("HTTPAccept",CCSHOW(p->HTTPAccept));     CHKEND //HTTP_ACCEPT;
	CHKDSK(p->HTTPConnection, __LINE__) CPRINT("HTTPConnection",CCSHOW(p->HTTPConnection));  CHKEND // HTTP_CONNECTION
	CHKDSK(p->HTTPAccept_language, __LINE__) CPRINT("HTTPAccept_language",CCSHOW(p->HTTPAccept_language)); CHKEND //HTTP_ACCEPT_LANGUAGE;  30
	CHKDSK(p->HTTPAccept_charset, __LINE__) CPRINT("HTTPAccept_charset",CCSHOW(p->HTTPAccept_charset));  CHKEND//HTTP_ACCEPT_CHARSET;
	CHKDSK(p->HTTPAccept_encoding, __LINE__) CPRINT("HTTPAccept_encoding",CCSHOW(p->HTTPAccept_encoding)); CHKEND //HTTP_ACCEPT_ENCODING;
	
	CHKDSK(p->HTTPContentType, __LINE__) CPRINT("HTTPContentType",CCSHOW(p->HTTPContentType)); CHKEND //HTTP_ACCEPT_CHARSET;
	CHKDSK(p->KeepAlive, __LINE__) CPRINT("KeepAlive",CCSHOW(p->KeepAlive)); CHKEND//HTTP_ACCEPT_ENCODING;
	
	//PHP_AUTH_USER
	//PHP_AUTH_PW
	//AUTH_TYPE
	
	CHKDSK(p->HTTPPragma, __LINE__) CPRINT("HTTPPragma",CCSHOW(p->HTTPPragma)); CHKEND
	CHKDSK(p->HTTPCacheControl,__LINE__) CPRINT("HTTPCacheControl",CCSHOW(p->HTTPCacheControl)); CHKEND
	
	CHKDSK(p->RequestTimes,__LINE__) CPRINT("RequestTimes",CCSHOW(p->RequestTimes)); CHKEND
    
    CHKDSK(p->FileLastName,__LINE__) CPRINT("FileLastName",CCSHOW(p->FileLastName)); CHKEND
    CHKDSK(p->FileIndexName,__LINE__) CPRINT("FileIndexName",CCSHOW(p->FileIndexName)); CHKEND
    
    //printf("----------------------------------------------------------------------\n");
    
    }while(0);
     
    *s = p;
    
    return 0;
}
