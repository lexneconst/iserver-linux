/* Certificate creation. Demonstrates some certificate related
 * operations.
 */


#include <localsign.h>

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days);
int add_ext(X509 *cert, int nid, char *value);
int new_x509_crl(X509_CRL **crl,X509 *x509, EVP_PKEY *pkey);

int main(int argc, char **argv)
	{
	BIO      *bio_err;
	X509     *x509=NULL;
	EVP_PKEY *pkey=NULL;
	X509_REQ *xreq=NULL;
	X509_CRL *crl=NULL;
	PKCS12   *pkc12=NULL;
	FILE     *fp;
	char     *szfile=NULL;
	char      pass[2048];
	
    BIO       *certs = BIO_new_file("certs/localsign.crt", "w");
    BIO       *keys  = BIO_new_file("certs/localsign.key", "r");
    //BIO       *reqs  = BIO_new_file("certs\\localsign.cer", "w");
    //BIO       *crls  = BIO_new_file("certs\\localsign.crl", "w");
    //BIO       *pubs  = BIO_new_file("certs\\localsign.cet", "w");
    
    szfile = "certs/localsign.p12";
    
	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

	bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);

    pkey = PEM_read_bio_PrivateKey(keys, NULL, NULL, NULL);
    if(pkey==NULL){
        printf("ERROR: pkey \n");
        return 0;
    }
	mkcert(&x509,&pkey,2048,0x32DA2C56,365*8);
    if(x509==NULL){
        printf("ERROR: x509 \n");
        return 0;
    }
	//RSA_print_fp(stdout,pkey->pkey.rsa,0);
	X509_print_fp(stdout,x509);

	//PEM_write_PrivateKey(stdout,pkey,NULL,NULL,0,NULL, NULL);
	PEM_write_X509(stdout,x509);
    X509_ocspid_print(bio_err, x509);
    
    //PEM_write_bio_PrivateKey(keys, pkey, NULL,NULL, 0,NULL,NULL );
    PEM_write_bio_X509(certs, x509 );
    
    #ifdef __STD_P12
    if (EVP_read_pw_string(pass, sizeof pass, "Enter Export Password:",
                               1)) {
            BIO_printf(bio_err, "Can't read Password\n");
            
    }
    printf("EVP_read_pw_string[%s]\n", pass);
    pkc12 = PKCS12_create(pass, 
            "Lexne", pkey, x509, NULL, 0, 0, 0, 0, 0);
    if(pkc12 != NULL){
      
      if ((fp = fopen(szfile, "wb")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", szfile);
        ERR_print_errors_fp(stderr);
      }else{       
             
        i2d_PKCS12_fp(fp, pkc12);
      }
      if(pkc12!=NULL) PKCS12_free(pkc12), pkc12=NULL;
      if(fp) fclose(fp);
    
    }else{
       printf("[%s] creating PKCS#12 structure\n", __FILE__, __FUNCTION__, __LINE__);
    }
    #endif
    //xreq = X509_to_X509_REQ(x509, pkey, EVP_sha1() );
    //PEM_write_bio_X509_REQ(reqs, xreq);
    
    //new_x509_crl(&crl, x509, pkey);
    //PEM_write_bio_X509_CRL(crls , crl );
    
    //PEM_write_bio_RSAPublicKey(pubs, pkey->pkey.rsa);
    
   // BIO_free(pubs);
    //BIO_free(crls);
    BIO_free(certs);    
    //BIO_free(keys);
   // BIO_free(reqs);   
    
	X509_free(x509);
	EVP_PKEY_free(pkey);

#ifndef OPENSSL_NO_ENGINE
	ENGINE_cleanup();
#endif
	CRYPTO_cleanup_all_ex_data();
    #ifdef DEBUG_TEST
	CRYPTO_mem_leaks(bio_err);
    #endif
	BIO_free(bio_err);
	
	//system("pause");
	
	return(0);
	}

