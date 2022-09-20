/*
 * RSAVerify.h
 *
 *  Created on: Sep 19, 2022
 *      Author: Abhijith
 */

#ifndef INCLUDE_RSAVERIFY_H_
#define INCLUDE_RSAVERIFY_H_
#include "PublicInterface.h"

class RSAVerify: public IPublic
{
	RSA * publicRSA;
	void createPublicRSA(void);
public:
	RSAVerify();
	bool RSAVerifySignature(unsigned char* MsgHash, size_t MsgHashLen, const unsigned char* Msg,
	                         size_t MsgLen, bool* Authentic);
};

#endif /* INCLUDE_RSAVERIFY_H_ */
