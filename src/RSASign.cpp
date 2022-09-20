/*
 * RSASign.cpp
 *
 *  Created on: Sep 19, 2022
 *      Author: Abhijith
 */
#include "../include/RSASign.h"

RSASign::RSASign()
{
	UpdatePrivateKey("private.pem");
	privateRSA = NULL;
	createPrivateRSA();
}

void RSASign::createPrivateRSA(void)
{
	//FixME: check if private key is available
	const char* c_string = getPrivateKey();
	BIO * keybio = BIO_new_mem_buf((void*)c_string, -1);
	if (keybio==NULL) {
		return;
	}
	privateRSA = PEM_read_bio_RSAPrivateKey(keybio, &privateRSA, NULL, NULL);
}

bool RSASign::RSASignature(const unsigned char* Msg, size_t MsgLen, unsigned char** EncMsg,
	                size_t* MsgLenEnc)
{
	  EVP_MD_CTX* m_RSASignCtx = EVP_MD_CTX_new();
	  EVP_PKEY* priKey  = EVP_PKEY_new();
	  EVP_PKEY_assign_RSA(priKey, privateRSA);
	  if (EVP_DigestSignInit(m_RSASignCtx,NULL, EVP_sha256(), NULL,priKey)<=0) {
	      return false;
	  }
	  if (EVP_DigestSignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0) {
	      return false;
	  }
	  if (EVP_DigestSignFinal(m_RSASignCtx, NULL, MsgLenEnc) <=0) {
	      return false;
	  }
	  *EncMsg = (unsigned char*)malloc(*MsgLenEnc);
	  if (EVP_DigestSignFinal(m_RSASignCtx, *EncMsg, MsgLenEnc) <= 0) {
	      return false;
	  }
	  EVP_MD_CTX_reset(m_RSASignCtx);
	  return true;
}


