/* A simple set of book class.

Author: Mark Young

  * @ID:		$Id: set_of_books.cpp 133 2008-05-15 03:50:37Z  $
  * @lastmodified    	$Date: 2008-05-14 22:50:37 -0500 (Wed, 14 May 2008) $ 
  * @version         	$Revision: 133 $ 

*/


#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "set_of_books.h"
#include "Accounts.h"
#include "Category.h"


//package libraries to include
#include "lib/tinyxml/tinyxml.h"
#include "lib/strextra/Strextra.h"


using namespace std;


Books::Books()
{
}

Books::Books(string _name, string _memo)
{
	//Initialize the account object variables.
	name = _name; memo = _memo;
	
	//set balance to be zero.
	mainBalance = "0.00";

	//initialize the main category
	categories = Category ("all", 0);
	
	//set doc decloaration.
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	BookXML.LinkEndChild( decl );
	
	//Initialize the XML Element AccountXML
	TiXmlElement * BookRoot = new TiXmlElement( "setofbooks" );
	BookXML.LinkEndChild( BookRoot );
	
	//Set XML data.
	setXML();
}

Books::Books(TiXmlElement * rootpass)
{
	//set doc decloaration.
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	BookXML.LinkEndChild( decl );
	
	TiXmlElement * root = new TiXmlElement(* rootpass);
	BookXML.LinkEndChild( root);	
	
	TiXmlNode* pElem = (*root).FirstChild( "name" );	
    for( pElem; pElem; pElem=pElem->NextSiblingElement())
    {  
		//string pKey = to_string( pElem->Value() );
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
		}	
	}
}

//makes a new account in the current set of books
void Books::insertAccount( Accounts newAccount)
{	
	( BookXML.FirstChildElement( "setofbooks" ) )->LinkEndChild( newAccount.getXML() );
} 

//makes a new account with the given info for the account
void Books::insertAccount(string _name, string _memo, string _initialbalance)
{	
	Accounts newAccount(_name, _memo, _initialbalance);
	
	( BookXML.FirstChildElement( "setofbooks" ) )->LinkEndChild( newAccount.getXML() );
} 

	
void Books::insertAccountByHand( )
{
	string answer;
	string _initialbalance;
	string _name, _memo;
	
	cout << "Would you like to create an account? (Y/ anykey for no): ";
	cin >> answer;
	while(answer == "Y" || answer == "y")
	{
		cout << "Please enter a name (as string): " ;
		cin >> _name;
		cout << "Please enter a memo (as string): " ;
		cin >> _memo;
		cout << "Please enter an initial balance (as int): " ;
		cin >> _initialbalance;
	
		Accounts newAccount(_name, _memo, _initialbalance);
		
		newAccount.insertTransactionByHand( categories );
		
		cout << "merging account with books" << endl;
		
		( BookXML.FirstChildElement( "setofbooks" ) )->LinkEndChild( newAccount.getXML() );
		
		cout << "Would you like to create another account? (Y/ anykey for no): ";
		cin >> answer;

	}
} 	

void Books::listAccounts( )
{
	cout << "Set of Books stats\n" <<
			"total balance $" << mainBalance << endl;

	cout << "\n########################" << endl;
	cout << "Listing accounts...\n" << endl;
	
	int counter = 0;
	TiXmlHandle docHandle( &BookXML );
	TiXmlElement* child = docHandle.FirstChild( "setofbooks" ).FirstChild( "account" ).ToElement();
	for( child; child; child=child->NextSiblingElement() )
	{
		counter++;
		TiXmlNode* pElem = (*child).FirstChild( "name" );
		string _account_name = to_string( ((TiXmlElement*)pElem)->GetText() );
		cout << counter << "  account_name: " << _account_name << endl;
	}
}

void Books::showAccount( )
{
	string answer, _name;
	listAccounts();
	
	//cout << "which account would you like to open? (account name / string) " << endl;
	//cin >> answer;
	
	answer = _name;

	cout << "\n########################" << endl;
	cout << "Showing Account with name: " << _name << endl << endl;
	
	TiXmlHandle docHandle( &BookXML );
	TiXmlElement* child = docHandle.FirstChild( "setofbooks" ).FirstChild( "account" ).ToElement();
	for( child; child; child=child->NextSiblingElement() )
	{
		TiXmlNode* pElem = (*child).FirstChild( "name" );
		string pElem_name = to_string( ((TiXmlElement*)pElem)->GetText() );
		cout << "testing " << pElem_name << endl;
		if ( pElem_name .compare( _name ) )
		{
			cout << "Found Account...  OPENING for Show... " << endl;
			Accounts tmp(child);
			tmp.longShow();
			return;
		}
	}	
	cout << "Unable to find account by that name... " << endl;
}


