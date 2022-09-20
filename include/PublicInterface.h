/*
 * PublicInterface.h
 *
 *  Created on: Sep 19, 2022
 *      Author: Abhijith
 */

#ifndef INCLUDE_PUBLICINTERFACE_H_
#define INCLUDE_PUBLICINTERFACE_H_
#include <string>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <fstream>
class IPublic
{
	std::string publicKey;
public:
	const char * getPublicKey() const { return publicKey.c_str(); }

	void UpdatePublicKey( const std::string & publicFile)
	{
		std::ifstream fpub(publicFile.c_str());
		if(fpub)
		{
			publicKey.assign( (std::istreambuf_iterator<char>(fpub) ),
					(std::istreambuf_iterator<char>() ) );
		}
	}

	~IPublic() {}
};

#endif /* INCLUDE_PUBLICINTERFACE_H_ */
