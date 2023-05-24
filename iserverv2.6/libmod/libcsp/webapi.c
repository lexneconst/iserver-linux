
#include "libcsp.h"

int32_t XSPAPI xsp_webapi(xspapi_module **ext, const char *name, char **out_str)
{
	xspapi_module  *mod = (xspapi_module*) *ext;
	zrequest_externs_t *req=NULL;
do{
	if(mod==NULL){
		fatal("Segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	req = mod->request;
	if(req==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	printf("QUERY STRING (%s) \n", CCSHOW(req->QueryString ));
	
	XSPRESPONSE(&mod, "200");
}while(0);
    
    *ext = (xspapi_module *) mod;

	return 0;
}

int32_t XSPAPI xsp_cache(xspapi_module **ext, const char *name, char **out_str)
{
	xspapi_module  *mod = (xspapi_module*) *ext;
	zrequest_externs_t *req=NULL;
	//char               *buffer=NULL;
do{
	if(mod==NULL){
		fatal("Segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	req = mod->request;
	if(req==NULL){
		fatal("segment memory ", __FILE__, __FUNCTION__, __LINE__);
		break;
	}
	
	printf("CACHE (%s) \n", CCSHOW(req->UrlCache));
	XSPAPPEND(&mod, CCSHOW(req->UrlCache), strlen(CCSHOW(req->UrlCache)));
	//buffer = (char *) xmalloc( strlen(req->UrlCache) + 5);
//	if(buffer == NULL){
		
	//	break;
	//}
	//strcpy(buffer, req->UrlCache);
	
}while(0);
    //*out_str = (char *) buffer;
    *ext = (xspapi_module *) mod;

	return 0;
}
