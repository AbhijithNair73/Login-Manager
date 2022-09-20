/*
 * LoginManager.h
 *
 *  Created on: Sep 19, 2022
 *      Author: Abhijith
 */

#ifndef INCLUDE_LOGINMANAGER_H_
#define INCLUDE_LOGINMANAGER_H_
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <openssl/sha.h>
using namespace std;

int getch() {
    int ch;
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

unsigned char* getpass(const char *prompt, bool show_asterisk=true)
{
  const char BACKSPACE=127;
  const char RETURN=10;

  string password;
  unsigned char ch=0;

  cout <<prompt<<endl;
  while((ch=getch())!=RETURN || password.length() < 1)
    {
	  if(ch == RETURN)
		  continue;
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
    cout<<endl;
    unsigned char text[20]={0};
    std::copy(password.cbegin(), password.cend(), text);
	unsigned int len = strlen ((const char*) text);
	unsigned char * hash = new unsigned char[SHA256_DIGEST_LENGTH];
	SHA256 (text, len, hash);
  	return hash;
}

string getUserId()
{
	string userId;
	cout << "Please input userId: ";
	cin >> userId;
	return userId;
}

unsigned char * getUserLoginPassword()
{
	fflush(STDIN_FILENO);
	unsigned char * password=getpass("Please enter the password: ",true); // Show asterisks
	return password; // dont forgot to delete after calling.
}

#endif /* INCLUDE_LOGINMANAGER_H_ */
