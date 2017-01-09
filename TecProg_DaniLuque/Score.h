#pragma once

#include <string>
#include <map>
#include <exception>			//Management of exceptions
#include <iostream>				//Management of cin and cout
#include <stdlib.h>				//Management of random numbers: srand, rand 
#include <cstdlib>				//Management of system functions such as pause
#include <fstream>				//Management of files

/*
* This class represent a person with the following data: age, sex and name
*/
class Score {
	int _score;
	char _name[100];

	
public:
	//Default constructor
	Score();
	//Overload constructor
	Score(Score & p);
	//Copy constructor
	Score(std::string name, int score);
	//Destructor
	~Score();

	//Get and Set methods for getting and setting the attribute values
	int getScore();
	void setScore(int age);
	std::string getName();
	void setName(std::string name);

	//In and output methods
	void printScore();
	void askPersonName();

};


