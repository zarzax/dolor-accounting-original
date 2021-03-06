/* Transaction.cpp --
			Transaction class.  base class for working with account
			data.  Works with TinyXML to create an XML element that
			can be passed around to more broad classes.

Author: Mark Young

  * @ID:				$Id: Transaction.cpp 132 2008-05-15 02:50:16Z youn0624 $
  * @lastmodified    	$Date: 2008-05-14 21:50:16 -0500 (Wed, 14 May 2008) $ 
  * @version         	$Revision: 132 $ 

*/

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>


#include "Category.h"
#include "Transaction.h" 

//package libraries to include
//#include "lib/cvsgetline/cvsgetline.h"
#include "lib/tinyxml/tinyxml.h"
//#include "lib/tinyxpath/xpath_static.h"
#include "lib/strextra/Strextra.h"

using namespace std;

Transaction::Transaction ()
{
}

//create a transaction when the date is given as a single string
Transaction::Transaction(string _amount, string _date, string _memo, string _tofrom, bool _credit){
	amount 	= _amount;
	date 	= _date;
	memo	= _memo;
	tofrom	= _tofrom;
	credit	= _credit;
	
	year  = atoi( (date.substr(0,3)).c_str() );
	month = atoi( (date.substr(4,2)).c_str() );
	day   = atoi( (date.substr(6,2)).c_str() );
	
	//Initialize the XML Element TransactionXML
	TransactionXML	= new TiXmlElement( "transaction" );
	
	//set the xml portion.
	setXML();
}

//create a transaction when the date is given as a single string and cat code
Transaction::Transaction(string _amount, string _date, string _memo, string _tofrom, bool _credit, int _cat_code){
	amount 	= _amount;
	date 	= _date;
	memo	= _memo;
	tofrom	= _tofrom;
	credit	= _credit;
	cat_code = _cat_code;
	
	year  = atoi( (date.substr(0,3)).c_str() );
	month = atoi( (date.substr(4,2)).c_str() );
	day   = atoi( (date.substr(6,2)).c_str() );
	
	//Initialize the XML Element TransactionXML
	TransactionXML	= new TiXmlElement( "transaction" );
	
	//set the xml portion.
	setXML();
}

/* A way to manually set all parts of the Transactoin Object */
Transaction::Transaction(string a, int m, int d, int y, int i, string mem, string tofm, bool is) 
{
    amount = a; month = m; day = d; year = y;
    
    //set date string
    if (month < 10){
		date = to_string(year).append("0");
		date.append(to_string(month));
		date.append(to_string(day));
	}
	else{
		date = to_string(year).append(to_string(month));
		date.append(to_string(day));
	}  
    
	//ID unique to transaction... possibility to implement a counter, for automatic uniques...
	idnum = i;

	//strings
    memo = mem; tofrom = tofm;
	
	//bool
    credit = is;
	
	//Initialize the XML Element TransactionXML
	TransactionXML	= new TiXmlElement( "transaction" );
	
	//set the xml portion.
	setXML();	
}

