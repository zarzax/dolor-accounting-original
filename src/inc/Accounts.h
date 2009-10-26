/* Accounts header file.

Author: Mark Young

  * @ID:				$Id: Accounts.h 111 2008-05-09 21:52:45Z youn0624 $
  * @lastmodified    	$Date: 2008-05-09 16:52:45 -0500 (Fri, 09 May 2008) $ 
  * @version         	$Revision: 111 $ 

*/
#ifndef H_ACCOUNTS
#define H_ACCOUNTS

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>


#include "Transaction.h" 
#include "Category.h" 

//package libraries to include
//#include "lib/cvsgetline/cvsgetline.h"
#include "lib/tinyxml/tinyxml.h"
//#include "lib/tinyxpath/xpath_static.h"
#include "lib/strextra/Strextra.h" 

using namespace std;

class Accounts {
public:
	//default contructor
	Accounts ();
	//full constructors
	Accounts (string, string, string);
	Accounts (TiXmlElement*);

	//variables
	string name, memo;
	int accountNumber;
	string balance, initialbalance;

	void create(string,string, int);
	void shortShow();	
	void longShow();
	void insertTransaction (string, string, string, string, bool, int);	
	void insertTransaction ( Transaction, Category  );
	//bool removeTransaction(int);
	
	void insertTransactionByHand ( Category );

	void read(string) ; 
	void write(string); 

	void updateBalance( Transaction );

	//bool empty();
	bool emptyAccount();



	//XML operations
	void showXML();
	TiXmlElement * getXML();
	
private:
	TiXmlElement * AccountXML;
	void setXML();

	//to autogenerate transaction ids
	int transactionID;	
} ;
#endif

