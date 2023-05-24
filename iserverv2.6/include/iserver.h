#ifndef _ISERVER_CONF_H
#define _ISERVER_CONF_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <dlfcn.h> 
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>      /*  timeval */
#include <sys/ioctl.h>     /*  ioctl  */
#include <netdb.h> 
#include <errno.h>

#include "cdef.h"
#include "ctypes.h"

#include <openssl/lhash.h>
#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <openssl/ocsp.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif
#include <openssl/bio.h>

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET  -1
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR    -1
#endif
#ifndef SD_SEND
#define SD_SEND    SHUT_WR
#endif
#ifndef SD_RECEIVE
#define SD_RECEIVE SHUT_RD
#endif
#ifndef SD_BOTH
#define SD_BOTH    SHUT_RDWR
#endif
#ifndef closesocket
#define closesocket(x)  close(x)
#endif
/*#define ISERVER_OS      "CaseniumOS"*/
#define ISERVER_NAME  "IServer"
#define ISERVER_VERSION "1.25"
#define ISERVER_OS     "CaseniumOS"
#define ISERVER_ADMIN  "Casenium"
#define ISERVER_GATEWAY "CCG/1.0"

#define ISERVER_POWERBY  "xcsp 1.0"

#define SERVER_OS       ISERVER_OS
#define SERVER_SOFTWARE ISERVER_NAME
#define SERVER_VERSION  ISERVER_VERSION
#define SERVER_ADMINWH  ISERVER_ADMIN
#define SERVER_GATEWAY  ISERVER_GATEWAY

#define SERVER_POWERBY  ISERVER_POWERBY


typedef struct _cstring_t
{
	char     *buffer;
	uint32_t length;
}cstring_t;

struct config_stack_t
{
    char    *name;
    void    *keys;
};
typedef struct config_stack_t zconfig_stack_t;

#define _MGC_STRING  cstring_t *
#define _MGC_UINT    uint32_t

struct module_stack_t;
struct _sapi_server;

typedef struct _sapi_server sapi_server;
DLLRUN void fatal_fini(void);
DLLRUN void fatal_init(void);
DLLRUN void fatal_clean(void);
DLLRUN int get_fatal(char *str);
DLLRUN void fatal(char *str, const char *file,const char *func, unsigned long line);

DLLRUN char *_newadd_str(const char *str, const char *pad);
DLLRUN char *_new_str(const char *zstr);
DLLRUN char *_new_str1(const char *zstr, uint32_t length);

DLLRUN uint32_t einit(void *s);
DLLRUN uint32_t efini(void *s);
DLLRUN void *emalloc(uint32_t  length);
DLLRUN void *efree(void *ptr);

DLLRUN uint32_t cstring_create(cstring_t** ptr);
DLLRUN uint32_t cstring_clean(cstring_t** ptr);
DLLRUN uint32_t cstring_clone(cstring_t** ptr, cstring_t *str);
DLLRUN uint32_t cstring_check(cstring_t **ptr);
DLLRUN char* cstring_str(cstring_t *ptr);
DLLRUN uint32_t cstring_len(cstring_t *ptr);
DLLRUN uint32_t cstring_newadd(cstring_t **ptr, cstring_t *dst , cstring_t *src);
DLLRUN uint32_t cstring_new(cstring_t **ptr, const char *buf);
DLLRUN uint32_t cstring_newpad(cstring_t **ptr, const char *buf,const char *pad);
DLLRUN uint32_t cstring_renew(cstring_t **ptr, const char *buf);
DLLRUN uint32_t cstring_stat(cstring_t **ptr, const char v);
DLLRUN uint32_t cstring_remove(cstring_t **ptr, uint32_t len);
DLLRUN uint32_t cstring_clear(cstring_t **ptr);

DLLRUN char * getmoduledir(void);

