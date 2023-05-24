
#include <localsign.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	X509 *x509;
	EVP_PKEY *pkey;
	PKCS7 *p7;
	PKCS7_SIGNER_INFO *si;
	BIO *in;
	BIO *data,*p7bio;
	char buf[1024*4];
	int i;
	int nodetach=0;
	X509_CRL *crl;
		
#ifndef OPENSSL_NO_MD2
	EVP_add_digest(EVP_md2());
#endif
#ifndef OPENSSL_NO_MD5
	EVP_add_digest(EVP_md5());
#endif
#ifndef OPENSSL_NO_SHA1
	EVP_add_digest(EVP_sha1());
#endif
#ifndef OPENSSL_NO_MDC2
	EVP_add_digest(EVP_mdc2());
#endif
    data=BIO_new(BIO_s_file());
    //BIO_set_fp(data,stdin,BIO_NOCLOSE);
    BIO_read_filename(data, "certs/caseniumsign.pem");
    
    BIO          *certs0= BIO_new_file("certs/localsign.crt", "r");
    BIO          *keys0= BIO_new_file("certs/localsign.key", "r");
	BIO          *bip = BIO_new_file("certs/casenium.p7b","w");  // *.p7s

    BIO          *certs1= BIO_new_file("certs/caseniumsign.crt", "r");
    BIO          *keys1= BIO_new_file("certs/caseniumsign.key", "r");
    
    BIO          *certs2= BIO_new_file("certs/casenium.crt", "r");
    BIO          *keys2= BIO_new_file("certs/casenium.key", "r");
	
	BIO          *crl0 = BIO_new_file("certs/localsign.crl", "r");
	crl = PEM_read_bio_X509_CRL(crl0, NULL,NULL,NULL);
	
	x509 = PEM_read_bio_X509(certs0, NULL, NULL, NULL);
    pkey = PEM_read_bio_PrivateKey(keys0, NULL,NULL,NULL);

    p7=PKCS7_new();
	PKCS7_set_type(p7,NID_pkcs7_signed);
	 
	si=PKCS7_add_signature(p7,x509,pkey,EVP_sha1());
	if (si == NULL) goto err;

	/* If you do this then you get signing time automatically added */
	PKCS7_add_signed_attribute(si, NID_pkcs9_contentType, V_ASN1_OBJECT,
						OBJ_nid2obj(NID_pkcs7_data));
    printf("------------------------------------------------------\n");
	/* we may want to add more */
	PKCS7_add_certificate(p7,x509);
	x509 = PEM_read_bio_X509(certs1, NULL, NULL, NULL);
    PKCS7_add_certificate(p7,x509);
    x509 = PEM_read_bio_X509(certs2, NULL, NULL, NULL);
    PKCS7_add_certificate(p7,x509);
    
    PKCS7_add_crl(p7, crl);
    //PKCS7_add_certificate(p7,x509);
	/* Set the content of the signed to 'data' */
	PKCS7_content_new(p7,NID_pkcs7_data);
    printf("------------------------------------------------------\n");
	if (!nodetach)
		PKCS7_set_detached(p7,1);
    printf("------------------------------------------------------\n");
	if ((p7bio=PKCS7_dataInit(p7,NULL)) == NULL) goto err;
    printf("------------------------------------------------------\n");
	for (;;)
		{
		i=BIO_read(data,buf,sizeof(buf));
		if (i <= 0) break;
		BIO_write(p7bio,buf,i);

	}
    printf("------------------------------------------------------\n");
	if (!PKCS7_dataFinal(p7,p7bio)) goto err;
	BIO_free(p7bio);
    printf("------------------------------------------------------\n");
	PEM_write_PKCS7(stdout,p7);
	
    printf("------------------------------------------------------\n");
    
    PEM_write_bio_PKCS7(bip, p7);
    
	PKCS7_free(p7);
    
	BIO_free(bip);
	
	//bip = BIO_new_file("certs\\lexne.p7s","r");
	
	
	
	//system("pause");
	exit(0);
err:
	ERR_load_crypto_strings();
	ERR_print_errors_fp(stderr);
	exit(1);
	
	system("pause");
	return 0;
}
