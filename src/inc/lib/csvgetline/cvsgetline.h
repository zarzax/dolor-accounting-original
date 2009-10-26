/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */

/*
 * Moddified by mark young to be used as a class.
 *
 * @ID:		$Id: cvsgetline.h 27 2008-04-07 14:56:12Z youn0624 $
  * @lastmodified    	$Date: 2008-04-07 09:56:12 -0500 (Mon, 07 Apr 2008) $ 

  * @version         	$Revision: 27 $ 
   *
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>



class Csv {	// read and parse comma-separated values
	// sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625

  public:
	Csv(istream& fin = cin, string sep = ",") : 
		fin(fin), fieldsep(sep) {}

	int getline(string&);
	string getfield(int n);
	int getnfield() const { return nfield; }

  private:
	istream& fin;			// input file pointer
	string line;			// input line
	vector<string> field;	// field strings
	int nfield;				// number of fields
	string fieldsep;		// separator characters

	int split();
	int endofline(char);
	int advplain(const string& line, string& fld, int);
	int advquoted(const string& line, string& fld, int);
};