typedef struct _zconfig_server_t
{
    unsigned int           signature;
    unsigned int           oscpserver;
    
    char                  *initroot;    
        
    _MGC_STRING            Domain;
    _MGC_STRING            Version;
    //char                  *domain;
    //char                  *version;
    _MGC_STRING            ServerAddr;
    _MGC_STRING            ServerPort;
    //char                  *serveraddr;
    //char                  *serverport;
    
    #ifdef __FTP_SERVER__
    _MGC_STRING             FileServerAddr;
    _MGC_STRING             FileServerPort;
    //char                  *zserveraddr;
    //char                  *zserverport;
    #endif
    
    _MGC_STRING            Connection;
    _MGC_STRING            ServerTimeout;
    //char                  *connection;
    //char                  *timeout;
    _MGC_STRING            ServerName;
    _MGC_STRING            ServerRoot;
    _MGC_STRING            DocumentRoot;
    _MGC_STRING            DocumentDirectory;
    //char                  *servername;
    //char                  *serverroot;
    //char                  *documentroot;
    //char                  *documentdir;
    _MGC_STRING            DocumentIndex;
    _MGC_STRING            DocumentName;
    _MGC_STRING            RequestLength;
    
    //char                  *documentindex;
    //char                  *documentname;
    //char                  *requestlength;
    _MGC_STRING            ContentCharset;
    _MGC_STRING            ContentType;
    //char                  *charset;
    //char                  *contenttype;
    _MGC_STRING            ModuleRoot;
    _MGC_STRING            ModuleFile;
    //char                  *moduleroot;
    //char                  *modulefile;
    
    _MGC_STRING            SSLCert;
    _MGC_STRING            SSLKey;
    _MGC_STRING            SSLChain;
    _MGC_STRING            SSLFile;
    _MGC_STRING            SSLPath;
    
    _MGC_STRING            SSLCrl;
    _MGC_STRING            SSLXml;
    //char                  *sslcert;
    //char                  *sslkey;
    //char                  *sslchain;
    //char                  *sslcrl;
    //char                  *sslxml;
    _MGC_STRING            hFileError;
    _MGC_STRING            hFileWarn;
    _MGC_STRING            hFileAccess;
    //char                  *hferror;
    //char                  *hfwarn;
    //char                  *hfaccess;
    
    //zconfig_folder_t       *nfolder;
    //zconfig_state_t        *nresponse; 
    //zconfig_state_t        *ncontent;
    
    //zconfig_array_t        *fdocindex;
    //zconfig_array_t        *fdocname;
    //zconfig_array_t        *fcharset;
    //zconfig_array_t        *fcontenttype;
    
    struct _zconfig_server_t *next;
} zconfig_server_t;

typedef struct _iserver_config
{
     int  sfd,_s;
     int  sign;
     char  *argv;
     
     int  status;
     
     char  *config_file;
     char  *types_file;
     char  *pages_file;
     char  *folder_file;
     
     
     #ifndef SSL_CERT
     void        *ssl_ctx;
     void        *method;
    
     void        *ssl;
    
     char        *cipher;
     
     char        *ssl_ver;
     unsigned     flags;
     
     char         *SSLCert;
     char         *SSLKey;
     char         *SSLChain;
     
     char        *SSLFile;
     char        *SSLPath;
     
     #endif
}iserver_config;

typedef struct _iserver_module
{
        char *version;
        char *name;
        char *os;
        
        uint32_t (*cstartup)(iserver_config *);
        uint32_t (*ccleanup)(iserver_config *);
        uint32_t (*cbuild)(iserver_config *);
        
        uint32_t (*cmodule)(struct _iserver_module *c, iserver_config *x);
        uint32_t (*cread)(iserver_config *,char *buffer,uint32_t len);
        uint32_t (*cwrite)(iserver_config *,char *buffer, uint32_t len);
        uint32_t (*cdone)(iserver_config *s);
        uint32_t (*ctime)(iserver_config *s, uint32_t dwtime);
        uint32_t (*cipaddr)(iserver_config *s, _MGC_STRING serveraddr,_MGC_STRING remoteaddr);
        
        uint32_t (*tread)(iserver_config *,char *buffer,uint32_t len);
        uint32_t (*twrite)(iserver_config *,char *buffer, uint32_t len);
        
        uint32_t (*clogs)(iserver_config *);
        uint32_t (*caccess)(iserver_config *);
        
}iserver_module;

