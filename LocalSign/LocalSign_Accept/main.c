/* Certificate creation. Demonstrates some certificate related
 * operations.
 */

#include <localsign.h>

X509_EXTENSION *new_authkey(X509 *imp);

int mkcert(X509 **x509x,X509 **x509p , EVP_PKEY **pkeyp,
   EVP_PKEY **nkeyp, int bits, int serial, int days);
int add_ext(X509 *cert, int nid, char *value);
int new_x509_crl(X509_CRL **crl,X509 *x509, EVP_PKEY *pkey);

X509_EXTENSION *new_subjectauthkey(X509 *imp);
X509_EXTENSION *new_subject_alt(char *name);
X509_EXTENSION *new_cert_policies(char *stringc);

int main(int argc, char **argv)
	{
	BIO      *bio_err;
	X509     *x509=NULL, *px5s=NULL;
	EVP_PKEY *pkey=NULL, *nkey=NULL;
	X509_REQ *xreq=NULL;
	X509_CRL *crl=NULL;
	
    BIO       *certs = BIO_new_file("certs/casenium.crt", "w");
    BIO       *lkeys = BIO_new_file("certs/casenium.key", "w");
    BIO       *keys  = BIO_new_file("certs/caseniumsign.key", "r");
    
    BIO       *imps  = BIO_new_file("certs/caseniumsign.crt", "r");
    BIO       *reqs  = BIO_new_file("certs/casenium.txt", "w");
    //BIO       *crls  = BIO_new_file("certs\\localsign.crl", "w");
    //BIO       *pubs  = BIO_new_file("certs\\localsign.cet", "w");
    
	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

	bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);

    pkey = PEM_read_bio_PrivateKey(keys, NULL, NULL, NULL);
    px5s = PEM_read_bio_X509(imps, NULL, NULL, NULL);
	mkcert(&px5s, &x509,&pkey, &nkey,2048,0xEF59EA32,365*2);

	//RSA_print_fp(stdout,pkey->pkey.rsa,0);
	X509_print_fp(stdout,x509);

	//PEM_write_PrivateKey(stdout,pkey,NULL,NULL,0,NULL, NULL);
	PEM_write_X509(stdout,x509);
    X509_ocspid_print(bio_err, x509);
    
    PEM_write_bio_PrivateKey(lkeys, nkey, NULL,NULL, 0,NULL,NULL );
    PEM_write_bio_X509(certs, x509 );
    
    xreq = X509_to_X509_REQ(x509, pkey, EVP_sha1() );
    PEM_write_bio_X509_REQ(reqs, xreq);
    
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