Transaction::Transaction (TiXmlElement * root)
{	
	TransactionXML = new TiXmlElement( *root );
	
	TiXmlNode* pElem = (*root).FirstChild( "memo" );
	
    for( pElem; pElem; pElem=pElem->NextSiblingElement())
    {
    
		//string pKey = to_string( pElem->Value() );
		const char *pKey=pElem->Value();
	
		if ( pKey )
	  	{
	  		
	    	//show elements in userdata
	    	if ( to_string(pKey) == "memo" ) {
	    		memo = to_string( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    		
	    	if ( to_string(pKey) == "tofrom" ) {
	    		tofrom = to_string( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    	
	    	if ( to_string(pKey) == "amount" ) {
	    		amount = to_string( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    	
	    	if ( to_string(pKey) == "date" ){
	    		date = to_string( ((TiXmlElement*)pElem)->GetText() ) ;
	    		year  = atoi( (date.substr(0,3)).c_str() );
	    		month = atoi( (date.substr(4,2)).c_str() );
	    		day   = atoi( (date.substr(6,2)).c_str() );
	    	}
	    	
	    	if ( to_string(pKey) == "credit" ) {
	    		credit = (bool) atoi( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    	
	    	if ( to_string(pKey) == "category" ) {
	    		TiXmlNode* pElem_cat = pElem->FirstChildElement( "category" );
	    		cat_code = atoi( ((TiXmlElement*)pElem)->GetText() ) ;
	    		}
	    
		}	
	}

}


/* Prints the transaction out to the terminal in a logical way */
void Transaction::show() {
    //cout << "## Transaction: tofrom: " << tofrom << " dated: " << date << endl;
    
	if(credit)
	{
		cout << "\tfrom: \"" << tofrom << "\"\tdate: \"" << date << "\"\tamount: $" << amount << "memo: \"" << memo << "\"" << endl;
		//cout << "\t" << "CREDIT:\t$" << amount << endl;
	}
	else
	{
		cout << "\t  to: \"" << tofrom << "\"\tdate: \"" << date << "\"\tamount: $" << amount << "memo: \"" << memo << "\"" << endl;
		//cout << "\t" << "DEBIT: \t$" << amount << endl;
	}
	
    	//cout << "\t" << "MEMO: " << "\t" << memo << endl;						
}


/* Sets the XML for a Transaction object. */
void Transaction::setXML() {
	/*  //Example Transaction XML //
	 *	<transaction>
		 *	<memo>Weekly Fuel Purchase</memo>
		 *	<tofrom>B&V Gas Station</tofrom>
		 *	<amount>540.43</amount> 
		 *	<date>20080401</date>
		 *	<credit>1</credit>		<-- if the charge is a credit (not a debit), this field contains a "1" 
		 *	<categories>
		 *		<Category>4</Category>
		 *	</categories>
	 *	</transaction>
	 */
 
 	// <memo>Weekly Fuel Purchase</memo>
 	TiXmlElement * tMemo = new TiXmlElement( "memo" );
	TransactionXML->LinkEndChild( tMemo);
	TiXmlText * txMemo = new TiXmlText( memo );
	tMemo->LinkEndChild( txMemo );
	
	// <tofrom>B&V Gas Station</tofrom>
	TiXmlElement * tTofrom = new TiXmlElement( "tofrom" );
	TransactionXML->LinkEndChild( tTofrom);
	TiXmlText * txTofrom = new TiXmlText( tofrom );
	tTofrom->LinkEndChild( txTofrom );
	
	// <amount>540.43</amount>
	TiXmlElement * tAmount = new TiXmlElement( "amount" );
	TransactionXML->LinkEndChild( tAmount );
	TiXmlText * txAmount = new TiXmlText( amount );
	tAmount->LinkEndChild( txAmount );
	
	// <date>20080401</date>
	if (month < 10){
		date = to_string(year).append("0");
		date.append(to_string(month));
		date.append(to_string(day));
	}
	else{
		date = to_string(year).append(to_string(month));
		date.append(to_string(day));
	}
	TiXmlElement * tDate = new TiXmlElement( "date" );
	TransactionXML->LinkEndChild( tDate );
	TiXmlText * txDate = new TiXmlText( date );
	tDate->LinkEndChild( txDate );
	
	// <credit>1</credit>
	TiXmlElement * tCredit = new TiXmlElement( "credit" );
	TransactionXML->LinkEndChild( tCredit );
	TiXmlText * txCredit = new TiXmlText( to_string( credit ) );
	tCredit->LinkEndChild( txCredit );
	
	// create the category in XML
	TiXmlElement * tCatP = new TiXmlElement( "categories" );
	TransactionXML->LinkEndChild( tCatP );
	TiXmlElement * tCatC = new TiXmlElement( "category" );
	tCatP->LinkEndChild( tCatC );
	TiXmlText * txCat = new TiXmlText( to_string( cat_code ) );
	tCatC->LinkEndChild( txCat );

}

TiXmlElement * Transaction::getXML() 
{
	return TransactionXML;
}

//returns the amount in a transaction
string Transaction::getAmount()
{	
	return amount;
}

