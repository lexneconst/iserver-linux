#include "iserver.h"





#ifndef _SSL_CERT
#define _SSL_CERT

#define COOKIE_SECRET_LENGTH    16

int verify_depth = 0;
int verify_quiet = 0;
int verify_error = X509_V_OK;
int verify_return_error = 0;

static int s_server_verify = SSL_VERIFY_PEER; //SSL_VERIFY_NONE;
static int context_num = 1; /* anything will do */

static unsigned char cookie_secret[COOKIE_SECRET_LENGTH];
static int cookie_initialized = 0;

BIO*           bio_err;

static int
no_passphrase_callback(char *buf, int num, int w, void *arg)
{
    return -1;
}

static int verify_callback(int ok, X509_STORE_CTX *ctx)
{
    X509 *err_cert;
    int err, depth;
    
    printf("[%s] status [%d] \n", __FUNCTION__, ok);
     
    err_cert = X509_STORE_CTX_get_current_cert(ctx);
    err = X509_STORE_CTX_get_error(ctx);
    depth = X509_STORE_CTX_get_error_depth(ctx);

    if (!verify_quiet || !ok) {
        BIO_printf(bio_err, "depth=%d ", depth);
        if (err_cert) {
            X509_NAME_print_ex(bio_err,
                               X509_get_subject_name(err_cert),
                               0, XN_FLAG_ONELINE);
            BIO_puts(bio_err, "\n");
        } else
            BIO_puts(bio_err, "<no cert>\n");
    }
    if (!ok) {
        BIO_printf(bio_err, "verify error:num=%d:%s\n", err,
                   X509_verify_cert_error_string(err));
        if (verify_depth >= depth) {
            if (!verify_return_error)
                ok = 1;
            verify_error = err;
        } else {
            ok = 0;
            verify_error = X509_V_ERR_CERT_CHAIN_TOO_LONG;
        }
    }
    switch (err) {
    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
        BIO_puts(bio_err, "issuer= ");
        X509_NAME_print_ex(bio_err, X509_get_issuer_name(err_cert),
                           0, XN_FLAG_ONELINE);
        BIO_puts(bio_err, "\n");
        break;
    case X509_V_ERR_CERT_NOT_YET_VALID:
    case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
        BIO_printf(bio_err, "notBefore=");
        ASN1_TIME_print(bio_err, X509_get_notBefore(err_cert));
        BIO_printf(bio_err, "\n");
        break;
    case X509_V_ERR_CERT_HAS_EXPIRED:
    case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
        BIO_printf(bio_err, "notAfter=");
        ASN1_TIME_print(bio_err, X509_get_notAfter(err_cert));
        BIO_printf(bio_err, "\n");
        break;
    case X509_V_ERR_NO_EXPLICIT_POLICY:
        if (!verify_quiet){
            //policies_print(ctx);
        }
        break;
    }
    if (err == X509_V_OK && ok == 2 && !verify_quiet)
    {   //policies_print(ctx);
    }
    if (ok && !verify_quiet)
        BIO_printf(bio_err, "verify return:%d\n", ok);
    return (ok);
}


