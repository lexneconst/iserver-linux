
#include "libcsp.h"




uint32_t      XSPAPI xcsp_createheader(sapi_header **req_header, zrequest_externs_t *request)
{
	sapi_header *header = (sapi_header *) *req_header;
	sapi_header *prev=NULL, *next=NULL;
	uint32_t     i=0;
	uint32_t     ebool = 0;
	char         buff[MAX_PATH];
	
do{
    header->count = 0;
	prev = header;
	
	if(prev==NULL){
		
		break;
	}
	if(prev==NULL){
		fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	prev->data = (sapi_buffer *) xmalloc( sizeof(sapi_buffer));
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
		next = ( sapi_header *) xmalloc( sizeof( sapi_header ));
		if(next==NULL){
			fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		next->data = (sapi_buffer *) xmalloc( sizeof(sapi_buffer));
		if(next->data ==NULL){
			fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
		next->next = NULL;
		
		TRY:
		switch(i){
			case 0:
				if(request->RequestTimes!=NULL){
				    sprintf(buff,"Date: %s\r\n", request->RequestTimes);
                    next->data->buffer = _new_str1(buff, 64);
				    next->data->length = strlen(buff);
				    
				    header->count+= 1;
				}else{
					
					i+= i;
					
					goto TRY;
				}
				
			break;
			case 1:
				if(request->ServerName!=NULL){
                    sprintf(buff,"Server: %s\r\n", request->ServerName);
                    next->data->buffer = _new_str1(buff, 64);
				    next->data->length = strlen(buff);
				    
				    header->count+= 1;
                }else{
					
					i+= i;
					
					goto TRY;
				}
			break;
			case 2:
				
				strcpy(buff,"X-Powered-By:: CSP 1.0 \r\n");
				next->data->buffer = _new_str1(buff, 64);
				next->data->length = strlen(buff);
				
				header->count+= 1;	
					
			break;
			case 3:
				strcpy(buff,"Accept-Ranges: bytes\r\n");
				next->data->buffer = _new_str1(buff, 64);
				next->data->length = strlen(buff);
				
				header->count+= 1;
			break;
			case 4:
				strcpy(buff,"Connection: close\r\n");
				next->data->buffer = _new_str1(buff, 64);
				next->data->length = strlen(buff);
				
				header->count+= 1;
				
				ebool = 1;
			break;
			/*case 4:
				
				if(request->ContentType!=NULL){
                   sprintf(buff,"Content-Type: %s;\r\n", request->ContentType);
                   next->data->buffer = _new_str1(buff, 64);
			  	   next->data->length = strlen(buff);
				
				   header->count+= 1;
				   
				   
                }else{
					
					i+= i;
				}
			break;
			*/
		}
		
		
		prev->next = next;
		prev = next;
	}	
}while(0);
    
    header->number = header->saveid = header->count;
    
    *req_header = (sapi_header *) header;

	return 0;
}
uint32_t      XSPAPI xcsp_addheader(sapi_header **req_header, const char *str)
{
	sapi_header *header = (sapi_header *) *req_header;
	sapi_header *prev=NULL, *next=NULL;
	uint32_t     i=0;
	uint32_t     count = 0;
	char         buff[MAX_PATH];
do{
	count = header->count;
	prev = header;
	for(i=0;i<=count;i++){
		if(prev==NULL){
			
			break;
		}
		next = prev->next;
		
	    if(next == NULL){
	    	next = (sapi_header *) xmalloc (sizeof(sapi_header));
	    	if(next == NULL){
	    		fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
	    		break;
			}
	    	next->data = (sapi_buffer *) xmalloc( sizeof(sapi_buffer));
		    if(next->data ==NULL){
			    fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
			    break;
		    }
		    next->next = NULL;
		    
			next->data->buffer = _new_str1(str, 64);
			next->data->length = strlen(str);
			
		    next->data->buffer[next->data->length] = '\0';
		    
	    	count+= 1;
	    	
	    	prev->next = next;
			break;
		}
		
		prev = next;  
    }
    
    header->count = header->saveid = header->number = count;
}while(0);

   *req_header = (sapi_header *) header;
   
	return 0;
}