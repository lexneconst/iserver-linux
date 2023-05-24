

#ifndef LIBCSP_H
#define LIBCSP_H

#include <stdio.h>
#include <stdlib.h>
#include <iserverx.h>


DLLIMPORT void *csp_module_startup( sapi_server *req, zrequest_externs_t *ext );
DLLIMPORT void *csp_module_execute( sapi_server *req);
DLLIMPORT void *csp_module_cleanup( sapi_server *req);

#endif

