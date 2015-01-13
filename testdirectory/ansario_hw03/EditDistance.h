/****************************************************************
 * Header file for the application class for the edit distance
 * program.
 *
 * Author/copyright:  Duncan Buell edited by Omar A. Ansari
 * Date: 11 July 2014 modified 9 September 2014
 *
**/

#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <iostream>
#include <vector>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#define COSTINSERTION 1
#define COSTSUBSTITUTION 2
#define DUMMYDISTANCE -1
#define DUMMYSTRING "XX"

class EditDistance
{
public:
  EditDistance();
  virtual ~EditDistance();

  void computeDistances();
  void initialize(Scanner& scanner);
  string toString();

private:
  //int length; I did not use this variable. 
    
  vector<vector<int> > dist;

  vector<string> sentence1;
  vector<string> sentence2;

};

#endif
