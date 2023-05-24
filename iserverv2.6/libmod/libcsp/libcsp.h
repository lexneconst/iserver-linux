#ifndef _CSP_SCRIPT_H_
#define _CSP_SCRIPT_H_


#include <libcspx.h>
#include <libarx.h>

#include "sha2.h"


uint32_t      XSPAPI xcsp_startup(xcsp_class_function *module, const char *file);
uint32_t      XSPAPI xcsp_cleanup(xcsp_class_function *module);
uint32_t      XSPAPI xcsp_analyze(xcsp_class_function *module, const char *src);
uint32_t      XSPAPI xcsp_syntex(xcsp_class_function *module, char **outstr );
uint32_t      XSPAPI xcsp_length(xcsp_class_function *module, uint32_t *length);
uint32_t      XSPAPI xcsp_read(xcsp_class_function *module,  char *buffer, uint32_t length);
uint32_t      XSPAPI xcsp_readline(xcsp_class_function *module, const char *dst, char *src);
uint32_t      XSPAPI xcsp_execute(xcsp_class_function *module, sapi_header **header, sapi_buffer **buffer );

uint32_t      XSPAPI xcsp_createheader(sapi_header **header, zrequest_externs_t *request);
uint32_t      XSPAPI xcsp_addheader(sapi_header **header,const char *str);

#ifndef MYSQL_MODULE
#define MYSQL_MODULE  1
#endif

typedef struct _xspapi_module
{
	int fd;
	uint32_t    line;
	uint32_t    length;
	//struct _xspapi_stream *capi;
	char        *file;
	
	uint32_t     cerrno;
	
	zrequest_externs_t  *request;
}xspapi_module;
uint32_t xspapi_module_startup(xspapi_module **ext, zrequest_externs_t *request);
uint32_t xspapi_module_cleanup(xspapi_module **ext);
uint32_t xspapi_module_read(xspapi_module **ext, char **buffer, uint32_t *length);
uint32_t xspapi_module_append(xspapi_module **ext, const char *str, uint32_t len);
uint32_t xspapi_module_error(xspapi_module **ext, const char *str);
uint32_t xspapi_module_response(xspapi_module **ext, const char *str);
#define XSPERROR(x,s)   xspapi_module_error(x, s)
#define XSPAPPEND(x,s,l)  xspapi_module_append(x, s, l)
#define XSPRESPONSE(x,s)  xspapi_module_response(x, s)

int32_t XSPAPI xsp_print( xspapi_module **ext, const char *var, char **out_str );
int32_t XSPAPI xsp_echo(xspapi_module **ext, const char *name, char **out_str);

int32_t XSPAPI xsp_webapi(xspapi_module **ext, const char *name, char **out_str);
int32_t XSPAPI xsp_cache(xspapi_module **ext, const char *name, char **out_str);


int32_t XSPAPI isql_connect(xspapi_module **ext, const char *name, char **result);
int32_t XSPAPI isql_create(xspapi_module **ext, const char *name, char**result);
int32_t XSPAPI isql_remove(xspapi_module **ext, const char *name,char **result);
int32_t XSPAPI isql_close(xspapi_module **ext, const char *name, char **result);
int32_t XSPAPI isql_result(xspapi_module **ext, const char *name, char **result);
int32_t XSPAPI isql_insert(xspapi_module **ext, const char *name, char **result);
int32_t XSPAPI isql_read(xspapi_module **ext, const char *name, char **result);
int32_t XSPAPI isql_write(xspapi_module **ext, const char *name,char  **result);
int32_t XSPAPI isql_query(xspapi_module **ext, const char *name, char **result);
int32_t XSPAPI isql_fetch(xspapi_module **ext, const char *name, char **result);

extern sapi_module wsapi_module[256];

#endif /* _DLL_H_ */
