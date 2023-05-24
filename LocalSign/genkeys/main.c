#include <localsign.h>
#define ISC_SHA1_DIGESTLENGTH 16
#define MS_CALLBACK 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
static void callback(int p, int n, void *arg);	
static int MS_CALLBACK dh_cb(int p, int n, BN_GENCB *cb);

int main(int argc, char *argv[]) {
	
	RSA      *rsa=NULL;
	DH       *dh = NULL;
	DSA      *dsa= NULL;
	EVP_PKEY *pk=NULL;
	EC_KEY   *eckey=NULL;
	EC_GROUP *group = NULL;
	BIO      *bio_err;
	BN_GENCB *cbx=NULL;
	int      nid;
    int      ret=0;

	unsigned char rand_array[ISC_SHA1_DIGESTLENGTH];
    char     *rand_str = "xxx";

	BIO      *keys = BIO_new_file("certs/localsign.key", "w");
	
    memset(rand_array, 0, sizeof(rand_array));
    memcpy(rand_array, rand_str, strlen(rand_str));

	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

	bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);
	
	if ((pk=EVP_PKEY_new()) == NULL){
		return 0;
	}
	rsa=RSA_generate_key(2048,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
		{
		abort();
		return 0;
		}
	rsa=NULL;
    cbx = BN_GENCB_new();
    if(cbx ==NULL){
        printf("ERROR eee ...........");
        return 0;
    }
	printf("XX ----------------------------------------------------------------------\n");
	RSA_print_fp(stdout,EVP_PKEY_get1_RSA(pk),0);
	PEM_write_bio_RSAPrivateKey(bio_err, EVP_PKEY_get0_RSA(pk), NULL, NULL, 0, NULL, NULL);
	printf("XZ ----------------------------------------------------------------------\n");
	BN_GENCB_set(cbx, dh_cb, bio_err);
	if(((dh = DH_new()) == NULL) || !DH_generate_parameters_ex(dh, 512, 5, cbx)){
        printf("ERROR: zzz..... \n");	   
        return 0;
    }
	printf("X0 ----------------------------------------------------------------------\n");
    DH_generate_key(dh);
	if (!EVP_PKEY_assign_DH(pk,dh))
	{
        printf("ERROR: pkey assign dh ..... \n");
		abort();
		return 0;
	}
		
	//DHparams_print(bio_err, dh);	
	//PEM_write_bio_DHparams(bio_err, dh);	
    printf("X1 ----------------------------------------------------------------------\n");
    
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////	
	////////////////////////////////////////////////////////////////////////////////////////
    #if OPENSSL_VERSION_NUMBER > 0x00908000L
    cbx=NULL; // rand_array // ISC_SHA1_DIGESTLENGTH
    if((dsa = DSA_new()) == NULL || !(ret = DSA_generate_parameters_ex(dsa, 2048, NULL,
					1, NULL, NULL, cbx))){
        DSA_free(dsa);
	    printf("ERROR: if xxx..... (%x)(%d) \n", dsa, ret);   
        return 0; 	
	}
    #else
	dsa = DSA_generate_parameters(2048, rand_array,
				      ISC_SHA1_DIGESTLENGTH, NULL, NULL,
				      NULL, NULL);
	if (dsa == NULL){
	    printf("ERROR: else xxx..... \n");   
        return 0; 	
	}
    #endif

	DSA_generate_key(dsa);
	
	if (!EVP_PKEY_assign_DSA(pk,dsa))
	{
        printf("ERROR: pkey assign dsa ..... \n");
		abort();
		return 0;
	}
		
	printf("X2 ----------------------------------------------------------------------\n");
	DSAparams_print(bio_err, dsa);
	DSA_print(bio_err, dsa, -1);
	PEM_write_bio_DSAPrivateKey(bio_err, dsa, NULL, NULL, 0, NULL ,NULL);
	
	/////////////////////////////////////////////////////////////////////////////////////////
	
	printf("X3 ----------------------------------------------------------------------\n");
	if(((eckey=EC_KEY_new())==NULL))
	  printf("ERROR: ccc............\n");
	nid = NID_X9_62_prime192v1;
	group = EC_GROUP_new_by_curve_name(nid);
	if (group == NULL)
	{
		printf("[ERR] new group name 'EC_KEY' \n");
	}	
	EC_GROUP_set_asn1_flag(group, 0); // OPENSSL_EC_NAMED_CURVE
	EC_GROUP_set_point_conversion_form(group, POINT_CONVERSION_COMPRESSED); 
		
	if (EC_KEY_set_group(eckey, group) == 0)
	{
		printf("[ERR] set group key.. 'EC_KEY'\n");
	}  
	if(!EC_KEY_generate_key(eckey)){
		printf("[ERR] generate key.. 'EC KEY'\n");
	}
	/*
	if (!EVP_PKEY_assign_EC_KEY(pk,eckey))
	{
		abort();
		return 0;
	}
	*/
	ECParameters_print(bio_err , eckey);
	EC_KEY_print(bio_err , eckey, 0);
	PEM_write_bio_ECPrivateKey(bio_err, eckey, NULL,
				NULL, 0, NULL, NULL);
	

	printf("X4 ----------------------------------------------------------------------\n");
	PEM_write_bio_PrivateKey(bio_err, pk, NULL,NULL,0, NULL,NULL);
    printf("X5 **********************************************************************\n");
	PEM_write_bio_PrivateKey(keys, pk , NULL, NULL, 0, NULL, NULL);
	
	BIO_free(keys);
	
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

static void callback(int p, int n, void *arg)
	{
	char c='B';

	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	fputc(c,stderr);
	}
	
static int MS_CALLBACK dh_cb(int p, int n, BN_GENCB *cb)
	{
	char c='*';

	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	BIO_write((BIO *)BN_GENCB_get_arg(cb),&c,1);
	(void)BIO_flush((BIO *)BN_GENCB_get_arg(cb));
#ifdef LINT
	p=n;
#endif
	return 1;
	}

