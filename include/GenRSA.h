/*
 * GENRSA.h
 *
 *  Created on: Sep 19, 2022
 *      Author: Abhijith
 */

#ifndef INCLUDE_GENRSA_H_
#define INCLUDE_GENRSA_H_
#include <cstdio>
#include <openssl/rsa.h>
#include <openssl/pem.h>

class GenerateRSA
{
	string publicFileName;
	string privateFileName;
	bool generate_key();
	int updatePublicToPKCS8();
public:
	GenerateRSA(const string & pubfile = "private.pem", const string & privFile = "public.pem")
	{
	}

	int generateKeyPair()
	{
		if(!generate_key())
		{
			cout<<"Error in generating Key Pair"<<endl;
			return -1;
		}
		return updatePublicToPKCS8();
	}
	~GenerateRSA() = default;
};


bool GenerateRSA::generate_key()
{
	int	ret = 0;
	RSA	*r = NULL;
	BIGNUM *bne = NULL;
	BIO	*bp_public = NULL, *bp_private = NULL;

	int bits = 2048;
	unsigned long e = RSA_F4;

	do
	{
		// 1. generate rsa key
		bne = BN_new();
		ret = BN_set_word(bne,e);
		if(ret != 1){
			break;
		}

		r = RSA_new();
		ret = RSA_generate_key_ex(r, bits, bne, NULL);
		if(ret != 1){
			break;
		}

		// 2. save public key
		bp_public = BIO_new_file("public.pem", "w+");
		ret = PEM_write_bio_RSAPublicKey(bp_public, r);
		if(ret != 1){
			break;
		}

		// 3. save private key
		bp_private = BIO_new_file("private.pem", "w+");
		ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

	}while(false);
	// 4. free
	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(r);
	BN_free(bne);
//	cout << ""
	return (ret == 1);
}

int GenerateRSA::updatePublicToPKCS8()
{
	return system("openssl rsa -RSAPublicKey_in -in public.pem -pubout -out vipapub.pem > file.txt");
}

#endif /* INCLUDE_GENRSA_H_ */
