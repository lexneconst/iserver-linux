
#include "libcsp.h"


uint32_t tcstrncmp(const char *str, const char *val, uint32_t len){
	uint32_t i=0;
	for(i=0;i<strlen(val);i++){
	    //printf("%d \n", memcmp(str, val, 2));
	    if(memcmp(str,val, 2) ==0) return 1;
		i+=len;	
	}
	return 0;
}

uint32_t tcmemcmp(const char *str, const char val, uint32_t len){
	if(*str == val){
		return 1;
	}
	return 0;
}

uint32_t      XSPAPI xcsp_startup(xcsp_class_function *module, const char *file)
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	
do{
	if(module==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	module->buffer=NULL;
	module->file = (char *) xmalloc( strlen(file)+2);
	if(module->file==NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	strcpy(module->file, file);
	module->file[strlen(file)] ='\0';
	
}while(0);
	return 0;
}
uint32_t      XSPAPI xcsp_cleanup(xcsp_class_function *module)
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	
do{
	if(module==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	XCLEAN(module->buffer);
	XCLEAN(module->file);
	
	#ifdef DEBUG_H
	printf("---------------------------------------------\n");
	#endif
	
}while(0);
	return 0;
}
uint32_t      XSPAPI xcsp_analyze(xcsp_class_function *module,  const char *src)
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	
	uint32_t  count=0,num=0;
	uint32_t  i=0;
	char     *ptr =NULL;
do{
	if(module == NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	//XCLEAN(module->buffer);
	module->length = strlen(src);
	module->buffer = (char *) xmalloc( module->length+2);
	if(module->buffer==NULL){
		fatal("segment memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	memset(module->buffer, 0, strlen(src));
	
	ptr =(char*)src;
	//printf("-buffer(%s)\n", ptr);
	count = 0;
	while(*ptr!=0){
		if(count>= strlen(src)){
			
			break;
		}
		if(*ptr == '\r' || *ptr == '\t' || *ptr == ' '){
		   
	    }else{
		   module->buffer[num] = ptr[count];
		   //*module->buffer++ = *ptr;
		   ++num;
	    }
		count++;
	}

	i=count;
	do
	{
	    if(module->buffer[i] == '\n'){
	    	module->buffer[num] = '\0';
	        module->length = num;
	
	    	break;
		} else{
			
			num--;
		}
		i--;
	}while(i>0);
	//printf("+buffer(%s)\n", module->buffer);
	
	
}while(0);	
	return 0;
}
uint32_t      XSPAPI xcsp_syntex(xcsp_class_function *module,  char **outstr )
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	return 0;
}
uint32_t      XSPAPI xcsp_length(xcsp_class_function *module, uint32_t *length)
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	
	struct stat ts;
    
    *length = 0;
do{
   if(module==NULL){
   	   fatal("segment memory", __FILE__, __FUNCTION__, __LINE__);
   	   break;
   }
   
   if(access(module->file, 0 ) != 0){
   	   fatal("access file", __FILE__, __FUNCTION__, __LINE__);
   	   break;
   }
   //memset(&ts, 0, sizeof(ts));
   if(stat(module->file, &ts)==-1){ 
      fatal("open length", __FILE__,__FUNCTION__,__LINE__);
      return 0;
   }
   
   *length =ts.st_size;
}while(0);

	return 0;
}
uint32_t      XSPAPI xcsp_read(xcsp_class_function *module, char *buffer, uint32_t length)
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	
	int fd = -1;
	uint32_t  i=0;
	uint32_t  size=0;
	
do{
	if(module==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	module->length = length;
	//module->buffer = (char *) xmalloc( length + 2 );
	
	//if(module->buffer==NULL){
	//	fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
	//	break;
	//}
	
	#ifdef DEBUG_H
	printf("path: (%s)\n", module->file );
	#endif
	
	fd = open(module->file, O_RDONLY, 0);
	if(fd!=-1){
		
		lseek(fd, 0, SEEK_SET);
		if((size= read(fd, buffer, length)) == -1)
		{
			fatal("read file", __FILE__, __FUNCTION__, __LINE__);
		}
		buffer[size] ='\0';
		
		close(fd);
	}else{
		fatal("open file", __FILE__, __FUNCTION__, __LINE__);
	}
	
	for(i=0;i<length;i++){
		
		if(buffer[i] == 0) {
		   buffer[i] ='\0';
		   break;
		}
	}
	
	#ifdef DEBUG_H
	printf("buffer(%s) \n", buffer);
	#endif
	
}while(0);
	return 0;
}
uint32_t      XSPAPI xcsp_readline(xcsp_class_function *module, const char *dst, char *src)
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	
	return 0;
}
uint32_t      XSPAPI xcsp_execute(xcsp_class_function *module,  sapi_header **req_header, sapi_buffer **req_buffer )
{
	#ifdef DEBUG_H
	printf("%s,%d == %x \n", __FUNCTION__, __LINE__, module);
	#endif
	
	sapi_header  *header= (sapi_header *) *req_header;
	sapi_buffer  *buffer= (sapi_buffer *) *req_buffer;
	uint32_t      i=0,j=0, c=0;
	uint32_t      cstart=0;
	char          buff[MAX_PATH];
	char          *result=NULL;
	uint32_t      line=0;
	xspapi_module    *req_ext=NULL;
	
do{
	
    if(module==NULL){
    	fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}	
	
    header = (sapi_header*) xmalloc( sizeof( sapi_header));
    if(header == NULL){
    	fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
    	break;
	}
	buffer = (sapi_buffer *) xmalloc( sizeof(sapi_buffer));
	if(buffer == NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	xcsp_createheader(&header, module->request);
	
	if(module->length <= 0){
		fatal("size of buffer", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	xcsp_addheader(&header, "Content-Type: text/html;\r\n");
	
	buffer->buffer = NULL;
	buffer->length = 0;
	cstart=0;
	
	//printf("loading check buffer (%d,%d)\n", i, module->length);
	//printf("module buffer (%s) \n", module->buffer);
	xspapi_module_startup(&req_ext, module->request);
	
	if(req_ext!=NULL){
		req_ext->fd = 0;
		req_ext->line = 0;
		req_ext->length = 0;
		req_ext->cerrno = 1;
	}
	
	for(i=0;i<module->length;i+=1){
		
		if(i>= module->length){
		   printf("module length final (%d=%d) \n", i, module->length);
		   line = 0;
		   break;
		} 
		
		if(req_ext!=NULL && !req_ext->cerrno)
		{
			
			break;
		}
		if(tcmemcmp(module->buffer+i,'\n', 1) > 0){
			if(req_ext!=NULL) req_ext->line = line;
			line++;
		}
		//printf("check i (%d) (%d) \n", i, strncmp(module->buffer+i, "<#",2));	
		if(tcstrncmp(module->buffer+i,"<#", 2)>0){
			
			//printf("[%s]\n", buffer->buffer);
		    //csp_start = 1;
			//printf("CMP_START: %d \n", __LINE__);
			//buffer->length+= 2;
			cstart = 1;
			continue;
	    }else{
	        //printf("data any (%s) (%d) (%d)\n", __FUNCTION__, __LINE__, cstart);
	    	if(cstart){
	    	   //printf("CMP_FUNC: %d \n", __LINE__);
	    	   
			   c=0;
			   while(&(wsapi_module[c])!=NULL && wsapi_module[c].name_func != NULL && req_ext !=NULL && req_ext->cerrno){
			   	   //printf("(%d)::(%s)\n",i, module->buffer+i);
			   	   #ifdef DEBUG_H
			   	   printf("FUNC (%s) \n", wsapi_module[c].name_func);
			   	   #endif
			   	   
			   	   if(strncmp(module->buffer+i, wsapi_module[c].name_func,strlen(wsapi_module[c].name_func) )>=0){
			   	   	   
			   	   	   #ifdef DEBUG_H
					   printf("init (%s) \n", wsapi_module[c].name_func);
			   	   	   #endif
			   	   	   
					   i+= strlen(wsapi_module[c].name_func);
					   sprintf(buff, "%s\0", module->buffer+i);
					   for(j=0;j<strlen(module->buffer+i);j++){
					   	
					   	   if(buff[j] == ';'){
						      buff[j] = '\0';
						      break;
						   }
						   if(buff[j] == '\n'){
						   	   sprintf(buff,  "error: %s::%d stack memory \0", __FILE__, __LINE__);
						   	   break;
						   }
					   }
					   
					   if(tcstrncmp(buff, "error", 5)> 0){
					   	     XSPERROR(&req_ext, buff);
					      
					   }else{
					   	 if(req_ext!=NULL){
					   	    req_ext->fd = 0;
					   	    req_ext->length = 0;
					   	    req_ext->request = module->request;		
					   	 }
					     wsapi_module[c].func_ctrl(&req_ext , buff , &result);
					     if(result!=NULL){
					       //buffer->length += strlen(result);
					       //strncat(buffer->buffer, result, buffer->length);
					      // XSPAPPEND(&req_ext, result, strlen(result));
					       //printf("result (%s) \n", result);
					       XCLEAN(result);
					       
				         }
						 //else{
				         //	sprintf(buff,  "error: %s::%d stack memory \0", __FILE__, __LINE__);
				         //   XSPERROR(&req_ext, buff);
						 //}
				       }
				       
				       
					   i+= strlen(buff);
					   c=0;
					   
					  
				   }
				   //printf("Loop (%d) \n", i);
				  
				   //printf("%d, %x \n", c, &(wsapi_module[c]) );
				   c+=1;
			   }	
	    	   //printf("END\n");
			   if(tcstrncmp(module->buffer+i, "#>", 2) > 0){
	    		    
	                cstart = 0;
	                
	                i++;
	                //printf("END LINE (%d) \n", i);      
	                
			    }else
				if(tcstrncmp(module->buffer+i,"<#", 2) > 0){
				   sprintf(buff,  "error: %s::%d stack memory \0", __FILE__, __LINE__);
				   XSPERROR(&req_ext, buff);
				   
				   //buffer->length += strlen(buff);
				   //strncat(buffer->buffer, buff, buffer->length);
				   //line = 0;
				   break;	
				}
				 
			}else{
		      //printf("data(%s) \n", module->buffer+i );
		      //printf("data: %d \n", i);
		      //
	    	  //strncat(buffer->buffer, module->buffer+i, 1);
	    	  //buffer->length += 1;
	    	  XSPAPPEND(&req_ext, module->buffer+i, 1);
	    	   
	    	  //i+= 1;
	    	  cstart = 0;
	    	  
	        }
		}
	}
	
	//if(line){
    //	 sprintf(buff,  "error: %s::%d stack memory \0", __FILE__, __LINE__);
	//	 XSPERROR(&req_ext, buff);
	//}
	
	xspapi_module_read(&req_ext, &buffer->buffer, &buffer->length);
	
	xspapi_module_cleanup(&req_ext);
    
	//strcpy(buffer->buffer, module->buffer);
	//printf("buffer::%s\n", buffer->buffer);
}while(0);
    
    *req_header = (sapi_header*) header;
    *req_buffer = (sapi_buffer*) buffer;
    
	return 0;
}
