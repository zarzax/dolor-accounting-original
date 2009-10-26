/* Transaction.h --
			Transaction class.  base class for working with account
			data.  Works with TinyXML to create an XML element that
			can be passed around to more broad classes.

Author: Mark Young

  * @ID:				$Id: Transaction.h 111 2008-05-09 21:52:45Z youn0624 $
  * @lastmodified    	$Date: 2008-05-09 16:52:45 -0500 (Fri, 09 May 2008) $ 
  * @version         	$Revision: 111 $ 

*/
#ifndef H_TRANSACTION
#define H_TRANSACTION

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>



//package libraries to include
#include "lib/tinyxml/tinyxml.h"
#include "lib/strextra/Strextra.h"

using namespace std;

class Transaction {
public:
	//default constructor
	Transaction ();
	//full constructors
	Transaction (string, string, string, string, bool);
	Transaction (string, int, int, int, int, string, string, bool);
	Transaction (TiXmlElement*);
	
	//transaction with category
	Transaction (string, string, string, string, bool, int);
	
	//object variables
	int month, day, year, idnum, cat_code;
	string amount;
    string memo;
    string date;
    string tofrom;
    bool credit;

	//XML operations
    void show();
	TiXmlElement * getXML();
	
	string getAmount();

private:
	TiXmlElement * TransactionXML;	
	void setXML();
} ;
#endif

