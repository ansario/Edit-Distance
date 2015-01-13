#include "EditDistance.h"

 /******************************************************************************
 *
 * Class 'EditDistance' for the computation of exactly how dissimilar two lines containing strings are.
 *
 * Author: Omar A. Ansari
 * Created: 20 September 2014
 * Modified: 25 September 2014
 * Copyright Omar Ansari 2014. All rights reserved.
**/

/******************************************************************************
 * Constructor
**/
EditDistance::EditDistance()
{
}

/******************************************************************************
 * Destructor
**/
EditDistance::~EditDistance()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'computeDistances'.
 * This function computes the dissimilarity between two lines of string. The string at the ith position of sentence1 is compared
 * to the jth position of sentence2. If the two strings are the same, the value placed in the dist vecotor at the intersection of sentence1 and sentence2 in the matrix
 * is equivilant to the position at i-1, j. If they are different, a check is done to find the minumum value either above, to the left, or diagonally to the left to determine what the next dist value will be.  
 *
**/
void EditDistance::computeDistances()
{

	int column = sentence1.size(); //Initialize variables. Column indicates the "column" position in a standard 2x2 matrix.
	int row = sentence2.size(); //Row indicates the "row" position in a standard 2x2 matrix.
	int min = 0;
	
	dist.resize(column);//Resize the dist vector to allocate just enough memory for the 2x2 matrix. 

	for (int i = 0; i < column; i++){
		dist[i].resize(row);
	}

	for (int i = 0; i < column; i++){ //Begin computation here. Using a 2 dimensional array, each string in sentence1 is compared against the coresponding string in sentence2. A decsion is made based on the parameters mentioned above.
			
		for (int j = 0; j < row; j++){
			
			if (i == 0){ //First bounds checker. This checks if i == 0 to ensure that we do not move out of bounds of the dist vector.

				if (sentence1[j] == sentence2[i]){//Check if equal.
					
					dist[i][j] = 0;//Add value to vector.

				} else if (sentence1[j] != sentence2[i]){
					
					dist[i][j] = (dist[i][j-1] + COSTINSERTION);//Add value to vector.


				} else if (j == 0){ //Second bounds checker. This checks if j == 0 to ensure that we do not move out of bounds of the dist vector.

					dist[i][j] = (dist[i-1][j] + COSTINSERTION); //Add value to vector.

				}
			
			}
			
			if (j == 0 && i != 0){ ////Third bounds checker. This checks if j == 0 && i != 0 to ensure that we do not move out of bounds of the dist vector.
					
					dist[i][j] = (dist[i-1][j] + COSTINSERTION);//Add value to vector.

			}
			
			if (i != 0 && j != 0){ //Fourth and final bounds checker. This checks if i != 0 && j !=0 to ensure that we do not move out of bounds of the dist vector.
				
				min = 10000; //When checking which position (left, up, or diagonal left) is the minimum, we are comparing them to a hardcoded int value of 10000. I do not anticipate needing a higher value for this assignment. It's not necessary to waste memory on a greater integer.
				
				if (sentence1[j] == sentence2[i]){ //Check if equal.
					
					if (dist[i-1][j] < min){ //Check above.
						
						min = dist[i-1][j];

					} 
					if (dist[i][j-1] < min) { //Check left.

						min = dist[i][j-1];

					}
					if (dist[i-1][j-1] < min) { //Check diagonal left.

						min = dist[i-1][j-1];

					}

				dist[i][j] = min;//Add value to vector.

			}

				if (sentence1[j] != sentence2[i]){ //Check if not equal.
					
					if (dist[i-1][j] < min){ //Check above.
						
						min = dist[i-1][j] + COSTINSERTION;

					} 
					
					if (dist[i][j-1] < min) {//Check left.
						
						min = dist[i][j-1] + COSTINSERTION;

					}
					
					if (dist[i-1][j-1] < min) {//Check diagonal left.
						
						min = dist[i-1][j-1] + COSTSUBSTITUTION;

					}

				dist[i][j] = min;//Add value to vector.

				
				}

			}

		}

	}

}

/******************************************************************************
 * Function 'initialize'.
 *
 * Parameters:
 *   scanner - object of type 'Scanner' passed by referece.  
**/
void EditDistance::initialize(Scanner& scanner)
{

	string one = "DUMMY_STRING_ONE"; //Initialize variables.
	string two = "DUMMY_STRING_TWO";

	sentence1.push_back(DUMMYSTRING); //Add a padding to the begnnning of each sentence vector.
	sentence2.push_back(DUMMYSTRING);

	ScanLine scanLine1; //Create two objects of type ScanLine.
	ScanLine scanLine2;
	
	while (scanner.hasNext()){ //Get the lines of data in the Scanner into strings.
		
		one = scanner.nextLine();
		two = scanner.nextLine();

	}

	scanLine1.openString(one); //Open the strings in the ScanLine objects. This allows us to parse each word as a token.
	scanLine2.openString(two);

	while (scanLine1.hasNext()){  //Add tokens from sentence1 into the sentence1 vector.
		
		sentence1.push_back(scanLine1.next());
	
	}

	while (scanLine2.hasNext()){   //Add tokens from sentence2 into the sentence2 vector.

		sentence2.push_back(scanLine2.next());
		
	}

	
	while (sentence1.size() != sentence2.size()){ //Add additional padding at the end of the vectors in case one is short than the other.
		
		if (sentence1.size() > sentence2.size()){
			
			sentence2.push_back(DUMMYSTRING);

		} else if (sentence1.size() < sentence2.size()){
			
			sentence1.push_back(DUMMYSTRING);

		} else {
			
			break;

		}
	}

}

/******************************************************************************
 * Function 'toStringTheData'.
 * This function simply dumps the 'vector' of sentence1, sentence2, and dist to a 'string' and returns it.
**/
string EditDistance::toString()
{
	string s = "";

	s+= "Sentence One: \n";  
	
	for (unsigned int a = 0; a < sentence1.size(); a++){ //Print out sentence1.
		s+= sentence1[a] + " | ";
	}
	
	s+= "\n";

	s+= "Sentence Two: \n";
	for (unsigned int b = 0; b < sentence2.size(); b++){ //Print out sentence2.
		s+= sentence2[b] + " | ";
	}
	
	s+= "\n"; 

	s+= "Distance Matrix: \n"; 

	s+="\n";
	s+="		";


	for (unsigned int i = 0; i < sentence1.size(); i++){  //Print sentence1 at the top of the matrix.
	
	s +=  Utils::Format(sentence1[i]) + "	";

	}

	s+="\n";


	for (unsigned int i = 0; i < sentence1.size(); i++){ //Print value of sentence2 at ith position and then print row of values from dist.
		
			s += sentence2[i] + "		";	

		for (unsigned int j = 0; j < sentence2.size(); j++){

			s+= Utils::Format(dist[i][j]) + "	";

		}
		
		s+="\n";
	}

	return s;
}
