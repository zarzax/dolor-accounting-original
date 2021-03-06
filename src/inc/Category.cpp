/* A simple Category class.

Author: Mark Young

  * @ID:				$Id: Category.cpp 63 2008-05-01 04:05:12Z youn0624 $
  * @lastmodified    	$Date: 2008-04-30 23:05:12 -0500 (Wed, 30 Apr 2008) $ 
  * @version         	$Revision: 63 $ 

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "Category.h"

//package libraries to include
//#include "lib/cvsgetline/cvsgetline.h"
#include "lib/tinyxml/tinyxml.h"
//#include "lib/tinyxpath/xpath_static.h"
#include "lib/strextra/Strextra.h"

using namespace std;

Category::Category()
{
}

Category::Category(string _name, int _code)
{
	name = _name;
	code = _code;
	
	//Initialize the XML Element TransactionXML
	CategoryXML	= new TiXmlElement( "cat" );
	
	//set the xml portion.
	setXML();
}

Category::Category(TiXmlElement * parent)
{

	name = to_string(parent->Attribute("name"));
	
	code = atoi( parent->Attribute("code") );
	
	cout << "Name:: " << name << " Code:: " << code << endl;
	
	CategoryXML = new TiXmlElement( *parent );
}


/* recursivly lists all categories and indents them
 * based on parent child relationships
 */
void Category::listCategory(int indent)
{
cout<<"#####################################\n"
	<<"Categories \n";
	string indent_tabs;
	
	for (int i= 0; i < indent; i++)
	{
		indent_tabs += '\t';
	}

	int counter_base = 0;
	
	TiXmlNode* pElem = (TiXmlNode*) CategoryXML;
	for ( pElem; pElem; pElem=pElem->NextSiblingElement() )
	{
		//set up the tabs and counter.  Then print the catagory.
		cout << indent_tabs << counter_base << ": " ;
		
		//create the tmp object and print the tmp category.
		Category tmp( (TiXmlElement*)pElem );
		tmp.print() ;
		
		TiXmlNode* pElem_child = pElem->FirstChildElement( "cat" );
		if ( pElem_child )
		{
			Category child( (TiXmlElement*)pElem_child );
			child.listCategory(indent + 1);
			
		}
		counter_base++;
	}

}

/* prints out the variables only if the size is zero.  Otherwise it
 * calls the list again if the vector is full.
 */
void Category::print()
{
	cout << "Category\tname \"" << name << "\"\t code \"" << code << "\"" << endl;
	
}


/* adds a category to be a sibling of the main
 * category element;
 */
void Category::addCategory(Category child)
{
	CategoryXML->LinkEndChild( child.getXML() );
}


/* adds a subcategory to be a child of another categories
 * category element;
 */
void Category::addSubCategory(Category parent, Category child)
{
	
	TiXmlNode* pElem = (TiXmlNode*) CategoryXML;
	for ( pElem; pElem; pElem=pElem->NextSiblingElement() )
	{
		TiXmlNode* pElem_child = pElem->FirstChildElement( "cat" );
		Category current( (TiXmlElement*)pElem );
		if ( catcmp( current, parent) )
		{
			current.addCategory( child );
			return;
			
		}
		
		if ( pElem_child )
		{
			//Category new_child( pElem_child.ToElement() ) ;
			//new_child.addSubCategory(parent, child) ;
			
			Category child_cat( (TiXmlElement*)pElem_child );
			child_cat.addSubCategory(parent, child);
		}
	}
	
}


/* Set the XML attributes for the node */
void Category::setXML()
{
/*	//Sample category end product code.
*	<cat name="all" code="0">
*		<cat name="Auto" code="1">
*			<cat name="Fuel" code="12"></cat>
*			<cat name="Insurance" code="13"></cat>
*			<cat name="Registration" code="14"></cat>
*			<cat name="Maintenance" code="15"></cat>
*			<cat name="Car Payment" code="16"></cat>
*		</cat>
*		<ciop90-at name="Food" code="4">
*		</cat>
*		<cat name="Income" code="5">
*		</cat>
*		<cat name="Savings" code="6">
*		</cat>
*	</cat>
*/

	CategoryXML->SetAttribute("name", name);
	CategoryXML->SetAttribute("code", code);	

}

/* Get the xml element from the category object
 */
TiXmlElement *  Category::getXML(){
	return CategoryXML;
}


/* compare two categories using their name and code
 * this does not check for the XML to be the same.
 */
bool Category::catcmp(Category c_one, Category c_two)
{

	if ( c_one.name == c_two.name && c_one.code == c_two.code )
	{
		return true;
	}
	else
	{
		return false;
	}	
		
}
