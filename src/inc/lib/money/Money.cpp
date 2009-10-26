<html><head></head><body>//<pre>//%TITLE  IDI Money class:  implementation of non-in-line functions
//  Copyright 1995, Information Disciplines, Inc., Chicago 

//  See Money.hpp for documentation and declarations
//%SPACE 3
#include <iostream.h>
#include "Money.hpp"
//%SPACE 3
//  The static member data are public, allowing user overrides without 
//  incurring the overhead of member functions.  This is acceptable, 
//  because any user errors will be immediately obvious, and are 
//  unlikely to affect computational integrity.
//%SPACE 3
// Initial (default) constant values for U.S. currency
// ---------------------------------------------------

//  The user-program may override these values.  To avoid inconsistencies,
//  this should be done only before any Money objects are created.

char       Money::pfx_symbol[]    = "$";
char       Money::sfx_symbol[]    = "" ;
char       Money::decimal_point   = '.';
char       Money::group_separator = ',';
char       Money::unit_name[]     = "dollar";
char       Money::cent_name[]     = "cent";
MoneyIType Money::scale           = 100;        //  Cents
//%SPACE 4
//double     Money::dummy;                                
double Money::round(const double x)            //  Static internal function
 {double dummy;                                //    to round and truncate
  return modf(x + (x&lt;0 ? -.5 : .5),&amp;dummy), dummy;
 }
//%EJECT
//  Output display (stream insertion) operator
//  ------------------------------------------

//  This version displays a Money object in the form:

//   -  leading minus sign, if negative
//   -  floating prefix currency symbol (if symbol_pfx = 1)
//   -  whole amount in groups of three digits separated by punctuation
//   -  decimal point
//   -  2-digit (or more when needed) decimal fraction

 ostream&amp; operator&lt;&lt; (ostream&amp; ls, MONEY rs)
 {Money absx = rs &gt; 0 ? rs : - rs;      //  Get magnitude of argument
  double whole = absx.MoneyInt();       //  Isolate whole monetary units
  short  cents = absx.MoneyCents();     //  Isolate fractional units
  Money  remdr = absx - Money((whole * 100 + cents) / 100);

  if  (rs &lt; 0) ls &lt;&lt; '-';               //  Print prefix minus, if needed
  ls &lt;&lt; Money::pfx_symbol;              //  Insert dollar sign

//  Print groups of 3 digits separated by punctuation
//  -------------------------------------------------

  const float group_divisors[6] = {1E0f, 1E3f, 1E6f, 1E9f, 1E12f, 1E15f};
  short  grpNum = (whole == 0) ? 0 : short(log10(whole) / 3);
  int    grpVal =  int(whole / group_divisors[grpNum]);

  ls &lt;&lt; grpVal;                // Print leftmost 3-digits (no leading 0's)
  while (grpNum != 0)          // For remaining 3-digit groups
   {ls &lt;&lt; rs.group_separator;                     // Print group separator
    whole -= grpVal * group_divisors[grpNum--];   // Compute new remainder
    grpVal  = int(whole / group_divisors[grpNum]);// Get next 3-digit value
       
    if   (grpVal &lt; 100) ls  &lt;&lt; '0';               // Insert embedded 0's
    if   (grpVal &lt; 10)  ls  &lt;&lt; '0';               //   as needed
    ls &lt;&lt; grpVal;}                                // Print 3-digit value

//  Print cents portion
//  -------------------

  ls &lt;&lt;  rs.decimal_point              //  Append decimal point
     &lt;&lt; (cents &lt; 10 ? "0" : "")        //  Append leading 0 if needed
     &lt;&lt;  cents;                        //  Append cents value

//  Append any additional fractional digits
//  ---------------------------------------

  for (int i = int(Money::scale/100 -1); i&amp;&amp;(remdr&gt;0); i--, remdr/=10)
       ls &lt;&lt; (10 * remdr).MoneyCents();
  ls &lt;&lt; Money::sfx_symbol;             //    Insert trailing currency symbol

  return ls;}                          //    Allow nested stream operations
//</iostream.h></pre></body></html>