uint32_t cstartup(iserver_config *);
uint32_t ccleanup(iserver_config *);
uint32_t cbuild(iserver_config *);
        
uint32_t cmodule(iserver_module *,iserver_config *);
uint32_t cread(iserver_config *,char *buffer,uint32_t len);
uint32_t cwrite(iserver_config *,char *buffer, uint32_t len);
uint32_t cdone(iserver_config *s);
uint32_t ctimem(iserver_config *s, uint32_t dwtime);
uint32_t cipaddr(iserver_config *s, _MGC_STRING serveraddr,_MGC_STRING remoteaddr);

uint32_t tread(iserver_config *,char *buffer,uint32_t len);
uint32_t twrite(iserver_config *,char *buffer, uint32_t len);

uint32_t clogs(iserver_config *);
uint32_t caccess(iserver_config *);

uint32_t onserver(iserver_module *b, iserver_config *s);

typedef int (*cserver_string)(char *str);
        
void fatal(char *str, const char *file,const char *func, unsigned long line);
        
extern zconfig_server_t *server;        
      

#define CPRINT(c, x) if(x!=NULL){ printf("%16s:%s\n",c, x); }
#define CLEAN(x)  if(x!=NULL) (x= efree(x)),x=NULL;
#define CNULL(x)  x=NULL;

#define CCSTAT(x,l)       cstring_stat(&x,l)
#define CCREMOVE(x, l)    cstring_remove(&x, l)
#define CCNEWPAD(x,c,s) cstring_newpad(&x,c,s)
#define CCNEWADD(x,a,b) cstring_newadd(&x,a,b)
#define CCNEW(x,c)  cstring_new(&x,c)
#define CCRENEW(x,l) cstring_renew(&x, l)
#define CCCLONE(x,l) cstring_clone(&x, l)
#define CCSHOW(x)  cstring_str(x)
#define CCCHECK(x) cstring_check(&x)
#define CCLEAN(x) cstring_clean(&x)
#define CCNULL(x) cstring_create(&x)
#define CCCLEAR(x) cstring_clear(&x)

#define CHKDSK(x,l) if(!CCCHECK(x)){ //printf("(%d)\n", l);
#define CHKEND }

#define CCSTART   {
#define CCEND     }

#define xmalloc  emalloc
#define xrealloc erealloc
#define xfree    free
#define XCLEAN(x) if(x!=NULL) xfree(x),x=NULL;

uint32_t  _conf_load(const char *root, const char *file, cserver_string mod);
uint32_t  _conf_copy(zconfig_server_t **info, const char *buff);
uint32_t  _conf_clean(zconfig_server_t **info);
uint32_t  _conf_null(zconfig_server_t **info);      
        