static void callback(int p, int n, void *arg)
	{
	char c='B';

	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	fputc(c,stderr);
	}

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days)
	{
	X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	int len;
	ASN1_OBJECT *object;
	 
	if ((pkeyp == NULL) || (*pkeyp == NULL))
		{
		if ((pk=EVP_PKEY_new()) == NULL)
			{
			abort(); 
			return(0);
			}
		}
	else
		pk= *pkeyp;

	if ((x509p == NULL) || (*x509p == NULL))
		{
		if ((x=X509_new()) == NULL)
			goto err;
		}
	else
		x= *x509p;

	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
		{
		abort();
		goto err;
		}
//	rsa=NULL;

	X509_set_version(x,2);
	ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
	X509_gmtime_adj(X509_get_notBefore(x),0);
	X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
	X509_set_pubkey(x,pk);

	name=X509_get_subject_name(x);

	X509_NAME_add_entry_by_txt(name,"C",
				MBSTRING_ASC, (unsigned char *)"TH", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"O",
				MBSTRING_ASC, (unsigned char *)"LocalSign", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name,"OU", 
				MBSTRING_ASC, (unsigned char *)"LocalSign Trusted Network", -1, -1, 0);
	//X509_NAME_add_entry_by_txt(name,"OU", 
	//  MBSTRING_ASC, (unsigned char *)"(C) 2013 LocalSign CA", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
	            MBSTRING_ASC, (unsigned char *)"LocalSign Root CA", -1, -1, 0);

	X509_set_issuer_name(x,name);

	add_ext(x, NID_subject_key_identifier, "hash");
    add_ext(x, NID_authority_key_identifier, "keyid");
    
	add_ext(x, NID_basic_constraints, "critical,CA:TRUE");
	add_ext(x, NID_key_usage, "critical,keyCertSign,cRLSign");

	//add_ext(x, NID_netscape_cert_type, "sslCA");

	//add_ext(x, NID_netscape_comment, "example comment extension");
    /*#ifndef CUSTOM_EXT
	{
		int nid;
		nid = OBJ_create("1.3.6.1.5.5.7.1.12", "Trusted", "Trusted Alias");
		printf("OBJ: %d \n", nid);
		X509V3_EXT_add_alias(nid, NID_undef | NID_netscape_ca_policy_url );
		printf("OBJ: %d \n", nid);
		add_ext(x, nid, "https://www.lexne.com/images/signature.gif");
	}
    #endif
    */
    
    #ifdef __STD__
    X509_alias_set1(x, (unsigned char *)"LocalSign ", 15); 
    X509_keyid_set1(x, (unsigned char *)"E0EACD85900EA98", 15);
    #endif
   
    //printf("> %s \n", X509_alias_get0(x, &len) );
    //printf("> %s \n", X509_keyid_get0(x, &len) );
    
    /////////////////////////////////////////////////////////////////////////////    
    object = ASN1_OBJECT_create(NID_server_auth, 
	      (unsigned char *)"serverAuth", strlen("serverAuth"),
	            "X55", "xxx" );
	if(object!=NULL) {   
      X509_add1_trust_object(x, object),
      X509_add1_reject_object(x, object),
      ASN1_OBJECT_free(object);
    } else
      printf("ERROR \n");
    
    /////////////////////////////////////////////////////////////////////////////
	object = ASN1_OBJECT_create(NID_client_auth , 
	      (unsigned char *)"clientAuth", strlen("clientAuth"),
	            "X56", "ccc" );
	if(object!=NULL){      
      X509_add1_trust_object(x, object),
      X509_add1_reject_object(x, object),
      ASN1_OBJECT_free(object);
    }else
      printf("ERROR \n");
	


	
	if (!X509_sign(x,pk,EVP_sha512())){
        printf("Error: x509 sign \n");
		goto err;
    }

	*x509p=x;
	*pkeyp=pk;
	return(1);
err:
    printf("ERROR: result status \n");
	return(0);
	}