int mkcert(X509 **x509x,X509 **x509p, EVP_PKEY **pkeyp, 
                  EVP_PKEY **nkeyp, int bits, int serial, int days)
	{
	X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	int len;
	ASN1_OBJECT *object;
	X509_EXTENSION *ex;
	 	
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
	rsa=NULL;
	*nkeyp=pk;

	X509_set_version(x,2);
	ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
	X509_gmtime_adj(X509_get_notBefore(x),0);
	X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
	X509_set_pubkey(x,pk);
  
  	name=X509_get_subject_name(*x509x);
    X509_set_issuer_name(x,name);
  
	name=X509_get_subject_name(x);

    #ifdef __SS_MM_
	X509_NAME_add_entry_by_txt(name,"C",
				MBSTRING_ASC, (unsigned char *)"TH", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"O",
				MBSTRING_ASC, (unsigned char *)"LocalSign", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name,"OU", 
				MBSTRING_ASC, (unsigned char *)"LocalSign Trusted Network", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"OU", 
	  MBSTRING_ASC, (unsigned char *)"(C) 2021 LocalSign - SSL CA", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
				MBSTRING_ASC, 
		(unsigned char *)"www.casenium.com", -1, -1, 0);
    #else
    
     X509_NAME_add_entry_by_txt(name,"1.3.6.1.4.1.311.60.2.1.3",
				MBSTRING_ASC, (unsigned char *)"TH", -1, -1, 0);
	 X509_NAME_add_entry_by_txt(name,"1.3.6.1.4.1.311.60.2.1.2",
				MBSTRING_ASC, (unsigned char *)"AmphoeMoung", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name,"O",
				MBSTRING_ASC, (unsigned char *)"LocalSign", -1, -1, 0);
				
    X509_NAME_add_entry_by_txt(name,"C",
				MBSTRING_ASC, (unsigned char *)"TH", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"ST",
				MBSTRING_ASC, (unsigned char *)"Khonkaen", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name,"L",
				MBSTRING_ASC, (unsigned char *)"Ban Khok Si", -1, -1, 0);			
	
    X509_NAME_add_entry_by_txt(name,"2.5.4.15", 
	  MBSTRING_ASC, (unsigned char *)"Private Organization", -1, -1, 0);
	  
    X509_NAME_add_entry_by_NID(name, NID_serialNumber, 
          MBSTRING_ASC, (unsigned char *)"3898362", -1, -1, 0);
    //X509_NAME_add_entry_by_txt(name,"SERIALNUMBER", 
	//  MBSTRING_ASC, (unsigned char *)"3898362", -1, -1, 0);
	  
    X509_NAME_add_entry_by_txt(name,"OU", 
	  MBSTRING_ASC, (unsigned char *)"LocalSign Public Certification Authority", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
				MBSTRING_ASC, 
		(unsigned char *)"*.casenium.com", -1, -1, 0);
    
    
    #endif
    
	X509_set_subject_name(x,name);

	
    //Unknown Key Usage (2.16.840.1.113730.4.1)
    //Unknown Key Usage (2.16.840.1.113733.1.8.1)
    add_ext(x, NID_subject_alt_name, "DNS:www.casenium.com,DNS:casenium.com,DNS:*.casenium.com");
    add_ext(x, NID_basic_constraints, "CA:FALSE");
	add_ext(x, NID_crl_distribution_points,"URI:http://www.casenium.com/casenium.crl");
    
	ex = new_cert_policies("2.16.840.1.113733.1.7.23.6");
    if(ex){
      X509_add_ext(x, ex, -1);
	  X509_EXTENSION_free(ex);
    }else{
       printf("error : new_cert_policies\n");
    }
    //add_ext(x, NID_ext_key_usage,"serverAuth,clientAuth" //");//"msSGC,nsSGC");
    //                    ",codeSigning,SN_email_protect,timeStamping");
    
	add_ext(x, NID_ext_key_usage,
        "serverAuth,clientAuth,nsSGC,msSGC");//"msSGC,nsSGC");
    
    ex =new_authkey(*x509x);
	if(ex == NULL){
		printf("ERROR : new  , NID_private_key_usage_period \n");
	}else{
	  X509_add_ext(x, ex, -1);
	  X509_EXTENSION_free(ex);
	}  
    
    add_ext(x, NID_info_access , "caIssuers;URI:http://www.casenium.com/casenium.crt,"
                                 "OCSP;URI:http://www.casenium.com:8080/");
    #ifdef __CCS_                             
    add_ext(x, NID_netscape_cert_type ,"server,client,sslCA");
    #endif
    
	add_ext(x, NID_key_usage, "critical,keyEncipherment,digitalSignature");
    
    /*    
    ex =new_subject_alt("ClassEVS2048-12-2");
	if(ex == NULL){
		printf("ERROR : new  , NID_private_key_usage_period \n");
	}else{
	  X509_add_ext(x, ex, -1);
	  X509_EXTENSION_free(ex);
	}  
    */
    
	//add_ext(x, NID_server_auth, "sslserver" );
	
    //add_ext(x, NID_subject_key_identifier, "hash");
     #ifdef __CCS_
    ex = new_subjectauthkey(x);
    if(ex == NULL){
		printf("ERROR : new  , new_subjectauthkey \n");
	}else{
	  X509_add_ext(x, ex, -1);
	  X509_EXTENSION_free(ex);
	} 
    #endif  
  
	
	 //,emailProtection,OCSPSigning
    //add_ext(x, NID_authority_key_identifier, "keyid");
	//add_ext(x, NID_netscape_cert_type, "sslCA");

	//add_ext(x, NID_netscape_comment, "example comment extension");
    #ifndef CUSTOM_EXT
	{
		int nid;
		nid = OBJ_create("1.3.6.1.4.1.11129.2.4.2", "Trusted", "Trusted Alias");
        //nid = OBJ_create("1.3.6.1.5.5.7.1.12", "Trusted", "Trusted Alias");
		printf("OBJ: %d \n", nid);
		X509V3_EXT_add_alias(nid, NID_undef | NID_netscape_ca_policy_url );
		printf("OBJ: %d \n", nid);
		add_ext(x, nid, "https://www.casenium.com/images/localsign.gif");
	}
    #endif
    
    
    #ifdef __STD__
    X509_alias_set1(x, (unsigned char *)"CaseniumSign, Inc.", 15); 
    X509_keyid_set1(x, (unsigned char *)"E0EACD85900EA98", 15);
    #endif
   
    //printf("> %s \n", X509_alias_get0(x, &len) );
    //printf("> %s \n", X509_keyid_get0(x, &len) );
    
    /////////////////////////////////////////////////////////////////////////////    
    object = ASN1_OBJECT_create(NID_server_auth, 
	      (unsigned char *)"serverAuth", strlen("serverAuth"),
	            "X55", "xxx" );
	if(object!=NULL){      
      X509_add1_trust_object(x, object),
      X509_add1_reject_object(x, object),
      ASN1_OBJECT_free(object);
    }else
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
	

    pk= *pkeyp;
	
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
	    printf("> %d \n", OBJ_obj2nid( X509_EXTENSION_get_object(ext) ));
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


X509_EXTENSION *new_subjectauthkey(X509 *imp)
{
    X509_EXTENSION    *ext,*zext;
    ASN1_OCTET_STRING *ext_oct = NULL, *pk=NULL;
    AUTHORITY_KEYID *akeyid;
    int                i;
    unsigned char pkey_dig[EVP_MAX_MD_SIZE];
    unsigned int diglen;
    
do{  
    if(imp==NULL){
        printf("[%s] ASN1_OCTET_STRING_set failed.,", __FILE__, __FUNCTION__, __LINE__);
        break;
    }
    pk = X509_EXTENSION_get_data(X509_get0_extensions(imp));
    if (!pk) {
        X509V3err(X509V3_F_S2I_SKEY_ID, X509V3_R_NO_PUBLIC_KEY);
        printf("[%s] ASN1_OCTET_STRING_set failed.,", __FILE__, __FUNCTION__, __LINE__);
        break;
    }

    if (!EVP_Digest
        (pk->data, pk->length, pkey_dig, &diglen, EVP_sha1(), NULL)){
        printf("[%s] ASN1_OCTET_STRING_set failed.,", __FILE__, __FUNCTION__, __LINE__);
        break;
    }

    
    if ((ext_oct = ASN1_OCTET_STRING_new()) == NULL)
    {
       printf("[%s] create extension \n", __FILE__, __FUNCTION__, __LINE__); 
       break;
    }
    
    
    
    if (!ASN1_OCTET_STRING_set(ext_oct, pkey_dig, diglen)) {
        X509V3err(X509V3_F_S2I_SKEY_ID, ERR_R_MALLOC_FAILURE);
        printf("[%s] ASN1_OCTET_STRING_set failed.,", __FILE__, __FUNCTION__, __LINE__);
        break;
    }
    
    /*
    //ASN1_STRING_set(ext_oct, zext->object->data , zext->object->length);
    //;
    ext_oct = (ASN1_OCTET_STRING*)X509V3_EXT_d2i(zext);
    if(ext_oct==NULL){
       printf("X509V3_EXT_d2i \n", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    if ((akeyid = AUTHORITY_KEYID_new()) == NULL)
    {
       printf("AUTHORITY_KEYID_new \n", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    
    akeyid->keyid = ext_oct;
    */
    
    ext = X509V3_EXT_i2d(NID_subject_key_identifier ,  0, ext_oct); 
   // ext = X509_EXTENSION_create_by_NID(NULL, NID_authority_key_identifier, 
    //      0, akeyid);
          
    if(ext==NULL){
       printf("[%s] create extension \n", __FILE__, __FUNCTION__, __LINE__); 
       break;
    }
}while(0);

    return ext;
}

X509_EXTENSION *new_authkey(X509 *imp)
{
    X509_EXTENSION    *ext,*zext;
    ASN1_OCTET_STRING *ext_oct = NULL;
    AUTHORITY_KEYID *akeyid;
    int                i;
    
do{  
    printf("new: [%s]\n", __FUNCTION__); 
    //if(imp->skid!=NULL){
    //  printf("[%s]\n",  imp->skid->data );
    //}
    i = X509_get_ext_by_NID(imp, NID_subject_key_identifier, -1);
    zext = X509_get_ext(imp, i);
    if(zext!=NULL){
       
       printf("read match ..[%s]\n", __FUNCTION__); 
    }
    
    
    if ((ext_oct = ASN1_OCTET_STRING_new()) == NULL)
    {
       printf("[%s] create extension \n", __FILE__, __FUNCTION__, __LINE__); 
       break;
    }
    //ASN1_STRING_set(ext_oct, zext->object->data , zext->object->length);
    //;
    ext_oct = (ASN1_OCTET_STRING*)X509V3_EXT_d2i(zext);
    if(ext_oct==NULL){
       printf("X509V3_EXT_d2i \n", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    if ((akeyid = AUTHORITY_KEYID_new()) == NULL)
    {
       printf("AUTHORITY_KEYID_new \n", __FILE__, __FUNCTION__, __LINE__);
       break;
    }
    
    akeyid->keyid = ext_oct;
    
    
    ext = X509V3_EXT_i2d(NID_authority_key_identifier,  0, akeyid); 
   // ext = X509_EXTENSION_create_by_NID(NULL, NID_authority_key_identifier, 
    //      0, akeyid);
          
    if(ext==NULL){
       printf("[%s] create extension \n", __FILE__, __FUNCTION__, __LINE__); 
       break;
    }
}while(0);

    return ext;
}


X509_EXTENSION *new_cert_policies(char *stringc)
{
    STACK_OF(POLICYINFO) *pols = 0;
   	POLICYQUALINFO *qual;
    ASN1_OBJECT *obj;
    USERNOTICE *note;
    NOTICEREF *nref;
    STACK_OF(CONF_VALUE) *nos;
    CONF_VALUE *cnf;
	ASN1_INTEGER *aint;
	int i=0;
    //USERNOTICE *not;
    char url[1024],buffer[1024];
    strcpy(url, "https://www.casenium.com/cps");
    //2.16.840.1.113733.1.7.1.8,SN_any_policy
    if(!(obj = OBJ_txt2obj(stringc, 0))) {
       X509V3err(X509V3_F_R2I_CERTPOL,X509V3_R_INVALID_OBJECT_IDENTIFIER);
	  // X509V3_conf_err(cnf);
	}
    
    if(!pols)
		pols = sk_POLICYINFO_new_null();
	POLICYINFO *pol = POLICYINFO_new();
	pol->policyid = obj;
	//pol->STACK_OF()
 
    if(!pol->qualifiers) pol->qualifiers = sk_POLICYQUALINFO_new_null();
	if(!(qual = POLICYQUALINFO_new())) printf("Error: 1-000\n");
	//if(!sk_POLICYQUALINFO_push(pol->qualifiers, qual)) printf("Error: 2.000\n");
	qual->pqualid = OBJ_nid2obj(NID_id_qt_cps);
	qual->d.cpsuri = ASN1_IA5STRING_new();
	if(!ASN1_STRING_set(qual->d.cpsuri, url , strlen(url))) printf("Error: 3.000\n");
    //if(!sk_POLICYQUALINFO_push(pol->qualifiers, qual))
     //   return 0;
    //qual->pqualid = OBJ_nid2sn(NID_id_qt_unotice);
    //qual->
    if(!sk_POLICYQUALINFO_push(pol->qualifiers, qual))
           return 0;
    
    if(!(qual = POLICYQUALINFO_new())) printf("error: 000-43543\n");
    
    qual->pqualid = OBJ_nid2obj(NID_id_qt_unotice);  
    if(!(note = USERNOTICE_new())) printf("error: 43-43543\n");
    
    qual->d.usernotice = note;
        
		
		strcpy(buffer, " LocalSign Trusted Network .\r\n");
		strcat(buffer, "\r\n");      
        strcat(buffer," Copyright (c) 2021 LocalSign - Casenium, Inc.");
        
    note->exptext = ASN1_VISIBLESTRING_new();
	if(!ASN1_STRING_set(note->exptext, buffer,
						 strlen(buffer))) printf("error: ccxv");
    
    if(!(note = USERNOTICE_new())) printf("error: 20-344343\n");
	if(!note->noticeref) {
		if(!(nref = NOTICEREF_new())) printf("error: csfs\n");
		note->noticeref = nref;
	} else { nref = note->noticeref; }
	
	strcpy(buffer,"Casenium Technology");
    nref->organization->type = V_ASN1_VISIBLESTRING;
	if(!ASN1_STRING_set(nref->organization, buffer,
						 strlen(buffer))) printf("Error: ds-43543\n");
    strcpy(buffer,"32");
    nos = X509V3_parse_list(buffer);
    for( i = 0; i < sk_CONF_VALUE_num(nos); i++) {
		cnf = sk_CONF_VALUE_value(nos, i);
		if(!(aint = s2i_ASN1_INTEGER(NULL, cnf->name))) {
			X509V3err(X509V3_F_NREF_NOS,X509V3_R_INVALID_NUMBER);
			printf("error: appx re-fsd\n");
		}
		if(!sk_ASN1_INTEGER_push(nref->noticenos , aint)) printf("error : cxcx\n");
	}
    /*note->noticeref->organization; 
    note->noticeref = nref;
		strcpy(buffer,"Lexne ,inc.");
	nref->organization->type = V_ASN1_VISIBLESTRING;
	if(!ASN1_STRING_set(nref->organization, buffer,
						 strlen(buffer))) printf("error: cdssss");
   */
        
    if(!sk_POLICYQUALINFO_push(pol->qualifiers, qual))
        return 0;
    
	sk_POLICYINFO_push(pols, pol);
        
	if(!pols)
		return 0;

	X509_EXTENSION *ex = X509V3_EXT_i2d(NID_certificate_policies, 0, pols); // 0 = not critical
	sk_POLICYINFO_pop_free(pols, POLICYINFO_free);
	return ex;
}; 

X509_EXTENSION *new_usage_period(void)
{
	PKEY_USAGE_PERIOD *usage = 0;

    usage = (PKEY_USAGE_PERIOD *) malloc(sizeof( PKEY_USAGE_PERIOD ) * 2);
	//ASN1_GENERALIZEDTIME x;
	if(usage->notAfter == NULL || !usage->notBefore){
		usage->notAfter = ASN1_GENERALIZEDTIME_new();
		usage->notBefore = ASN1_GENERALIZEDTIME_new();
	}
	
	if(!usage->notAfter || !usage->notBefore ){
		printf("ERROR: Create Allocate Memory \n");
		return NULL;
	}else{
		printf("STATUS: create allocate memory \n");
		usage->notBefore = ASN1_GENERALIZEDTIME_set(NULL,time(NULL));
		usage->notAfter = ASN1_GENERALIZEDTIME_set(NULL,time(NULL)+2);
		//ASN1_GENERALIZEDTIME_print(stdout , usage->notBefore);
	}
	
	if(!usage){
	  printf("ERROR: Create Interface Externsion.. \n");
	  return NULL;
    }
	X509_EXTENSION *ex = X509V3_EXT_i2d(NID_private_key_usage_period, 0, usage );
	return ex;
}
X509_EXTENSION *new_subject_alt(char *name){
    GENERAL_NAME *gen = NULL;
    GENERAL_NAMES *gens = NULL;
    X509_NAME *nm;
    X509 *x;
    
    if(!(gens = sk_GENERAL_NAME_new_null())) {
		X509V3err(X509V3_F_V2I_ISSUER_ALT,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
    
    if(!(gen = GENERAL_NAME_new())) printf("new gen \n");
     if(!(x = X509_new())) printf("init x509 new\n");
     
     nm=X509_get_subject_name(x);
     X509_NAME_add_entry_by_txt(nm,"CN",
				MBSTRING_ASC, (u_char *) name , -1, -1, 0);
     X509_set_subject_name(x, nm);
     
    gen->d.dirn = nm;
    gen->type = GEN_DIRNAME;
    
    //printf("xxx");
    sk_GENERAL_NAME_push(gens, gen);
    
    X509_EXTENSION *ex = X509V3_EXT_i2d(NID_subject_alt_name, 0, gens); // 0 = not critical
	
	//M_ASN1_OCTET_STRING_free(ikeyid);
    
    return ex;
}	

