/* A simple set of book class.

Author: Mark Young

  * @ID:				$Id: set_of_books.h 127 2008-05-13 19:26:21Z  $
  * @lastmodified    	$Date: 2008-05-13 14:26:21 -0500 (Tue, 13 May 2008) $ 
  * @version         	$Revision: 127 $ 

*/

#ifndef H_BOOKS
#define H_BOOKS

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>


#include "Accounts.h"

//package libraries to include
#include "lib/tinyxml/tinyxml.h"
#include "lib/strextra/Strextra.h"

using namespace std;

class Books {
public:
	//default contructor
	Books ();
	//full constructor
	Books (string, string);
	Books (TiXmlElement *);


    	string name, memo;
	string mainBalance;
	
		
	Category categories;

	void listAccounts();
	void openAccount(string);
	void showAccount();
	void insertAccount(Accounts );
	void insertAccount(string, string, string);
	void insertAccountByHand();
	
	bool read(string) ; 
	bool write(string); 	
	
	void listCat();
	void addSubCat(Category, Category);
	
	TiXmlElement * getXML();
	
	
	
private:
	TiXmlDocument BookXML;
	void setXML();
} ;

#endif