int add_ext(X509 *cert, int nid, char *value)
	{
	X509_EXTENSION *ex;
	X509V3_CTX ctx;
	X509V3_set_ctx_nodb(&ctx);

	X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
	ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
	if (!ex)
		return 0;

	X509_add_ext(cert,ex,-1);
	X509_EXTENSION_free(ex);
	return 1;
	}
	

int new_x509_crl(X509_CRL **crl,X509 *x509, EVP_PKEY *pkey)
{
    X509_CRL *crlX= (*crl);
    X509_EXTENSION *ext;
    X509_REQ       *x;
	ASN1_TIME   *tmptm;
	int i=0;
	STACK_OF(X509_EXTENSION) *ex;
	 
    if(!crlX){
    	crlX = X509_CRL_new();
    }
    
    if(crlX){
       if (!X509_CRL_set_issuer_name(crlX, X509_get_subject_name(x509 ))){
       	  printf("Set Issuer Name CRL \n");
       }
       
       tmptm = ASN1_TIME_new();
		if (!tmptm){
			printf("ASN Time New \n");
		}
		X509_gmtime_adj(tmptm,0);
		X509_CRL_set_lastUpdate(crlX, tmptm);	
		if (!X509_time_adj(tmptm,(long)60*60*24*365 *4,NULL))
			{
			  printf("error setting CRL nextUpdate\n");
			 //BIO_puts(bio_err, "error setting CRL nextUpdate\n");
			//goto err;
			}
		X509_CRL_set_nextUpdate(crlX, tmptm);	

		ASN1_TIME_free(tmptm);
		
		X509_REVOKED *rev = 0;
		if(!rev){
			rev = X509_REVOKED_new();
		}
		//ASN1_INTEGER *tmpser = 0;
		//if( !tmpser ){
		//	 tmpser = M_ASN1_INTEGER_new();
		//}
	    //ASN1_INTEGER_set(tmpser, ASN1_INTEGER_get(tmpser));
	   
		X509_REVOKED_set_serialNumber(rev, X509_get_serialNumber(x509 ));
		X509_REVOKED_set_revocationDate(rev,X509_get_notAfter (x509 ) );
		X509_CRL_add0_revoked(crlX, rev);
	    //ASN1_INTEGER_free(tmpser);
		
		X509_CRL_sort(crlX);
		
		X509_CRL_verify(crlX, pkey );
		
		if (!X509_CRL_set_version(crlX, 1)){
		
			printf("error version 2 CRL \n");
	    }
      
      x = X509_to_X509_REQ(x509, pkey, EVP_md5());
      
	  //ex = X509_REQ_get_extensions(x);
      for (i=0; i<X509_get_ext_count(x509); i++){
        
        //i = X509_get_ext_by_NID(x509, NID_subject_key_identifier, -1);
        if((i >= 0)  && (ext = X509_get_ext(x509, i)))
	    printf("> %d \n", OBJ_obj2nid(X509_EXTENSION_get_object(ext)));
	    printf(">[%s] \n", OBJ_nid2sn(OBJ_obj2nid( X509_EXTENSION_get_object(ext) )));
	    printf("?[%s] \n", OBJ_nid2ln(OBJ_obj2nid( X509_EXTENSION_get_object(ext) )));
//	rintf(":\n"/);
	    X509V3_EXT_print_fp(stdout, ext, 0, 0);
	    printf("\n");
	    if(ext!=NULL){
	    	X509_CRL_add_ext(crlX, ext, -1);
	    }
	  }
		/*
		ex = new_crl_basic();
		if(ex){
		   X509_CRL_add_ext(crlX, ex, -1);
           X509_EXTENSION_free(ex);
        }else{
           printf("error : CRL BASIC\n");
        }
        
		ex = new_crl_key_usage();
        if(ex){
		   X509_CRL_add_ext(crlX, ex, -1);
           X509_EXTENSION_free(ex);
        }else{
           printf("error : CRL KEY USAGE\n");
        }
		*/
		X509_CRL_sign(crlX, pkey, EVP_sha1() );
			
        //PEM_write_bio_X509_CRL(crls , crlX );
       
        //BIO_free_all(crls);
    }
    *crl = crlX;
}