typedef struct _zrequest_externs_t
{
	_MGC_UINT       ServerCode;
	
    _MGC_STRING     ServerOS;
	_MGC_STRING	    ServerSoftware; //SERVER_SOFTWARE;
	_MGC_STRING	    ServerName;     //SERVER_NAME;
	_MGC_STRING     ServerVersion;   //SERVER_VERSION
	_MGC_STRING	    ServerProtocol; //SERVER_PROTOCOL;
	_MGC_STRING     ServerAddress;   // SERVER_ADDRESS
	_MGC_STRING	    ServerPort;     //SERVER_PORT;
	_MGC_STRING	    ServerAdmin;    //SERVER_ADMIN;
	_MGC_STRING	    GatewayInterface;//GATEWAY_INTERFACE;
	_MGC_STRING	    DocumentRoot;    //DOCUMENT_ROOT;
	_MGC_STRING     ServerRoot;
	
	_MGC_STRING	    PathTranslated;  //PATH_TRANSLATED;
	_MGC_STRING     FullPathTranslated;
	_MGC_STRING  	RequestMethod;   //REQUEST_METHOD;  10
	_MGC_STRING	    RequestUri;      //REQUEST_URI;
	_MGC_STRING	    ScriptName;      //SCRIPT_NAME;
	_MGC_STRING	    FileSelf;         //PHP_SELF;
	_MGC_STRING     FileQuery;        // FILE_QUERY
	_MGC_STRING	    QueryString;     //QUERY_STRING;
	
	_MGC_STRING     UrlCache;
	
	_MGC_STRING	    ServerAddr;
	_MGC_STRING	    RemoteAddr;      //REMOTE_ADDR;
	_MGC_STRING     ServerStatus;
	_MGC_STRING     ServerHeader;
	_MGC_STRING	    ContentLength;   //CONTENT_LENGTH;
	_MGC_STRING	    ContentType;     //CONTENT_TYPE;
	_MGC_STRING     Charset;
	
	_MGC_STRING	    DefaultContentType;  //CONTENT_TYPE;
	_MGC_STRING     DefaultCharset;
	
    _MGC_STRING	    AuthType;        //AUTH_TYPE;
	_MGC_STRING	    EntityPath;      //ENTITY_PATH;        20
	_MGC_STRING	    RemoteUser;      //REMOTE_USER;
	_MGC_STRING     ServerHost;      //SERVER_HOST
	_MGC_STRING     HTTPHostName;        // HTTP_HOSTNAME
	_MGC_STRING	    HTTPCookie;      //HTTP_COOKIE;
	_MGC_STRING	    HTTPUserAgent;  //HTTP_USER_AGENT;
	_MGC_STRING     HTTPWebBrowser;  //HTTP_WEBBROWSER ; DEFINE BY Lexne
	_MGC_STRING	    HTTPReferer;     //HTTP_REFERER;
	_MGC_STRING	    HTTPAccept;      //HTTP_ACCEPT;
	_MGC_STRING     HTTPConnection;   // HTTP_CONNECTION
	_MGC_STRING	    HTTPAccept_language; //HTTP_ACCEPT_LANGUAGE;  30
	_MGC_STRING	    HTTPAccept_charset;  //HTTP_ACCEPT_CHARSET;
	_MGC_STRING	    HTTPAccept_encoding; //HTTP_ACCEPT_ENCODING;
	
	_MGC_STRING     HTTPContentType;
	_MGC_STRING     KeepAlive;
	//PHP_AUTH_USER
	//PHP_AUTH_PW
	//AUTH_TYPE
	
	_MGC_STRING     HTTPPragma;
	_MGC_STRING     HTTPCacheControl;
	
	_MGC_STRING     RequestTimes;
    
    _MGC_STRING     FileLastName;
    _MGC_STRING     FileIndexName;
    
    //_MGC_STREAM     *Unknown;
    
    //_MGC_LENGTH      Count; 
} zrequest_externs_t;        

#define SG(x) request->x        

typedef struct _zrequest_module
{
   	char *name;
   	char *version;
   	int32_t  (*module)(zrequest_externs_t **req);
}zrequest_module;
 
typedef struct _logs_data{
	_MGC_STRING    ipaddr;
	_MGC_STRING    request;
	_MGC_STRING    logs;
	_MGC_STRING    fulldate;
} zlogs_data;        
       
char    *get_error(void);
char    *get_realtime(void);
uint32_t ulogs_access(zlogs_data *s);
	
#define CACHE_LENGTH    16

	
#define METHOD_HEAD      0x0401
#define METHOD_GET       0x0302
#define METHOD_POST      0x0403
#define METHOD_PUT       0x0304
#define METHOD_TRACE     0x0505
#define METHOD_DELETE    0x0606
#define METHOD_OPTIONS   0x0707
#define METHOD_PROPFIND  0x0808        

