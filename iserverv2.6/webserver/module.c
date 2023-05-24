
#include "iserver.h"

uint32_t cstartup(iserver_config *s)
{
         uint32_t  result =0;
         cserver_load(&s);
         
        //printf("> %s \n", __FUNCTION__);
         do{
           module_stack = (zmodule_stack_t*)emalloc(sizeof(zmodule_stack_t));
            if(module_stack==NULL){
                fatal("allocate memory", __FILE__,__FUNCTION__,__LINE__);
                break;
            }
            result = 1;
        }while(0);
        
        return result;
}
uint32_t ccleanup(iserver_config *s)
{
        // printf("> %s \n", __FUNCTION__);
        CLEAN(module_stack);
         
         
}
uint32_t cbuild(iserver_config *s)
{
        //printf("> %s \n", __FUNCTION__);
        struct sockaddr_in  sa;
        struct hostent     *he=NULL;
        char host[MAX_PATH];
        int yes = 1;
        uint32_t     length = 0;
        uint32_t     ret = 1;
        
        do{ 
           
           #ifndef _INFO_ 
           _conf_infow(server);
           #endif
           
           
          s->sfd = socket(AF_INET, SOCK_STREAM, 0);
          if(s->sfd == INVALID_SOCKET){
                fatal("invalid socket ", __FILE__, __FUNCTION__, __LINE__);
                ret  = 0;
                break;   
          } 
          memset(&sa, 0, sizeof(struct sockaddr_in));
          sa.sin_family = AF_INET;
          sa.sin_port = htons( atoi(CCSHOW(server->ServerPort))  );
          if(strncmp(CCSHOW(server->ServerAddr), "{$DEF}", 6)==0||
            strncmp(CCSHOW(server->ServerAddr), "${DEF}", 6)==0){
             sa.sin_addr.s_addr = INADDR_ANY;
          }else{
             sa.sin_addr.s_addr = inet_addr(CCSHOW(server->ServerAddr));
          }
         printf("Server: [%s][%s]\n", CCSHOW(server->ServerAddr),CCSHOW(server->ServerPort));
         yes = 1;
         if(setsockopt(s->sfd, SOL_SOCKET, SO_REUSEADDR, (char *) &yes, sizeof(int)) == SOCKET_ERROR){
            fatal("set socket option addr", __FILE__, __FUNCTION__, __LINE__);
         }
         yes = 1;
         if(setsockopt(s->sfd, SOL_SOCKET, SO_REUSEPORT, (char *) &yes, sizeof(int)) == SOCKET_ERROR){
            fatal("set socket option port", __FILE__, __FUNCTION__, __LINE__);
         }

         if(bind(s->sfd, (struct sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR){
   	         fatal(" @bind to socket ..", __FILE__, __FUNCTION__, __LINE__);
             sa.sin_addr.s_addr = INADDR_ANY;
   	         if(bind(s->sfd, (struct sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR){
   	 	         fatal(" #bind to socket ..", __FILE__, __FUNCTION__, __LINE__);
                 gethostname(host, sizeof(host));
   	 	         he = gethostbyname(host);
   	 	         if(he != NULL){
                     sa.sin_addr = *(struct in_addr *) he->h_addr;   	     
   	                 if(bind(s->sfd, (struct sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR){
	                   fatal(" $bind to socket ..", __FILE__, __FUNCTION__, __LINE__);
	                    ret = 0;
   	                    break;
		             } 
	    	    }else{
			       fatal(" bind to socket .", __FILE__, __FUNCTION__, __LINE__);
			        break;
	    	    }	
	         }
          }
          listen(s->sfd, atoi(CCSHOW(server->Connection)));
          
          
           if(bio_sign){
               
               
               do{
               length = strlen(s->argv)+ strlen(CCSHOW(server->SSLCert));
               
               if(s->SSLCert!=NULL){
                   fatal("memory new allocate ",__FILE__,__FUNCTION__,__LINE__);
               }
               s->SSLCert = (char *) emalloc( length+8 );
               if(s->SSLCert == NULL){
                   fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
                   break;
               }
               length = strlen(s->argv)+ strlen(CCSHOW(server->SSLKey));
               
               if(s->SSLKey!=NULL){
                   fatal("memory new allocate",__FILE__,__FUNCTION__,__LINE__);
               }
               s->SSLKey = (char *) emalloc( length+8 );
               if(s->SSLKey == NULL){
                   fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
                   break;
               }
               length = strlen(s->argv)+ strlen(CCSHOW(server->SSLChain));
               
               if(s->SSLChain!=NULL){
                   fatal("memory new allocate", __FILE__ ,__FUNCTION__, __LINE__);
               }
               s->SSLChain = (char *) emalloc( length+8 );
               if(s->SSLChain == NULL){
                   fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
                   break;
               }
               
               length = strlen(s->argv)+ strlen(CCSHOW(server->SSLFile));
               
               if(s->SSLFile!=NULL){
                   fatal("memory new allocate", __FILE__ ,__FUNCTION__, __LINE__);
               }
               s->SSLFile = (char *) emalloc( length+8 );
               if(s->SSLFile == NULL){
                   fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
                   break;
               }
               
               length = strlen(s->argv)+ strlen(CCSHOW(server->SSLPath));
               
               if(s->SSLPath!=NULL){
                   fatal("memory new allocate", __FILE__ ,__FUNCTION__, __LINE__);
               }
               s->SSLPath = (char *) emalloc( length+8 );
               if(s->SSLPath == NULL){
                   fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
                   break;
               }
               
               
               strcpy(s->SSLCert, s->argv);
               strcat(s->SSLCert, "/");
               strcat(s->SSLCert, CCSHOW(server->SSLCert));

               strcpy(s->SSLKey, s->argv);
               strcat(s->SSLKey, "/");
               strcat(s->SSLKey, CCSHOW(server->SSLKey));
               
               strcpy(s->SSLChain, s->argv);
               strcat(s->SSLChain, "/");
               strcat(s->SSLChain, CCSHOW(server->SSLChain));               
               //printf("> %s \n", s->argv);
               /*printf("> %s \n", s->SSLCert);
               printf("> %s \n", s->SSLKey);
               printf("> %s \n", s->SSLChain);
               */
               strcpy(s->SSLFile, s->argv);
               strcat(s->SSLFile, "\\");
               strcat(s->SSLFile, CCSHOW(server->SSLFile));   
               
               strcpy(s->SSLPath, s->argv);
               strcat(s->SSLPath, "\\");
               strcat(s->SSLPath, CCSHOW(server->SSLPath));   
               
               
               SSL_Openssl_startup(&s, s->SSLCert, s->SSLKey, 
                               s->SSLChain, s->SSLFile, s->SSLPath );
               
               }while(0);
               
           }
           
           
        }while(0);
        
        return ret;
           
}
        
uint32_t cmodule(iserver_module *b, iserver_config *s)
{
         //printf("> %s \n", __FUNCTION__);   
         struct sockaddr_in ca,addr;
         int  sock_len;
         unsigned   ret;
         char       ipaddr[256],remoteaddr[256];
         
     do{    
         if(s->sfd == INVALID_SOCKET){
            fatal("invalid accept ", __FILE__, __FUNCTION__, __LINE__);
            break;
         }
         while(1){
             sock_len = sizeof(ca);
   	         s->_s = accept(s->sfd, (struct sockaddr*)&ca, &sock_len);
   	         if(s->_s == INVALID_SOCKET){
   	   	        fatal("socket accept ", __FILE__, __FUNCTION__, __LINE__);
   	   	        closesocket(s->_s);
   	   	   
   	          }else{
                 //printf("CCCC\n");
                 //getpeername
                 
                 //getsockname(s->_s,  (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
                 //printf("Server socket's ip : %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
                 cipaddr(s, ipaddr, remoteaddr);
                 
                 #ifdef DEBUG_H
                 printf("Server socket's ip : %s \n", remoteaddr);
                 #endif
                 
                 if(bio_sign){
                    //printf("* bios accept\n");
                    s->ssl=SSL_Openssl_accept(s, s->_s);
                    //_beginthreadex(NULL,0, threadproc, cserv, 0, &ret);
                    if(s->ssl == NULL){
                        fatal("accept ssl server", __FILE__, __FUNCTION__, __LINE__);
                    }else{
                        s->cipher = SSL_Getcipher(s->ssl);
                        if(s->cipher == NULL){
                            fatal("cipher ssl server", __FILE__, __FUNCTION__, __LINE__);
                            
                        }else{
                        	#ifdef DEBUG_H
                            printf("SH> Cipher [%s] \n", s->cipher);
                            #endif
                            onserver(b,s);
                        }
                    }
                 }else{
                    onserver(b,s);
                 }
                 
              }
         }
    }while(0);                            
    
    if(s->sfd!= INVALID_SOCKET)
        closesocket(s->sfd);
    
    _conf_clean(&server);
}
uint32_t cread(iserver_config *s,char *buffer,uint32_t length)
{
    //printf("> %s \n", __FUNCTION__);
  do{
    if(s == NULL){
       fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    if(bio_sign){ 
       //printf("* ssl read \n");
       if(s->ssl == NULL){
          fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
          break;
       }else{
          return SSL_Recv(s->ssl, buffer, length);
       }
    }  
    #define ZSEOL      "\r\n"
    #define ZSEOL_SIZE  2
    
    char        *ptr=NULL;
    int          eol_matched = 0;
    unsigned int count=0;
    
    ptr= buffer;
    while(recv(s->_s, ptr, 1, 0) == 1){
       if(count>= length){
           fatal("buffer limit", __FILE__, __FUNCTION__, __LINE__);
           break;
       }
       if(*ptr== ZSEOL[eol_matched]){
          eol_matched++;
          
          if(eol_matched == ZSEOL_SIZE){
             *(ptr+1-ZSEOL_SIZE) = '\0';
             
             return strlen(buffer);
          }
          
       }else{
          eol_matched=0;
       }
       ptr++;
       count+=1;
    }
  
  }while(0);
  
    return 0;
    
}
uint32_t cwrite(iserver_config *s,char *buffer, uint32_t length)
{
    //printf("> %s \n", __FUNCTION__);
    //printf("W[%s]\n",buffer);
  do{        
    if(s == NULL){
       fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
       break;
    }         
    if(bio_sign){ 
        if(s->ssl==NULL){
            fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        
        return SSL_Write(s->ssl, buffer, length);        
    }     
    unsigned int sent_bytes=0, bytes_to_send=0;
    bytes_to_send = length;
    while(bytes_to_send){
       if(buffer==NULL) break;
       if(sent_bytes >= length) break;
       sent_bytes = send(s->_s, (char *)buffer, bytes_to_send,0);
       if(sent_bytes == -1){
          return 0;
       }
       bytes_to_send -= sent_bytes;
       buffer+= sent_bytes;
    }
  }while(0);
  
    return 1;
  
          
}

uint32_t tread(iserver_config *s,char *buffer,uint32_t len)
{
   uint32_t  size=0;
   do{
      if(s==NULL){
         fatal("stack memory failed", __FILE__,__FUNCTION__,__LINE__);
         break;
      }
      size = recv(s->_s, buffer, len, 0);
            
   }while(0);
   return size;
}
uint32_t twrite(iserver_config *s,char *buffer, uint32_t len)
{
   uint32_t  size = 0;
   do{
      if(s==NULL){
         fatal("stack memory failed", __FILE__,__FUNCTION__,__LINE__);
         break;
      }
      
      size = send(s->_s, buffer, len, 0);
      
   }while(0);
   return size;
}


uint32_t cdone(iserver_config *s){
    //printf("> %s \n", __FUNCTION__);
 do{
    if(s == NULL){
       fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    if(bio_sign){
        SSL_Openssl_close(s);
    }
    shutdown(s->_s, SD_SEND );

    #ifdef DEBUG_H
    CLEAN(s->cipher);
    #endif
    
 }while(0);
 
    return 0;
}
uint32_t ctimem(iserver_config *s, uint32_t dwtime)
{
    fd_set fds;
    struct timeval tv;
    FD_ZERO(&fds);
    FD_SET(s->_s,&fds);
    tv.tv_sec = dwtime *10;
    tv.tv_usec = 0;
    //Bugs(1134);
    select(s->_s+1,&fds,NULL,NULL,&tv);
    if(!FD_ISSET(s->_s,&fds)){
        return 1; // 
    } 	        
    return 0;
}
uint32_t cipaddr(iserver_config *s, _MGC_STRING serveraddr,_MGC_STRING remoteaddr)
{
    struct sockaddr_in ca;
	int sock_len = sizeof(ca);
	char       buffer[MAX_PATH];
  do{
    if(s==NULL){ 
        fatal("stack memory",__FILE__,__FUNCTION__,__LINE__);
        break;
    }
    if(remoteaddr==NULL || serveraddr==NULL){
        break;
    }
	if(getpeername(s->_s, (struct sockaddr*)&ca, &sock_len)!=-1){
	    //buffer = (char *)VirtualAlloc(NULL, 128, MEM_COMMIT, PAGE_READWRITE);
		//if(NULL!= buffer){
	      sprintf(buffer, "%s:%d\0", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));
	      //return 1;
	      CCNEW(remoteaddr, buffer);
	    //}	
	}
	if(getsockname(s->_s, (struct sockaddr*)&ca, &sock_len)!=-1){
	    //buffer = (char *)VirtualAlloc(NULL, 128, MEM_COMMIT, PAGE_READWRITE);
		//if(NULL!= buffer){
	      sprintf(buffer, "%s:%d\0", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));
	      CCNEW(serveraddr, buffer);
	      //return 1;
	    //}	
	}
   }while(0);
   
   return 0;
}
