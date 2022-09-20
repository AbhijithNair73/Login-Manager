/*
 * PrivateInterface.h
 *
 *  Created on: Sep 19, 2022
 *      Author: vfi
 */

#ifndef INCLUDE_PRIVATEINTERFACE_H_
#define INCLUDE_PRIVATEINTERFACE_H_
#include <string>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <fstream>
class IPrivate
{
	std::string privateKey;
public:
//	void UpdatePrivateKey( const std::string & privateFile);
//	const char * getPrivateKey() const;
//	virtual ~IPrivate() = 0;
	void UpdatePrivateKey( const std::string & privateFile)
	{
		std::ifstream fpriv(privateFile.c_str());
		if(fpriv)
		{
			privateKey.assign( (std::istreambuf_iterator<char>(fpriv) ),
					(std::istreambuf_iterator<char>() ) );
			privateKey.push_back('\0');
		}
	}

	const char * getPrivateKey() const { return privateKey.c_str(); }

	~IPrivate() {}
};



#endif /* INCLUDE_PRIVATEINTERFACE_H_ */