#define METHOD_HEAD_STR      "HEAD"
#define METHOD_GET_STR       "GET"
#define METHOD_POST_STR      "POST"
#define METHOD_PUT_STR       "PUT"
#define METHOD_TRACE_STR     "TRACE"
#define METHOD_DELETE_STR    "DELETE"
#define METHOD_OPTIONS_STR   "OPTIONS"
#define METHOD_PROPFIND_STR  "PROPFIND" 
        
#define HTTPACCEPT            0x0701
#define HTTPACCEPTLANGUAGE    0x1002
#define HTTPACCEPTCHARSET     0x0f03 
#define HTTPUSERAGENT         0x0b04
#define HTTPWEBBROWSER        0x1005
#define HTTPACCEPTENCODING    0x1006 
#define HTTPHOSTNAME          0x0507
#define HTTPCONNECTION        0x0b08 
#define HTTPPRAGMA            0x0709
#define HTTPCACHECONTROL      0x0e10 
#define HTTPREFERER           0x0811
#define HTTPCOOKIE            0x0712
#define HTTPCONTENTTYPE       0x0e13
#define HTTPKEEPALIVE         0x0b14
        
        
char *_new_str(const char *zstr);
char *_newadd_str(const char *str, const char *pad);
char* _new_time();

extern
char   *rtype;
extern
char   *page;
extern char   *grfront;
extern char   *grback;
extern uint32_t  grfront_size ;
extern uint32_t  grback_size ;

uint32_t  request_inittype(const char *file);
char *request_contentType(const char *path, const char *type);
char * request_contentLength(const char *path);
char*  request_getheader(unsigned int code);
char * request_getstatus(unsigned int code);

uint32_t request_initpage(const char *file);
char*  request_pageLength(const char *serverstatus, const char *servername);
uint32_t request_readpage(char *str, const char *status, const char *name, uint32_t length);

uint32_t request_initdir(const char *file);

uint32_t  request_module(iserver_module *b, iserver_config *s, void *d);
uint32_t  request_init(zrequest_externs_t **s);
uint32_t  request_fini(zrequest_externs_t **s);
uint32_t  request_startup(zrequest_externs_t **s, zconfig_server_t *c);
uint32_t  request_client(zrequest_externs_t  **s, const char *buffer, int *status);
uint32_t  request_externs(zrequest_externs_t **s, const char *str);
uint32_t  request_info(zrequest_externs_t **s);
uint32_t request_checkfile(const char *path, uint32_t *status);

char * request_ascii(const char *buffer);
char * request_pathdecrypt( char * s);
uint32_t  request_path(zrequest_externs_t **s);

char *_new_str(const char *zstr);

struct module_addr_t {
    char *mod_name;

    int (*mod_init)(char *file);
    int (*mod_exit)(void);
    int (*mod_ctrl)(void *input, int flags, void **output);
    
    int (*mod_verify)(void *param);

    int (*mod_startup)(void **handle, void *request);
    int (*mod_execute)(void **handle);
    int (*mod_cleanup)(void **handle);
 
    struct module_addr_t *next;
};
struct module_stack_t {
    unsigned int          count;
    struct module_addr_t *addr;
};
typedef struct module_stack_t zmodule_stack_t;

char*  zmod_request_pageLength(zmodule_stack_t *ptr, const char *serverstatus, const char *servername);
void *zmod_csp_module_startup(zmodule_stack_t *ptr, sapi_server *req, zrequest_externs_t *ext );
void *zmod_csp_module_execute(zmodule_stack_t *ptr, sapi_server *req);
void *zmod_csp_module_cleanup(zmodule_stack_t *ptr, sapi_server *req);
uint32_t zmod_request_module_script(zmodule_stack_t *ptr, zrequest_externs_t *request);
uint32_t zmod_request_readpage(zmodule_stack_t *ptr, char *str, zrequest_externs_t *request);

uint32_t zmod_request_dirinit(zmodule_stack_t *ptr);
uint32_t zmod_request_dirfini(zmodule_stack_t *ptr);

