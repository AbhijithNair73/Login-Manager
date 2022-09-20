/*
 * RSAVerify.cpp
 *
 *  Created on: Sep 19, 2022
 *      Author: Abhijith
 */
#include "../include/RSAVerify.h"

RSAVerify::RSAVerify()
{
	publicRSA = NULL;
	UpdatePublicKey("vipapub.pem");
	createPublicRSA();
}

void RSAVerify::createPublicRSA(void)
{
	  //FixME: check if public key is available
	  const char* c_string = getPublicKey();
	  BIO *keybio = BIO_new_mem_buf((void*)c_string, -1);
	  if (keybio==NULL) {
	      return;
	  }
	  publicRSA = PEM_read_bio_RSA_PUBKEY(keybio, &publicRSA,NULL, NULL);
}

bool RSAVerify::RSAVerifySignature(unsigned char* MsgHash, size_t MsgHashLen, const unsigned char* Msg,
	                         size_t MsgLen, bool* Authentic)
{
	  *Authentic = false;
	  EVP_PKEY* pubKey  = EVP_PKEY_new();
	  EVP_PKEY_assign_RSA(pubKey, publicRSA);
	  EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_new();

	  if (EVP_DigestVerifyInit(m_RSAVerifyCtx,NULL, EVP_sha256(),NULL,pubKey)<=0) {
	    return false;
	  }
	  if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
	    return false;
	  }
	  int AuthStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen);
	  if (AuthStatus==1)
	  {
	    *Authentic = true;
	    EVP_MD_CTX_reset(m_RSAVerifyCtx);
	    return true;
	  }
	  else if(AuthStatus==0)
	  {
	    *Authentic = false;
	    EVP_MD_CTX_reset(m_RSAVerifyCtx);
	    return true;
	  }
	  else
	  {
	    *Authentic = false;
	    EVP_MD_CTX_reset(m_RSAVerifyCtx);
	    return false;
	  }
}