uint32_t SSL_Openssl_startup( iserver_config    **svc,
    const char *certfile,
    const char *keyfile, const char *chainfile, 
    const char *cafile, const char *capath)
{
    unsigned int            ret=1;
    int                     r;
    static long context_num = 0;
    iserver_config   * server = (iserver_config*) *svc;

    SSL_load_error_strings();
	
	SSLeay_add_ssl_algorithms();
	//SSLeay_add_all_ciphers();
	//SSLeay_add_all_digests();

	#ifdef DEBUG_H
    printf("cert: %s \n", certfile);
    #endif
	//printf("key:  %s \n", keyfile);
	//printf("chainfile: %s\n", chainfile);
	//printf("cafile: %s \n", cafile);
	//printf("capath: %s \n", capath);
	
	
do{
    if(server == NULL){
       fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    server->flags = 1;
    
    switch(server->flags){
       case 0:
        // server->method=SSLv3_server_method();
         break;
       case 1:
       	 server->method= SSLv23_server_method();
       	 break;
       case 2:
       	// server->method=SSLv2_server_method();
       	 break;
       default:
       	 fatal("TLSv1_server_method" , __FILE__, __FUNCTION__, __LINE__);
       	 server->method=TLSv1_server_method();
       	 break;
	}
	#ifdef DEBUG_H
	printf("Notify: LINE <%d> \n", __LINE__);
	#endif
	if(server->method==NULL){
		fatal("SSL Method Don't Loaded.", __FILE__, __FUNCTION__, __LINE__);
		ret=0;
		break;
	}
	#ifdef DEBUG_H
	printf("Notify: LINE <%d> \n", __LINE__);
	#endif
	server->ssl_ctx=SSL_CTX_new((SSL_METHOD*) server->method);
	#ifdef DEBUG_H
	printf("Notify: LINE <%d> \n", __LINE__);
	#endif
	
	if(server->ssl_ctx==NULL){
        fatal("SSL Method Don't re-Loaded.", __FILE__, __FUNCTION__, __LINE__);
        server->method=SSLv23_server_method();
  	    if(server->method==NULL){
		   fatal("SSL Method Don't Loaded.", __FILE__, __FUNCTION__, __LINE__);
		   ret=0;
		   break;
	    }
                          
		server->ssl_ctx=
           SSL_CTX_new((SSL_METHOD*) server->method);
		if(server->ssl_ctx==NULL){
		    fatal("SSL Method Don't Loaded.",  __FILE__, __FUNCTION__, __LINE__);
			ret=0;
			break;
		}else{
		   server->ssl_ver = (char *) _new_str("SSLv23");
		   if(server->ssl_ver==NULL){
		  	  fatal("segment memory failed,.", __FILE__, __FUNCTION__, __LINE__);
			  break;
		   }
		}
	}else{
		
		server->ssl_ver = (char *) _new_str("SSLv3");
		if(server->ssl_ver==NULL){
			fatal("segment memory failed,.", __FILE__, __FUNCTION__, __LINE__);
			break;
		}
	}
	#ifdef DEBUG_H
	printf("Notify: LINE <%d> \n", __LINE__);
	#endif
	if(certfile ==NULL){
       fatal("file not found", __FILE__, __FUNCTION__, __LINE__);
       ret=0;
       break;
    }
    if(keyfile == NULL){
       fatal("file not found", __FILE__, __FUNCTION__, __LINE__);
       ret=0;
       break;
    }
    if(chainfile == NULL){
       fatal("file not found", __FILE__, __FUNCTION__, __LINE__);
       ret=0;
       break;
    }
    #ifdef DEBUG_H
	printf("Notify: LINE <%> \n", __LINE__);
	#endif
	
	#ifndef __DBG_SH
	if(certfile!=NULL)
	printf("[%s] FILE[%s] \n", __FUNCTION__, certfile );
	if(keyfile!=NULL)
	printf("[%s] FILE[%s] \n", __FUNCTION__,keyfile );
	if(chainfile!=NULL)
	printf("[%s] FILE[%s] \n", __FUNCTION__,chainfile );
	
	#endif
	SSL_CTX_set_default_passwd_cb(server->ssl_ctx, no_passphrase_callback);
    SSL_CTX_set_mode(server->ssl_ctx, SSL_MODE_ENABLE_PARTIAL_WRITE);
    #ifdef DEBUG_H
	printf("Notify: LINE <%d> \n", __LINE__);
	#endif
	//printf("%s \n", data->certs);
	if(SSL_CTX_use_certificate_file(
          (SSL_CTX*)server->ssl_ctx, certfile , SSL_FILETYPE_PEM )<=0)
	{
		fatal("Create Certificate File", __FILE__, __FUNCTION__, __LINE__);
		ret=0;
		break;
	}
	if(SSL_CTX_use_PrivateKey_file(
          (SSL_CTX*)server->ssl_ctx, keyfile , SSL_FILETYPE_PEM) <= 0){
		       //printf("[Warning] Create PrivateKey File \n");
	     fatal ( "Create PrivateKey File", __FILE__, __FUNCTION__, __LINE__);
		 ret=0;
		break;
	}
	if(SSL_CTX_use_certificate_chain_file(
         (SSL_CTX*)server->ssl_ctx, chainfile ) <= 0){
		       //printf("[warning] Create Certificate Chain File \n");
		 fatal( "Create Certificate Chain File ",
	                 __FILE__, __FUNCTION__, __LINE__);
		ret=0;
		break;
    }
    
    if (!SSL_CTX_check_private_key((SSL_CTX*)server->ssl_ctx)) {
	    fatal( "Private key does not match the certificate public key",
	                   __FILE__, __FUNCTION__, __LINE__);
	    ret=0;
		break;
    } 
    #ifdef DEBUG_H
    printf("Notify: LINE <%d> \n", __LINE__);
    #endif
	SSL_CTX_set_verify(server->ssl_ctx, s_server_verify, verify_callback);
	SSL_CTX_set_verify_depth(server->ssl_ctx, 4);

    SSL_CTX_set_mode(server->ssl_ctx, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_session_cache_mode(server->ssl_ctx, SSL_SESS_CACHE_OFF);
    
    SSL_CTX_set_trust(server->ssl_ctx, X509_TRUST_SSL_SERVER);
    #ifdef DEBUG_H
    printf("Notify: LINE <%d> \n", __LINE__);
    #endif

    #ifdef DEBUG_TEST
    r = SSL_CTX_load_verify_locations(server->ssl_ctx, 
               cafile, capath /* no CA-directory */);
	if (!r){
        fatal( "SSL CTX load verify locations",
	                   __FILE__, __FUNCTION__, __LINE__);
	    ret=0;
		break;
   }
   #endif

   #ifdef DEBUG_H
   printf("Notify: LINE <%d> \n", __LINE__);
   #endif
   
   SSL_CTX_set_client_CA_list(server->ssl_ctx, SSL_load_client_CA_file(certfile));
		/* SSL_CTX_set_client_CA_list does not have a return value;
		 * it does not really need one, but make sure
		 * (we really test if SSL_load_client_CA_file worked) */
	if (SSL_CTX_get_client_CA_list(server->ssl_ctx) == NULL) {
		  fatal( "Could not set client CA list from ",
            __FILE__, __FUNCTION__, __LINE__);
		 ret=0;
		 break;
	}
    #ifdef DEBUG_H
    printf("Notify: LINE <%d> \n", __LINE__);
    #endif
    #ifdef __STD__
    //context_num++;
    
    if (!SSL_CTX_set_session_id_context(server->ssl_ctx,
                (void *)&context_num,
                sizeof context_num)) {
        //BIO_printf(bio_err, "error setting session id context\n");
        //ERR_print_errors(bio_err);
        fatal( "SSL_CTX set session id context",
	                   __FILE__, __FUNCTION__, __LINE__);
	    ret=0;
		break;
    }
    //SSL_CTX_set_cookie_generate_cb(server->ssl_ctx, generate_cookie_callback);
    //SSL_CTX_set_cookie_verify_cb(server->ssl_ctx, verify_cookie_callback);

    #endif
    
    #ifdef __SCC_
	


    
    #endif
	
	
}while(0);
    
   //SSL_CTX_set_verify( server->ssl_ctx , SSL_VERIFY_PEER, verify_callback);
   
    
   if(!ret){
            
     if(server->ssl_ctx!=NULL)
       SSL_CTX_free((SSL_CTX*)server->ssl_ctx), server->ssl_ctx=NULL;
       
    // if(server!=NULL){
       
    //   CLEAN( server );
    // }
	   
   }
   if(server==NULL){
      fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
      return ret;
   }
    
   *svc = server; 
    
   return ret;
}

int ssl_callback (int ok,X509_STORE_CTX *ctx)
{
	printf("%s> %d \n", __FUNCTION__, ok);
	return 0;
}

int verify_result(int id)
{
	#ifdef DEBUG_H
	printf("%s > %d | %s\n", __FUNCTION__, id, X509_verify_cert_error_string(id));
	#endif
	return 0;
}

void *SSL_Openssl_accept(iserver_config *server, int s_)
{
   SSL         *ssl=NULL;
   X509        *xss=NULL; 
   unsigned int ret=1;
   int          res=0;
   SSL_CIPHER  *cipher=NULL;
   #ifdef DEBUG_H
   printf("-------------------------------------------------\n");
   #endif
do{
   if(server==NULL){
      fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
      ret=0;
      break;
   }        
   if(server->ssl_ctx==NULL){
      fatal("stack memory failed.,", __FILE__, __FUNCTION__, __LINE__);
      ret=0;
      break;                          
   }  
   if(s_ == SOCKET_ERROR){
       fatal("invalid socket ", __FILE__, __FUNCTION__,__LINE__);
       ret=0;
       break;
   }
   //printf("ssl [%s] %p \n", server->ssl_ver, server->ssl_ctx);
            
   ssl = SSL_new((SSL_CTX*) server->ssl_ctx );
   if(ssl == NULL){
      fatal("ssl 'SSL_new' ",__FILE__, __FUNCTION__, __LINE__);
      ret=0;
      break;
   }
   if(SSL_set_fd (ssl, s_ )==-1){
   	   SSL_clear(ssl);
       
	   fatal("ssl 'SSL_set_fd' ", __FILE__, __FUNCTION__, __LINE__);
       ret=0;         
       break;
   }
   
   SSL_set_verify(ssl, SSL_VERIFY_PEER, ssl_callback);
   SSL_set_verify_depth(ssl, 4);
   SSL_set_purpose(ssl, X509_PURPOSE_SSL_SERVER);
   SSL_set_trust(ssl, X509_TRUST_SSL_SERVER);
   
   //SSL_set_accept_state(ssl);
   
   if((res=SSL_accept (ssl)) == -1){
       //
       #ifdef DEBUG_H
       printf("ERR> %s | %s\n",SSL_state_string(ssl), SSL_state_string_long(ssl)); 
       #endif
       
       switch(SSL_get_error(ssl, 0) ){
       	case SSL_ERROR_NONE:
       		#ifdef DEBUG_H
       		printf("SSL_ERROR_NONE");
       		#endif
       		break;
       	case SSL_ERROR_SSL:
       		#ifdef DEBUG_H
       		printf("SSL_ERROR_SSL");
       		#endif
			break;
       	case SSL_ERROR_WANT_READ:
       		#ifdef DEBUG_H
       		printf("SSL_ERROR_WANT_READ");
       		#endif
       		break;
       	case SSL_ERROR_WANT_WRITE:
       		#ifdef DEBUG_H
       		printf("SSL_ERROR_WANT_WRITE");
       		#endif
			break;
       	case SSL_ERROR_WANT_X509_LOOKUP:
       		#ifdef DEBUG_H
       		printf("SSL_ERROR_WANT_X509_LOOKUP");
       		#endif
       		break;
       	case SSL_ERROR_SYSCALL:
       		#ifdef DEBUG_H
       		printf("SSL_ERROR_SYSCALL");
       		#endif
       		break; 
		case SSL_ERROR_ZERO_RETURN:
			#ifdef DEBUG_H
			printf("SSL_ERROR_ZERO_RETURN");
			#endif
			break;
		case SSL_ERROR_WANT_CONNECT:
			#ifdef DEBUG_H
			printf("SSL_ERROR_WANT_CONNECT");
			#endif
			break;
		case SSL_ERROR_WANT_ACCEPT:
			#ifdef DEBUG_H
			printf("SSL_ERROR_WANT_ACCEPT");
			#endif
			break;
       }
       #ifdef DEBUG_H
       printf("\n");
       #endif
       
   	   SSL_renegotiate(ssl);
   	   SSL_clear(ssl);
	   //SSL_clear(ssl);
       //SSL_shutdown(ssl);
       fatal("ssl 'SSL_accept' ", __FILE__, __FUNCTION__, __LINE__);
       ret=0;         
       break;
   }
}while(0);
  if(ssl==NULL) goto ENDL;

  verify_result(SSL_get_verify_result(ssl));
  SSL_set_verify_result(ssl, X509_V_OK);
  
  cipher = SSL_get_current_cipher(ssl);
  //printf("--> V: %s | N: %s",SSL_CIPHER_get_version(cipher), SSL_CIPHER_get_name(cipher) );
  
  //bio_err = BIO_new_fp(stderr,BIO_NOCLOSE|BIO_FP_TEXT);
 
  //printf("\n");
  		   
  xss =SSL_get_certificate(ssl);
  if (xss) {
  	  #ifdef DEBUG_H
  	  printf("GET> gs <%x>\n", xss );
  	  #endif
  	  
  	  BIO_puts(bio_err, "subject= ");	
      X509_NAME_print_ex(bio_err, X509_get_subject_name(xss), 0, XN_FLAG_ONELINE);
      BIO_puts(bio_err, "\n");
      BIO_puts(bio_err, "issuer= ");
      X509_NAME_print_ex(bio_err, X509_get_issuer_name(xss), 0, XN_FLAG_ONELINE);
      BIO_puts(bio_err, "\n");
      
	  //X509_free(xss);
      /*SSL_get_peer_certificate(ssl);
      SSL_get_peer_cert_chain(ssl);*/
      
  }else{
  	  #ifdef DEBUG_H
  	  printf("NOT> gs <%x>\n", xss);
  	  #endif
  	  
  	  SSL_renegotiate(ssl);
  }
  
  //
  
  xss = SSL_get_peer_certificate(ssl);
  if(xss) {
     #ifdef DEBUG_H  
  	 printf("GET> ar <%x>\n", xss );
  	 #endif
     BIO_puts(bio_err, "subject= ");	
     X509_NAME_print_ex(bio_err, X509_get_subject_name(xss), 0, XN_FLAG_ONELINE);
     BIO_puts(bio_err, "\n");
     BIO_puts(bio_err, "issuer= ");
     X509_NAME_print_ex(bio_err, X509_get_issuer_name(xss), 0, XN_FLAG_ONELINE);
     BIO_puts(bio_err, "\n");
     
	 //X509_free(cert); 
  }else{
  	 #ifdef DEBUG_H
  	 printf("NOT> ar <%x>\n", xss);	
     #endif
  }

  res = SSL_get_verify_result(ssl);
  if(!(X509_V_OK == res)){
  	 #ifdef DEBUG_H
     printf("ERROR (NOT VERIFIED - %s) \n", X509_verify_cert_error_string(res));
     #endif
  }else{
  	 #ifdef DEBUG_H
  	 printf("SUCCESS (VERIFIED - %s) \n", X509_verify_cert_error_string(res));
  	 #endif
  }
    
  if(ret==0){
  	#ifdef DEBUG_H
    printf("SRC> not ssl create \n");
    #endif
    
    if(ssl!=NULL)
       SSL_free(ssl), ssl=NULL;
    
  }
  #ifdef DEBUG_H
  printf("-------------------------------------------------\n");
  #endif
 ENDL:
   return ssl;
}

void SSL_Openssl_close(iserver_config *server)
{
   do{
     
     if(server==NULL){
         fatal("stack memory ", __FILE__ ,__FUNCTION__, __LINE__);
         break;
     }
     if(server->ssl==NULL){
         fatal("stack memory ", __FILE__ ,__FUNCTION__, __LINE__);
         break;
     }
     
     if(server->ssl!=NULL) SSL_set_shutdown(server->ssl, SSL_SENT_SHUTDOWN/*|SSL_RECEIVED_SHUTDOWN*/);
     //SSL_shutdown(server->ssl_ctx);
     if(server->ssl!=NULL) SSL_free(server->ssl );
     
     //if(server->ssl!=NULL){
     //   SSL_clear(server->ssl);
    // }
   }while(0);
   
}


int  SSL_Recv(SSL *ssl,char* buffer,unsigned int length)
{   
    char *ptr=NULL;
    int eol_matched = 0;
    unsigned long num = 0;
    //printf("size : %d \n", length);
    
   #define EOL "\r\n"
   #define EOL_SIZE 2
   ptr = buffer;
		  //printf("> no signture ..\n");
       while(SSL_read(ssl, ptr, 1) == 1){
  	    if(num >= length){
  	         //DllErrorA("@ Terminal Buffer Receive ,", 
			 //    length, __LINE__ , (PVOID)__FUNCTION__);
			 return -2; 
	    }
	    //printf("%s", ptr);
  	    num+=1;
        if(*ptr == EOL[eol_matched]){
         eol_matched ++;
         if(eol_matched == EOL_SIZE){
            *(ptr +1- EOL_SIZE) = '\0';
            
	        //IsInitFinished(ssl);
            return strlen(buffer);
         }
        }else{
          eol_matched = 0;
        }
        ptr ++;
    }
    return -1;
}
int  SSL_Readbytes(SSL *ssl,char* buffer,unsigned int length)
{
	return SSL_read(ssl, buffer, length);
}
int  SSL_Write(SSL *ssl,char* buffer,unsigned int length)
{
    unsigned int sent_bytes=0, bytes_to_send=0;

	do{
	  if(ssl==NULL){
          fatal("stack memory ", __FILE__, __FUNCTION__, __LINE__);
          break;
      }
      
      bytes_to_send = length;
      while(bytes_to_send){
       if(buffer==NULL) break;
       if(sent_bytes >= length) break;
       sent_bytes = SSL_write(ssl, (char *)buffer, bytes_to_send);
       if(sent_bytes == -1){
          return 0;
       }
       bytes_to_send -= sent_bytes;
       buffer+= sent_bytes;
      }
		/*
		pstr = (char *) emalloc( length + 64);
		if(pstr==NULL){
			break;
		}
		strcpy(pstr, buffer); */
		//strcat(pstr, "\r\n");
		//size = SSL_write(ssl,buffer, length);
		/*if(pstr!=NULL){
		  
		  CLEAN( pstr );
		}*/
		  
	}while(0);
	return 0;
}
int SSL_Writebytes(SSL *ssl,char* buffer,unsigned int length)
{
	return SSL_write(ssl, buffer, length);
}

char *SSL_Getcipher(SSL *ssl)
{
   SSL_CIPHER  *cipher=NULL;   
   char        *c = NULL;
   char        *p = NULL;
   
   do{
    if(ssl== NULL){
    	fatal("ssl current loaded", __FILE__, __FUNCTION__, __LINE__);
        break;
    }
    cipher = SSL_get_current_cipher(ssl);
    if(cipher==NULL){
        fatal("ssl current cipher", __FILE__, __FUNCTION__, __LINE__);
        //break;
    }
    p= (char *)SSL_CIPHER_get_version( cipher );
    #ifdef DEBUG_H
	printf("CIP> <%s> |", p);
    #endif
	c= (char *)SSL_CIPHER_get_name( cipher );
    #ifdef DEBUG_H
	printf(" <%s> \n", c);
    #endif
    
  }while(0);
  
  #ifdef DEBUG_H
  CLEAN(cipher);
  #endif
  
  return c;
}


unsigned int SSL_openssl_cleanup(iserver_config *server)
{
    unsigned int ret=1;
    
do{
   if(server==NULL){
      ret=0;
      break;
   }
   
   if(server->ssl_ctx!=NULL)
       SSL_CTX_free((SSL_CTX*)server->ssl_ctx), server->ssl_ctx=NULL;
       
   if(server!=NULL){
       
       CLEAN( server );
   }
}while(0);

    return ret;
}

#endif