uint32_t zmod_request_getfrontsize(zmodule_stack_t *ptr, char *path);
uint32_t zmod_request_getfront(zmodule_stack_t *ptr, char *buffer, uint32_t length, const char *path);
long zmod_request_dirliststart(zmodule_stack_t *ptr, char *path);
char* zmod_request_dirlistloop(zmodule_stack_t *ptr, long *hfd,const char *path,  uint32_t *size);
uint32_t zmod_request_dirlistend(zmodule_stack_t *ptr, long *hfd);
uint32_t zmod_request_getbacksize(zmodule_stack_t *ptr,
   const char *name,const char *ver, const char *os, const char *addr, char *port);
uint32_t zmod_request_getback(zmodule_stack_t *ptr, char *buffer, uint32_t length, 
   const char *name,const char *ver, const char *os, const char *addr, char *port);

extern
zmodule_stack_t *module_stack;

#define SCRIPTFILE  ".htaccess\0"
#define XSPAPI  

#define XSP_VERSION  "1.0"
#define ISQL_VERSION "1.0"

#define XFLAGS    1

typedef struct _xcsp_class_function
{
	zrequest_externs_t *request;
	
	char     *buffer;
	uint32_t  length;
	
	char     *file;
	
}xcsp_class_function;

typedef struct _sapi_buffer
{
    char      *buffer;
	uint32_t  length;	
}sapi_buffer;

typedef struct _sapi_header
{
	uint32_t      count;
	uint32_t      number;
	uint32_t      saveid;
	
	struct _sapi_buffer *data;
	struct _sapi_header *next;
}sapi_header;

typedef struct _sapi_value
{
    uint32_t     count;
    
    sapi_buffer  name;
    sapi_buffer  value;
    
    struct _sapi_value *next;
}sapi_value;

typedef struct _sapi_module
{
	char  *name_func;
	char  *version;
	int32_t  (XSPAPI *func_ctrl)(void *ext, const char *query_string, char **result);
	uint32_t flags;
}sapi_module;


struct _sapi_server 
{
	int           s;
	
	uint32_t      (XSPAPI *startup)(xcsp_class_function *module, const char *file);
	uint32_t      (XSPAPI *cleanup)(xcsp_class_function *module);
	uint32_t      (XSPAPI *analyze)(xcsp_class_function *module, const char *src);
	uint32_t      (XSPAPI *syntex)(xcsp_class_function *module, char **outstr );
	
	uint32_t      (XSPAPI *length)(xcsp_class_function *module, uint32_t *length);
	uint32_t      (XSPAPI *read)(xcsp_class_function *module, char *buffer, uint32_t length);
	uint32_t      (XSPAPI *readline)(xcsp_class_function *module, const char *dst, char *src);
	
	uint32_t      (XSPAPI *execute)(xcsp_class_function *module, sapi_header **header, sapi_buffer **buffer );
	
	xcsp_class_function *module;
	
	sapi_header       *header;
	sapi_buffer       *buffer;
	
	sapi_buffer       *temp;
	
	struct _sapi_server *first;
	struct _sapi_server *next;
};


uint32_t request_module_script(zrequest_externs_t *request, iserver_module *controls, uint32_t status);


typedef struct _script_server
{
	uint32_t           status;
	
	sapi_buffer       *buffer;
}script_server;


int libsec_verify(char *buffer);

extern 
int bio_sign;



uint32_t SSL_Openssl_startup( iserver_config    **svc,
    const char *certfile,
    const char *keyfile, const char *chainfile, 
    const char *cafile, const char *capath);
void *   SSL_Openssl_accept(iserver_config *server, int s_);
void     SSL_Openssl_close(iserver_config *server);
int      SSL_Recv(SSL *ssl,char* buffer,unsigned int length);
int      SSL_Readbytes(SSL *ssl,char* buffer,unsigned int length);
int      SSL_Write(SSL *ssl,char* buffer,unsigned int length);
int      SSL_Writebytes(SSL *ssl,char* buffer,unsigned int length);
unsigned 
int      SSL_openssl_cleanup(iserver_config *server);
char     *SSL_Getcipher(SSL *ssl);

#endif
