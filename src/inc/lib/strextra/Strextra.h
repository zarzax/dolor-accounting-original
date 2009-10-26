/* STREXTRA library file.

Mark's String Extra library.  Helpful additional function related to c++ strings.

Author: Mark Young

A template class to be covert different types to a standard c++ string. Also has a function to add money

  * @ID:		$Id: Strextra.h 78 2008-05-05 17:50:50Z  $
  * @lastmodified    	$Date: 2008-05-05 12:50:50 -0500 (Mon, 05 May 2008) $ 
  * 
  * @version         	$Revision: 78 $ 

*/

#ifndef H_STREXTRA
#define H_STREXTRA

#include <string>
#include <sstream>

using namespace std;

template <class T>
inline std::string to_string (const T&);

//converts anything into a string
template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

inline std::string mstr_add(string, string);

//takes in 2 strings, converts to ints, adds them, then converts back to string and returns

inline std::string mstr_add(string s1, string s2){
	string total, amt1, amt2;
	int d, d1, d2, c, c1, c2, pos1, pos2, neg1, neg2;
	
	pos1=s1.find(".");
	pos2=s2.find(".");
	
	if(pos1 < 0 && pos2 < 0){ //case if both numbers have no "." so they are ints
		
		d1 = atoi(s1.c_str());
		d2 = atoi(s2.c_str());
		d = d1+d2;
		total = to_string(d);
		return total;
		
	}
	
	neg1 = s1.find("-");  //these check to see if they are negative, for adding of cents
	neg2 = s2.find("-");
	
	if (pos1 < 0){   		//checks if the first one is an int
		d1 = atoi(s1.c_str());
		c1 = 0;
		
	} else {
		amt1 = s1.substr (0,pos1); // from the start to  the "."
		amt2 = s1.substr (pos1+1);   // get from after "." to the end
		
		d1 = atoi(amt1.c_str());
		c1 = atoi(amt2.c_str());
	}

	if (pos2 < 0){        //checks if the second one is an int
		d2 = atoi(s2.c_str());
		c2 = 0;
		
	}else {

		amt1 = s2.substr (0,pos2); // from the start to "."
		amt2 = s2.substr (pos2+1);   //  get from after "." to the end
		
		d2 = atoi(amt1.c_str());
		c2 = atoi(amt2.c_str());
	}


	//if negative, make the cents negative too
	
	if (neg1 == 0){
		c1 = -c1;	
	}
	
	if (neg2 == 0){
		c2 = -c2;		
	}
	
	d = d1+d2;
	c = c1+c2;
	
	if(d > 0){
		if (c >= 100){
			d = d+1;
			c = c-100;
		}
		if (c < 0){
			d = d-1;
			c=c+100;
		}
	}
	
	if(d ==0){
		if(c>=100){
			d=d+1;
			c=c-100;
		}
		
		if(c<=-100){
			d=d-1;
			c=c+100;
		}
		
		if(c<0){
			c=-c;
			if(c<10){
				total = "-";
				total.append(to_string(d));
				total.append(".");
				total.append("0");
				total.append(to_string(c));
				return total;
			}
			total = "-";
			total.append(to_string(d));
			total.append(".");
			total.append(to_string(c));
			return total;
		}		
	}
	
	if (d < 0){
		if(c <= -100){
			d=d-1;
			c=c+100;
		}
		if (c > 0) {
			d=d+1;
			c=c-100;
		}
		if (c < 0){
			c=-c;
		}

	}
	if (c < 10){
		total = to_string(d);
		total.append(".");
		total.append("0");
		total.append(to_string(c));
		return total;
	}
	
	total = to_string(d);
	total.append(".");
	total.append(to_string(c));
	return total;
}
#endif

