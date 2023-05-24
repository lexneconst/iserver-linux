
#include "libcsp.h"

int32_t XSPAPI xsp_print(xspapi_module **ext, const char *name, char **result )
{
	//printf("%s= %s \n", __FUNCTION__, name);
	uint32_t  i=0;
	//char *str = (char *) *result;
	char *ptr = (char *) name;
	xspapi_module  *mod = (xspapi_module*) *ext;
	zrequest_externs_t *req=NULL;
	
	//zrequest_externs_t  *req = (zrequest_externs_t*) ext->request;
	
do{
	if(mod ==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	//printf("DATA_0(%s) \n", ptr);
	for(i=0;i<=strlen(ptr);i++){
		if(*ptr == '"') {
		    ptr++;
			break;	
		}else{
		   ptr++;
	    }
	}
	//printf("DATA_1(%s) \n", ptr);
	for(i=strlen(ptr);i>0;i--){
		if(ptr[i] == '"'){
		    ptr[i] = '\0';
		    break;	
		}
		ptr[i] ='\0';
	}
	if(ptr==NULL){
		break;
	}
	//printf("DATA_2(%s) \n", ptr);
	#ifdef DEBUG_H
	printf("REQ (%x) \n", req);
	#endif
	
	XSPAPPEND(&mod, ptr, strlen(ptr));
	//str = (char *) xmalloc( strlen(ptr) +2 );
	//if(str!=NULL){
	//	strcpy(str, ptr);
	//}
	
}while(0);
	
	*result = (char *) NULL;
	
	*ext = (xspapi_module*) mod;
	
	return 0;
}

int32_t XSPAPI xsp_echo(xspapi_module **ext, const char *name, char **result)
{
	//printf("%s= %s \n", __FUNCTION__, name);
	uint32_t  i=0;
	//char *str = (char *) *result;
	char *ptr = (char *) name;
	xspapi_module  *mod = (xspapi_module*) *ext;
	zrequest_externs_t *req=NULL;
	
	//zrequest_externs_t  *req = (zrequest_externs_t*) ext->request;
	
do{
	if(mod ==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	//printf("DATA_0(%s) \n", ptr);
	for(i=0;i<=strlen(ptr);i++){
		if(*ptr == '"') {
		    ptr++;
			break;	
		}else{
		   ptr++;
	    }
	}
	//printf("DATA_1(%s) \n", ptr);
	for(i=strlen(ptr);i>0;i--){
		if(ptr[i] == '"'){
		    ptr[i] = '\0';
		    break;	
		}
		ptr[i] ='\0';
	}
	if(ptr==NULL){
		break;
	}
	//printf("DATA_2(%s) \n", ptr);
	#ifdef DEBUG_H
	printf("REQ (%x) \n", req);
	#endif
	
	XSPAPPEND(&mod, ptr, strlen(ptr));
	//str = (char *) xmalloc( strlen(ptr) +2 );
	//if(str!=NULL){
	//	strcpy(str, ptr);
	//}
	
}while(0);
	
	*result = (char *) NULL;
	
	*ext = (xspapi_module*) mod;
	
	return 0;	
}