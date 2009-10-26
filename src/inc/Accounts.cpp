/* A simple Account class.

Author: Mark Young

  * @ID:				$Id: Accounts.cpp 131 2008-05-15 02:47:11Z youn0624 $
  * @lastmodified    	$Date: 2008-05-14 21:47:11 -0500 (Wed, 14 May 2008) $ 
  * @version         	$Revision: 131 $ 

*/

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>


#include "Accounts.h"
#include "Transaction.h" 
#include "Category.h"

//package libraries to include
#include "lib/tinyxml/tinyxml.h"
#include "lib/strextra/Strextra.h" 

using namespace std;

Accounts::Accounts()
{
}

Accounts::Accounts(string _name, string _memo, string _initialbalance)
{
	//Initialize the account object variables.
	name = _name; memo = _memo; initialbalance = _initialbalance; 
	
	//set balance to be zero.
	balance = _initialbalance;

	//Initialize the XML Element AccountXML
	AccountXML = new TiXmlElement( "account" );
	
	//Set XML data.
	setXML();
}

Accounts::Accounts(TiXmlElement* root)
{
	/*	//Example xml
	 *	<account>
	 *	<name></name>
	 *	<memo></memo>
	 *	<initialbalance></initialbalance>
	 *	
	 *	<transaction>
	 *		...
	 *	</transaction>
	 *	
	 *	
	 *	</account>
	 */
	 
	AccountXML = new TiXmlElement( *root );
	
	TiXmlNode* pElem = (*root).FirstChild( "name" );
	
    for( pElem; pElem; pElem=pElem->NextSiblingElement())
    {
		const char *pKey=pElem->Value();
	
		if ( pKey )
	  	{
	  		
	    	//show elements in userdata
	    	if ( to_string(pKey) == "name" ) {
	    		name = to_string( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    		
	    	if ( to_string(pKey) == "memo" ) {
	    		memo = to_string( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    	
	    	if ( to_string(pKey) == "initialbalance" ) {
	    		initialbalance = atoi( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    		
	    	if ( to_string(pKey) == "transaction" ) {
	    		Transaction tmp((TiXmlElement*)pElem);
	    		balance = mstr_add(balance, tmp.getAmount());
	    		}	
		}	
	}	
}


/* Prints the transaction out to the terminal in a logical way */
void Accounts::shortShow()
{
	cout << "\n###### ACCOUNT: \"" << name << "\" #######################" << endl;
	cout << "\t\t:::::: balance: $" << balance << "\tmemo: \"" << memo << "\" ::::::" << endl;						
}

/* Prints the transaction out to the terminal in a logical way */
void Accounts::longShow() 
{
	
	shortShow();		
	
	TiXmlNode* pElem = (*AccountXML).FirstChild( "name" );	
    for( pElem; pElem; pElem=pElem->NextSiblingElement())
    {
		const char *pKey=pElem->Value();
		if ( pKey )
	  	{
	    		
	    	if ( to_string(pKey) == "transaction" ) 
	    	{
	    		Transaction tmp((TiXmlElement*)pElem);
	    		tmp.show();
	    	}	
		}	
	}
	
}

/* Inserts the transaction into the transaction xml */
void Accounts::insertTransaction (string _amount, string _date, string _memo, string _tofrom, bool _credit, int _cat_code) 
{ 

	//setup the transaction object and get the xml element.
	Transaction t( _amount,  _date,  _memo,  _tofrom, _credit, _cat_code);
	TiXmlElement * tmpTransactionXML = t.getXML();
	
	AccountXML->LinkEndChild( tmpTransactionXML );
	
	updateBalance( t );
} 

/* Overloaded insert to take a premade tranaction object and insert it into the account array */
void Accounts::insertTransaction (Transaction t, Category categ) 
{ 
	//setup the transaction object and get the xml element.
	TiXmlElement * tmpTransactionXML = t.getXML();
	
	AccountXML->LinkEndChild( tmpTransactionXML );
	
	updateBalance( t );
}

/*  Removes the transaction with supplied IDnum */	
// bool Accounts::removeTransaction(int _idnum) {

	// TiXmlElement* child = AccountRoot.FirstChild( "Account" ).FirstChild( "Transaction" ).ToElement();
	// for (  ; child; child->NextSibling() )
	// {
		// if ( child.FirstAttribute( "idnum" ).Value() == _idnum )
		// {
			// if ( child.RemoveChild( child.toNode() ) ){
				// cout << "Transaction Removed Successfully!" << endl;
				// return true;
			// }	
		// }		
	// }
	// return false;
// }


void Accounts::insertTransactionByHand ( Category categ )
{
	//initialize variables
	string _amount, _date, _memo, _tofrom;
	int _credit, _cat_code;
	string answer;

	cout << "\n###########################\n\n"
		 << "Inserting a transaction in Account::" << name << " by terminal input:\n" ;

	cout << "Please enter '1' for credit else '0' (as int): " ;
	cin >> _credit;		 
	cout << "Please enter amount (as string): " ;
	cin >> _amount;
	cout << "Please enter date (as string. ex. 20080524): " ;
	cin >> _date;
	cout << "Please enter memo (as string): " ;
	cin >> _memo;
	cout << "Please enter to/from (as string): " ;
	cin >> _tofrom;
	
	cout << "Would you like to list or add a category the enter (as string. \"list\", \"add\", or any key to skip" ;
	cin >> answer;
	if ( answer == "list")
	{
		categ.listCategory( 0 );
	}else if ( answer == "add" )
	{
		string _cname;
		int _ccode;
		cout << "Enter a name for the category: " ;
		cin >> _cname ;
		cout << "Enter a code for the category: " ;
		cin >> _ccode ;
		categ.addSubCategory( Category ("all", 0), Category ( _cname, _ccode) );
	}
	cout << "Please enter a category code (as int): " ;
	cin >> _cat_code;


	insertTransaction(_amount, _date, _memo, _tofrom, _credit, _cat_code);

	cout << "Insert successfull.." << endl;

	cout << "Would you like to insert another? (Y/N): ";
	cin >> answer;

	if (answer == "Y" || answer == "y")
	{
		insertTransactionByHand( categ );
	}
	
}


void Accounts::updateBalance(Transaction t) 
{	
	balance = mstr_add(balance, t.getAmount());
}
 

//bool Accounts::empty() { return transaction_list.empty(); }

/* Empties the transactions*/
bool Accounts::emptyAccount() 
{ 

	//set balance and initialbalance to be zero.
	balance = "0.00";
	
	initialbalance = "0.00";
	
	
	//Initialize the XML Element AccountXML
	AccountXML = new TiXmlElement( "account" );

	
	//Set XML data.
	setXML();
	
	return true;
}

/* reads xml files*/
void Accounts::read( string filename ) { 

	TiXmlDocument in( filename.c_str() );
	//load file, check for success.
	if (in.LoadFile()) 
	{
		cout << "\nFile loaded successfully.. " << endl;
	}
	else 
	{
		cout << "\nFailed to load file.." << endl;
		return;
	}
	
	//find the root, check for success..
	TiXmlHandle docHandle( &in );
	TiXmlElement* root = docHandle.FirstChild( "account" ).ToElement();
	if ( !root )
	{
		cout << "Root element not found." << endl;
		return;
	}	
	
	AccountXML = new TiXmlElement( * root );
	
	Accounts tmp(AccountXML);
	name = tmp.name;
	memo = tmp.memo;
	initialbalance = tmp.initialbalance;
} 

void Accounts::write( string filename ){

	//create new document.
	
	TiXmlDocument doc;

	//set doc decloaration.
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	//link accountXML
	
	doc.LinkEndChild( AccountXML );
	
	//save the file to filename..
	doc.SaveFile( filename.c_str() );
} 

void Accounts::setXML( ){

	/*	//Example xml
	 *	<account>
	 *	<name></name>
	 *	<memo></memo>
	 *	<initialbalance></initialbalance>
	 *	
	 *	<transaction>
	 *		...
	 *	</transaction>
	 *	
	 *	
	 *	</account>
	 */
	 
	
	// <name>WELLS FARGO</name>
 	TiXmlElement * tName = new TiXmlElement( "name" );
	AccountXML->LinkEndChild( tName);
	TiXmlText * txName = new TiXmlText( name );
	tName->LinkEndChild( txName);
	
	// <memo>Checking Account</memo>
 	TiXmlElement * tMemo = new TiXmlElement( "memo" );
	AccountXML->LinkEndChild( tMemo);
	TiXmlText * txMemo = new TiXmlText( memo );
	tMemo->LinkEndChild( txMemo );
	
	// <initialbalance>540.43</initialbalance>
	TiXmlElement * tInitialbalance = new TiXmlElement( "initialbalance" );
	AccountXML->LinkEndChild( tInitialbalance );
	TiXmlText * txInitialbalance = new TiXmlText( to_string(initialbalance) );
	tInitialbalance->LinkEndChild( txInitialbalance );
	
	
} 

void Accounts::showXML( ){
	cout << "AccountXML::::\n" << AccountXML << endl;
	
} 

TiXmlElement * Accounts::getXML(){
	return AccountXML;
} 


