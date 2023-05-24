
#include "libcsp.h"

void *csp_module_startup( sapi_server *req, zrequest_externs_t *ext )
{
	uint32_t   length  =0;
	
do{
	if(req==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	req->s = 0;
	
	req->startup =  xcsp_startup;
	req->analyze =  xcsp_analyze;
	req->syntex  =  xcsp_syntex;
	req->readline=  xcsp_readline;
	req->read    =  xcsp_read;
	req->length  =  xcsp_length;
	req->cleanup =  xcsp_cleanup;
	req->execute =  xcsp_execute;
	
	req->header = NULL;
	req->buffer = NULL;
	
	req->next = NULL;
	
	req->temp = NULL;
	req->module = NULL;
	
	req->module = (xcsp_class_function *) xmalloc( sizeof(xcsp_class_function));
	if(req->module==NULL){
		fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
    req->module->buffer = NULL;
    req->module->length = 0;
    req->module->request = ext;
    
    if(req->startup!=NULL){
    	req->startup(req->module, CCSHOW(ext->PathTranslated));
	}
    
	if(req->read !=NULL && req->length!=NULL){
	    req->length(req->module, &length);	
		
		if(length <= 0)
		{
		    fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
			break;		
		}
	    req->temp  = (sapi_buffer *) xmalloc( sizeof(sapi_buffer));
	    if(req->temp == NULL){
		    fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);		
		    break;
	    }
	    
	    req->temp->length = length;
	    
		req->temp->buffer = (char *) xmalloc( length + 2);
		if(req->temp->buffer==NULL){
			fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);		
			break;
		}
		
		req->read(req->module, req->temp->buffer, req->temp->length );
		
		if(req->analyze!=NULL){
			
			req->analyze(req->module, req->temp->buffer);
			
		}
		
	}
	
}while(0);
    
    if(req!=NULL){
    	
    	if(req->temp!=NULL){
    		if(req->temp->buffer!=NULL)
    		{
    			XCLEAN(req->temp->buffer);
    			req->temp->length = 0;
			}
    		XCLEAN(req->temp);
		}
    	
	}

	return NULL;
}
void *csp_module_execute( sapi_server *req)
{
	req->header =NULL;
	req->buffer =NULL;
do{
	if(req==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	if(req->syntex!=NULL && req->execute!=NULL)
	{
		if(req->syntex(req->module, &req->buffer->buffer)){
			
			break;
		}
		
		req->execute(req->module, &req->header, &req->buffer);
	}
	
}while(0);
   
    //printf("%s\n", req->buffer->buffer);
   
    if(req->header==NULL){
    	fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
	}
	if(req->buffer==NULL){
		fatal("stack memory", __FILE__, __FUNCTION__, __LINE__);
	}

	return NULL;
}
void *csp_module_cleanup( sapi_server *req)
{
do{
	 if(req==NULL){
	 	
	 	break;
	 }
	 
	 if(req->header!=NULL)
	 {
	 	if(req->header->data!=NULL){
		   if(req->header->data->buffer!=NULL){
		   	   XCLEAN(req->header->data->buffer);
		   	   req->header->data->length = 0;
		   }
	 	   XCLEAN(req->header->data);
	    }
	 }
	 
	 if(req->buffer!=NULL){
	 	if(req->buffer->buffer!=NULL){
	 	   XCLEAN(req->buffer->buffer);	
	 	   req->buffer->length = 0;
		}
	 	XCLEAN(req->buffer);
	 }
	 
	 if(req->temp!=NULL){
	 	if(req->temp->buffer!=NULL){
	 		XCLEAN(req->temp->buffer);
	 		req->temp->length = 0;
		 }
	 	XCLEAN(req->temp);
	 }
	 
	 if(req->cleanup!=NULL)
	 {
	 	req->cleanup(req->module);
	 }
	
	 if(req->module!=NULL){
	 	XCLEAN(req->module);
	 }
	 
}while(0);
	return NULL;
}



sapi_module wsapi_module[256] ={
   {"print", XSP_VERSION, xsp_print, XFLAGS},
   {"echo", XSP_VERSION, xsp_echo, XFLAGS},
   {"webapi", XSP_VERSION, xsp_webapi, XFLAGS},
   {"cache", XSP_VERSION, xsp_cache, XFLAGS},
   #ifdef MYSQL_MODULE
   {"isql_connect", ISQL_VERSION, isql_connect, XFLAGS},
   {"isql_create", ISQL_VERSION, isql_create ,XFLAGS}, 
   {"isql_remove", ISQL_VERSION, isql_remove, XFLAGS},
   {"isql_close", ISQL_VERSION, isql_close, XFLAGS},
   {"isql_result", ISQL_VERSION, isql_result, XFLAGS},
   {"isql_inert", ISQL_VERSION, isql_insert, XFLAGS},
   {"isql_read", ISQL_VERSION, isql_read, XFLAGS},
   {"isql_write", ISQL_VERSION, isql_write, XFLAGS},
   {"isql_query", ISQL_VERSION, isql_query, XFLAGS},
   {"isql_fetch", ISQL_VERSION, isql_fetch, XFLAGS},
   #endif
   {NULL,NULL,NULL,NULL},
   NULL,
   NULL,
   NULL
}; 