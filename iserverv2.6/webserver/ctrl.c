#include <iserver.h>

char*  zmod_request_pageLength(zmodule_stack_t *ptr, const char *serverstatus, const char *servername)
{
    return _new_str("0");
}

void *zmod_csp_module_startup(zmodule_stack_t *ptr, sapi_server *req, zrequest_externs_t *ext )
{
    return 0;
}
 void *zmod_csp_module_execute(zmodule_stack_t *ptr, sapi_server *req)
{
    return 0;
}
void *zmod_csp_module_cleanup(zmodule_stack_t *ptr, sapi_server *req)
{
    return 0;
}
uint32_t zmod_request_module_script(zmodule_stack_t *ptr, zrequest_externs_t *request)
{
    return 0;
}

uint32_t zmod_request_readpage(zmodule_stack_t *ptr, char *str, zrequest_externs_t *request)
{
    return 0;
}

uint32_t zmod_request_dirinit(zmodule_stack_t *ptr)
{
}
uint32_t zmod_request_dirfini(zmodule_stack_t *ptr)
{
}

uint32_t zmod_request_getfrontsize(zmodule_stack_t *ptr, char *path)
{
}
uint32_t zmod_request_getfront(zmodule_stack_t *ptr, char *buffer, uint32_t length, const char *path)
{
}
long zmod_request_dirliststart(zmodule_stack_t *ptr, char *path)
{
}
char* zmod_request_dirlistloop(zmodule_stack_t *ptr, long *hfd,const char *path,  uint32_t *size)
{
}
uint32_t zmod_request_dirlistend(zmodule_stack_t *ptr, long *hfd)
{
}
uint32_t zmod_request_getbacksize(zmodule_stack_t *ptr,
   const char *name,const char *ver, const char *os, const char *addr, char *port)
{
}
uint32_t zmod_request_getback(zmodule_stack_t *ptr, char *buffer, uint32_t length, 
   const char *name,const char *ver, const char *os, const char *addr, char *port)
{
}
