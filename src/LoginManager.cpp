//============================================================================
// Name        : LoginManager.cpp
// Author      : Abhijith Nair
// Version     :
// Copyright   : Your copyright notice
// Description : LoginManager in C++, Ansi-style
//============================================================================
#include "../include/LoginManager.h"
#include "../include/GenRSA.h"
#include "../include/RSASign.h"
#include "../include/RSAVerify.h"
#include <memory>
#include <map>
map<string, unsigned char *> keyStore;

void DisplayRegistration()
{
	char ch;
	while(ch != 'n' && ch !='N')
	{
		cout<<"For new registration, please choose an userid & password" <<endl;
		string userid = getUserId();
		unsigned char * hashedPassword = getUserLoginPassword();

		size_t userIdSize = userid.size();
		size_t messageLen = userIdSize+SHA256_DIGEST_LENGTH;
		unsigned char * message = new unsigned char[messageLen+1];

		memmove(message, userid.data(),userIdSize);
		message[userIdSize]='\0';

		memmove(message+userIdSize, hashedPassword, SHA256_DIGEST_LENGTH);
		message[messageLen]='\0';
		keyStore[userid] = message;
		delete hashedPassword;

		cout<<"Press 'n' for exiting the registration Menu"<<endl;
		cin>>ch;
		cout<<endl;
	}

}
string getFileContents(ifstream& File)
{
	string output;
    if (File)
    {
		string line;
		while ( getline (File,line) )
		{
		  output+=line;
		  output.push_back('\n');
		}
		return output;
    }
    else
    {
	return "ERROR File does not exist.";
    }
}

void header()
{
    ifstream fileRead("header.txt");
    string output = getFileContents(fileRead);
    cout << output << endl;
    fileRead.close();
}

void DisplayMainMenu()
{
    int option;

    do
    {
        system("clear"); // clear console.
        header();
        cout << "   Please choose your option." << endl;
        cout << "   1 : LOGIN" << endl;
        cout << "   2 : REGISTER" << endl;
        cout << "   3 : INFO" << endl;
        cout << "   4 : QUIT" << endl;
        cout << "   Option : ";
        cin >> option;

                switch(option)
                {
                    case 1:
                        cout << "   LOGIN \n";
//                        usleep(500);
//                        loginScreen();
                        option =4;
                        break;

                    case 2:
                        cout << "   REGISTER INITIALIZED...\n";
                        usleep(500);
                        system("clear"); // clear console.
                        header();
                        DisplayRegistration();
//                        option = 4;
                        break;

                    case 3:
                        cout << "   INFO INITIALIZED...\n";
                        usleep(500);
//                        infoScreen();
                        break;

                    case 4:
                        cout << "   QUIT INITIALIZED...\n";
                        usleep(500);
//                        exit(0);

                    default:
                        cout << "   INVALID OPTION.\n";
                        cout << "   Please choose an option from 1 to 4.\n";
                        usleep(500);
//                        mainMenu();
                        break;
                }
            } while (option != 4);


}

int main()
{
	DisplayMainMenu();
	string userid = getUserId();
	unsigned char * hashedPassword = getUserLoginPassword();

	GenerateRSA rsaObj;
	int result = rsaObj.generateKeyPair();
	if(result < 0)
	{
		cout<<"ERROR: Key Generation failed"<<endl;
		delete hashedPassword;
		return EXIT_SUCCESS;
	}
	size_t userIdSize = userid.size();
	size_t messageLen = userIdSize+SHA256_DIGEST_LENGTH;
	unsigned char * message = new unsigned char[messageLen+1];

	memmove(message, userid.data(),userIdSize);
	message[userIdSize]='\0';

	memmove(message+userIdSize, hashedPassword, SHA256_DIGEST_LENGTH);
	message[messageLen]='\0';

	delete hashedPassword;
	unsigned char* encMessage;
	size_t encMessageLength;
	RSASign signObj;
	signObj.RSASignature(message, messageLen,  &encMessage, &encMessageLength);


	// Verification by fetching data from keystore

	//if userid not found in database
	if(!(keyStore.count(userid)>0))
	{
		cout<<"userid not registered"<<endl;
		delete message;
		for(auto elem: keyStore)
		{
			delete elem.second;
		}
		free(encMessage);
		return 0;
	}

	unsigned char * actualResult = keyStore[userid];
	bool authentic;
	RSAVerify verifyObj;
	bool result1 =verifyObj.RSAVerifySignature(encMessage, encMessageLength, actualResult, messageLen, &authentic);
	if(result1 & authentic)
	{
		std::cout << "Authenticated" << std::endl;
	}
	else
	{
		std::cout << "Not Authentic" << std::endl;
	}
	delete message;
	for(auto elem: keyStore)
	{
		delete elem.second;
	}
	free(encMessage);
	return 0;
}
