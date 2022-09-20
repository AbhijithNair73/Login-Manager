/*
 * RSASign.h
 *
 *  Created on: Sep 19, 2022
 *      Author: vfi
 */

#ifndef INCLUDE_RSASIGN_H_
#define INCLUDE_RSASIGN_H_

#include "PrivateInterface.h"

class RSASign: public IPrivate
{
	RSA * privateRSA;
	void createPrivateRSA(void);
public:
	RSASign();
	bool RSASignature(const unsigned char* Msg, size_t MsgLen, unsigned char** EncMsg,
			size_t* MsgLenEnc);
};
#endif /* INCLUDE_RSASIGN_H_ */
