/* Catagories header file.

Author: Mark Young

  * @ID:				$Id: Category.h 63 2008-05-01 04:05:12Z youn0624 $
  * @lastmodified    	$Date: 2008-04-30 23:05:12 -0500 (Wed, 30 Apr 2008) $ 
  * @version         	$Revision: 63 $ 

*/

#ifndef Category_H
#define Category_H

#include <iostream>
#include <string>
#include <vector> 

//package libraries to include
#include "lib/tinyxml/tinyxml.h"
#include "lib/strextra/Strextra.h"


using namespace std;


class Category {
public:
	string name;
	int code;
	
	//constructors
	Category();
	Category(string, int);
	Category(TiXmlElement*);
	//Category(Category);
		
	void addCategory(Category); 
	//void addCategory(string, int); 
	void addSubCategory(Category, Category);
	
	bool catcmp(Category, Category);
	
	void listCategory(int);
	void print();
	
	TiXmlElement * getXML();

private:
	TiXmlElement * CategoryXML;
	void setXML();
};

#endif