void Books::openAccount( string _name )
{	
	TiXmlHandle docHandle( &BookXML );
	TiXmlElement* child = docHandle.FirstChild( "setofbooks" ).FirstChild( "account" ).ToElement();
	for( child; child; child=child->NextSiblingElement() )
	{
		TiXmlNode* pElem = (*child).FirstChild( "name" );
		string pElem_name = to_string( ((TiXmlElement*)pElem)->GetText() );
		if ( pElem_name == _name )
		{
			cout << "Found Account...  OPENING... " << endl;
			Accounts tmp(child);
			tmp.shortShow();
			///tmp.insertTransactionByHand( categories );
			return;
		}
	}	
	cout << "Unable to find account by that name... " << endl;
}

bool Books::read( string filename ) 
{ 
	bool returnVal = true;
	TiXmlDocument in( filename.c_str() );
	//load file, check for success.
	if (in.LoadFile()) 
	{
		cout << "\nFile loaded successfully.. " << endl;
		returnVal = true;
	}
	else 
	{
		cout << "\nFailed to load file.." << endl;
		return false;
	}
	
	//find the root, check for success..
	TiXmlHandle docHandle( &in );
	TiXmlElement* root = docHandle.FirstChild( "setofbooks" ).ToElement();
	if ( !root )
	{
		cout << "Root element not found." << endl;
		return false;
	}	
	
	//find the cattree and set the categories accordingly.
	TiXmlElement* categ = docHandle.FirstChild( "setofbooks" ).FirstChild( "cattree" ).ToElement();
	if ( categ )
	{
		//cout << "cattree found.  Attempting to set categories" << endl;
		categories = Category ( docHandle.FirstChild( "setofbooks" ).FirstChild( "cattree" ).FirstChild( "cat" ).ToElement() );
	}else
	{
		cout << "cattree not found in XML.  perhaps an old XML dataset" << endl;
		cout << "UPDATING...." << endl;
		
		TiXmlElement * tCategory = new TiXmlElement( "cattree" );
		TiXmlNode* accnt = docHandle.FirstChild( "setofbooks" ).FirstChild( "account" ).ToNode();
		if( (*root).InsertBeforeChild ( accnt, (*tCategory) ) )
		{
			cout << "update failed.." << endl;
			returnVal = false;
		}else
		{
			cout << "UPDATE SUCCESSFUL!" << endl;
		}
		
	}
	
	//Set all the variables...
	BookXML = TiXmlDocument( in );	
	//create a tmp Books object to get the values for the variables.
	Books tmp(root);
	name = tmp.name;
	memo = tmp.memo;

	return returnVal;	
} 

bool Books::write( string filename )
{
	if( ! BookXML.SaveFile( filename.c_str() ) )
	{
		cout << "error writing set_of_books to file: " << filename << endl;
		return false;
	}
	
	return true;
} 

void Books::setXML( )
{
	/*  //Example XML
	 *	<setofbooks>
	 *	<name></name>
	 *  <cattree>
	 *     <cat name="..." code="...">
	 *        ...
	 *     </cat>
	 *  </cattree>
	 *	<memo></memo>
	 *	<account>
	 *		...
	 *	</account>
	 *	<setofbooks>
	 */
 
	TiXmlHandle docHandle( &BookXML );
	TiXmlElement* root = docHandle.FirstChild( "setofbooks" ).ToElement();
	
	// <name>Marks Books</name>
 	TiXmlElement * tName = new TiXmlElement( "name" );
	root->LinkEndChild( tName);
	TiXmlText * txName = new TiXmlText( name );
	tName->LinkEndChild( txName);
	
	// <memo>All combined books</memo>
 	TiXmlElement * tMemo = new TiXmlElement( "memo" );
	root->LinkEndChild( tMemo);
	TiXmlText * txMemo = new TiXmlText( memo );
	tMemo->LinkEndChild( txMemo );
	
	// <cattree> ... </cattree>
	TiXmlElement * tCategory = new TiXmlElement( "cattree" );
	root->LinkEndChild( tCategory );
} 


void Books::listCat()
{
	categories.listCategory(0);
}

void Books::addSubCat(Category parent, Category child)
{
	categories.addSubCategory(parent, child);
}


TiXmlElement* Books::getXML()
{
	TiXmlHandle docHandle( &BookXML );
	TiXmlElement* root = docHandle.FirstChild( "setofbooks" ).ToElement();
	if (root)
	{
		return root;
	}else
	{
		cout << "root element not found in Books::getXML() on line:" << __LINE__ << endl;
		return NULL;
	}
		
}

