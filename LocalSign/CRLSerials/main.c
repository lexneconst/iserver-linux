#include <localsign.h>

int new_x509_crl(X509_CRL **crl,X509 *x509, X509 *certs, X509 *certs0, EVP_PKEY *pkey);
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
BIO *bio_err;
int main(int argc, char *argv[]) {
	X509 *x5090=NULL,*x5091=NULL, *x5092=NULL;
	EVP_PKEY *pkeys=NULL;
	X509_CRL *crl=NULL;
		
	BIO       *certs0 = BIO_new_file("certs/localsign.crt", "r");
    BIO       *certs1  = BIO_new_file("certs/caseniumsign.crt", "r");
    BIO       *certs2  = BIO_new_file("certs/casenium.crt", "r");
    BIO       *keys  = BIO_new_file("certs/casenium.key", "r");
	BIO       *crls  = BIO_new_file("certs/localsign.crl", "w");
    
    x5090 = PEM_read_bio_X509(certs0, NULL,NULL,NULL);
    x5091 = PEM_read_bio_X509(certs1,NULL,NULL,NULL);
    x5092 = PEM_read_bio_X509(certs2,NULL,NULL,NULL);
    pkeys = PEM_read_bio_PrivateKey(keys,NULL,NULL,NULL);
    
	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);
		bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);
	
    new_x509_crl(&crl, x5090, x5091, x5092, pkeys);
    PEM_write_bio_X509_CRL(crls , crl );
	
	X509_free(x5090);
	X509_free(x5091);
	X509_free(x5092);
	EVP_PKEY_free(pkeys);
    
	
    BIO_free(certs0);
    BIO_free(certs1);
    BIO_free(certs2);
    BIO_free(keys);
    BIO_free(crls);    
    
    #ifndef OPENSSL_NO_ENGINE
	ENGINE_cleanup();
#endif
	CRYPTO_cleanup_all_ex_data();
    #ifdef DEBUG_TEST
	CRYPTO_mem_leaks(bio_err);
    #endif
	BIO_free(bio_err);
	
	//system("pause");
    
	return 0;
}

int new_x509_crl(X509_CRL **crl,X509 *x509, X509 *certs, X509 *certs0, EVP_PKEY *pkey)
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
		
		X509_REVOKED *rev = 0,*rev0 = 0, *rev1 = 0;
		if(!rev){
			rev = X509_REVOKED_new();
		}
		if(!rev0){
			rev0 = X509_REVOKED_new();
		}
		if(!rev1){
			rev1 = X509_REVOKED_new();
		}
		//ASN1_INTEGER *tmpser = 0;
		//if( !tmpser ){
		//	 tmpser = M_ASN1_INTEGER_new();
		//}
	    //ASN1_INTEGER_set(tmpser, ASN1_INTEGER_get(tmpser));
	   
		X509_REVOKED_set_serialNumber(rev, X509_get_serialNumber(x509 ));
		X509_REVOKED_set_revocationDate(rev,X509_get_notAfter (x509 ) );
		X509_CRL_add0_revoked(crlX, rev);
		
		X509_REVOKED_set_serialNumber(rev0, X509_get_serialNumber(certs ));
		X509_REVOKED_set_revocationDate(rev0,X509_get_notAfter (certs ) );
		X509_CRL_add0_revoked(crlX, rev0);
	    
		X509_REVOKED_set_serialNumber(rev1, X509_get_serialNumber(certs0 ));
		X509_REVOKED_set_revocationDate(rev1,X509_get_notAfter (certs0 ) );
		X509_CRL_add0_revoked(crlX, rev1);
		//ASN1_INTEGER_free(tmpser);
		
		X509_CRL_sort(crlX);
		
		X509_CRL_verify(crlX, pkey );
		
		if (!X509_CRL_set_version(crlX, 1)){
		
			printf("error version 2 CRL \n");
	    }
      
      x = X509_to_X509_REQ(x509, pkey, EVP_md5());
      
	  //ex = X509_REQ_get_extensions(x);
	  /*
      for (i=0; i<X509_get_ext_count(x509); i++){
        
        //i = X509_get_ext_by_NID(x509, NID_subject_key_identifier, -1);
        if((i >= 0)  && (ext = X509_get_ext(x509, i)))
	    printf("> %d \n", OBJ_obj2nid(ext->object));
	    printf(">[%s] \n", OBJ_nid2sn(OBJ_obj2nid(ext->object)));
	    printf("?[%s] \n", OBJ_nid2ln(OBJ_obj2nid(ext->object)));
//	rintf(":\n"/);
	    X509V3_EXT_print_fp(stdout, ext, 0, 0);
	    printf("\n");
	    if(ext!=NULL){
	    	X509_CRL_add_ext(crlX, ext, -1);
	    }
	  }*/
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


