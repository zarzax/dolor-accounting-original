/* The main driver program for the project.

Author: Mark Young

* @ID:				$Id: main.cpp 133 2008-05-15 03:50:37Z  $
* @lastmodified    	$Date: 2008-05-14 22:50:37 -0500 (Wed, 14 May 2008) $ 
* @version         	$Revision: 133 $ 

*/


#include <iostream>
#include <fstream>
#include <string>

#include "inc/set_of_books.h"
#include "inc/Category.h"
#include "inc/lib/tinyxml/tinyxml.h"


using namespace std;



/*
*	##############################
*
*	   ::Global Declorations::
*
*  ##############################
*/

/*
*	Global book variable
*/
Books book("test", "test");

/*
*	Declare fuctions before use.
*/
void displayMenu();
void doWork(string);
void displayBookMenu();
void doBookWork(string);
//void displayAccountMenu();
//void doAccountWork(string);
//void displayCategoryMenu();
//void doCategoryWork(string);


/*
*	##############################
*
*	  ::Main Driving Functions::
*
*  ##############################
*/


/*
void displayAccountMenu()
{
int answer;

//system( "clear" );

cout << "DOLOR --  Accounting Program\n"
<<"ACCOUNTS MENU \n"
<< "############################\n\n" ;

cout << "1. SHOW BASIC INFO \n 2. SHOW ALL INFO \n  3. ADD A TRANSACTION \n "
<<"4.RETURN TO BOOK MENU \n (Enter Numerical Value)\n";
cin >> answer ;


doAccountWork( answer);



}
*/
void displayMenu()
{
	string answer;

	system( "clear" );

	cout << "DOLOR --  Accounting Program\n"
	<< "############################\n\n" ;

	cout <<" 1. READ IN A SET OF BOOKS \n 2. ADD A SET OF BOOKS \n 3. SAVE AND QUIT \n";
	cin >> answer ;	

	doWork(answer);

}

void doWork(string ans){

	string bookname, bookmemo, filename;
	int answer;

	if(ans == "1" || ans == "2" || ans == "3"){
		answer = atoi (ans.c_str());
	}else {
		answer = 10;
	}

	switch(answer){
		
	case 1:
		cout<<"Please enter a file name to read in\n";
		cin >>filename;
		book.read(filename.c_str());
		displayBookMenu();
		
		break;
		
	case 2:
		cout<<"Enter in the name of the Set of Books \n";
		cin>> bookname;
		cout<<"Enter in a memo \n";

		cin>> bookmemo;
		book = Books(bookname, bookmemo);
		displayBookMenu();
		break;
		
		
	case 3:
		book.write(filename.c_str());
		cout<<"goodbye\n";
		
		break;	
		
	default:
		cout<<"Invalid Selection, Try again\n";
		displayMenu();
		break;
	}
}

void displayBookMenu()
{
	string answer;

	//system( "clear" );

	cout<<"\n ########################### \n";
	cout << "DOLOR --  Accounting Program\n"
	<<"SET OF BOOKS MENU \n"
	<< "############################\n\n" ;

	cout << " 1. OPEN ACCOUNT \n 2. ADD ACCOUNT \n 3. LIST CATEGORIES \n"
	<<" 4. ADD CATEGORY / SUB-CATEGORY \n 5. RETURN TO MAIN MENU \n (Enter Numerical Value)\n";
	cin >> answer ;
	
	doBookWork( answer);


}

/*
*	JOHN FIX the account menu calls I commented out...
*/
void doBookWork( string ans )
{
	string actname,uname,u2name;
	int cat, ucode, u2code, answer;

	if(ans == "1" || ans == "2" || ans == "3" || ans == "4" || ans == "5"){
		answer = atoi (ans.c_str());
	}else {
		answer = 10;
	}

	switch (answer) {
		
	case 1:  
		book.listAccounts();
		cout<< "Please Select an account to open, type in the name \n";
		cin>>actname;
		book.openAccount(actname);
		//displayAccountMenu();
		break;
		
	case 2:
		book.insertAccountByHand();
		//displayAccountMenu();
		
		break;
	case 3:
		book.listCat();
		displayBookMenu();
		
		break;
		
	case 4:
		book.listCat();
		cout<<"Type 1 if you ant to create a category, and 2 for a sub-category \n";
		cin>> cat;
		if (cat ==1){
			cout<<"Please type the category's name\n";
			cin>> uname;
			cout<<"Please type the category's code (int)\n";
			cin>> ucode;
			Category tmp("all", 0);
			Category usr(uname, ucode);
			book.addSubCat(tmp, usr);
			displayBookMenu();
		}
		if(cat ==2){
			cout<<"Please give the category name you want a sub-category in\n";
			cin>>uname;
			cout<<"What is that category's code?";
			cin>>ucode;
			cout<<"What do you want the sub-category to be called?";
			cin>>u2name;
			cout<<"What do you want the sub-category's code to be (int)? \n";
			cin>>u2code;
			Category usr(uname, ucode);
			Category usr2(u2name, u2code);
			book.addSubCat(usr, usr2);
			displayBookMenu();
		}
		break;
		
	case 5:

		displayMenu();
		break;
		
	default:
		cout<<"Invalid Selection, Try again\n";
		displayBookMenu();
		break;
	}

}

/*
void doAccountWork(int answer){

string bookname, bookmemo;

switch(answer){
	
case 1:
shortShow();
displayAccountMenu();
	
break;
	
case 2:
longShow();
displayAccountMenu();
break;
	
case 3:
insertTransactionByHand(0);
displayAccountMenu();
	
break;
	
case 4:
displayBookMenu();
break;
	
default:
cout<<"Invalid Selection, Try again\n";
displayAccountMenu();
break;
}
}
*/



/*
*	###############################
*
*	       ::MAIN Function::
*
*  ###############################
*/


/*
*  Main function.. Needs to be expanded to take in arguments..
*/

int main() {	
	
	displayMenu();
	
	//Books tmp("test book 1", "test");
	
	//tmp.read("sample_book.xml");
	
	//tmp.listAccounts();
	
	//tmp.listCat();
	
	return 1;
}



